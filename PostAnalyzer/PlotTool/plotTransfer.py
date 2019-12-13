from ROOT import *
import os
from sys import argv
from PlotTool import *
import config
import re

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

def SetBounds(hs):

    bins = list(hs)[1:-1]
    avg = sum( ibin for ibin in bins ) / len(bins)
    maxdiff = max( abs(ibin - avg) for ibin in bins )
    hs.SetMinimum( (avg - maxdiff)*0.7 )
    hs.SetMaximum( (avg + maxdiff)*1.3 )
def getTFUncertainty(norm,num_proc,den_proc):
    unclist = [
            "QCD_Scale",
            "QCD_Shape",
            "QCD_Proc",
            "NNLO_EWK",
            "NNLO_Miss",
            "NNLO_Sud",
            "QCD_EWK_Mix"]
    for proc in (num_proc,den_proc):
        proc.fullUnc(unclist,show=False)
        print proc.nuisances['Total']
    nbins = norm.GetNbinsX()
    up,dn = norm.Clone(),norm.Clone(); up.Reset(); dn.Reset()
    for ibin in range(1,nbins+1):
        if norm[ibin] == 0: continue
        up[ibin] = norm[ibin] * TMath.Sqrt( sum( (proc.nuisances['Total'].up[ibin]/proc.histo[ibin])**2 for proc in (num_proc,den_proc) ) )
        dn[ibin] = norm[ibin] * TMath.Sqrt( sum( (proc.nuisances['Total'].dn[ibin]/proc.histo[ibin])**2 for proc in (num_proc,den_proc) ) )
    nuisance = Nuisance('tf','Total',up,dn,norm)
    print nuisance
    up,dn = nuisance.GetHistos()
    return GetUncBand(up,dn)
def plotTF(num_sample,den_sample):

    lumi_label = '%s' % float('%.3g' % (num_sample.lumi/1000.)) + " fb^{-1}"
    year = num_sample.year
    varname = num_sample.varname
    
    num_info = processMap[num_sample.region][num_sample.num_boson]
    den_info = processMap[den_sample.region][den_sample.den_boson]
    num_proc = num_sample[num_info["proc"]]
    den_proc = den_sample[den_info["proc"]]

    tf = GetRatio(num_proc.histo,den_proc.histo)

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
    # pad1.SetLeftMargin(0.2)
    # pad1.SetBottomMargin(0.);
    
    SetBounds(tf)
    tf.Draw("axis")
    uncband = getTFUncertainty(tf,num_proc,den_proc)
    UncBandStyle(uncband)
    uncband.Draw("2same")
    tf.Draw("pex0same")
    
    tf.SetLineWidth(2)
    tf.SetLineColor(kBlack);
    tf.SetMarkerStyle(20);
    tf.SetMarkerSize(1);
    tf.SetTitle("")
    tf.GetYaxis().SetTitle("Ratio_{%s/%s}" % (num_info['label'],den_info['label']))
    tf.GetYaxis().CenterTitle()
    tf.GetYaxis().SetTitleOffset(1.2)
    tf.GetXaxis().SetTitle(num_sample.name)
    tf.GetXaxis().SetTitleOffset(1.2)
    
    texCMS,texLumi = getCMSText(lumi_label,year)
    for tex in (texCMS,texLumi): tex.SetTextSize(0.03)
    leg = getLegend(xmin=0.5,xmax=0.7)
    leg.AddEntry(tf,"Transfer Factor (Stat Uncert)","p")
    leg.Draw()

    variable,binning = re.split('_\d*',varname)
    outdir = out_dir % (year,variable)
    if not os.path.isdir(outdir): os.mkdir(outdir)

    tfproc = "%s%s%s%s" % (num_sample.num_boson,num_info['text'],den_sample.den_boson,den_info['text'])
    outname = "%s_%s_%s.png" % (tfproc,variable,binning)
    output = os.path.join(outdir,outname)
    c.SaveAs( output )
    

def plotTransfer(variable,samplemap):
    for region in samplemap:
        var = variable+'_'+config.regions[region]
        samplemap[region].initiate(var)

    print "Z/W Linking"
    samplemap["SignalRegion"].num_boson = "Z"
    samplemap["SignalRegion"].den_boson = "W"
    plotTF(samplemap["SignalRegion"],samplemap["SignalRegion"])
    
    print "DoubleEleCR Transfer"
    samplemap["SignalRegion"].den_boson = "Z"
    samplemap["DoubleEleCR"].num_boson = "Z"
    plotTF(samplemap["DoubleEleCR"],samplemap["SignalRegion"])
    print "DoubleMuCR Transfer"
    samplemap["SignalRegion"].den_boson = "Z"
    samplemap["DoubleMuCR"].num_boson = "Z"
    plotTF(samplemap["DoubleMuCR"],samplemap["SignalRegion"])
    
    print "SingleEleCR Transfer"
    samplemap["SignalRegion"].den_boson = "W"
    samplemap["SingleEleCR"].num_boson = "W"
    plotTF(samplemap["SingleEleCR"],samplemap["SignalRegion"])
    print "SingleMuCR Transfer"
    samplemap["SignalRegion"].den_boson = "W"
    samplemap["SingleMuCR"].num_boson = "W"
    plotTF(samplemap["SingleMuCR"],samplemap["SignalRegion"])

def runAll(args):
    scale_lumi = max(config.lumi.values())
    samplemap = { region:Region(path=region,show=False,lumi=scale_lumi) for region in config.regions }
    for variable in args.argv: plotTransfer(variable,samplemap)

if __name__ == "__main__":
    args = parser.parse_args()
    if not any(args.argv): args.argv.append('ChNemPtFrac')
    runAll(args)
