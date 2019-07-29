from ROOT import *
import threading
import sys
from os import path,system,getcwd,listdir,mkdir,remove
from optparse import OptionParser
from samplenames import samplenames

class datamc(object):

    def __init__(self,command=None,show=1,lumi=None,fileDir="./"):

        if fileDir != "./":
            if path.isdir(fileDir+"PlotTool/"):
                sys.path[0] = fileDir+"PlotTool/"
        import mcinfo as mc
        self.version = mc.version
        self.xsec = mc.xsec
        
        parser = OptionParser()
        parser.add_option("-r","--reset",help="removes all post files from currently directory and rehadds them from the .output directory",action="store_true", default=False)
        parser.add_option("--nohadd",help="does not try to hadd files together",action="store_true",default=False)
        parser.add_option("--thn",help="specifies that all following plots are TH2 or TH3 plots",action="store_true", default=False)
        parser.add_option("-l","--lumi",help="set the luminosity for scaling",action="store",type="float",dest="lumi")
        parser.add_option("-a","--allHisto",help="plot all 1D histograms in the post root files",action="store_true",default=False)
        parser.add_option("--single",help="hadd files using a single thread, instead of multiple",action="store_true",default=False)
        parser.add_option("-n","--normalize",help="normalize plots to 1",action="store_true",default=False)
        parser.add_option("-s","--signal",help="specify the signal file to use",action="store",type="str",default=None,dest="signal")
        parser.add_option("--sub",help="specify a sub directory to place output",action="store",type="str",default=None,dest="sub")
        (options, args) = parser.parse_args()

        self.options = options

        self.args = args

        #Luminosity
        self.lumi_by_era = mc.lumi_by_era
        self.lumi = (mc.lumi if (lumi == None) else lumi)
        if (options.lumi != None): self.lumi = options.lumi

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
        
        self.MC_FileNames = {"WJets":mc.WJets_FileNames,"ZJets":mc.ZJets_FileNames,"GJets":mc.GJets_FileNames,"DYJets":mc.DYJets_FileNames,"TTJets":mc.TTJets_FileNames,"DiBoson":mc.DiBoson_FileNames,"QCD":mc.QCD_FileNames};
        self.MC_Color =     {"WJets":kRed-10        ,"ZJets":kAzure+10      ,"GJets":kGray+2        ,"DYJets":kTeal-9         ,"TTJets":kOrange-2       ,"DiBoson":kCyan-10         ,"QCD":kGray};
        self.MC_Integral = {"WJets":0     ,"ZJets":0     ,"GJets":0    ,"DYJets":0    ,"TTJets":0     ,"DiBoson":0    ,"QCD":0};
        self.BkgIntegral = 0

        self.SampleList = ["Data","WJets","ZJets","GJets","DYJets","TTJets","DiBoson","QCD"]

        preRegionData = ["postMETdata","postSingleEle","postSingleMu","postDoubleEle_","postDoubleMu"]
        postRegionData =["postMETdata.root","postSingleEle.root","postSingleMu.root","postDoubleEle.root","postDoubleMu.root"] 
        RegionName = ["SignalRegion","SingleEle","SingleMu","DoubleEle","DoubleMu"]

        self.region=None
        for i in range(len(RegionName)):
            if any(f for f in listdir('.output') if preRegionData[i] in f) or path.isfile(postRegionData[i]): self.region=RegionName[i]
        if self.region==None:print "No Region Data Files Found, Exiting...";exit()
        if (type(self.lumi) == dict):
            self.lumi = self.lumi[self.region]
            self.lumi_by_era = self.lumi_by_era[self.region]
        
        if self.region == "SignalRegion" and self.options.signal != None:
            self.getSignalXsec()
            if self.options.signal == "-1":
                self.signal = []
                mxList = self.Mx_Mv.keys();mxList.sort(key=int);
                for mx in mxList:
                    mvList = self.Mx_Mv[mx].keys();mvList.sort(key=int)
                    for mv in mvList:
                        self.signal.append("Mx"+mx+"_Mv"+mv)
            elif "Mx" in self.options.signal and "_Mv" in self.options.signal: self.signal = [self.options.signal];
        if self.show == 1:
            print "Running in "+self.region+":"
            print "Plotting at",self.lumi,"pb^{-1}"
        self.HaddFiles()
        if (self.options.allHisto):
            self.GetAllHisto()
    ###############################################################################################################
            
    def initiate(self,variable):
        self.GetVariable(variable)
        self.ScaleHistogram()
    ###############################################################################################################
        
    def getSumOfBkg(self):
        sumOfBkg = self.histo["WJets"].Clone()
        for mc in self.MC_Color:
            if (mc != "WJets"):
                sumOfBkg.Add(self.histo[mc])
        return sumOfBkg
    ###############################################################################################################

    def getSignalXsec(self,scale=1):
        from monoZprime_XS import signalxsec
        for data in signalxsec:
            fn="post"+data
            xsec=signalxsec[data]
            mx=data.split("_")[0].replace("Mx","")
            mv=data.split("_")[1].replace("Mv","")
            if not mx in self.Mx_Mv:self.Mx_Mv[mx]={};self.Mx_Mv_Xsec[mx]={}
            self.Mx_Mv[mx][mv]=fn; self.Mx_Mv_Xsec[mx][mv]=xsec*scale;
    ###############################################################################################################
        
    def HaddFiles(self):
        AllFiles=[]
        for mcSample in self.xsec: AllFiles.append(mcSample)
        dataFiles = [ self.Data_FileNames[self.region]+"_"+str(i)
                      for i,e in enumerate(sorted(self.lumi_by_era.keys()))
                      if not path.isfile("DataEra/"+self.Data_FileNames[self.region]+"_"+e+".root")
                      and any(self.Data_FileNames[self.region]+"_"+str(i) in file for file in listdir(".output"))]
        AllFiles.extend(dataFiles)
        if self.signal != None:
            Mx_Value=self.Mx_Mv.keys();Mx_Value.sort(key=int)
            for mx in Mx_Value:
                Mv_Value=self.Mx_Mv[mx].keys();Mv_Value.sort(key=int)
                for mv in Mv_Value:
                    AllFiles.append(self.Mx_Mv[mx][mv])
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
            if len(threads) != 0: print
            nthreads = len(threads)
            merging = True if nthreads != 0 else False
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
            if merging: print "\nFiles Merged"
        ###################################
        def mergeData(dataFiles):
            arg = "hadd "+self.Data_FileNames[self.region]+".root "
            if not path.isdir("DataEra/"): mkdir("DataEra/")
            for i,e in enumerate(sorted(self.lumi_by_era.keys())):
                if self.Data_FileNames[self.region]+"_"+str(i)+".root" in listdir("."):
                    system("mv "+self.Data_FileNames[self.region]+"_"+str(i)+".root DataEra/"+self.Data_FileNames[self.region]+"_"+e+".root")
                if self.Data_FileNames[self.region]+"_"+e+".root" in listdir("DataEra"):
                    arg += "DataEra/"+self.Data_FileNames[self.region]+"_"+e+".root "
            arg += " >/dev/null"
            if path.isfile(self.Data_FileNames[self.region]+".root"): return
            print "Merging Data"
            system(arg)
        ###################################
        if (self.options.single): singleThread(AllFiles)
        else:multiThread(AllFiles)
        mergeData(dataFiles)
    ###############################################################################################################

    def GetAllHisto(self):
        if (self.region == "SignalRegion"): basic = "8"
        else: basic = "10"
        rfile=TFile.Open(self.fileDir+self.Data_FileNames[self.region]+".root")
        self.args = []
        for key in gDirectory.GetListOfKeys():
            nhisto = key.GetName().split("_")[-1]
            if (type(rfile.Get(key.GetName())) == TH1F or type(rfile.Get(key.GetName())) == TH1D) and (not nhisto.isdigit() or nhisto == basic):
                self.args.append(key.GetName())
    ###############################################################################################################

    def GetVariableName(self,variable):
        self.name = 'Xaxis Title'
        for title in samplenames:
            if title in variable:
                self.name = samplenames[title];
            key = variable.split("_")[-2]
            if key == title:
                self.name = samplenames[title];
                break
    ###############################################################################################################

    def GetHisto(self,fname,variable):
        rfile=TFile.Open(self.fileDir+fname)
        keys = [keylist.GetName() for keylist in gDirectory.GetListOfKeys()]
        if variable in keys:hs=rfile.Get(variable).Clone();hs.SetDirectory(0)
        else:               hs=None
        cutflow=rfile.Get("h_cutflow").Clone();cutflow.SetDirectory(0)
        return hs,cutflow
    ###############################################################################################################
                      
    def GetVariable(self,variable):
        self.histo = {}
        self.total = {}

        self.GetVariableName(variable)

        hs,cutflow = self.GetHisto(self.Data_FileNames[self.region]+".root",variable)
        self.histo['Data'] = hs

        if self.signal != None:
            for signal in self.signal:
                mx = signal.split("_")[0].replace("Mx","")
                mv = signal.split("_")[1].replace("Mv","")
                hs,cutflow = self.GetHisto(self.Mx_Mv[mx][mv]+".root",variable)
                self.histo[signal]=hs
                self.total[signal] = cutflow.GetBinContent(1)
            if not 'Signal' in self.SampleList:self.SampleList.append('Signal')

        for sample in self.MC_FileNames:
            # print sample
            self.histo[sample]=[]
            self.total[sample]=[]
            for fn in self.MC_FileNames[sample]:
                # print '\t',fn
                if not path.isfile(self.fileDir+fn+".root"): continue
                hs,cutflow = self.GetHisto(fn+".root",variable)
                hs.SetName(variable+"_"+fn)
                self.histo[sample].append(hs)
                self.total[sample].append(cutflow.GetBinContent(1))
        
        if (self.name == 'Xaxis Title'):
            for sample in self.histo:
                if type(self.histo[sample]) == TH1:
                    self.name = self.histo[sample].GetXaxis().GetTitle()
    ###############################################################################################################

    def ScaleHistogram(self):
        self.BkgIntegral = 0
        for sample in self.SampleList:
            if sample == 'Data':
                if self.histo[sample] == None: continue
                integral=(self.histo[sample].Integral())
                space=" "*(15-len(sample))
                if self.show == 1:print "integral of "+sample+space+" here:"+"%.6g" % integral
            elif sample == 'Signal':
                for signal in self.signal:
                    if self.histo[signal] == None: continue
                    mx = signal.split("_")[0].replace("Mx","")
                    mv = signal.split("_")[1].replace("Mv","")
                    #Scaling = (1/TotalEvents)*Luminosity*NNLO-cross-section
                    scale=(1./self.total[signal])*self.lumi*self.Mx_Mv_Xsec[mx][mv] 
                    self.histo[signal].Scale(scale)
                    integral=(self.histo[signal].Integral())
                    space=" "*(15-len(signal))
                    if self.show == 1:print "integral of "+signal+space+" here:"+"%.6g" % integral
            else:
                # print sample,'raw','total','xsec','lumi','scaled'
                if self.histo[sample] == None: continue
                rawevents = 0
                for i in range(len(self.histo[sample])):
                    if self.MC_FileNames[sample] == "null":continue
                    #Scaling = (1/TotalEvents)*Luminosity*NNLO-cross-section
                    rawevents = self.histo[sample][i].Integral()
                    if (self.total[sample][i] == 0): scale = 0
                    else:                            scale=(1./self.total[sample][i])*self.lumi*self.xsec[self.MC_FileNames[sample][i]]
                    self.histo[sample][i].Scale(scale)
                    # print self.MC_FileNames[sample][i],rawevents,self.total[sample][i],self.xsec[self.MC_FileNames[sample][i]],self.lumi,self.histo[sample][i].Integral()
                if (len(self.histo[sample]) > 0):
                    for i in range(1,len(self.histo[sample])): self.histo[sample][0].Add(self.histo[sample][i])
                    self.histo[sample]=self.histo[sample][0]
                    self.histo[sample].SetName(self.histo[sample].GetName().replace(self.MC_FileNames[sample][0],sample))
                    integral=(self.histo[sample].Integral())
                    # print 'summed',integral
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
