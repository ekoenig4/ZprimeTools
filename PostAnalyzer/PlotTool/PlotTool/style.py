from ROOT import *

store = []
boundaries = []
def GetUsery(ndcy):
    gPad.Update(); #this is necessary!
    return ndcy*(gPad.GetY2()-gPad.GetY1()) + gPad.GetY1();
def GetUserx(ndcx):
    gPad.Update(); #this is necessary!
    return ndcx*(gPad.GetX2()-gPad.GetX1()) + gPad.GetX1();
def GetNDCy(usery):
    gPad.Update(); #this is necessary!
    return (usery - gPad.GetY1())/(gPad.GetY2()-gPad.GetY1());
def GetNDCx(userx):
    gPad.Update(); #this is necessary!
    return (userx - gPad.GetX1())/(gPad.GetX2()-gPad.GetX1());
class Box:
    def __init__(self,ndcx1,ndcy1,ndcx2,ndcy2):
        self.ndcx1 = ndcx1
        self.ndcx2 = ndcx2
        self.ndcy1 = ndcy1
        self.ndcy2 = ndcy2
    def userx1(self): return GetUserx(self.ndcx1)
    def userx2(self): return GetUserx(self.ndcx2)
    def usery1(self): return pow(10,GetUsery(self.ndcy1))
    def usery2(self): return pow(10,GetUsery(self.ndcy2))

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
    hs_data.SetMarkerSize(1);
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

def getLegend(xmin=0.75,ymin=0.65,xmax=0.95,ymax=0.887173):
    leg = TLegend(xmin,ymin,xmax,ymax,"")
    boundaries.append( Box(xmin,ymin,xmax,ymax) )
    leg.SetFillColor(kWhite);
    leg.SetFillStyle(0);
    leg.SetTextSize(0.025);
    store.append(leg)
    return leg
###################################################################

def getCMSText(lumi,year):
    texS = TLatex(0.62,0.907173,("%s (13 TeV, %s)" % (lumi,year)));#VS
    texS.SetNDC();
    texS.SetTextFont(42);
    texS.SetTextSize(0.040);
    texS.Draw();
    texS1 = TLatex(0.15,0.837173,"#bf{CMS} #it{Preliminary}"); 
    texS1.SetNDC();
    texS1.SetTextFont(42);
    texS1.SetTextSize(0.040);
    texS1.Draw();
    store.append(texS)
    store.append(texS1)
    return texS,texS1
###################################################################

def RatioStyle(ratio,rymin=0.65,rymax=1.35):
    gPad.SetGridy();
    ratio.GetYaxis().SetRangeUser(rymin,rymax);
    ratio.SetStats(0);
    ratio.GetYaxis().CenterTitle();
    ratio.SetMarkerStyle(20);
    ratio.SetMarkerSize(1);
    ratio.GetYaxis().SetLabelSize(0.14);
    ratio.GetYaxis().SetTitleSize(0.12);
    ratio.GetYaxis().SetLabelFont(42);
    ratio.GetYaxis().SetTitleFont(42);
    ratio.GetYaxis().SetTitleOffset(0.25);
    ratio.GetYaxis().SetNdivisions(4);
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
    store.append(line)
    return line
###################################################################

def StackStyle(hs_stack,ymin=None,ymax=None):
    hs_stack.GetYaxis().SetTitle("Events");
    hs_stack.GetYaxis().SetTitleOffset(1.5);
    hs_stack.SetTitle("");
    hs_stack.SetMinimum(0.1)
    def checkbin(x,y,box):
        if x > box.userx1() and x < box.userx2() and y > box.usery1():
            # print '%f < %f < %f && %f > %f' % (box.userx1(),x,box.userx2(),y,box.usery1())
            return y/box.usery1()
        return 1;
    hs = hs_stack
    if type(hs) == THStack: hs = hs.GetStack().Last()
    scale = 1
    ymin = hs.GetMinimum()
    ymax = hs.GetMaximum()
    for box in boundaries:
        for ibin in range(1,hs.GetNbinsX()+1):
            scale = max(scale,checkbin(hs.GetBinCenter(ibin),hs[ibin],box))
    ymax *= scale*pow(10,1.2)
    hs_stack.SetMaximum(ymax)
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
    yaxis.SetNdivisions(4)
    return yaxis
###################################################################
