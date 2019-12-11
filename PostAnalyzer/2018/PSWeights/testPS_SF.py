from ROOT import *
import sys

store = []
pswlist = [ "isrRed","fsrRed","isrDef","fsrDef","isrCon","fsrCon",      
	    "fsr_G2GG_muR","fsr_G2QQ_muR","fsr_Q2QG_muR","fsr_X2XG_muR",
	    "fsr_G2GG_cNS","fsr_G2QQ_cNS","fsr_Q2QG_cNS","fsr_X2XG_cNS",
	    "isr_G2GG_muR","isr_G2QQ_muR","isr_Q2QG_muR","isr_X2XG_muR",
	    "isr_G2GG_cNS","isr_G2QQ_cNS","isr_Q2QG_cNS","isr_X2XG_cNS"]

def MakeSF(tfile,psw):
    norm = tfile.Get("norm")
    up = tfile.Get("%sUp" % psw)
    dn = tfile.Get("%sDown" % psw)

    up.Divide(norm); dn.Divide(norm);

    c = TCanvas(psw,psw,800,800)
    up.SetLineColor(kRed)
    up.Draw("hist"); dn.Draw("histsame")
    up.GetYaxis().SetRangeUser(0.7,1.3)
    store.append(c); store.append(up); store.append(dn)

tfile = TFile.Open(sys.argv[1])
MakeSF(tfile,"isrRed")
MakeSF(tfile,"isrDef")
MakeSF(tfile,"isrCon")
MakeSF(tfile,"fsrRed")
MakeSF(tfile,"fsrDef")
MakeSF(tfile,"fsrCon")

raw_input()
