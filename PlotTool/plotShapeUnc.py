from ROOT import *
import os
from optparse import OptionParser
from Plot import GetRatio,GetUncBand
from collections import OrderedDict

gROOT.SetBatch(1)

parser = OptionParser()
parser.add_option("-i","--input",help="Specify an input Systematics file to plot on",action="store",type="str",default=None)

options,args = parser.parse_args()

if options.input == None or not os.path.isfile(options.input):
    print "Please specify an existing systematics file with -i option."
    exit()
#######################################################################
def getXNDC(x): gPad.Update(); return (x - gPad.GetX1())/(gPad.GetX2()-gPad.GetX1());
def getYNDC(y): gPad.Update(); return (y - gPad.GetY1())/(gPad.GetY2()-gPad.GetY1());
#######################################################################
def Metadata(data,rfile):
    lumi = rfile.Get('lumi').GetBinContent(1)
    year = str(int( rfile.Get('year').GetBinContent(1) ))
    type = rfile.Get('variable').GetTitle()
    xaxis = rfile.Get('variable').GetXaxis().GetTitle()
    data['lumi'] = lumi
    data['year'] = year
    data['variable'] = {'type':type,'xaxis':xaxis}
#######################################################################
rfile = TFile.Open(options.input)
rfile.cd('sr')
keys = [ key.GetName().replace('Up','') for key in gDirectory.GetListOfKeys() if 'sumOfBkg' in key.GetName() and 'Down' not in key.GetName() ]
rfile.cd()
data = {}
Metadata(data,rfile)
unclist = []
categories = OrderedDict([ ('sr','Signal Region'),('e','Single Electron'),('m','Single Muon'),('ee','Double Electron'),('mm','Double Muon') ])
for cat in categories:
    histos = {}
    for key in keys:
        if key == 'sumOfBkg':
            norm = rfile.Get(cat+'/'+key).Clone('norm'); norm.SetDirectory(0)
            histos['norm'] = norm
        else:
            unc = key.replace('sumOfBkg_','');
            if unc not in unclist: unclist.append(unc)
            keyup = cat+'/'+key+'Up'
            up = rfile.Get(keyup); up.SetDirectory(0)
            keydn = cat+'/'+key+'Down'
            dn = rfile.Get(keydn); dn.SetDirectory(0)
            up = GetRatio(histos['norm'],up); dn = GetRatio(histos['norm'],dn)
            band = GetUncBand(up,dn)
            histos[unc] = band
    data[cat] = histos
####################################################################################
for unc in unclist:
    print unc
    c = TCanvas('c', "canvas",800,800);
    gStyle.SetOptStat(0);
    gStyle.SetLegendBorderSize(0);
    gStyle.SetTextFont(42)

    store = []
    for i,cat in enumerate(categories):
        c.cd()
        ymax = 0.9-i*0.16;
        if cat != 'mm': ymin = ymax - 0.16
        else: ymin = 0
        scale = 1
        pad = TPad(cat,cat,0.01,ymin,0.99,ymax)
        pad.Draw(); pad.cd();
        pad.SetFillColor(0); pad.SetFrameBorderMode(0); pad.SetBorderMode(0);
        pad.SetTopMargin(0)
        if cat != 'mm': pad.SetBottomMargin(0)
        else: scale=0.16/0.26;pad.SetBottomMargin(1-scale)

        rymin = 0.3; rymax = 1.7
        band = data[cat][unc]
        band.SetTitle('')
        band.GetYaxis().SetRangeUser(rymin,rymax);
        band.SetFillColor(12)
        band.SetLineColor(12)
        band.SetFillStyle(3001)
        band.GetYaxis().SetLabelSize(0.14*scale);
        band.GetYaxis().SetTitleSize(0.12*scale);
        band.GetYaxis().SetTitleOffset(0.25*scale);
        band.GetYaxis().SetNdivisions(5);
        band.GetYaxis().SetTickLength(0.05*scale);
        
        band.GetXaxis().SetLabelSize(0);
        band.GetXaxis().SetTitleSize(0);
        band.GetXaxis().SetTitleOffset(999);
        band.GetXaxis().SetTickLength(0.05*scale);
        band.Draw('A 5')

        title = TPaveText(0.4,getYNDC(rymax-0.3),0.6,getYNDC(rymax-0.1),'ndc')
        title.AddText(categories[cat])
        title.SetFillColor(0);
        title.SetTextSize(0.12*scale)
        title.Draw('same')
        
        xmax = band.GetXaxis().GetXmax()
        xmin = band.GetXaxis().GetXmin()
        
        line = TLine(xmin,1,xmax,1)
        line.SetLineStyle(8);
        line.SetLineColor(kBlack);
        line.Draw('same')

        store.append(pad)
        store.append(title)
        store.append(line)
    ################################################
    xaxis = TGaxis(xmin,rymin,xmax,rymin,xmin,xmax,510);
    xaxis.SetTitle(data['variable']['xaxis'])
    xaxis.SetLabelFont(42)
    xaxis.SetLabelSize(0.15*scale);
    xaxis.SetTitleFont(42)
    xaxis.SetTitleSize(0.15*scale);
    xaxis.SetTitleOffset(1.2);
    xaxis.Draw("SAME");

    c.cd()
    
    lumi_label = '%s' % float('%.3g' % (data['lumi']/1000.)) + " fb^{-1}"
    texS = TLatex(0.12092,0.905,("#sqrt{s} = 13 TeV, "+lumi_label));
    texS.SetNDC();
    texS.SetTextSize(0.030);
    texS.Draw('same');
    texS1 = TLatex(0.12092,0.95,"#bf{CMS} : #it{Preliminary} ("+data['year']+")");
    texS1.SetNDC();
    texS1.SetTextSize(0.030);
    texS1.Draw('same');
    texS2 = TLatex(0.5,0.905, 'SumOfBkg '+unc.upper()+' Uncertainty')
    texS2.SetNDC();
    texS2.SetTextSize(0.030);
    texS2.Draw('same');

    c.SaveAs("~/public_html/MonoZprimeJet/Plots2016/Uncertainty/"+unc.upper()+'_'+data['variable']['type']+'.png')
####################################################
        
