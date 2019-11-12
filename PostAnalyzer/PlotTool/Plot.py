from ROOT import *
import sys
import os
from Parser import PlotParser as parser
from samplenames import samplenames
from array import array
import mergeFiles as merge
import changeBinning as binning
from Process import Process

def valid_directory(directory):
    if not os.path.isdir(directory): raise ValueError("%s is not a valid directory" % directory)
    return directory

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

def GetRegion():
    region_pattern = ["postMETdata","postSingleEle","postSingleMu","postDoubleEle_","postDoubleMu"]
    RegionName = ["SignalRegion","SingleEleCR","SingleMuCR","DoubleEleCR","DoubleMuCR"]

    found = False
    for region,pattern in zip(RegionName,region_pattern):
        if os.path.isdir('.output/'):
            if any( pattern in fname for fname in os.listdir('.output/') ): found = True; break
        if any( pattern in fname for fname in os.listdir('.') ): found = True; break
    if not found: return None
    return region
def GetMCxsec(filenames,xsecMap):
    return { fname:xsecMap[fname] for fname in filenames }
def IsSignal(signal):
    return 'Mx' in signal and '_Mv' in signal
def FindConfig():
    wd,wf = os.path.split(__file__)
    def updirectory(path): path += '/../'; return path
    repo_path = os.path.realpath( updirectory(wd) )
    def helper(path):
        if any( directory == 'config' for directory in os.listdir(path) ): return path
        elif os.path.realpath(path) != repo_path: return helper( updirectory(path) )
    config_path = helper('.')
    if config_path == None: print 'year config directory was not found in current or parent directory'; exit(1)
    else: sys.path.append(config_path)

FindConfig()

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
        import mcinfo as mc
        self.version = mc.version
        self.xsec = mc.xsec

        self.variable = None
        self.varname = None
        
        #Luminosity
        self.lumi_by_era = mc.lumi_by_era
        self.lumi = (mc.lumi if (lumi == None) else lumi)
        if (self.args.lumi != None): self.lumi = self.args.lumi

        self.show = show

        self.name = 'Xaxis Title'
        
        #List of Signal Files and Xsec
        
        self.Mx_Mv_Files = []
        self.Mx_Mv_Xsec = {}
        self.signal=None
        self.processes = {}
        self.nuisances = []

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
        self.processes["WJets"] =   Process("WJets",  mc.WJets_FileNames,  GetMCxsec(mc.WJets_FileNames,mc.xsec),  'bkg',lumi=self.lumi,color=kRed-10)
        self.processes["ZJets"] =   Process("ZJets",  mc.ZJets_FileNames,  GetMCxsec(mc.ZJets_FileNames,mc.xsec),  'bkg',lumi=self.lumi,color=kAzure+10)
        self.processes["GJets"] =   Process("GJets",  mc.GJets_FileNames,  GetMCxsec(mc.GJets_FileNames,mc.xsec),  'bkg',lumi=self.lumi,color=kGray+2)
        self.processes["DYJets"] =  Process("DYJets", mc.DYJets_FileNames, GetMCxsec(mc.DYJets_FileNames,mc.xsec), 'bkg',lumi=self.lumi,color=kTeal-9)
        self.processes["TTJets"] =  Process("TTJets", mc.TTJets_FileNames, GetMCxsec(mc.TTJets_FileNames,mc.xsec), 'bkg',lumi=self.lumi,color=kOrange-2)
        self.processes["DiBoson"] = Process("DiBoson",mc.DiBoson_FileNames,GetMCxsec(mc.DiBoson_FileNames,mc.xsec),'bkg',lumi=self.lumi,color=kCyan-10)
        self.processes["QCD"] =     Process("QCD",    mc.QCD_FileNames,    GetMCxsec(mc.QCD_FileNames,mc.xsec),    'bkg',lumi=self.lumi,color=kGray)

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
            print prompt % ( ntemp.format(sample),itemp.format( '%.6g' % process.scaled_total ) ),'| %.4g%%' % (100*process.scaled_total/self.BkgIntegral)
        ratio = self.processes['Data'].raw_total/self.BkgIntegral
        print '            %s: %s' % (ntemp.format('data/mc'),itemp.format('%.6g' % ratio))
    ###############################################################################################################

    def getBinning(self):
        hs = None
        if self.args.binning == None: return None
        elif 'perc' in self.args.binning:
            nbins = self.args.binning.replace('perc','')
            hs = binning.percentBinning(nbins=int(nbins))
            if hs != None: self.varname += 'perc'+nbins
        elif 'incl'  in self.args.binning:
            nbins = self.args.binning.replace('incl','')
            hs = binning.inclusiveBinning(nbins=int(nbins))
            if hs != None: self.varname += 'incl'+nbins
        return hs
    ###############################################################################################################
            
    def initiate(self,variable):
        if os.getcwd() != self.fileDir: os.chdir(self.fileDir)
        self.cut = ''
        if '>' in variable: self.cut = '>'+variable.split('>')[-1]
        if '<' in variable: self.cut = '<'+variable.split('<')[-1]
        self.varname = variable.replace('>','+').replace('<','-')
        self.variable = variable.replace(self.cut,'')
        self.getVariableName(variable)
        b_template = self.getBinning()
        for sample in self.SampleList:
            process = self.processes[sample]
            process.getVariable(self.variable,b_template,self.cut)
            self.nuisances += [ nuisance for nuisance in process.nuisances if nuisance not in self.nuisances ]
        self.BkgIntegral = sum( process.scaled_total for name,process in self.processes.iteritems() if process.proctype == 'bkg' )
        if self.show: self.output()
        if self.name == 'Xaxis Title':
            self.name = next( process.histo.GetXaxis().GetTitle() for name,process in self.processes.iteritems() if process.histo != None )
        if os.getcwd() != self.cwd: os.chdir(self.cwd)
    ###############################################################################################################
        
    def getSumOfBkg(self):
        sumOfBkg = self.processes['WJets'].histo.Clone('sumOfBkg')
        sumOfBkg.Reset()
        for name,process in self.processes.iteritems():
            if process.proctype == 'bkg':
                sumOfBkg.Add(process.histo)
        return sumOfBkg
    ###############################################################################################################

    def getSignalInfo(self,scale=1):
        from monoZprime_XS import signalxsec
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

    def addUnc(self,nuisance):
        for name,process in self.processes.iteritems():
            if process.proctype == 'data': continue
            process.addUnc(nuisance)
    ###############################################################################################################

    def removeUnc(self,nuisance):
        if nuisance not in self.nuisances: return
        for name,process in self.processes.iteritems():
            if process.proctype == 'data': continue
            process.removeUnc(nuisance)
######################################################################    

            
def GetRatio(hs_num,hs_den):
    nbins = hs_num.GetNbinsX();  
    Ratio = hs_num.Clone("Ratio");
    last = hs_den.Clone("last");
    # for ibin in range(1,nbins+1):
    #     stackcontent = last.GetBinContent(ibin);
    #     stackerror = last.GetBinError(ibin);
    #     datacontent = hs_num.GetBinContent(ibin);
    #     dataerror = hs_num.GetBinError(ibin);
    #     # print "bin: "+str(ibin)+"stackcontent: "+str(stackcontent)+" and data content: "+str(datacontent)
    #     ratiocontent=0;
    #     if(datacontent!=0 and stackcontent != 0):ratiocontent = ( datacontent) / stackcontent
    #     error=0;
    #     if(datacontent!=0 and stackcontent != 0): error = ratiocontent*((dataerror/datacontent)**2 + (stackerror/stackcontent)**2)**(0.5)
    #     else: error = 2.07
    #     # print "bin: "+str(ibin)+" ratio content: "+str(ratiocontent)+" and error: "+str(error);
    #     Ratio.SetBinContent(ibin,ratiocontent);
    #     Ratio.SetBinError(ibin,error);
    Ratio.Divide(last)
    return Ratio
#######################################
def Get2DRatio(hs_num,hs_den):
    xbins = hs_num.GetNbinsX()
    ybins = hs_num.GetNbinsY()
    Ratio = hs_num.Clone("Ratio")
    last = hs_den.Clone("last")
    for xbin in range(1,xbins+1):
        for ybin in range(1,ybins+1):
            stackcontent = last.GetBinContent(xbin,ybin)
            stackerror = last.GetBinError(xbin,ybin)
            datacontent = hs_num.GetBinContent(xbin,ybin)
            dataerror = hs_num.GetBinError(xbin,ybin)
            ratiocontent = 0
            if(datacontent!=0 and stackcontent != 0):ratiocontent = ( datacontent) / stackcontent
            error=0;
            if(datacontent!=0 and stackcontent != 0): error = ratiocontent*((dataerror/datacontent)**2 + (stackerror/stackcontent)**2)**(0.5)
            else: error = 2.07
            Ratio.SetBinContent(xbin,ybin,ratiocontent)
            Ratio.SetBinError(xbin,ybin,error)
    return Ratio
########################################
def GetUncBand(up,dn):
    xbins = up.GetNbinsX()
    x = []; y = []; ex = []; ey = []
    nbins = 0
    for ibin in range(1,xbins+1):
        if up.GetBinContent(ibin) == 0 and dn.GetBinContent(ibin) == 0: continue
        x.append(up.GetBinCenter(ibin))
        ex.append(up.GetBinWidth(ibin)/2)
        y.append((up.GetBinContent(ibin)+dn.GetBinContent(ibin))/2)
        ey.append(abs(up.GetBinContent(ibin)-dn.GetBinContent(ibin))/2)
        nbins += 1
    return TGraphErrors(nbins,array('d',x),array('d',y),array('d',ex),array('d',ey))