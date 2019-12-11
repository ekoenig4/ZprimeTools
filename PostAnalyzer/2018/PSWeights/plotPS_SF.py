import os
from ROOT import *
import sys
sys.path.append('PlotTool')
from PlotTool import *
from config import *

gROOT.SetBatch(1)

pswlist = [ "isrRed","fsrRed","isrDef","fsrDef","isrCon","fsrCon",      
	    "fsr_G2GG_muR","fsr_G2QQ_muR","fsr_Q2QG_muR","fsr_X2XG_muR",
	    "fsr_G2GG_cNS","fsr_G2QQ_cNS","fsr_Q2QG_cNS","fsr_X2XG_cNS",
	    "isr_G2GG_muR","isr_G2QQ_muR","isr_Q2QG_muR","isr_X2XG_muR",
	    "isr_G2GG_cNS","isr_G2QQ_cNS","isr_Q2QG_cNS","isr_X2XG_cNS"]
tfile = TFile.Open("PSW_SF.root")
def PlotPSW(process,psw):
    up = tfile.Get('%s/PSW_%sUp' % (process,psw))
    dn = tfile.Get('%s/PSW_%sDown' % (process,psw))
    c = TCanvas("%s_%s" % (process,psw),"%s_%s" % (process,psw),800,800)
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    c.SetLeftMargin(0.15)

    up.SetLineColor(kRed)
    up.SetLineWidth(3)
    up.Draw("hist][")
    dn.SetLineColor(kBlue)
    dn.SetLineWidth(3)
    dn.Draw("hist][same")

    up.GetYaxis().SetRangeUser(0.5,1.5)
    up.GetYaxis().SetTitle(psw)

    line= getRatioLine(up.GetXaxis().GetXmin(),up.GetXaxis().GetXmax())
    line.Draw()

    leg = getLegend()
    leg.AddEntry(up,"pswUp","l")
    leg.AddEntry(dn,"pswDn","l")
    leg.Draw()

    outdir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/PSWeights/%s/test" % process
    if not os.path.isdir(outdir): os.mkdir(outdir)
    fname = "%s.png" % psw
    c.SaveAs("%s/%s" % (outdir,fname))

for mc in ("ZJets","WJets","DYJets"):
    for psw in pswlist:
        PlotPSW(mc,psw)
