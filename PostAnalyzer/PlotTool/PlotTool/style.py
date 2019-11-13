from ROOT import *

store = []

def DataStyle(hs_data):
    hs_data.SetLineWidth(2)
    hs_data.SetLineColor(kWhite);
    hs_data.SetTitle("");
    hs_data.GetXaxis().SetTitle("");
    hs_data.GetXaxis().SetTickLength(0);
    hs_data.GetXaxis().SetLabelOffset(999);
    hs_data.GetYaxis().SetTitle("");
    hs_data.GetYaxis().SetTickLength(0);
    hs_data.GetYaxis().SetLabelOffset(999);
    hs_data.SetLineColor(kBlack);
    hs_data.SetMarkerStyle(20);
    hs_data.SetMarkerSize(0.9);
###################################################################
    
def MCStyle(hs_mc,color):
    hs_mc.SetTitle("");
    hs_mc.GetXaxis().SetTitle("");
    hs_mc.GetXaxis().SetTickLength(0);
    hs_mc.GetXaxis().SetLabelOffset(999);
    # hs_mc.GetYaxis().SetTitle("");
    # hs_mc.GetYaxis().SetTickLength(0);
    # hs_mc.GetYaxis().SetLabelOffset(999);
    hs_mc.SetFillColor(color);
###################################################################

def fillStack(samples,hs_datamc):
    order = [ process for name,process in samples.processes.iteritems() if process.proctype == 'bkg' ]
    if (samples.name == "Cutflow"):
        nbin = samples.processes['Data'].histo.GetNbinsX()
        order.sort(key=lambda process: process.histo.GetBinContent(nbin))
    else: order.sort(key=lambda process: process.scaled_total)
    for process in order: hs_datamc.Add(process.histo)
###################################################################

def getLegend(xmin,ymin,xmax,ymax):
    leg = TLegend(xmin,ymin,xmax,ymax,"")
    leg.SetFillColor(kWhite);
    leg.SetFillStyle(0);
    leg.SetTextSize(0.025);
    return leg
###################################################################

def getCMSText(lumi,year):
    texS = TLatex(0.20,0.837173,("#sqrt{s} = 13 TeV, "+lumi));
    texS.SetNDC();
    texS.SetTextFont(42);
    texS.SetTextSize(0.040);
    texS.Draw();
    texS1 = TLatex(0.12092,0.907173,"#bf{CMS} : #it{Preliminary} ("+year+")");
    texS1.SetNDC();
    texS1.SetTextFont(42);
    texS1.SetTextSize(0.040);
    texS1.Draw();
    return texS,texS1
###################################################################

def RatioStyle(ratio,rymin,rymax):
    ratio.GetYaxis().SetRangeUser(rymin,rymax);
    ratio.SetStats(0);
    ratio.GetYaxis().CenterTitle();
    ratio.SetMarkerStyle(20);
    ratio.SetMarkerSize(0.7);
    ratio.GetYaxis().SetLabelSize(0.14);
    ratio.GetYaxis().SetTitleSize(0.12);
    ratio.GetYaxis().SetLabelFont(42);
    ratio.GetYaxis().SetTitleFont(42);
    ratio.GetYaxis().SetTitleOffset(0.25);
    ratio.GetYaxis().SetNdivisions(100);
    ratio.GetYaxis().SetTickLength(0.05);
    
    ratio.GetXaxis().SetLabelSize(0.15);
    ratio.GetXaxis().SetTitleSize(0.12);
    ratio.GetXaxis().SetLabelFont(42);
    ratio.GetXaxis().SetTitleFont(42);
    ratio.GetXaxis().SetTitleOffset(0.9);
    ratio.GetXaxis().SetTickLength(0.05);
###################################################################

def getRatioLine(xmin,xmax):
    line = TLine(xmin, 1.,xmax, 1.);
    line.SetLineStyle(8);
    line.SetLineColor(kBlack);
    return line
###################################################################

def StackStyle(hs_stack,ymin,ymax):
    hs_stack.SetMinimum(ymin);
    hs_stack.SetMaximum(ymax);
    hs_stack.GetYaxis().SetTitle("Events");
    hs_stack.GetYaxis().SetTitleOffset(1.5);
    hs_stack.SetTitle("");
###################################################################

def makeXaxis(xmin,xmax,ymin,ndiv,name=None):
    xaxis = TGaxis(xmin,ymin,xmax,ymin,xmin,xmax,ndiv);
    if name != None: xaxis.SetTitle(name);
    xaxis.SetLabelFont(42);
    xaxis.SetLabelSize(0.10);
    xaxis.SetTitleFont(42);
    xaxis.SetTitleSize(0.12);
    xaxis.SetTitleOffset(1.2);
    return xaxis
###################################################################

def XaxisCutflowStyle(xaxis,hs):
    xaxis.SetLabelOffset(-999)
    xaxis.SetTitle("");
    for i in range(1,hs.GetXaxis().GetNbins()+1):
        label = TLatex(i-0.5,xaxis.GetY1()-0.2,hs.GetXaxis().GetBinLabel(i));
	label.SetTextSize(0.065);
	label.SetTextAngle(-30.);
	label.Draw("SAME");
        store.append(label)
###################################################################

def makeYaxis(ymin,ymax,xmin,ndiv,name=None):
    if name == None: name == 'YAxis'
    yaxis = TGaxis(xmin,ymin,xmin,ymax,ymin,ymax,ndiv,"");
    yaxis.SetTitle(name);
    yaxis.SetLabelFont(42);
    yaxis.SetLabelSize(0.10);
    yaxis.SetTitleFont(42);
    yaxis.SetTitleSize(0.12);
    yaxis.SetTitleOffset(0.35);
    return yaxis
###################################################################
