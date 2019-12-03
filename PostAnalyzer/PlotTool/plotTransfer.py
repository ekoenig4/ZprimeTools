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

out_dir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoJet/Plots%s/TransferFactors/%s/"
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
    "GammaCR": {
        "G":{"proc":"GJets","label":"#gamma","text":""}
    },
}

def SetBounds(hslist):
    binlist = range(1,hslist[0].GetNbinsX()+1)
    maxY = max( max( hs[ibin] for hs in hslist ) for ibin in binlist )
    minY = min( min( hs[ibin] for hs in hslist if hs[ibin] != 0 ) for ibin in binlist )

    hslist[0].SetMinimum(minY*0.8)
    hslist[0].SetMaximum(maxY*1.2)
def GetAVUncertainty(norm,ajets,vjets,unclist):
    for v_info in (ajets,vjets):
        for unc in unclist: v_info.addUnc(unc)
        v_info.fullUnc()
    nbins = norm.GetNbinsX()+1
    up,dn = norm.Clone(),norm.Clone()
    for ibin in range(1,nbins):
        percUp = TMath.Sqrt(sum( (1-vjets.nuisances['Total']['Up'][ibin]/vjets.histo[ibin])**2 for vjets in (ajets,vjets) ))
        percDn = TMath.Sqrt(sum( (1-vjets.nuisances['Total']['Down'][ibin]/vjets.histo[ibin])**2 for vjets in (ajets,vjets) ))
        up.SetBinContent(ibin,norm[ibin]*(1+percUp))
        dn.SetBinContent(ibin,norm[ibin]*(1-percDn))
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

    avlink_norm = GetRatio(ajets_norm,vjets_norm)
    # unclist = [
    #         "QCD_Scale",
    #         "QCD_Shape",
    #         "QCD_Proc",
    #         "NNLO_EWK",
    #         "NNLO_Miss",
    #         "NNLO_Sud",
    #         "QCD_EWK_Mix"]
    # avlink_unc= GetAVUncertainty(avlink_norm,ajets,vjets,unclist)

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

    avlink_norm.Draw("pex0same")
    avlink_norm.SetLineWidth(2)
    avlink_norm.SetLineColor(kBlack);
    avlink_norm.SetMarkerStyle(20);
    avlink_norm.SetMarkerSize(1);
    avlink_norm.SetTitle("")
    avlink_norm.GetYaxis().SetTitle("Ratio_{%s/%s}" % (ajetinfo['label'],vjetinfo['label']))
    avlink_norm.GetYaxis().CenterTitle()
    avlink_norm.GetYaxis().SetTitleOffset(1.3)
    avlink_norm.GetXaxis().SetTitle(a_sample.name)
    avlink_norm.GetXaxis().SetTitleOffset(1.2)
    
    gPad.Update()
    ymin,ymax = gPad.GetUymin(),gPad.GetUymax()
    print ymin,ymax
    avlink_norm.SetMinimum(ymin*0.8)
    avlink_norm.SetMaximum(ymax*1.2)

    texCMS,texLumi = getCMSText(lumi_label,year)
    for tex in (texCMS,texLumi): tex.SetTextSize(0.03)
    leg = getLegend(xmin=0.5,xmax=0.7)
    leg.AddEntry(avlink_norm,"Transfer Factor (Stat Uncert)","p")
    leg.Draw()

    # SetBounds([zwlink_norm])
    
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

    avlink_mc = GetRatio(ajets_mc_norm,vjets_mc_norm)
    avlink_data = GetRatio(ajets_data_norm,vjets_data_norm)

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

    avlink_mc.Draw("hist")
    avlink_data.Draw("psame")
    
    avlink_mc.SetTitle("")
    avlink_mc.GetYaxis().SetTitle("Ratio_{%s/%s}" % (ajetinfo['label'],vjetinfo['label']))
    avlink_mc.GetYaxis().CenterTitle()
    # avlink_mc.GetYaxis().SetTitleOffset(1.8)
    avlink_mc.GetXaxis().SetTitle("");
    avlink_mc.GetXaxis().SetTickLength(0);
    avlink_mc.GetXaxis().SetLabelOffset(999);

    gPad.Update()
    ymin,ymax = gPad.GetUymin(),gPad.GetUymax()
    print ymin,ymax
    avlink_mc.SetMinimum(ymin*0.8)
    avlink_mc.SetMaximum(ymax*1.2)

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

    Ratio = GetRatio(avlink_data,avlink_mc)

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
    plotAVTF(samplemap["SignalRegion/"],samplemap["DoubleMuCR/"],"Z","Z")
    print "ZJet Electron CR TF"
    plotAVTF(samplemap["SignalRegion/"],samplemap["DoubleEleCR/"],"Z","Z")
    print "ZJet Gamma CR TF"
    plotAVTF(samplemap["SignalRegion/"],samplemap["GammaCR/"],"Z","G")

    print "WJet Muon CR TF"
    plotAVTF(samplemap["SignalRegion/"],samplemap["SingleMuCR/"],"W","W")
    print "WJet Electron CR TF"
    plotAVTF(samplemap["SignalRegion/"],samplemap["SingleEleCR/"],"W","W")

    print "SR ZW TF"
    plotAVTF(samplemap["SignalRegion/"],samplemap["SignalRegion/"],"Z","W")

    
    samplemap["DoubleLepCR/"] = samplemap["DoubleEleCR/"] + samplemap["DoubleMuCR/"]; samplemap["DoubleLepCR/"].region = "DoubleLepCR"
    samplemap["SingleLepCR/"] = samplemap["SingleEleCR/"] + samplemap["SingleMuCR/"]; samplemap["SingleLepCR/"].region = "SingleLepCR"
    
    print "Electron ZG TF"
    plotAVTF_ratio(samplemap["DoubleEleCR/"],samplemap["GammaCR/"],"Z","G")
    print "Muon ZG TF"
    plotAVTF_ratio(samplemap["DoubleMuCR/"],samplemap["GammaCR/"],"Z","G")
    print "CR ZG TF"
    plotAVTF_ratio(samplemap["DoubleLepCR/"],samplemap["GammaCR/"],"Z","G")

    print "Electron WG TF"
    plotAVTF_ratio(samplemap["SingleEleCR/"],samplemap["GammaCR/"],"W","G")
    print "Muon WG TF"
    plotAVTF_ratio(samplemap["SingleMuCR/"],samplemap["GammaCR/"],"W","G")
    print "CR WG TF"
    plotAVTF_ratio(samplemap["SingleLepCR/"],samplemap["GammaCR/"],"W","G")

    print "Electron ZW TF"
    plotAVTF_ratio(samplemap["DoubleEleCR/"],samplemap["SingleEleCR/"],"Z","W")
    print "Muon ZW TF"
    plotAVTF_ratio(samplemap["DoubleMuCR/"],samplemap["SingleMuCR/"],"Z","W")
    print "CR ZW TF"
    plotAVTF_ratio(samplemap["DoubleLepCR/"],samplemap["SingleLepCR/"],"Z","W")
    

def runAll(args):
    scale_lumi = max(lumimap.values())
    samplemap = { region:datamc(fileDir=region,show=0,lumi=scale_lumi) for region in config['regions'] }
    for variable in args.argv: plotTransfer(variable,samplemap)

if __name__ == "__main__":
    args = parser.parse_args()
    if not any(args.argv): args.argv.append('ChNemPtFrac')
    runAll(args)
