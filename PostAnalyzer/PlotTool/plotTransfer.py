from ROOT import *
import os
from sys import argv
from PlotTool import *
from config import config
from config import lumi as lumimap
import re

gROOT.SetBatch(1)
# gROOT.SetBatch(0)

out_dir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots%s/TransferFactors/%s/"
processMap = {
    "SignalRegion": {
        "Z":{"proc":"ZJets","label":"Z(#nu#nu)",'text':'nn'},
        "W":{"proc":"WJets","label":"W(l#nu)",'text':'ln'}
    },
    "SingleEleCR": {
        "W":{"proc":"WJets","label":"W(e#nu)",'text':'en'}
    }, 
    "SingleMuCR": {
        "W":{"proc":"WJets","label":"W(#mu#nu)",'text':'mn'}
    },
    "DoubleEleCR": {
        "Z":{"proc":"DYJets","label":"Z(ee)",'text':'ee'}
    },
    "DoubleMuCR": {
        "Z":{"proc":"DYJets","label":"Z(#mu#mu)",'text':'mm'}
    },
}

def plotSR_ZW(z_sample,w_sample):
    zjetinfo=processMap[z_sample.region]['Z']
    wjetinfo=processMap[w_sample.region]['W']

    lumi_label = '%s' % float('%.3g' % (z_sample.lumi/1000.)) + " fb^{-1}"
    year = z_sample.version
    varname = z_sample.varname

    zjets = z_sample.processes[zjetinfo['proc']]
    wjets = w_sample.processes[wjetinfo['proc']]

    zjets_norm = zjets.histo
    wjets_norm = wjets.histo

    zwlink_norm = GetRatio(zjets_norm,wjets_norm)

    c = TCanvas("c", "canvas",800,800);
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    # c.SetLeftMargin(0.15);
    #c.SetLogy();
    #c.cd();
    
    pad1 = TPad("pad1","pad1",0.01,0.05,0.99,0.99);
    pad1.Draw(); pad1.cd();
    # pad1.SetLogy();
    pad1.SetFillColor(0);
    pad1.SetFrameBorderMode(0);
    pad1.SetBorderMode(0);
    pad1.SetLeftMargin(0.15)
    # pad1.SetBottomMargin(0.);

    zwlink_norm.SetLineWidth(2)
    zwlink_norm.SetLineColor(kBlack);
    zwlink_norm.SetMarkerStyle(20);
    zwlink_norm.SetMarkerSize(1);
    zwlink_norm.Draw("pex0")
    zwlink_norm.SetTitle("")
    zwlink_norm.GetYaxis().SetTitle("Ratio_{%s/%s}" % (zjetinfo['label'],wjetinfo['label']))
    zwlink_norm.GetYaxis().CenterTitle()
    zwlink_norm.GetYaxis().SetTitleOffset(1.8)
    zwlink_norm.GetXaxis().SetTitle(z_sample.name)
    zwlink_norm.GetXaxis().SetTitleOffset(1.2)

    texS,texS1 = getCMSText(lumi_label,year)
    leg = getLegend(xmin=0.5,xmax=0.7)
    leg.AddEntry(zwlink_norm,"Transfer Factor (Stat Uncert)","p")
    leg.Draw()

    SetYBounds([zwlink_norm])

    variable,binning = re.split('_\d*',varname)
    outdir = out_dir % (year,variable)
    if not os.path.isdir(outdir): os.mkdir(outdir)
    
    outname = "Z%sW%s_%s_%s.png" % (zjetinfo['text'],wjetinfo['text'],variable,binning)
    output = os.path.join(outdir,outname)
    c.SaveAs( output )

def plotCR_ZW(z_sample,w_sample):
    
    zjetinfo=processMap[z_sample.region]['Z']
    wjetinfo=processMap[w_sample.region]['W']

    lumi_label = '%s' % float('%.3g' % (z_sample.lumi/1000.)) + " fb^{-1}"
    year = z_sample.version
    varname = z_sample.varname

    zjets_data = z_sample.processes['Data']
    wjets_data = w_sample.processes['Data']

    zjets_mc_norm = z_sample.getSumOfBkg()
    wjets_mc_norm = w_sample.getSumOfBkg()
    zjets_data_norm = zjets_data.histo
    wjets_data_norm = wjets_data.histo

    zwlink_mc = GetRatio(zjets_mc_norm,wjets_mc_norm)
    zwlink_data = GetRatio(zjets_data_norm,wjets_data_norm)

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

    DataStyle(zwlink_data)

    zwlink_mc.Draw("hist")
    zwlink_data.Draw("psame")
    
    zwlink_mc.SetTitle("")
    zwlink_mc.GetYaxis().SetTitle("Ratio_{%s/%s}" % (zjetinfo['label'],wjetinfo['label']))
    zwlink_mc.GetYaxis().CenterTitle()
    # zwlink_mc.GetYaxis().SetTitleOffset(1.8)
    zwlink_mc.GetXaxis().SetTitle("");
    zwlink_mc.GetXaxis().SetTickLength(0);
    zwlink_mc.GetXaxis().SetLabelOffset(999);

    ##############################
    leg = getLegend(xmin=0.5,xmax=0.7)
    leg.AddEntry(zwlink_data,"%s/%s Data" % (zjetinfo['label'],wjetinfo['label']),'p')
    leg.AddEntry(zwlink_mc,"%s/%s MC" % (zjetinfo['label'],wjetinfo['label']),'l')
    leg.Draw()

    texLumi,texCMS = getCMSText(lumi_label,year)

    SetYBounds([zwlink_mc,zwlink_data])
    ###############################################

    c.cd();
    pad2 = TPad("pad2","pad2",0.01,0.01,0.99,0.25);
    pad2.Draw(); pad2.cd();
    pad2.SetFillColor(0); pad2.SetFrameBorderMode(0); pad2.SetBorderMode(0);
    pad2.SetTopMargin(0);
    pad2.SetBottomMargin(0.35);

    Ratio = GetRatio(zwlink_data,zwlink_mc)

    rymin = 0.65; rymax = 1.35
    RatioStyle(Ratio,rymin,rymax)
    Ratio.Draw("pex0");
    
    line = getRatioLine(zwlink_data.GetXaxis().GetXmin(),zwlink_data.GetXaxis().GetXmax())
    line.Draw("same");

    c.Update();

    ########################################################

    nbins = zwlink_data.GetNbinsX();
    xmin = zwlink_data.GetXaxis().GetXmin();
    xmax = zwlink_data.GetXaxis().GetXmax();
    xwmin = xmin;
    xwmax = xmax;

    xname = z_sample.name if type(z_sample.name) == str else None
    xaxis = makeXaxis(xmin,xmax,rymin,510,name=xname);
    xaxis.Draw("SAME");

    yaxis = makeYaxis(rymin,rymax,xmin,6,name="Data/MC");
    yaxis.Draw("SAME");

    #######################################################
    variable,binning = re.split('_\d*',varname)
    outdir = out_dir % (year,variable)
    if not os.path.isdir(outdir): os.mkdir(outdir)
    
    outname = "Z%sW%s_%s_%s.png" % (zjetinfo['text'],wjetinfo['text'],variable,binning)
    output = os.path.join(outdir,outname)
    c.SaveAs( output )

def plotCR_TF(sr_sample,cr_sample,boson):
    srinfo=processMap[sr_sample.region][boson]
    crinfo=processMap[cr_sample.region][boson]

    lumi_label = '%s' % float('%.3g' % (sr_sample.lumi/1000.)) + " fb^{-1}"
    year = sr_sample.version
    varname = sr_sample.varname

    sr = sr_sample.processes[srinfo['proc']]
    cr = cr_sample.processes[crinfo['proc']]

    sr_norm = sr.histo
    cr_norm = cr.histo

    tf_norm = GetRatio(sr_norm,cr_norm)

    c = TCanvas("c", "canvas",800,800);
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    # c.SetLeftMargin(0.15);
    #c.SetLogy();
    #c.cd();
    
    pad1 = TPad("pad1","pad1",0.01,0.05,0.99,0.99);
    pad1.Draw(); pad1.cd();
    # pad1.SetLogy();
    pad1.SetFillColor(0);
    pad1.SetFrameBorderMode(0);
    pad1.SetBorderMode(0);
    pad1.SetLeftMargin(0.15)
    # pad1.SetBottomMargin(0.);

    tf_norm.SetLineWidth(2)
    tf_norm.SetLineColor(kBlack);
    tf_norm.SetMarkerStyle(20);
    tf_norm.SetMarkerSize(1);
    tf_norm.Draw("pex0")
    tf_norm.SetTitle("")
    tf_norm.GetYaxis().SetTitle("Ratio_{%s/%s}" % (srinfo['label'],crinfo['label']))
    tf_norm.GetYaxis().CenterTitle()
    tf_norm.GetYaxis().SetTitleOffset(1.8)
    tf_norm.GetXaxis().SetTitle(sr_sample.name)
    tf_norm.GetXaxis().SetTitleOffset(1.2)

    texS,texS1 = getCMSText(lumi_label,year)
    leg = getLegend(xmin=0.5,xmax=0.7)
    leg.AddEntry(tf_norm,"Transfer Factor (Stat Uncert)","p")
    leg.Draw()

    SetYBounds([tf_norm])
    
    variable,binning = re.split('_\d*',varname)
    outdir = out_dir % (year,variable)
    if not os.path.isdir(outdir): os.mkdir(outdir)
    
    outname = "%s%s%s%s_%s_%s.png" % (boson,srinfo['text'],boson,crinfo['text'],variable,binning)
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
    print "SR ZW Linking"
    plotSR_ZW(samplemap['SignalRegion/'],samplemap['SignalRegion/'])
    print "Electron ZW Linking"
    plotCR_ZW(samplemap['DoubleEleCR/'],samplemap['SingleEleCR/'])
    print "Muon ZW Linking"
    plotCR_ZW(samplemap['DoubleMuCR/'],samplemap['SingleMuCR/'])
    
    print "ZJets Electron TF"
    plotCR_TF(samplemap['SignalRegion/'],samplemap['DoubleEleCR/'],'Z')
    print "ZJets Muon TF"
    plotCR_TF(samplemap['SignalRegion/'],samplemap['DoubleMuCR/'],'Z')
    
    print "WJets Electron TF"
    plotCR_TF(samplemap['SignalRegion/'],samplemap['SingleEleCR/'],'W')
    print "WJets Muon TF"
    plotCR_TF(samplemap['SignalRegion/'],samplemap['SingleMuCR/'],'W')

def runAll(args):
    scale_lumi = max(lumimap.values())
    samplemap = { region:datamc(fileDir=region,show=0,lumi=scale_lumi) for region in config['regions'] }
    for variable in args.argv: plotTransfer(variable,samplemap)

if __name__ == "__main__":
    args = parser.parse_args()
    if not any(args.argv): args.argv.append('ChNemPtFrac')
    runAll(args)
