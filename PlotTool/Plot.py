from ROOT import *
import threading
import sys
from os import path,system,getcwd,listdir
from optparse import OptionParser
from samplenames import samplenames
from cross_section import xsec

signal_Xsec_file="PlotTool/monoZprime_XS-2016-correctPDF.txt"
# signal_Xsec_file="/nfs_scratch/ekoenig4/MonoZprimeJet/CMSSW_8_0_26_patch1/src/ZprimeTools/monoZprime_XS-2016-defaultPDF.txt"

class datamc(object):

    def __init__(self,command=None,show=1,lumi=41453,fileDir="./"):
        self.version = "PlotTool 2017"
        
        parser = OptionParser()
        parser.add_option("-r","--reset",help="removes all post files from currently directory and rehadds them from the .output directory",action="store_true", default=False)
        parser.add_option("-n","--nohadd",help="does not try to hadd files together",action="store_true",default=False)
        parser.add_option("--thn",help="specifies that all following plots are TH2 or TH3 plots",action="store_true", default=False)
        parser.add_option("-l","--lumi",help="set the luminosity for scaling",action="store",type="float",dest="lumi")
        parser.add_option("-a","--allHisto",help="plot all 1D histograms in the post root files",action="store_true",default=False)
        parser.add_option("-s","--single",help="hadd files using a single thread, instead of multiple",action="store_true",default=False)
        (options, args) = parser.parse_args()

        self.options = options

        self.args = args

        #Luminosity
        self.lumi= (options.lumi if (options.lumi != None) else lumi)

        self.show = show

        self.fileDir = fileDir

        self.name = 'Xaxis Title'
        
        #List of Signal Files and Xsec

        self.Mx_Mv = {}
        self.Mx_Mv_Xsec = {}
        self.signal=None
        
        #List of Region Data Files
        SignalData_FileNames = "postMETdata";
        SingleEleData_FileNames = "postSingleEle";
        SingleMuData_FileNames = "postSingleMu";
        DoubleEleData_FileNames = "postDoubleEle";
        DoubleMuData_FileNames = "postDoubleMu";

        self.Data_FileNames = {"SignalRegion":SignalData_FileNames,"SingleEle":SingleEleData_FileNames,"SingleMu":SingleMuData_FileNames,"DoubleEle":DoubleEleData_FileNames,"DoubleMu":DoubleMuData_FileNames}
        
        #List of Sample Files
        WJets_FileNames = ["postW100to200","postW200to400","postW400to600","postW600to800","postW800to1200","postW1200to2500","postW2500toInf","postWJets_MLM"]
        
        ZJets_FileNames = ["postZ100to200","postZ200to400","postZ400to600","postZ600to800","postZ800to1200","postZ1200to2500","postZ2500toInf"];
        
        GJets_FileNames = ["postGJets40to100","postGJets100to200","postGJets200to400","postGJets400to600","postGJets600toInf"];
        
        DYJets_FileNames = ["postDY100to200","postDY200to400","postDY400to600","postDY600to800","postDY800to1200","postDY1200to2500","postDY2500toInf","postDY_MLM"]
        
        TTJets_FileNames = ["postTTJets_MLM"]#,"postTTJetsDiLept"];
        
        DiBoson_FileNames = ["postWW","postWWto4Q","postWWtoLNuQQ","postWZ","postZZ","postWWto2L2Nu"]#,"postWWto2L2NuPS"]
        
        QCD_FileNames = ["postQCD100to200","postQCD200to300","postQCD300to500","postQCD500to700","postQCD700to1000","postQCD1000to1500","postQCD1500to2000","postQCD2000toInf"];
        
        self.MC_FileNames = {"WJets":WJets_FileNames,"ZJets":ZJets_FileNames,"GJets":GJets_FileNames,"DYJets":DYJets_FileNames,"TTJets":TTJets_FileNames,"DiBoson":DiBoson_FileNames,"QCD":QCD_FileNames};
        self.MC_Color =     {"WJets":kRed-10        ,"ZJets":kAzure+10      ,"GJets":kGray+2        ,"DYJets":kTeal-9         ,"TTJets":kOrange-2       ,"DiBoson":kCyan-10         ,"QCD":kGray};
        self.MC_Integral = {"WJets":0     ,"ZJets":0     ,"GJets":0    ,"DYJets":0    ,"TTJets":0     ,"DiBoson":0    ,"QCD":0};
        self.BkgIntegral = 0

        self.SampleList = ["Data","WJets","ZJets","GJets","DYJets","TTJets","DiBoson","QCD"]

        preRegionData = [".output/postMETdata_0_0.root",".output/postSingleEle_0_0.root",".output/postSingleMu_0_0.root",".output/postDoubleEle_0_0.root",".output/postDoubleMu_0_0.root"]
        postRegionData =["postMETdata.root","postSingleEle.root","postSingleMu.root","postDoubleEle.root","postDoubleMu.root"] 
        RegionName = ["SignalRegion","SingleEle","SingleMu","DoubleEle","DoubleMu"]

        self.region=None
        for i in range(len(RegionName)):
            if path.isfile(preRegionData[i]) or path.isfile(postRegionData[i]): self.region=RegionName[i]
        if self.region==None:print "No Region Data Files Found, Exiting...";exit()
        
        if self.region == "SignalRegion" and len(args) > 0:
            self.getSignalXsec(signal_Xsec_file)
            if args[0] == "-1":
                args.pop(0)
                self.signal = []
                mxList = self.Mx_Mv.keys();mxList.sort(key=int);
                for mx in mxList:
                    mvList = self.Mx_Mv[mx].keys();mvList.sort(key=int)
                    for mv in mvList:
                        self.signal.append("Mx"+mx+"_Mv"+mv)
            elif "Mx" in args[0] and "_Mv" in args[0]: self.signal = [args[0]]; args.pop(0);
        if self.show == 1:
            print "Running in "+self.region+":"
            print "Plotting at",self.lumi,"pb^{-1}"
        self.HaddFiles()
        exit()
        if (self.options.allHisto):
            self.GetAllHisto()
        
    def initiate(self,variable):
        self.GetVariable(variable)
        self.ScaleHistogram()

    def getSumOfBkg(self):
        sumOfBkg = self.histo["WJets"].Clone()
        for mc in self.MC_Color:
            if (mc != "WJets"):
                sumOfBkg.Add(self.histo[mc])
        return sumOfBkg

    def getSignalXsec(self,xsecFile=signal_Xsec_file,scale=1):
        with open(xsecFile) as f:
            text = f.readlines()
            for line in text:
                if "MonoZPrime_V_Mx" in line:
                    line=line.replace("#","")
                    data=line.replace("MonoZPrime_V_","").split()
                    fn="post"+data[0]+"_"
                    xsec=float(line.split(":")[1].split()[0])
                    mx=data[0].split("_")[0].replace("Mx","")
                    mv=data[0].split("_")[1].replace("Mv","")
                    if not mx in self.Mx_Mv:self.Mx_Mv[mx]={};self.Mx_Mv_Xsec[mx]={}
                    self.Mx_Mv[mx][mv]=fn; self.Mx_Mv_Xsec[mx][mv]=xsec*scale;
        
    def HaddFiles(self):
        AllFiles=[]
        for mcSample in xsec: AllFiles.append(mcSample)
        AllFiles.append(self.Data_FileNames[self.region])
        if self.signal != None:
            Mx_Value=self.Mx_Mv.keys();Mx_Value.sort(key=int)
            for mx in Mx_Value:
                Mv_Value=self.Mx_Mv[mx].keys();Mv_Value.sort(key=int)
                for mv in Mv_Value:
                    AllFiles.append([self.Mx_Mv[mx][mv]])
        ##################################
        def singleThread(AllFiles):
            #Hadd files together
            for fn in AllFiles:
                if (not path.isfile(fn+".root") and path or self.options.reset) and not self.options.nohadd:
                    nfile = [f for f in listdir(".output/") if fn+"_" in f]
                    if len(nfile) != 0:
                        arg = "hadd -f "+self.fileDir+fn+".root "
                        for f in nfile:arg+=".output/"+f+" "
                        system(arg)
        ###################################
        def multiThread(AllFiles):
            class haddThread (threading.Thread):
                def __init__(self, threadID,name,arg):
                    threading.Thread.__init__(self)
                    self.threadID = threadID
                    self.name = name
                    self.arg = arg
                def run(self):
                    system(arg)
            #Hadd files together
            threads = {}
            for fn in AllFiles:
                if (not path.isfile(fn+".root") and path or self.options.reset) and not self.options.nohadd:
                    nfile = [f for f in listdir(".output/") if fn+"_" in f]
                    if len(nfile) != 0:
                        arg = "hadd -f "+self.fileDir+fn+".root "
                        for f in nfile:arg+=".output/"+f+" "
                        arg += " >/dev/null"
                        ID = str(len(threads))
                        threads[ID]=haddThread(ID,fn,arg)
                        threads[ID].start()
                        sys.stdout.write("\r"+str(len(threads))+" Started Threads")
                        sys.stdout.flush()
            print
            nthreads = len(threads)
            out = "\r"+str(nthreads)+" Threads Remaining"
            while (len(threads) != 0):
                IDlist = threads.keys(); IDlist.sort(key=int)
                for ID in IDlist:
                    if not threads[ID].isAlive():
                        threads.pop(ID)
                if len(threads) != nthreads:
                    nthreads = len(threads)
                    out = "\r"+str(nthreads)+" Threads Remaining"
                if out != None and len(threads) != 0:
                    sys.stdout.write(out)
                    sys.stdout.flush()
                    out = None
            print "\nFiles Merged"
        ###################################
        print "Hadding Files"
        if (self.options.single): singleThread(AllFiles)
        else:multiThread(AllFiles)
                        

    def GetAllHisto(self):
        if (self.region == "SignalRegion"): basic = "8"
        else: basic = "10"
        rfile=TFile.Open(self.fileDir+self.Data_FileNames[self.region]+".root")
        self.args = []
        for key in gDirectory.GetListOfKeys():
            nhisto = key.GetName().split("_")[-1]
            if (type(rfile.Get(key.GetName())) == TH1F or type(rfile.Get(key.GetName())) == TH1D) and (not nhisto.isdigit() or nhisto == basic):
                self.args.append(key.GetName())

    def GetVariableName(self,variable):
        self.name = 'Xaxis Title'
        for title in samplenames:
            if title in variable:
                self.name = samplenames[title];
            key = variable.split("_")[-2]
            if key == title:
                self.name = samplenames[title];
                break
                    
    def GetVariable(self,variable):
        self.histo = {}
        self.total = {}

        self.GetVariableName(variable)

        rfile=TFile.Open(self.fileDir+self.Data_FileNames[self.region]+".root")
        keys = [keylist.GetName() for keylist in gDirectory.GetListOfKeys()]
        if variable in keys:self.histo['Data']=rfile.Get(variable).Clone();self.histo['Data'].SetDirectory(0)
        else:print "Could not find "+variable+" In "+self.Data_FileNames[self.region]+".root, Exiting...";exit()

        if (self.name == 'Xaxis Title'):
            self.name = self.histo['Data'].GetXaxis().GetTitle()

        if self.signal != None:
            for signal in self.signal:
                mx = signal.split("_")[0].replace("Mx","")
                mv = signal.split("_")[1].replace("Mv","")
                rfile=TFile.Open(self.fileDir+self.Mx_Mv[mx][mv]+".root")
                keys = [keylist.GetName() for keylist in gDirectory.GetListOfKeys()]
                if variable in keys:hs=rfile.Get(variable).Clone();hs.SetDirectory(0)
                else:print "Could not find "+variable+" In "+self.Mx_Mv[mx][mv]+".root, Exiting...";exit()
                self.histo[signal]=hs
                cutflow=rfile.Get("h_cutflow")
                self.total[signal] = cutflow.GetBinContent(1)
            if not 'Signal' in self.SampleList:self.SampleList.append('Signal')

        for sample in self.MC_FileNames:
            self.histo[sample]=[]
            self.total[sample]=[]
            for fn in self.MC_FileNames[sample]:
                if not path.isfile(self.fileDir+fn+".root"): continue
                rfile=TFile.Open(self.fileDir+fn+".root")
                keys = [keylist.GetName() for keylist in gDirectory.GetListOfKeys()]
                if variable in keys:hs=rfile.Get(variable).Clone();hs.SetDirectory(0)
                else:print "Could not find "+variable+" In "+fn+".root, Exiting...";exit()
                hs.SetName(variable+"_"+fn)
                self.histo[sample].append(hs)
                cutflow=rfile.Get("h_cutflow")
                self.total[sample].append(cutflow.GetBinContent(1))

    def ScaleHistogram(self):
        self.BkgIntegral = 0
        for sample in self.SampleList:
            if sample == 'Data':
                integral=(self.histo[sample].Integral())
                space=" "*(15-len(sample))
                if self.show == 1:print "integral of "+sample+space+" here:"+"%.6g" % integral
            elif sample == 'Signal':
                for signal in self.signal:
                    mx = signal.split("_")[0].replace("Mx","")
                    mv = signal.split("_")[1].replace("Mv","")
                    #Scaling = (1/TotalEvents)*Luminosity*NNLO-cross-section
                    scale=(1./self.total[signal])*self.lumi*self.Mx_Mv_Xsec[mx][mv] 
                    self.histo[signal].Scale(scale)
                    integral=(self.histo[signal].Integral())
                    space=" "*(15-len(signal))
                    if self.show == 1:print "integral of "+signal+space+" here:"+"%.6g" % integral
            else:
                rawevents = 0
                for i in range(len(self.histo[sample])):
                    if self.MC_FileNames[sample] == "null":continue
                    #Scaling = (1/TotalEvents)*Luminosity*NNLO-cross-section
                    rawevents += self.histo[sample][i].Integral()
                    # print self.MC_FileNames[sample][i],self.total[sample][i],xsec[self.MC_FileNames[sample][i]]
                    scale=(1./self.total[sample][i])*self.lumi*xsec[self.MC_FileNames[sample][i]]
                    self.histo[sample][i].Scale(scale)
                if (len(self.histo[sample]) > 0):
                    for i in range(1,len(self.histo[sample])): self.histo[sample][0].Add(self.histo[sample][i])
                    self.histo[sample]=self.histo[sample][0]
                    self.histo[sample].SetName(self.histo[sample].GetName().replace(self.MC_FileNames[sample][0],sample))
                    integral=(self.histo[sample].Integral())
                    self.MC_Integral[sample]=integral
                    self.BkgIntegral += integral

        if self.show == 1:
            bkgInt = {}
            for sample in self.MC_Integral:bkgInt[str(self.MC_Integral[sample])]=sample
            keylist = bkgInt.keys();keylist.sort(key=float)
            for i in keylist[::-1]:
                sample = bkgInt[i]
                integral = self.MC_Integral[sample]
                percentage = 100*integral/self.BkgIntegral
                space1=" "*(15-len(sample))
                space2=" "*(8-len("%.6g" % integral))
                # print "integral of raw"+sample+space+" here:"+"%.6g" % rawevents
                print "integral of "+sample+space1+" here:"+"%.6g" % integral+space2+" | "+"%.4g" % percentage+"%"

######################################################################    

            
def GetRatio(hs_num,hs_den):
    nbins = hs_num.GetNbinsX();  
    Ratio = hs_num.Clone("Ratio");
    last = hs_den.Clone("last");
    for ibin in range(1,nbins+1):
        stackcontent = last.GetBinContent(ibin);
        stackerror = last.GetBinError(ibin);
        datacontent = hs_num.GetBinContent(ibin);
        dataerror = hs_num.GetBinError(ibin);
        # print "bin: "+str(ibin)+"stackcontent: "+str(stackcontent)+" and data content: "+str(datacontent)
        ratiocontent=0;
        if(datacontent!=0 and stackcontent != 0):ratiocontent = ( datacontent) / stackcontent
        error=0;
        if(datacontent!=0 and stackcontent != 0): error = ratiocontent*((dataerror/datacontent)**2 + (stackerror/stackcontent)**2)**(0.5)
        else: error = 2.07
        # print "bin: "+str(ibin)+" ratio content: "+str(ratiocontent)+" and error: "+str(error);
        Ratio.SetBinContent(ibin,ratiocontent);
        Ratio.SetBinError(ibin,error);
     
    return Ratio
