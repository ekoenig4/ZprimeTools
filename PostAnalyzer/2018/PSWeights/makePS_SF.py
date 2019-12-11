import os
from ROOT import *
import sys
sys.path.append('PlotTool')
from PlotTool import *
from config import *

gROOT.SetBatch(1)

# HaddFiles([],ZJets_FileNames+WJets_FileNames+DYJets_FileNames)

output = TFile("PSW_SF.root","RECREATE")
pswlist = [ "isrRed","fsrRed","isrDef","fsrDef","isrCon","fsrCon",      
	    "fsr_G2GG_muR","fsr_G2QQ_muR","fsr_Q2QG_muR","fsr_X2XG_muR",
	    "fsr_G2GG_cNS","fsr_G2QQ_cNS","fsr_Q2QG_cNS","fsr_X2XG_cNS",
	    "isr_G2GG_muR","isr_G2QQ_muR","isr_Q2QG_muR","isr_X2XG_muR",
	    "isr_G2GG_cNS","isr_G2QQ_cNS","isr_Q2QG_cNS","isr_X2XG_cNS"]
# pswlist = ["fsrDef"]

def MakeSubSF(subprocess):
    print subprocess.name
    subprocess.norm = subprocess.tfile.Get("norm")
    subprocess.pswmap = { }
    subprocess.scale = subprocess.xsec/float(subprocess.cutflow)
    subprocess.norm.Scale(subprocess.scale)
    for psw in pswlist:
        for var in ("Up","Down"):
            subprocess.pswmap[psw+var] = subprocess.tfile.Get(psw+var)
            subprocess.pswmap[psw+var].Scale(subprocess.scale)
def MakeSF(process):
    print process.name
    process.initVariable()
    for subprocess in process: MakeSubSF(subprocess)
    process.pswmap = {}
    process.norm = None
    for subprocess in process:
        if process.norm is None: process.norm = subprocess.norm.Clone(process.name)
        else:                    process.norm.Add(subprocess.norm)
    for psw in pswlist:
        for var in ("Up","Down"):
            for subprocess in process:
                if psw+var not in process.pswmap: process.pswmap[psw+var] = subprocess.pswmap[psw+var].Clone("PSW_%s%s" % (psw,var))
                else:                             process.pswmap[psw+var].Add(subprocess.pswmap[psw+var])
            process.pswmap[psw+var].Divide(process.norm)

    output.cd()
    process.output = output.mkdir(process.name)
    process.output.cd()
    for psw in pswlist:
        for var in ("Up","Down"):
            process.pswmap[psw+var].Write()
    process.output.Close()
    
processes = {
    "ZJets": Process("ZJets", ZJets_FileNames, GetMCxsec(ZJets_FileNames, xsec),'bkg'),
    "WJets": Process("WJets", WJets_FileNames, GetMCxsec(WJets_FileNames, xsec),'bkg'),
    "DYJets":Process("DYJets",DYJets_FileNames,GetMCxsec(DYJets_FileNames,xsec),'bkg')
}

# MakeSF(processes['ZJets'])
for process in processes: MakeSF(processes[process])
