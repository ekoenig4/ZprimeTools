#!/usr/bin/env python

from ROOT import *
from sys import argv, path
from PlotTool import *
import os

gROOT.SetBatch(1)

# Storage list to be used to keep references around for ROOT before TCanvas is saved
parser.add_argument("--thn",help="specifies that all following plots are TH2 or TH3 plots",action="store_true", default=False)
parser.add_argument("-n","--normalize",help="normalize plots to 1",action="store_true",default=False)
parser.add_argument("--sub",help="specify a sub directory to place output",action="store",type=str,default=None,dest="sub")

def HigherDimension(samples,variable):
    axis = variable[-1]
    samples.initiate(variable[:-1])
    if (axis in ('x','y','z')):
        samples.name = samples.name[axis]
    for name,process in samples.processes.iteritems():
        if axis == "x":
           process.histo = process.histo.ProjectionX()
        if axis == "y":
            process.histo = process.histo.ProjectionY()
        if axis == "z":
            process.histo = process.histo.ProjectionZ()
            
###################################################################

def plotVariable(samples,variable):
    del store[:] # Clear storage list 
    print "Plotting",variable
    if (samples.args.thn):
        HigherDimension(samples,variable)
    else:
        samples.initiate(variable)
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

    data = samples.processes['Data']
    DataStyle(data.histo)
    if (samples.args.normalize): data.histo.Scale(1/data.total)

    for mc in samples.MCList:
        mc_proc = samples.processes[mc]
        MCStyle(mc_proc.histo,mc_proc.color)
        if (samples.args.normalize): mc_proc.histo.Scale(1/samples.BkgIntegral)
        

    hs_datamc = THStack("hs_datamc","Data/MC comparison");
    fillStack(samples,hs_datamc)
    ymin_s=pow(10,-6);ymax_s=pow(10,2.5);
    ymin = 0.1 if not samples.args.normalize else hs_datamc.GetMaximum()*ymin_s
    ymax = hs_datamc.GetMaximum()*ymax_s
    if samples.args.mc_solid:
        hs_bkg = hs_datamc.GetStack().Last()
        hs_bkg.Draw("hist")
        StackStyle(hs_bkg,ymin,ymax)
    else:
        hs_datamc.Draw("hist")
        StackStyle(hs_datamc,ymin,ymax)
        
    data.histo.Draw('pex0same')
    
    if samples.signal != None:
        signal = samples.processes['Signal']
        signal[0].histo.SetLineWidth(2)
        signal[0].histo.Draw("HIST SAME")

    #################################################

    leg = getLegend(); #0.62,0.60,0.86,0.887173
    leg.AddEntry(data.histo,"Data","lp");
    if (samples.signal != None): leg.AddEntry(signal[0].histo, signal[0].name)

    if samples.args.mc_solid:
        leg.AddEntry(hs_bkg,"Background","f")
    else:
        leg.AddEntry(samples.processes['WJets'].histo  ,"W#rightarrowl#nu","f");
        leg.AddEntry(samples.processes['DYJets'].histo ,"Z#rightarrow ll","F"); 
        leg.AddEntry(samples.processes['DiBoson'].histo,"WW/WZ/ZZ","F");
        leg.AddEntry(samples.processes['QCD'].histo    ,"QCD","F");
        leg.AddEntry(samples.processes['TTJets'].histo , "Top Quark", "F"); 
        leg.AddEntry(samples.processes['GJets'].histo  ,"#gamma+jets", "F"); 
        leg.AddEntry(samples.processes['ZJets'].histo  ,"Z#rightarrow#nu#nu","F");
    leg.Draw();

    lumi_label = '%s' % float('%.3g' % (samples.lumi/1000.)) + " fb^{-1}"
    if (samples.args.normalize): lumi_label="Normalized"
    texLumi,texCMS = getCMSText(lumi_label,samples.version)
    texLumi.Draw();
    texCMS.Draw();

    c.cd();
    pad2 = TPad("pad2","pad2",0.01,0.01,0.99,0.25);
    pad2.Draw(); pad2.cd();
    pad2.SetFillColor(0); pad2.SetFrameBorderMode(0); pad2.SetBorderMode(0);
    pad2.SetTopMargin(0);
    pad2.SetBottomMargin(0.35);

    ######################################

    Ratio = GetRatio(data.histo,hs_datamc.GetStack().Last())

    rymin = 0.65; rymax = 1.35
    RatioStyle(Ratio,rymin,rymax)
    Ratio.Draw("pex0");
    
    line = getRatioLine(data.histo.GetXaxis().GetXmin(),data.histo.GetXaxis().GetXmax())
    line.Draw("same");

    c.Update();

    ###########################################

    nbins = data.histo.GetNbinsX();
    xmin = data.histo.GetXaxis().GetXmin();
    xmax = data.histo.GetXaxis().GetXmax();
    xwmin = xmin;
    xwmax = xmax;

    xname = samples.name if type(samples.name) == str else None
    xaxis = makeXaxis(xmin,xmax,rymin,510,name=xname);
    xaxis.Draw("SAME");

    if (samples.name == "Cutflow"): XaxisCutflowStyle(xaxis,hs_datamc)
      

    yaxis = makeYaxis(rymin,rymax,xmin,6,name="Data/MC");
    yaxis.Draw("SAME");

    dir = os.getcwd().split("/")[-1]
    file_path="/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots"+samples.version+"/"+dir+"Plots_EWK/"
    #print file_path
    sub = ""
    if (samples.args.allHisto):sub = "all"
    if (samples.args.sub != None): sub = samples.args.sub
    directory=os.path.join(os.path.dirname(file_path),sub)
    if not os.path.exists(directory):
        os.mkdir(directory,0755)
        print directory
    c.SaveAs(directory+"/datamc_"+samples.varname+".pdf")
    c.SaveAs(directory+"/datamc_"+samples.varname+".png")
###################################################################
    
def plotter(args=[]):
    samples = datamc()
    if not any(args): args = samples.args.argv
    for variable in args:
        plotVariable(samples,variable)
###################################################################
    
  

if __name__ == "__main__":
    plotter()
