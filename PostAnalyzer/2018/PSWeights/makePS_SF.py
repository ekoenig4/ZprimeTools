import os
from ROOT import *
import sys
sys.path.append('PlotTool')
from PlotTool import *
import config

gROOT.SetBatch(1)

HaddFiles(config.filemap['ZJets']+config.filemap['WJets']+config.filemap['DYJets'])
# exit()

output = TFile("PSW_SF.root","RECREATE")
pswlist = [ "isrRed","fsrRed","isrDef","fsrDef","isrCon","fsrCon",      
	    "fsr_G2GG_muR","fsr_G2QQ_muR","fsr_Q2QG_muR","fsr_X2XG_muR",
	    "fsr_G2GG_cNS","fsr_G2QQ_cNS","fsr_Q2QG_cNS","fsr_X2XG_cNS",
	    "isr_G2GG_muR","isr_G2QQ_muR","isr_Q2QG_muR","isr_X2XG_muR",
	    "isr_G2GG_cNS","isr_G2QQ_cNS","isr_Q2QG_cNS","isr_X2XG_cNS"]
# pswlist = [ "fsr%s" % psw for psw in ("Red","Def","Con") ]

template = TH1F("template","template",50,0,1.05)
line = TLine(0,1,1.05,1)
def DebugDraw(process):
    process.up.SetMarkerStyle(22); process.up.SetLineStyle(1)
    process.dn.SetMarkerStyle(23); process.dn.SetLineStyle(1)
    process.up.Draw("p hist"); process.dn.Draw("p hist same"); line.Draw("same")
    process.up.GetYaxis().SetRangeUser(0.5,1.5)
    raw_input()
def getVariable(process,variable,weight):
    def getSubVariable(subprocess,variable,weight):
        if not hasattr(subprocess,'tree'):
            subprocess.tree = subprocess.tfile.Get("trees/norm")
            subprocess.scaling = subprocess.xsec / subprocess.cutflow
        hsname = '%s_%s_%s' % (subprocess.name,variable,weight)
        print '---Getting %s' % hsname
        histo = template.Clone(hsname); histo.Reset()
        subprocess.tree.Draw("%s>>%s" % (variable,hsname),"%s*(%s<160)" % (weight,weight),'goff')
        histo.Scale(subprocess.scaling)
        return histo
    hsname = '%s_%s_%s' % (process.name,variable,weight)
    print 'Getting %s' % hsname
    histo = template.Clone(hsname); histo.Reset()
    for subprocess in process: histo.Add( getSubVariable(subprocess,variable,weight) )
    return histo
def MakeSF(process,psw):
    process.up = getVariable(process,'ChNemPtFrac','PSW_%sUp' % psw)
    process.dn = getVariable(process,'ChNemPtFrac','PSW_%sDown' % psw)

    process.up.Divide(process.norm); process.dn.Divide(process.norm)
    
    process.output.cd()
    process.up.SetName("PSW_%sUp" % psw)
    process.dn.SetName("PSW_%sDown" % psw)
    process.up.Write()
    process.dn.Write()
def GenerateSF(process):
    process.open()
    process.norm = getVariable(process,'ChNemPtFrac','genWeight')
    process.output = output.mkdir(process.process)
    for psw in pswlist: MakeSF(process,psw)
    
processes = {
    mc:Process(mc,config.filemap[mc],GetMCxsec(config.filemap[mc],config.xsec),'bkg') for mc in ("ZJets","WJets","DYJets")
}

# GenerateSF(processes['ZJets'])
for process in processes: GenerateSF(processes[process])
