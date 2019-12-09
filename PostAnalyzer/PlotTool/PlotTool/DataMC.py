from ROOT import *
import sys
import os
from Parser import parser
from samplenames import samplenames
from array import array
import mergeFiles as merge
from changeBinning import binninglist
from Process import Process,Nuisance
from utilities import *

parser.add_argument("-r","--reset",help="removes all post files from currently directory and rehadds them from the .output directory",action="store_true", default=False)
parser.add_argument("--nohadd",help="does not try to hadd files together",action="store_true",default=False)
parser.add_argument("-l","--lumi",help="set the luminosity for scaling",action="store",type=float,dest="lumi")
parser.add_argument("-a","--allHisto",help="plot all 1D histograms in the post root files",action="store_true",default=False)
parser.add_argument("--single",help="hadd files using a single thread, instead of multiple",action="store_true",default=False)
parser.add_argument("-s","--signal",help="specify the signal file to use",action="store",type=str,default=None,dest="signal")
parser.add_argument("-b","--binning",help="specify function for rebinning histogram",action="store",type=str,default=None)
parser.add_argument("--mc-solid",help="Make MC solid color",action="store_true",default=False)
parser.add_argument("--nhists",help="Plot all 1D plots at nhists level",type=int)
parser.add_argument("-d","--directory",help="Specify directory to get post files from",type=valid_directory)

class datamc(object):

    def __init__(self,command=None,show=True,lumi=None,fileDir="./"):

        self.args = parser.parse_args()
        self.cwd = os.getcwd()
        if fileDir != './': os.chdir(fileDir)
        self.fileDir = os.getcwd()
        if self.args.directory is not None:
            print 'Using %s to get files' % self.args.directory
            self.fileDir = self.args.directory
            os.chdir(self.fileDir)
        import config
        self.version = config.version
        self.xsec = config.xsec

        self.variable = None
        self.varname = None
        self.cut = ''
        
        #Luminosity
        self.lumi_by_era = config.lumi_by_era
        self.lumi = (config.lumi if (lumi == None) else lumi)
        if (self.args.lumi != None): self.lumi = self.args.lumi

        self.show = show

        self.name = 'Xaxis Title'
        
        #List of Signal Files and Xsec
        
        self.Mx_Mv_Files = []
        self.Mx_Mv_Xsec = {}
        self.signal=None
        self.processes = {}
        self.nuisances = {}

        self.region = GetRegion()
        if (type(self.lumi) == dict):
            self.lumi = self.lumi[self.region]
            self.lumi_by_era = self.lumi_by_era[self.region]
        
        #List of Region Data Files
        SignalData_FileNames = "postMETdata";
        SingleEleData_FileNames = "postSingleEle";
        SingleMuData_FileNames = "postSingleMu";
        DoubleEleData_FileNames = "postDoubleEle";
        DoubleMuData_FileNames = "postDoubleMu";

        self.Data_FileNames = {"SignalRegion":SignalData_FileNames,"SingleEleCR":SingleEleData_FileNames,"SingleMuCR":SingleMuData_FileNames,"DoubleEleCR":DoubleEleData_FileNames,"DoubleMuCR":DoubleMuData_FileNames}
        
        self.Data_FileName = self.Data_FileNames[self.region]
        #List of Sample Files
        self.SampleList = ["Data","WJets","ZJets","GJets","DYJets","TTJets","DiBoson","QCD"]
        self.MCList = ["WJets","ZJets","GJets","DYJets","TTJets","DiBoson","QCD"]

        self.processes["Data"] =    Process("Data",  [self.Data_FileName],None                                 ,  'data')
        self.processes["WJets"] =   Process("WJets",  config.WJets_FileNames,  GetMCxsec(config.WJets_FileNames,config.xsec),  'bkg',leg="W#rightarrowl#nu",  lumi=self.lumi,color=kRed-10)
        self.processes["ZJets"] =   Process("ZJets",  config.ZJets_FileNames,  GetMCxsec(config.ZJets_FileNames,config.xsec),  'bkg',leg="Z#rightarrow#nu#nu",lumi=self.lumi,color=kAzure+10)
        self.processes["GJets"] =   Process("GJets",  config.GJets_FileNames,  GetMCxsec(config.GJets_FileNames,config.xsec),  'bkg',leg="#gamma+jets",       lumi=self.lumi,color=kGray+2)
        self.processes["DYJets"] =  Process("DYJets", config.DYJets_FileNames, GetMCxsec(config.DYJets_FileNames,config.xsec), 'bkg',leg="Z#rightarrow ll",   lumi=self.lumi,color=kTeal-9)
        self.processes["TTJets"] =  Process("TTJets", config.TTJets_FileNames, GetMCxsec(config.TTJets_FileNames,config.xsec), 'bkg',leg="Top Quark",         lumi=self.lumi,color=kOrange-2)
        self.processes["DiBoson"] = Process("DiBoson",config.DiBoson_FileNames,GetMCxsec(config.DiBoson_FileNames,config.xsec),'bkg',leg="WW/WZ/ZZ",          lumi=self.lumi,color=kCyan-10)
        self.processes["QCD"] =     Process("QCD",    config.QCD_FileNames,    GetMCxsec(config.QCD_FileNames,config.xsec),    'bkg',leg="QCD",               lumi=self.lumi,color=kGray)

        if self.region in config.region_masks:
            to_remove = [ sample for sample in self.MCList if sample not in config.region_masks[self.region] ]
            for sample in to_remove:
                self.SampleList.remove(sample)
                self.MCList.remove(sample)
                self.processes.pop(sample)

        if self.args.mc_solid:
            for name,process in self.processes.iteritems():
                if process.proctype == 'bkg':
                    process.color = 17
            
        if self.region == "SignalRegion" and self.args.signal != None:
            self.signal = self.args.signal
            self.getSignalInfo()
            self.SampleList.insert(1,'Signal')
            if self.args.signal == '-1':
                self.processes['Signal'] = Process('Signal',self.Mx_Mv_Files,self.Mx_Mv_Xsec,'signal',lumi=self.lumi)
            elif IsSignal(self.args.signal):
                signal = self.args.signal
                self.processes['Signal'] = Process(signal,['post'+signal],{'post'+signal:self.Mx_Mv_Xsec['post'+signal]},'signal',lumi=self.lumi)
        if self.show:
            print "Running in "+self.region+":"
            print "Plotting at",self.lumi,"pb^{-1}"
        self.HaddFiles()
        if (self.args.allHisto):
            self.getAllHisto()
        if (self.args.nhists != None):
            self.getAllNHisto()
        if os.getcwd() != self.cwd: os.chdir(self.cwd)
    ###############################################################################################################

    def HaddFiles(self):
        if self.args.nohadd: return
        if os.getcwd() != self.fileDir: os.chdir(self.fileDir)
        if not os.path.isdir('.output/'): return
        def validfile(fname): return os.path.isfile(fname)
        mcfiles = [ mcfname for mcfname in sorted(self.xsec.keys()) if not validfile(mcfname+'.root') ]
        
        eralist = sorted(self.lumi_by_era.keys())
        datafiles_v1 = [ '%s_%s' % (self.Data_FileName,era) for era in eralist if not validfile('%s_%s.root' % (self.Data_FileName,era)) ]
        datafiles_v2 = [ '%s_%i' % (self.Data_FileName,i) for i,era in enumerate(eralist) if not validfile('%s_%s.root' % (self.Data_FileName,era)) ]
        datafiles = datafiles_v1 + datafiles_v2
        ##########
        if self.signal != None:
            for fname in self.Mx_Mv_Files:
                if not validfile(fname+'.root'):
                    mcfiles.append(fname)
        ##########
        merge.HaddFiles(datafiles,mcfiles,eralist=eralist)
        if os.getcwd() != self.cwd: os.chdir(self.cwd)
    ###############################################################################################################

    def output(self):
        prompt = 'integral of %s: %s'
        ntemp = '{0:<15}'; itemp = '{0:<8}'
        print prompt % ( ntemp.format('Data'),itemp.format( '%.6g' % self.processes['Data'].raw_total ) )
        if 'Signal' in self.processes:
            process = self.processes['Signal']
            for signal in process:
                print prompt % ( ntemp.format(signal.name),itemp.format( '%.6g' % signal.scaled_total ) )
        for sample in sorted(self.MCList,key=lambda sample: self.processes[sample].scaled_total,reverse=True):
            process = self.processes[sample]
            percent = ("%.4g%%" % (100*process.scaled_total/self.BkgIntegral)) if self.BkgIntegral != 0 else 'Nan'
            print prompt % ( ntemp.format(sample),itemp.format( '%.6g' % process.scaled_total ) ),'| %s' % (percent)
        ratio = ('%.6g' % (self.processes['Data'].raw_total/self.BkgIntegral)) if self.BkgIntegral != 0 else 'Nan'
        print '            %s: %s' % (ntemp.format('data/mc'),itemp.format(ratio))
    ###############################################################################################################

    def getBinning(self):
        if self.args.binning == None: return None
        for label,binning in binninglist.iteritems():
            if label in self.args.binning:
                self.varname += self.args.binning
                return binning(self.args.binning,self,'%s_%s' % (self.region,self.variable)) 
        return None
    ###############################################################################################################
            
    def initiate(self,variable):
        if os.getcwd() != self.fileDir: os.chdir(self.fileDir)
        self.cut = ''; self.nuisances = {}
        if '>' in variable: self.cut = '>'+variable.split('>')[-1]
        if '<' in variable: self.cut = '<'+variable.split('<')[-1]
        self.varname = variable.replace('>','+').replace('<','-')
        self.variable = variable.replace(self.cut,'')
        self.getVariableName(variable)
        b_template = self.getBinning()
        for sample in self.SampleList:
            process = self.processes[sample]
            process.getVariable(self.variable,b_template,self.cut)
            for nuisance in process.nuisances: self.nuisances[nuisance] = False
        self.BkgIntegral = sum( process.scaled_total for name,process in self.processes.iteritems() if process.proctype == 'bkg' )
        if self.show: self.output()
        if self.name == 'Xaxis Title':
            self.name = next( process.histo.GetXaxis().GetTitle() for name,process in self.processes.iteritems() if process.histo != None )
        if os.getcwd() != self.cwd: os.chdir(self.cwd)
    ###############################################################################################################
        
    def getSumOfBkg(self):
        sumOfBkg = None
        for name,process in self.processes.iteritems():
            if process.proctype != 'bkg': continue
            if sumOfBkg is None: sumOfBkg = process.histo.Clone('SumOfBkg')
            else:                sumOfBkg.Add(process.histo)
        self.sumOfBkg = sumOfBkg
        return self.sumOfBkg
    ###############################################################################################################

    def getSignalInfo(self,scale=1):
        from monoZprime_XS import centralxsec as signalxsec
        for data in signalxsec:
            fn="post"+data
            xsec=signalxsec[data]
            self.Mx_Mv_Files.append(fn)
            self.Mx_Mv_Xsec[fn] = scale*xsec
    ###############################################################################################################

    def getAllHisto(self):
        return
        if (self.region == "SignalRegion"): basic = "8"
        else: basic = "10"
        rfile=TFile.Open(self.Data_FileName+".root")
        self.args = []
        for key in gDirectory.GetListOfKeys():
            nhisto = key.GetName().split("_")[-1]
            if (type(rfile.Get(key.GetName())) == TH1F or type(rfile.Get(key.GetName())) == TH1D) and (not nhisto.isdigit() or nhisto == basic):
                self.args.append(key.GetName())
    ###############################################################################################################
    
    def getAllNHisto(self):
        rfile=TFile.Open(self.Data_FileName+".root")
        self.args.argv = []
        tdir = rfile.Get('ZprimeJet_%i' % self.args.nhists)
        if tdir != None:
            for key in tdir.GetListOfKeys():
                keyname = key.GetName()
                obj = tdir.Get(keyname)
                if type(obj) == TH1F and ('_%i' % self.args.nhists) in keyname:
                    self.args.argv.append(keyname)
    ###############################################################################################################

    def getVariableName(self,variable):
        self.name = 'Xaxis Title'
        for title in samplenames:
            if title in variable:
                self.name = samplenames[title];
            key = variable.split("_")[-2]
            if key == title:
                self.name = samplenames[title];
                break
    ###############################################################################################################

    def addUnc(self,nuisance,show=None):
        if show is None: show = self.show
        self.nuisances[nuisance] = True
        if show: print nuisance
        for name,process in self.processes.iteritems():
            if process.proctype == 'data': continue
            process.addUnc(nuisance,show=show)
    ###############################################################################################################

    def removeUnc(self,nuisance):
        if nuisance not in self.nuisances: return
        self.nuisances[nuisance] = False
        for name,process in self.processes.iteritems():
            if process.proctype == 'data': continue
            process.removeUnc(nuisance)
    ###############################################################################################################

    def fullUnc(self,unclist=None,stat=True,show=None):
        if unclist is None: unclist = self.nuisances.keys()
        for name,process in self.processes.iteritems():
            for unc in unclist:
                if unc not in process.nuisances: process.addUnc(unc)
            process.fullUnc(stat=stat)
        norm = self.getSumOfBkg()
        up = norm.Clone('TotalUp'); dn = norm.Clone('TotalDown'); up.Reset(); dn.Reset()
        nbins = norm.GetNbinsX()
        for ibin in range(1,nbins+1):
            up[ibin] = sum( process.nuisances['Total'].up[ibin]**2 for _,process in self.processes.iteritems() if process.proctype == 'bkg' )
            dn[ibin] = sum( process.nuisances['Total'].dn[ibin]**2 for _,process in self.processes.iteritems() if process.proctype == 'bkg' )
            if stat:
                staterr = sum( process.histo.GetBinError(ibin) for _,process in self.processes.iteritems() if process.proctype == 'bkg' )
                up[ibin] += staterr; dn[ibin] += staterr
            up[ibin] = TMath.Sqrt(up[ibin])
            dn[ibin] = TMath.Sqrt(dn[ibin])
        self.nuisances['Total'] = Nuisance('Total',up,dn)
    ###############################################################################################################

    def getUncBand(self):
        if 'Total' not in self.nuisances: self.fullUnc(stat=True,show=False)
        data = self.processes['Data'].histo
        bkgUp,bkgDn = self.nuisances['Total'].GetHistos(self.sumOfBkg)
        ratio_up = GetRatio(data,bkgUp)
        ratio_dn = GetRatio(data,bkgDn)
        uncband = GetUncBand(ratio_up,ratio_dn,norm=1)
        return uncband
    ###############################################################################################################
    
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
######################################################################    
