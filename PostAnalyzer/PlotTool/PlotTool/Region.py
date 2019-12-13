from ROOT import *
import sys
import os
import mergeFiles as merge
from Parser import parser
from Process import Process
from Nuisance import Nuisance
from utilities import *
from samplenames import samplenames
from changeBinning import b_info

DataFileMap = {
    "SignalRegion":"postMETdata",
    "SingleEleCR":"postSingleEle",
    "SingleMuCR":"postSingleMu",
    "DoubleEleCR":"postDoubleEle",
    "DoubleMuCR":"postDoubleMu"
}

parser.add_argument("-r","--reset",help="removes all post files from currently directory and rehadds them from the .output directory",action="store_true", default=False)
parser.add_argument("-l","--lumi",help="set the luminosity for scaling",action="store",type=float,dest="lumi")
parser.add_argument("-a","--allHisto",help="plot all 1D histograms in the post root files",action="store_true",default=False)
parser.add_argument("-s","--signal",help="specify the signal file to use",action="store",type=str,default=None,dest="signal")
parser.add_argument("-b","--binning",help="specify function for rebinning histogram",action="store",type=str,default=None)
parser.add_argument("--nhists",help="Plot all 1D plots at nhists level",type=int)
parser.add_argument("--mc-solid",help="Make MC solid color",action="store_true",default=False)
parser.add_argument("-d","--directory",help="Specify directory to get post files from",type=valid_directory)
parser.add_argument("-c","--cut",help="Specify cut on branch variable using TTree string",type=lambda arg:str(arg).replace('"','').replace("'",""),default=None)

class Region(object):
    def __init__(self,year=None,region=None,lumi=None,path=None,show=True):
        self.args = parser.parse_args()
        self.year = year; self.region = region; self.lumi = lumi; self.path = path; self.show = show
        self.cwd = os.getcwd()
        if self.path is None: self.path = self.cwd
        elif self.args.directory is not None:
            print "Using %s to get files" % self.args.directory
            os.chdir(self.args.directory); self.path = os.getcwd()
        else: os.chdir(self.path); self.path = os.getcwd();
        
        import config
        if self.year is None: self.year = config.version
        self.xsec = config.xsec

        if self.region is None: self.region = GetRegion()
        self.lumimap = config.lumi_by_era[self.region]
        if self.lumi is None: self.lumi = config.lumi[self.region]
        if self.args.lumi is not None: self.lumi = self.args.lumi

        self.MCList = config.mclist
        self.SampleList = ["Data"] + self.MCList

        self.processes = {}
        datafile = DataFileMap[self.region]
        self.processes["Data"] =    Process("Data",[ '%s_%s' % (datafile,era) for era in sorted(self.lumimap.keys()) ],None,'data',year=self.year,region=self.region)
        for mc in config.mclist:
            self.processes[mc] = Process(mc,config.filemap[mc],GetMCxsec(config.filemap[mc],config.xsec),'bkg',lumi=self.lumi,leg=config.legmap[mc],color=config.colmap[mc],year=self.year,region=self.region)

        if self.region == "SignalRegion" and self.args.signal != None:
            self.setSignalInfo()
        if self.show:
            print "Running in "+self.region+":"
            print "Plotting at",self.lumi,"pb^{-1}"
        self.haddFiles()
        if os.getcwd() != self.cwd: os.chdir(self.cwd)
    def __len__(self): return len(self.processes)
    def __getitem__(self,i):
        if type(i) == str: key = i
        if type(i) == int: key = self.SampleList[i];
        return self.processes[key]
    def __iter__(self):
        for i in range(len(self)): yield self[i]
    def __contains__(self,procname): return procname in self.processes
    def haddFiles(self):
        if os.getcwd() != self.path: os.chdir(self.path)
        if not os.path.isdir('.output/'): return
        def validfile(fname): return os.path.isfile(fname)
        filelist = []
        for process in self: filelist += [ filename for filename in process.filenames if not validfile(filename+'.root') ]
        merge.HaddFiles([],filelist)
        if os.getcwd() != self.cwd: os.chdir(self.cwd)
    def setSignalInfo(self,scale=1):
        from monoZprime_XS import centralxsec as signalxsec
        self.signal = self.args.signal
        self.SampleList.insert(1,'Signal')
        filelist = []
        xsecmap = {}
        for data in signalxsec:
            fn="post"+data
            xsec=signalxsec[data]
            filelist.append(fn)
            xsecmap[fn] = scale*xsec
        if self.args.signal == '-1':
            self.processes['Signal'] = Process('Signal',filelist,xsecmap,'signal',lumi=self.lumi,year=self.year,region=self.region)
        elif IsSignal(self.args.signal):
            signal = self.args.signal
            fname = 'post'+signal
            xsecmap = {fname:xsecmap[fname]}
            self.processes['Signal'] = Process('Signal',[fname],xsecmap,'signal',lumi=self.lumi,year=self.year,region=self.region)
    def initVariable(self,variable=None):
        b_info.initVariable()
        Nuisance.unclist = []
        self.bkgIntegral = 0
        if 'SumOfBkg' in self.processes:
            tmp = self.processes.pop('SumOfBkg')
            del tmp
        if variable is not None:
            self.setXaxisTitle(variable)
            self.varname = variable
            self.cut = self.args.cut
            self.setBinning(variable,self.cut)
    def initiate(self,variable):
        if os.getcwd() != self.path: os.chdir(self.path)
        self.initVariable(variable)
        for process in self:
            process.setVariable(variable,b_info.template,b_info.cut)
            self.scaleWidth = process.scaleWidth
        if self.show: self.output()
        if os.getcwd() != self.cwd: os.chdir(self.cwd)
    def output(self):
        if self.scaleWidth: print "Bin Width Normalization"
        prompt = 'integral of %s: %s'
        ntemp = '{0:<15}'; itemp = '{0:<8}'
        print prompt % ( ntemp.format('Data'),itemp.format( '%.6g' % self.processes['Data'].scaled_total ) )
        if 'Signal' in self.processes:
            process = self.processes['Signal']
            for signal in process:
                print prompt % ( ntemp.format(signal.process),itemp.format( '%.6g' % signal.scaled_total ) )
        BkgIntegral = sum( process.scaled_total for name,process in self.processes.iteritems() if process.proctype == 'bkg' )
        for sample in sorted(self.MCList,key=lambda sample: self.processes[sample].scaled_total,reverse=True):
            process = self.processes[sample]
            percent = ("%.4g%%" % (100*process.scaled_total/BkgIntegral)) if BkgIntegral != 0 else 'Nan'
            print prompt % ( ntemp.format(sample),itemp.format( '%.6g' % process.scaled_total ) ),'| %s' % (percent)
        ratio = ('%.6g' % (self.processes['Data'].scaled_total/BkgIntegral)) if BkgIntegral != 0 else 'Nan'
        print '            %s: %s' % (ntemp.format('data/mc'),itemp.format(ratio))
    def setSumOfBkg(self):
        sumofbkg = Process('SumOfBkg',[],{},'sumofbkg',year=self.year,region=self.region)
        for process in self:
            if process.proctype == 'bkg': sumofbkg.add(process)
        self.processes['SumOfBkg'] = sumofbkg
        for nuisance in sumofbkg.nuisances: print sumofbkg.nuisances[nuisance]
    def setXaxisTitle(self,variable):
        self.name = 'Xaxis Title'
        for title in samplenames:
            if title in variable:
                self.name = samplenames[title];
            key = variable.split("_")[-2]
            if key == title:
                self.name = samplenames[title];
                break
    def setBinning(self,variable,cut):
        _,ndir = GetDirname(variable)
        b_variable = variable.replace('_%s' % ndir,'')
        b_info.cut = cut
        if cut is not None:
            cutvar = cut.replace('>','?').replace('<','?').split('?')[0]
            if cutvar in variable: self.varname = self.varname.replace('_%s' % ndir,'%s_%s' % (cut.replace(cutvar,'').replace('<','-').replace('>','+'),ndir))
            else: self.varname = self.varname.replace('_%s' % ndir,'_%s_%s' % (cut.replace('<','-').replace('>','+'),ndir))
        if self.args.binning == None: return
        for label,binning in b_info.binninglist.iteritems():
            if label in self.args.binning:
                self.varname += self.args.binning
                binning(self.args.binning,self,b_variable) 
    def addUnc(self,nuisance):
        for process in self: process.addUnc(nuisance)
    def fullUnc(self,unclist=None,stat=None):
        if unclist is None: unclist = self.nuisances.keys()
        if not stat and 'Stat' in unclist: unclist.remove('Stat')
        elif stat and 'Stat' not in unclist: unclist.append('Stat')
        self.unclist = unclist
        for process in self: process.fullUnc(unclist,stat)
        self.setSumOfBkg()
    def getUncBand(self,unclist=None):
        if not hasattr(self,'unclist'): self.fullUnc(unclist,True)
        elif sorted(unclist) != sorted(self.unclist): self.fullUnc(unclist,True)
        data = self['Data'].histo
        up,dn = self['SumOfBkg'].nuisances['Total'].GetHistos()
        rup = GetRatio(data,up); rdn = GetRatio(data,dn)
        uncband = GetUncBand(rup,rdn,norm=1)
        return uncband
    def __add__(self,other):
        # if self.variable != other.variable: raise ValueError("%s is not %s" % (self.variable,other.variable))
        from copy import deepcopy
        new = deepcopy(self)
        samplelist = new.processes.keys()
        for sample in other.processes.keys():
            if sample not in samplelist: samplelist.append(sample)
        for sample in samplelist:
            if sample in new.processes and sample in other.processes:
                new.processes[sample].add(other.processes[sample])
            if sample not in new.processes and sample in other.processes:
                new.processes[sample] = deepcopy(other.processes)
        return new
