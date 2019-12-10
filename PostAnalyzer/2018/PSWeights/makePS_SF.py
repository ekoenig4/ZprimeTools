import os
from ROOT import *
import sys
sys.path.append('PlotTool')
from PlotTool import *
from config import *

gROOT.SetBatch(1)

# HaddFiles([],ZJets_FileNames+WJets_FileNames+DYJets_FileNames)

output = TFile("PSW_SF.root","RECREATE")
def MakeWeightedAvg(process,sf,psw):
    sf_avg = TH1F("%s_%s" % (process.name,psw),";ChNemPtFrac;%s" % psw,40,0,1.05)
    xbins = sf.GetNbinsX(); ybins = sf.GetNbinsY()
    avgdev = 0
    for xbin in range(1,xbins+1):
        avg = 0; nevents = 0
        for ybin in range(1,ybins+1):
            avg += sf.GetBinContent(xbin,ybin) * sf.GetYaxis().GetBinCenter(ybin)
            nevents += sf.GetBinContent(xbin,ybin)
        if nevents == 0: avg = 0
        else: avg /= nevents
        sf_avg.SetBinContent(xbin,avg)
        if avg != 0: avgdev = max( avgdev,abs(1-avg) )

    sf_avg.Draw('hist')
    sf_avg.SetMinimum(1-1.2*avgdev); sf_avg.SetMaximum(1+1.2*avgdev)
    outdir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/PSWeights/%s/weighted" % process.name
    if not os.path.isdir(outdir): os.mkdir(outdir)
    fname = "%s_%s.png" % (process.name,psw)
    # gPad.SaveAs('%s/%s' % (outdir,fname))
    process.output.cd()
    sf_avg.Write()

def SetSubSF(subprocess,psw):
    subprocess.sf = TH2F("%s_%s" % (subprocess.name,psw),";ChNemPtFrac;PS Weight",40,0,1.05,40,0,8) 
    subprocess.tree.Draw('%s:ChNemPtFrac>>%s_%s' % (psw,subprocess.name,psw))
    nentries = subprocess.tree.GetEntries()
    subprocess.sf.Scale(subprocess.xsec * float(nentries) / subprocess.cutflow)
def MakePSW(process,psw):
    print psw
    if not process.isOpen: process.initVariable()
    sf = None
    for subprocess in process:
        if subprocess.tree is None:
            print 'Openning tree %s' % subprocess.name
            subprocess.tree = subprocess.tfile.Get('trees/norm');
        SetSubSF(subprocess,psw);
        if sf is None: sf = subprocess.sf.Clone('%s_%s' % (process.name,psw))
        else:          sf.Add(subprocess.sf)
    # sf.Draw("COLZ")
    # outdir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/PSWeights/%s/full" % process.name
    # if not os.path.isdir(outdir): os.mkdir(outdir)
    # fname = "%s_%s.png" % (process.name,psw)
    # gPad.SaveAs('%s/%s' % (outdir,fname))
    MakeWeightedAvg(process,sf,psw)
def MakeSF(process):
    print process.name
    pswlist = [ "isrRed",   
		"fsrRed",      
		"isrDef",    
		"fsrDef",  
		"isrCon",
		"fsrCon",      
		"fsr_G2GG_muR",
		"fsr_G2QQ_muR",
		"fsr_Q2QG_muR",
		"fsr_X2XG_muR",
		"fsr_G2GG_cNS",
		"fsr_G2QQ_cNS",
		"fsr_Q2QG_cNS",
		"fsr_X2XG_cNS",
		"isr_G2GG_muR",
		"isr_G2QQ_muR",
		"isr_Q2QG_muR",
		"isr_X2XG_muR",
		"isr_G2GG_cNS",
		"isr_G2QQ_cNS",
		"isr_Q2QG_cNS",
		"isr_X2XG_cNS"]
    process.output = output.mkdir(process.name)
    for psw in pswlist:
        for variation in ('Up','Down'): MakePSW(process,'PSW_%s%s' % (psw,variation))
    process.output.Close()
    
processes = {
    "ZJets": Process("ZJets", ZJets_FileNames, GetMCxsec(ZJets_FileNames, xsec),'bkg'),
    "WJets": Process("WJets", WJets_FileNames, GetMCxsec(WJets_FileNames, xsec),'bkg'),
    "DYJets":Process("DYJets",DYJets_FileNames,GetMCxsec(DYJets_FileNames,xsec),'bkg')
}

# MakeSF(processes['ZJets'])
for process in processes: MakeSF(processes[process])
