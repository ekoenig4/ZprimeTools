from ROOT import *
import os
from sys import argv
from PlotTool import *
from config import config
from config import lumi as lumimap
import re
import copy

gROOT.SetBatch(1)
# gROOT.SetBatch(0)

out_dir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots%s/TransferFactors/%s/"
processMap = {
    "SignalRegion": {
        "Z":{"proc":"ZJets","label":"Z(#nu#nu)",'text':'nn'},
        "W":{"proc":"WJets","label":"W(l#nu)",'text':'ln'},
    },
    "SingleEleCR": {
        "W":{"proc":"WJets","label":"W(e#nu)",'text':'en'}
    }, 
    "SingleMuCR": {
        "W":{"proc":"WJets","label":"W(#mu#nu)",'text':'mn'}
    },
    "SingleLepCR": {
        "W":{"proc":"WJets","label":"W(l#nu)",'text':'ln'},
    },
    "DoubleEleCR": {
        "Z":{"proc":"DYJets","label":"Z(ee)",'text':'ee'}
    },
    "DoubleMuCR": {
        "Z":{"proc":"DYJets","label":"Z(#mu#mu)",'text':'mm'}
    },
    "DoubleLepCR": {
        "Z":{"proc":"ZJets","label":"Z(ll)",'text':'ll'},
    },
}
def FixedRatio(num,den):
    ratio = GetRatio(num,den)
    for ibin in range(1,num.GetNbinsX()+1):
        if den[ibin] == 0 or num[ibin] == 0: continue
        rv = num[ibin]/den[ibin];
        re = rv*TMath.Sqrt(sum( (hs.GetBinError(ibin)/hs.GetBinContent(ibin))**2 for hs in (num,den)))
        ratio.SetBinError(ibin,re)
    return ratio
def SetBounds(hs,a_region,v_region):
    gPad.Update()
    ymin,ymax = gPad.GetUymin(),gPad.GetUymax()
    hs.SetMinimum(ymin*0.8)
    hs.SetMaximum(ymax*1.2)
    # return	
    if a_region == 'SignalRegion' and v_region == 'SignalRegion':
        hs.SetMinimum(0.3); hs.SetMaximum(2.6)
    if a_region == 'DoubleEleCR' and v_region == 'SingleEleCR':
        hs.SetMinimum(0.015); hs.SetMaximum(0.135)
    if a_region == 'DoubleMuCR' and v_region == 'SingleMuCR':
        hs.SetMinimum(0.01); hs.SetMaximum(0.12)
    if a_region == 'SignalRegion' and v_region == 'SingleEleCR':
        hs.SetMinimum(0); hs.SetMaximum(8)
    if a_region == 'SignalRegion' and v_region == 'SingleMuCR':
        hs.SetMinimum(0); hs.SetMaximum(5)
    if a_region == 'SignalRegion' and v_region == 'DoubleEleCR':
        hs.SetMinimum(17); hs.SetMaximum(40)
    if a_region == 'SignalRegion' and v_region == 'DoubleMuCR':
        hs.SetMinimum(15); hs.SetMaximum(28)
    if a_region == 'DoubleLepCR' and v_region == 'SingleLepCR':
        hs.SetMinimum(0.05); hs.SetMaximum(0.12)
def GetAVUncertainty(norm,ajets,vjets):
    unclist = [
            "QCD_Scale",
            "QCD_Shape",
            "QCD_Proc",
            "NNLO_EWK",
            "NNLO_Miss",
            "NNLO_Sud",
            "QCD_EWK_Mix"]
    class Info: pass
    ajets_info,vjets_info = Info(),Info()
    if type(ajets) == Process and type(vjets) == Process:
        for v_info in (ajets,vjets):
            for unc in unclist: v_info.addUnc(unc)
            v_info.fullUnc()
        ajets_info.norm = ajets.histo
        ajets_info.unc = ajets.nuisances['Total']
        vjets_info.norm = vjets.histo
        vjets_info.unc = vjets.nuisances['Total']
    elif type(ajets) == datamc and type(vjets) == datamc:
        for v_info in (ajets,vjets): v_info.fullUnc(unclist=unclist)
        ajets_info.norm = ajets.getSumOfBkg()
        ajets_info.unc = ajets.nuisances['Total']
        vjets_info.norm = vjets.getSumOfBkg()
        vjets_info.unc = vjets.nuisances['Total']
    nbins = norm.GetNbinsX()+1
    up,dn = norm.Clone(),norm.Clone(); up.Reset(); dn.Reset()
    for ibin in range(1,nbins+1):
        if norm[ibin] == 0: continue
        up[ibin] = norm[ibin] * (1 + TMath.Sqrt( sum( (info.unc.up[ibin]/info.norm[ibin])**2 for info in (ajets_info,vjets_info) if info.norm[ibin] != 0) ))
        dn[ibin] = norm[ibin] * (1 - TMath.Sqrt( sum( (info.unc.dn[ibin]/info.norm[ibin])**2 for info in (ajets_info,vjets_info) if info.norm[ibin] != 0) ))
    return GetUncBand(up,dn)
    
def plotAVTF(a_sample,v_sample,aboson,vboson):
    ajetinfo=processMap[a_sample.region][aboson];
    vjetinfo=processMap[v_sample.region][vboson];

    lumi_label = '%s' % float('%.3g' % (a_sample.lumi/1000.)) + " fb^{-1}"
    year = a_sample.version
    varname = a_sample.varname

    ajets = a_sample.processes[ajetinfo['proc']]
    vjets = v_sample.processes[vjetinfo['proc']]

    ajets_norm = ajets.histo
    vjets_norm = vjets.histo

    avlink_norm = FixedRatio(ajets_norm,vjets_norm)
    avlink_unc= GetAVUncertainty(avlink_norm,ajets,vjets)

    c = TCanvas("c", "canvas",800,800);
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    # c.SetLeftMargin(0.15);
    #c.SetLogy();
    #c.cd();
    
    pad1 = TPad("pad1","pad1",0.01,0.01,0.99,0.99);
    pad1.Draw(); pad1.cd();
    # pad1.SetLogy();
    pad1.SetFillColor(0);
    pad1.SetFrameBorderMode(0);
    pad1.SetBorderMode(0);
    # pad1.SetBottomMargin(0.);

    avlink_unc.Draw("a2same")
    avlink_norm.Draw("pex0same")
    UncBandStyle(avlink_unc)
    avlink_norm.SetLineWidth(2)
    avlink_norm.SetLineColor(kBlack);
    avlink_norm.SetMarkerStyle(20);
    avlink_norm.SetMarkerSize(1);
    avlink_norm.SetTitle("")
    avlink_unc.GetYaxis().SetTitle("Ratio_{%s/%s}" % (ajetinfo['label'],vjetinfo['label']))
    avlink_unc.GetYaxis().CenterTitle()
    avlink_unc.GetYaxis().SetTitleOffset(1.3)
    avlink_unc.GetXaxis().SetTitle(a_sample.name)
    avlink_unc.GetXaxis().SetTitleOffset(1.2)

    SetBounds(avlink_unc,a_sample.region,v_sample.region)

    texCMS,texLumi = getCMSText(lumi_label,year)
    for tex in (texCMS,texLumi): tex.SetTextSize(0.03)
    leg = getLegend(xmin=0.5,xmax=0.7)
    leg.AddEntry(avlink_norm,"Transfer Factor (Stat Uncert)","p")
    leg.Draw()
    
    variable,binning = re.split('_\d*',varname)
    outdir = out_dir % (year,variable)
    if not os.path.isdir(outdir): os.mkdir(outdir)

    tfproc = "%s%s%s%s" % (aboson,ajetinfo['text'],vboson,vjetinfo['text'])
    outname = "%s_%s_%s.png" % (tfproc,variable,binning)
    output = os.path.join(outdir,outname)
    c.SaveAs( output )

def plotAVTF_ratio(a_sample,v_sample,aboson,vboson):
    ajetinfo=processMap[a_sample.region][aboson];
    vjetinfo=processMap[v_sample.region][vboson];

    lumi_label = '%s' % float('%.3g' % (a_sample.lumi/1000.)) + " fb^{-1}"
    year = a_sample.version
    varname = a_sample.varname

    ajets_data = a_sample.processes['Data']
    vjets_data = v_sample.processes['Data']

    ajets_mc_norm = a_sample.getSumOfBkg()
    vjets_mc_norm = v_sample.getSumOfBkg()
    ajets_data_norm = ajets_data.histo
    vjets_data_norm = vjets_data.histo

    avlink_mc = FixedRatio(ajets_mc_norm,vjets_mc_norm)
    avlink_unc= GetAVUncertainty(avlink_mc,a_sample,v_sample)
    avlink_data = FixedRatio(ajets_data_norm,vjets_data_norm)

    c = TCanvas("c", "canvas",800,800);
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    #c.SetLeftMargin(0.15);
    #c.SetLogy();
    #c.cd();
    
    pad1 = TPad("pad1","pad1",0.01,0.25,0.99,0.99);
    pad1.Draw(); pad1.cd();
    # pad1.SetLogy();
    pad1.SetFillColor(0); pad1.SetFrameBorderMode(0); pad1.SetBorderMode(0);
    pad1.SetBottomMargin(0.);

    DataStyle(avlink_data)
    UncBandStyle(avlink_unc)

    avlink_unc.Draw("a2same")
    avlink_mc.Draw("histsame")
    avlink_data.Draw("psame")
    
    avlink_unc.SetTitle("")
    avlink_unc.GetYaxis().SetTitle("Ratio_{%s/%s}" % (ajetinfo['label'],vjetinfo['label']))
    avlink_unc.GetYaxis().CenterTitle()
    # avlink_unc.GetYaxis().SetTitleOffset(1.8)
    avlink_unc.GetXaxis().SetTitle("");
    avlink_unc.GetXaxis().SetTickLength(0);
    avlink_unc.GetXaxis().SetLabelOffset(999);
    
    SetBounds(avlink_unc,a_sample.region,v_sample.region)

    ##############################
    leg = getLegend(xmin=0.5,xmax=0.7)
    leg.AddEntry(avlink_data,"%s/%s Data" % (ajetinfo['label'],vjetinfo['label']),'p')
    leg.AddEntry(avlink_mc,"%s/%s MC" % (ajetinfo['label'],vjetinfo['label']),'l')
    leg.Draw()

    texLumi,texCMS = getCMSText(lumi_label,year)

    c.cd();
    pad2 = TPad("pad2","pad2",0.01,0.01,0.99,0.25);
    pad2.Draw(); pad2.cd();
    pad2.SetFillColor(0); pad2.SetFrameBorderMode(0); pad2.SetBorderMode(0);
    pad2.SetTopMargin(0);
    pad2.SetBottomMargin(0.35);

    Ratio = FixedRatio(avlink_data,avlink_mc)

    rymin = 0.65; rymax = 1.35
    RatioStyle(Ratio,rymin,rymax)
    Ratio.Draw("pex0");
    
    line = getRatioLine(avlink_data.GetXaxis().GetXmin(),avlink_data.GetXaxis().GetXmax())
    line.Draw("same");

    c.Update();

    ########################################################

    nbins = avlink_data.GetNbinsX();
    xmin = avlink_data.GetXaxis().GetXmin();
    xmax = avlink_data.GetXaxis().GetXmax();
    xwmin = xmin;
    xwmax = xmax;

    xname = a_sample.name if type(a_sample.name) == str else None
    xaxis = makeXaxis(xmin,xmax,rymin,510,name=xname);
    xaxis.Draw("SAME");

    yaxis = makeYaxis(rymin,rymax,xmin,6,name="Data/MC");
    yaxis.Draw("SAME");

    #######################################################
    variable,binning = re.split('_\d*',varname)
    outdir = out_dir % (year,variable)
    if not os.path.isdir(outdir): os.mkdir(outdir)
    
    tfproc = "%s%s%s%s" % (aboson,ajetinfo['text'],vboson,vjetinfo['text'])
    outname = "%s_%s_%s.png" % (tfproc,variable,binning)
    output = os.path.join(outdir,outname)
    c.SaveAs( output )
def plotTransfer(variable,samplemap):
    cut = ''
    if '>' in variable: cut = '>'+variable.split('>')[-1]
    if '<' in variable: cut = '<'+variable.split('<')[-1]
    varname = variable.replace('>','+').replace('<','-')
    variable = variable.replace(cut,'')
    for region in samplemap:
        var = variable+'_'+config['regions'][region]+cut
        samplemap[region].initiate(var)

    print "ZJet Muon CR TF"
    plotAVTF(samplemap["DoubleMuCR/"],samplemap["SignalRegion/"],"Z","Z")
    print "ZJet Electron CR TF"
    plotAVTF(samplemap["DoubleEleCR/"],samplemap["SignalRegion/"],"Z","Z")

    print "WJet Muon CR TF"
    plotAVTF(samplemap["SingleMuCR/"],samplemap["SignalRegion/"],"W","W")
    print "WJet Electron CR TF"
    plotAVTF(samplemap["SingleEleCR/"],samplemap["SignalRegion/"],"W","W")

    print "SR ZW TF"
    plotAVTF(samplemap["SignalRegion/"],samplemap["SignalRegion/"],"Z","W")

    
    # samplemap["DoubleLepCR/"] = samplemap["DoubleEleCR/"] + samplemap["DoubleMuCR/"]; samplemap["DoubleLepCR/"].region = "DoubleLepCR"
    # samplemap["SingleLepCR/"] = samplemap["SingleEleCR/"] + samplemap["SingleMuCR/"]; samplemap["SingleLepCR/"].region = "SingleLepCR"

    print "Electron ZW TF"
    plotAVTF_ratio(samplemap["DoubleEleCR/"],samplemap["SingleEleCR/"],"Z","W")
    print "Muon ZW TF"
    plotAVTF_ratio(samplemap["DoubleMuCR/"],samplemap["SingleMuCR/"],"Z","W")
    # print "CR ZW TF"
    # plotAVTF_ratio(samplemap["DoubleLepCR/"],samplemap["SingleLepCR/"],"Z","W")
    

def runAll(args):
    scale_lumi = max(lumimap.values())
    samplemap = { region:Region(fileDir=region,show=0,lumi=scale_lumi) for region in config['regions'] }
    for variable in args.argv: plotTransfer(variable,samplemap)

if __name__ == "__main__":
    args = parser.parse_args()
    if not any(args.argv): args.argv.append('ChNemPtFrac')
    runAll(args)
