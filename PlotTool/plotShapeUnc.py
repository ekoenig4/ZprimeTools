from ROOT import *
import os
from argparse import ArgumentParser
from Plot import datamc
from cfg_saveplot import config
from plotter import getLegend,makeXaxis,makeYaxis,RatioStyle,getRatioLine,getCMSText

gROOT.SetBatch(1)

out_dir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots%s/"
def plotCRUnc(sample,uncname):
    print 'Fetching %s' % uncname
    sample.addUnc(uncname)
    if 'Single' in sample.region: process = 'WJets'
    if 'Double' in sample.region: process = 'DYJets'

    norm = sample.processes[process].histo.Clone('norm')
    up   = sample.processes[process].nuisances[uncname]['Up'].Clone('up')
    dn   = sample.processes[process].nuisances[uncname]['Down'].Clone('dn')

    r_up = up.Clone('ratio_up'); r_up.Divide(norm)
    r_dn = dn.Clone('ratio_dn'); r_dn.Divide(norm)

    c = TCanvas("c", "canvas",800,800);
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    #c.SetLeftMargin(0.15);
    #c.SetLogy();
    #c.cd();
    
    pad1 = TPad("pad1","pad1",0.01,0.25,0.99,0.99);
    pad1.Draw(); pad1.cd();
    pad1.SetLogy();
    pad1.SetFillColor(0); pad1.SetFrameBorderMode(0); pad1.SetBorderMode(0);
    pad1.SetBottomMargin(0.);

    ymax = max( h.GetMaximum() for h in (norm,up,dn) ) * pow(10,2.5)
    ymin = ymax * pow(10,-6)

    for h in (up,dn): h.SetLineStyle(2)
    for h in (norm,up,dn):
        h.SetTitle("")
        h.GetYaxis().SetTitle("Events")
        h.GetYaxis().SetRangeUser(ymin,ymax)
    
    norm.Draw('hist')
    up.Draw('hist same')
    dn.Draw('hist same')
    
    lumi_label = '%s' % float('%.3g' % (sample.lumi/1000.)) + " fb^{-1}"
    texLumi,texCMS = getCMSText(lumi_label,sample.version)
    texLumi.Draw();
    texCMS.Draw();

    pt = TPaveText(0.62,0.60,0.86,0.887173,'NDC');
    pt.AddText("Systematic Variation")
    pt.AddText(uncname)
    pt.AddText(process)
    pt.Draw()
    
    c.cd();
    pad2 = TPad("pad2","pad2",0.01,0.01,0.99,0.25);
    pad2.Draw(); pad2.cd();
    pad2.SetFillColor(0); pad2.SetFrameBorderMode(0); pad2.SetBorderMode(0);
    pad2.SetTopMargin(0);
    pad2.SetBottomMargin(0.35);

    rbins = []
    for r in (r_up,r_dn): rbins += [ b for b in r if b != 0 ]

    def avg(bins): return sum(bins)/len(bins)
    def stdv(bins):
        bavg = avg(bins)
        return ( sum( (b - bavg)**2 for b in bins )/(len(bins)-1) ) ** 0.5
    
    rstdv = stdv(rbins)
    rymin = 1 - 3*rstdv; rymax = 1 + 3*rstdv
    
    RatioStyle(r_up,rymin,rymax)
    RatioStyle(r_dn,rymin,rymax)

    for r in (r_up,r_dn):
        r.SetMarkerStyle(1)
        r.SetTitle("")
        r.GetXaxis().SetTitle("");
        r.GetXaxis().SetTickLength(0);
        r.GetXaxis().SetLabelOffset(999);
        r.GetYaxis().SetTitle("");
        r.GetYaxis().SetTickLength(0);
        r.GetYaxis().SetLabelOffset(999);
    
    r_up.Draw()
    r_dn.Draw('same')
    
    nbins = norm.GetNbinsX();
    xmin = norm.GetXaxis().GetXmin();
    xmax = norm.GetXaxis().GetXmax();
    xwmin = xmin;
    xwmax = xmax;
    
    line = getRatioLine(xmin,xmax)
    line.Draw("same");

    xname = sample.name if type(sample.name) == str else None
    xaxis = makeXaxis(xmin,xmax,rymin,510,name=xname);
    xaxis.Draw("SAME");

    yaxis = makeYaxis(rymin,rymax,xmin,6,name="syst./cent.");
    yaxis.Draw("SAME");
    
    outdir = out_dir % sample.version
    outdir = "%s/%sPlots_EWK/UncertaintyPlots/"  % (outdir,sample.region)
    if not os.path.isdir(outdir): os.mkdir(outdir)
    
    outname = "%s_%s" % (uncname,sample.varname)
    c.SaveAs( "%s/%s.png" % (outdir,outname) )
    
def plotSRUnc(sample,uncname):
    print 'Fetching %s' % uncname
    sample.addUnc(uncname)
    z_norm = sample.processes['ZJets'].histo
    w_norm = sample.processes['WJets'].histo

    z_up = sample.processes['ZJets'].nuisances[uncname]['Up']
    z_dn = sample.processes['ZJets'].nuisances[uncname]['Down']

    w_up = sample.processes['WJets'].nuisances[uncname]['Up']
    w_dn = sample.processes['WJets'].nuisances[uncname]['Down']

    bins = []
    for w_h in (w_up,w_dn):
        w_h.Divide(w_norm)
        for i,b in enumerate(w_h):
            w_h[i] -= 1
            if w_h[i] != -1: bins.append( w_h[i] )
        w_h.SetLineColor(kBlue)
        w_h.SetLineWidth(2)
    for z_h in (z_up,z_dn):
        z_h.Divide(z_norm)
        for i,b in enumerate(z_h):
            z_h[i] -= 1
            if z_h[i] != -1: bins.append( z_h[i] )
        z_h.SetLineColor(kRed)
        z_h.SetLineWidth(2)

    maxY = max(bins)
    minY = min(bins)
    c = TCanvas(uncname,'',800,800)
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    c.SetLeftMargin(0.15)
    for h in (z_up,z_dn,w_up,w_dn):
        h.GetXaxis().SetTitle(sample.name)
        h.GetYaxis().SetRangeUser(minY*1.2,maxY*1.2)
        h.GetYaxis().SetTitle(uncname)
        h.Draw('hist same')
    
    leg = getLegend(0.62,0.60,0.86,0.887173)
    leg.AddEntry(z_up,'Z+jets','l')
    leg.AddEntry(w_up,'W+jets','l')
    leg.Draw()

    outdir = out_dir % sample.version
    outdir = "%s/SignalRegionPlots_EWK/UncertaintyPlots/"  % outdir
    if not os.path.isdir(outdir): os.mkdir(outdir)
    
    outname = "%s_%s" % (uncname,sample.varname)
    c.SaveAs( "%s/%s.png" % (outdir,outname) )
    
if __name__ == "__main__":
    variable = 'ChNemPtFrac'
    # uncname = 'QCD_Scale'
    
    sample = datamc()
    nvariable = '%s_%s' % (variable, config['regions'][sample.region+'/'])
    variations = []
    for name,unclist in config['Uncertainty'].iteritems(): variations += unclist

    sample.initiate(nvariable)
    if sample.region == 'SignalRegion':
        for uncname in variations: plotSRUnc(sample,uncname)
    else:
        for uncname in variations: plotCRUnc(sample,uncname)
