from ROOT import *
import threading
import sys
from os import path,system,getcwd,listdir,mkdir,remove,chdir
from optparse import OptionParser
from samplenames import samplenames
from array import array
import mergeFiles as merge

def getargs():
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
    return parser.parse_args()

class datamc(object):

    def __init__(self,command=None,show=True,lumi=None,fileDir="./"):

        self.cwd = getcwd()
        chdir(fileDir)
        self.fileDir = getcwd()
        if fileDir != "./":
            if path.isdir("PlotTool/"):
                sys.path[0] = "PlotTool/"
        import mcinfo as mc
        self.version = mc.version
        self.xsec = mc.xsec

        self.options,self.args = getargs()
        
        #Luminosity
        self.lumi_by_era = mc.lumi_by_era
        self.lumi = (mc.lumi if (lumi == None) else lumi)
        if (self.options.lumi != None): self.lumi = self.options.lumi

        self.show = show

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
        for i,region in enumerate(RegionName):
            if path.isfile(postRegionData[i]): self.region=region; break;
        if self.region == None:
            for i,region in enumerate(RegionName):
                if any(f for f in listdir('.output') if preRegionData[i] in f): self.region=region; break
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
        if self.show:
            print "Running in "+self.region+":"
            print "Plotting at",self.lumi,"pb^{-1}"
        self.HaddFiles()
        if (self.options.allHisto):
            self.GetAllHisto()
        if getcwd() != self.cwd: chdir(self.cwd)
    ###############################################################################################################

    def HaddFiles(self):
        if getcwd() != self.fileDir: chdir(self.fileDir)
        def validfile(fname): return path.isfile(fname)
        mcfiles = [ mcfname for mcfname in self.xsec if not validfile(mcfname+'.root') ]
        datafiles = []
        if self.region != 'SignalRegion': datafiles = [ self.Data_FileNames[self.region]+"_"+str(i)
                                                        for i,e in enumerate(sorted(self.lumi_by_era.keys()))
                                                        if not path.isfile("DataEra/"+self.Data_FileNames[self.region]+"_"+e+".root")
                                                        and any(self.Data_FileNames[self.region]+"_"+str(i) in file for file in listdir(".output"))]
        if not any(datafiles):
            if not validfile(self.Data_FileNames[self.region]+'.root'): datafiles = self.Data_FileNames[self.region]
        ##########
        if self.signal != None: mcfiles += [ self.Mx_Mv[mx][mv] for mv in sorted(self.Mx_Mv[mx],key=int) for mx in sorted(self.Mx_Mv,key=int) if not validfile(self.Mx_Mv[mx][mv]+'.root') ]
        merge.HaddFiles(datafiles,mcfiles,eramap=self.lumi_by_era)
        if getcwd() != self.cwd: chdir(self.cwd)
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

    def GetAllHisto(self):
        if (self.region == "SignalRegion"): basic = "8"
        else: basic = "10"
        rfile=TFile.Open(self.Data_FileNames[self.region]+".root")
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

    def GetPlot(self,fname,variable):
        rfile=TFile.Open(fname)
        cutflow = self.GetCutflow(fname,rfile=rfile)
        if '<' in variable or '>' in variable:
            if '>' in variable: cut = '>'+variable.split('>')[-1]
            if '<' in variable: cut = '<'+variable.split('<')[-1]
            variable = variable.replace(cut,'')
            hs = self.GetBranch(fname,variable,rfile=rfile,cut=cut)
        else:
            hs = self.GetBranch(fname,variable,rfile=rfile)
        return hs,cutflow
    ###############################################################################################################
    
    def GetCutflow(self,fname,rfile=None):
        if rfile == None: rfile=TFile.Open(fname)
        rfile.cd()
        cutflow=rfile.Get("h_cutflow").Clone();cutflow.SetDirectory(0)
        return cutflow
    ###############################################################################################################

    def GetHisto(self,fname,variable,rfile=None):
        if rfile == None: rfile=TFile.Open(fname)
        rfile.cd()
        if any( variable == key.GetName() for key in rfile.GetListOfKeys() ):
            hs = rfile.Get(variable).Clone("temp"); hs.SetDirectory(0)
        else:
            nhist = variable.split("_")[-1]
            rdir = "ZprimeJet_"+nhist+"/"
            rfile.cd(rdir)
            keys = [keylist.GetName() for keylist in gDirectory.GetListOfKeys()]
            if variable in keys:hs=rfile.Get(rdir+variable).Clone("temp");hs.SetDirectory(0)
            else:               hs=None
        return hs
    ###############################################################################################################

    def GetBranch(self,fname,variable,rfile=None,hs=None,cut=''):
        if rfile == None: rfile=TFile.Open(fname)
        if hs == None: hs = self.GetHisto(fname,variable,rfile=rfile)
        rfile.cd()
        nhist = variable.split("_")[-1]
        rdir = "ZprimeJet_"+nhist+"/"
        rfile.cd(rdir)
        if not any( True for key in gDirectory.GetListOfKeys() if "tree" == key.GetName() ): return hs
        tree = rfile.Get(rdir+"tree")
        variable = variable.replace("_"+nhist,"")
        if any( True for key in tree.GetListOfBranches() if variable == key.GetName() ):
            hs.SetDirectory(gDirectory)
            hs.Reset()
            if cut == '': tree.Draw(variable+">>temp","weight","goff")
            else:         tree.Draw(variable+">>temp","weight*(%s%s)" % (variable,cut),"goff")
            hs.SetDirectory(0)
        return hs 
    ###############################################################################################################
                      
    def GetVariable(self,variable):
        if getcwd() != self.fileDir: chdir(self.fileDir)
        self.histo = {}
        self.total = {}

        self.GetVariableName(variable)

        hs,cutflow = self.GetPlot(self.Data_FileNames[self.region]+".root",variable)
        self.histo['Data'] = hs

        if self.signal != None:
            for signal in self.signal:
                mx = signal.split("_")[0].replace("Mx","")
                mv = signal.split("_")[1].replace("Mv","")
                hs,cutflow = self.GetPlot(self.Mx_Mv[mx][mv]+".root",variable)
                self.histo[signal]=hs
                self.total[signal] = cutflow.GetBinContent(1)
            if not 'Signal' in self.SampleList:self.SampleList.append('Signal')

        for sample in self.MC_FileNames:
            # print sample
            self.histo[sample]=[]
            self.total[sample]=[]
            for fn in self.MC_FileNames[sample]:
                # print '\t',fn
                if not path.isfile(fn+".root"): continue
                hs,cutflow = self.GetPlot(fn+".root",variable)
                hs.SetName(variable+"_"+fn)
                self.histo[sample].append(hs)
                self.total[sample].append(cutflow.GetBinContent(1))
        
        if (self.name == 'Xaxis Title'):
            for sample in self.histo:
                if type(self.histo[sample]) == TH1:
                    self.name = self.histo[sample].GetXaxis().GetTitle()
        if getcwd() != self.cwd: chdir(self.cwd)
    ###############################################################################################################

    def ScaleHistogram(self):
        self.BkgIntegral = 0
        for sample in self.SampleList:
            if sample == 'Data':
                if self.histo[sample] == None: continue
                integral=(self.histo[sample].Integral())
                space=" "*(15-len(sample))
                if self.show:print "integral of "+sample+space+" here:"+"%.6g" % integral
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
                    if self.show:print "integral of "+signal+space+" here:"+"%.6g" % integral
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

        if self.show:
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
    ########################################################################################################################################

    def setUnc(self,up,dn):
        if getcwd() != self.fileDir: chdir(self.fileDir)
        self.unc = {}
        for sample in self.MC_FileNames:
            self.unc[sample]={'up':{},'dn':{}}
            unc_key = ['up','dn']
            for i,varlist in enumerate((up,dn)):
                if varlist == None: continue
                for variable in varlist:
                    self.unc[sample][unc_key[i]][variable] = []
                    for j,fn in enumerate(self.MC_FileNames[sample]):
                        if not path.isfile(fn+".root"): continue
                        rfile=TFile.Open(fn+".root")
                        keys = [keylist.GetName() for keylist in gDirectory.GetListOfKeys()]
                        if variable in keys:hs=rfile.Get(variable).Clone();hs.SetDirectory(0)
                        else:print "Could not find "+variable+" In "+fn+".root, Exiting...";exit()
                        hs.SetName(variable+"_"+fn)
                        self.unc[sample][unc_key[i]][variable].append(hs)

                    for j,hs in enumerate(self.unc[sample][unc_key[i]][variable]):
                        if self.MC_FileNames[sample] == "null":continue
                        #Scaling = (1/TotalEvents)*Luminosity*NNLO-cross-section
                        # print self.MC_FileNames[sample][i],self.total[sample][i],xsec[self.MC_FileNames[sample][i]]
                        if (self.total[sample][j] == 0): scale = 0
                        else:                            scale=(1./self.total[sample][j])*self.lumi*self.xsec[self.MC_FileNames[sample][j]]
                        hs.Scale(scale)
                    if any(self.unc[sample][unc_key[i]][variable]):
                        for j in range(1,len(self.unc[sample][unc_key[i]][variable])): self.unc[sample][unc_key[i]][variable][0].Add(self.unc[sample][unc_key[i]][variable][j])
                        self.unc[sample][unc_key[i]][variable]=self.unc[sample][unc_key[i]][variable][0]
                        self.unc[sample][unc_key[i]][variable].SetName(self.unc[sample][unc_key[i]][variable].GetName().replace(self.MC_FileNames[sample][0],sample))
                    # if self.MC_Integral[sample] != 0:
                    #     print unc_key[i],sample,'\t|',
                    #     print (self.unc[sample][unc_key[i]][variable].Integral()/self.MC_Integral[sample])
        if getcwd() != self.cwd: chdir(self.cwd)
    ########################################################################################################################################

    def getUnc(self):
        hs_bkg = self.getSumOfBkg()
        xbins = hs_bkg.GetNbinsX()
        hs_up = hs_bkg.Clone(); hs_dn = hs_bkg.Clone()
        for ibin in range(1,xbins+1):
            content_up = []; content_dn = [];
            for sample in self.unc:
                bin_bk = self.histo[sample].GetBinContent(ibin)
                for u in self.unc[sample]:
                    for variable in self.unc[sample][u]:
                        bin_un = self.unc[sample][u][variable].GetBinContent(ibin)
                        if bin_un > bin_bk: content_up.append(bin_un - bin_bk)
                        else:               content_dn.append(bin_bk - bin_un)
            bin_up = sum(bin**2 for bin in content_up)**0.5
            bin_dn = sum(bin**2 for bin in content_dn)**0.5
            bin_bk = hs_bkg.GetBinContent(ibin)
            hs_up.SetBinContent(ibin,bin_bk + bin_up)
            hs_dn.SetBinContent(ibin,bin_bk - bin_dn)
        return hs_up,hs_dn
    ########################################################################################################################################

    def getStackUnc(self):
        hs_up = []; hs_dn = []
        for i in range(len(self.unc['WJets']['up'])):
            var_up = self.unc['WJets']['up'].keys()[i]
            var_dn = self.unc['WJets']['dn'].keys()[i]
            hs_up.append(THStack())
            hs_dn.append(THStack())
            for sample in self.unc:
                sample_up = self.unc[sample]['up'][var_up].Clone()
                sample_up.SetLineColor(kBlue)
                sample_dn = self.unc[sample]['dn'][var_dn].Clone()
                sample_dn.SetLineColor(kRed)
                hs_up[i].Add(sample_up)
                hs_dn[i].Add(sample_dn)
        return hs_up,hs_dn
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
