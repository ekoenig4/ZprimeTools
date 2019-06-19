from ROOT import *
from PlotTool.Plot import datamc,GetRatio
from sys import argv,path
import os

gROOT.SetBatch(1)

norm = datamc()
UncertaintyBands= {
'isrRedHi':{id:'_11', eval:'muRfac=0.707'},'fsrRedHi':{id:'_12', eval:'muRfac=0.707'}, 'isrRedLo':{id:'_13', eval:'muRfac=1.414'},'fsrRedLo':{id:'_14', eval:'muRfac=1.414' },
'isrDefHi':{id:'_15', eval:'muRfac=0.5'  },'fsrDefHi':{id:'_16', eval:'muRfac=0.5'  }, 'isrDefLo':{id:'_17', eval:'muRfac=2.0'  },'fsrDefLo':{id:'_18', eval:'muRfac=2.0'   },
'isrConHi':{id:'_19', eval:'muRfac=0.25' },'fsrConHi':{id:'_20',eval:'muRfac=0.25' }, 'isrConLo':{id:'_21',eval:'muRfac=4.0'  },'fsrConLo':{id:'_22',eval:'uRfac=4.0'  },
'fsr_G2GG_muR_dn':{id:'_23',eval:'G2GG:muRfac=0.5'},
'fsr_G2GG_muR_up':{id:'_24',eval:'G2GG:muRfac=2.0'},
'fsr_G2QQ_muR_dn':{id:'_25',eval:'G2QQ:muRfac=0.5'},
'fsr_G2QQ_muR_up':{id:'_26',eval:'G2QQ:muRfac=2.0'},
'fsr_Q2QG_muR_dn':{id:'_27',eval:'Q2QG:muRfac=0.5'},
'fsr_Q2QG_muR_up':{id:'_28',eval:'Q2QG:muRfac=2.0'},
'fsr_X2XG_muR_dn':{id:'_29',eval:'X2XG:muRfac=0.5'},
'fsr_X2XG_muR_up':{id:'_30',eval:'X2XG:muRfac=2.0'},
'fsr_G2GG_cNS_dn':{id:'_31',eval:'G2GG:cNS=-2.0'  },
'fsr_G2GG_cNS_up':{id:'_32',eval:'G2GG:cNS=2.0'   },
'fsr_G2QQ_cNS_dn':{id:'_33',eval:'G2QQ:cNS=-2.0'  },
'fsr_G2QQ_cNS_up':{id:'_34',eval:'G2QQ:cNS=2.0'   },
'fsr_Q2QG_cNS_dn':{id:'_35',eval:'Q2QG:cNS=-2.0'  },
'fsr_Q2QG_cNS_up':{id:'_36',eval:'Q2QG:cNS=2.0'   },
'fsr_X2XG_cNS_dn':{id:'_37',eval:'X2XG:cNS=-2.0'  },
'fsr_X2XG_cNS_up':{id:'_38',eval:'X2XG:cNS=2.0'   },
'isr_G2GG_muR_dn':{id:'_39',eval:'G2GG:muRfac=0.5'},
'isr_G2GG_muR_up':{id:'_40',eval:'G2GG:muRfac=2.0'},
'isr_G2QQ_muR_dn':{id:'_41',eval:'G2QQ:muRfac=0.5'},
'isr_G2QQ_muR_up':{id:'_42',eval:'G2QQ:muRfac=2.0'},
'isr_Q2QG_muR_dn':{id:'_43',eval:'Q2QG:muRfac=0.5'},
'isr_Q2QG_muR_up':{id:'_44',eval:'Q2QG:muRfac=2.0'},
'isr_X2XG_muR_dn':{id:'_45',eval:'X2XG:muRfac=0.5'},
'isr_X2XG_muR_up':{id:'_46',eval:'X2XG:muRfac=2.0'},
'isr_G2GG_cNS_dn':{id:'_47',eval:'G2GG:cNS=-2.0'  },
'isr_G2GG_cNS_up':{id:'_48',eval:'G2GG:cNS=2.0'   },
'isr_G2QQ_cNS_dn':{id:'_49',eval:'G2QQ:cNS=-2.0'  },
'isr_G2QQ_cNS_up':{id:'_50',eval:'G2QQ:cNS=2.0'   },
'isr_Q2QG_cNS_dn':{id:'_51',eval:'Q2QG:cNS=-2.0'  },
'isr_Q2QG_cNS_up':{id:'_52',eval:'Q2QG:cNS=2.0'   },
'isr_X2XG_cNS_dn':{id:'_53',eval:'X2XG:cNS=-2.0'  },
'isr_X2XG_cNS_up':{id:'_54',eval:'X2XG:cNS=2.0'   }}
UncType = ['isrRed','isrDef','isrCon','fsrRed','fsrDef','fsrCon',
           'fsr_G2GG_muR','fsr_G2QQ_muR','fsr_Q2QG_muR','fsr_X2XG_muR',
           'fsr_G2GG_cNS','fsr_G2QQ_cNS','fsr_Q2QG_cNS','fsr_X2XG_cNS',
           'isr_G2GG_muR','isr_G2QQ_muR','isr_Q2QG_muR','isr_X2XG_muR',
           'isr_G2GG_cNS','isr_G2QQ_cNS','isr_Q2QG_cNS','isr_X2XG_cNS']
# UncType = UncType[:6]

for variable in norm.args:
    print "Plotting",variable

    norm.initiate(variable+"_10")

    bkg = norm.getSumOfBkg()
    
    norm.histo['Data'].SetLineWidth(2)
    norm.histo['Data'].SetLineColor(kWhite);
    norm.histo['Data'].SetTitle("");
    norm.histo['Data'].GetXaxis().SetTitle("");
    norm.histo['Data'].GetXaxis().SetTickLength(0);
    norm.histo['Data'].GetXaxis().SetLabelOffset(999);
    norm.histo['Data'].GetYaxis().SetTitle("");
    norm.histo['Data'].GetYaxis().SetTickLength(0);
    norm.histo['Data'].GetYaxis().SetLabelOffset(999);
    norm.histo['Data'].SetLineColor(kBlack);
    norm.histo['Data'].SetMarkerStyle(20);
    norm.histo['Data'].SetMarkerSize(0.9);
    if (norm.options.normalize):norm.histo['Data'].Scale(1/norm.histo['Data'].Integral())

    for mc in norm.MC_Color:
        norm.histo[mc].SetTitle("");
        norm.histo[mc].GetXaxis().SetTitle("");
        norm.histo[mc].GetXaxis().SetTickLength(0);
        norm.histo[mc].GetXaxis().SetLabelOffset(999);
        norm.histo[mc].GetYaxis().SetTitle("");
        norm.histo[mc].GetYaxis().SetTickLength(0);
        norm.histo[mc].GetYaxis().SetLabelOffset(999);
        norm.histo[mc].SetFillColor(norm.MC_Color[mc]);
        if (norm.options.normalize):norm.histo[mc].Scale(1/norm.BkgIntegral)
        

    hs_datamc = THStack("hs_datamc","Data/MC comparison");

    hs_order = {}
    if (norm.name == "Cutflow"):
        if norm.region == "SignalRegion":lastBin = 9
        else:lastBin = 11
        for key in norm.SampleList:
            if not (key == "Data" or key == "Signal"):hs_order[str(norm.histo[key].GetBinContent(lastBin))] = key
    else:
        for key in norm.MC_Integral:hs_order[str(norm.MC_Integral[key])] = key
    keylist = hs_order.keys()
    keylist.sort(key=float)
    for order in keylist:hs_datamc.Add(norm.histo[hs_order[order]])
    hs_datamc.SetTitle("");
    min=pow(10,-6);max=pow(10,2.5);
    hs_datamc.SetMinimum(0.1 if not norm.options.normalize else hs_datamc.GetMaximum()*min);
    hs_datamc.SetMaximum(hs_datamc.GetMaximum()*max);
    ####################################################################################3
    for unc in UncType:
        print unc
        if unc+'Hi' in UncertaintyBands: up,dn = 'Hi','Lo'
        if unc+'_up'in UncertaintyBands: up,dn = '_up','_dn'

        norm.setUnc(variable+UncertaintyBands[unc+up][id],variable+UncertaintyBands[unc+dn][id])
        
        hs_up,hs_dn = norm.getUnc();

        print "Up:",hs_up.Integral()/bkg.Integral(),"|Dn:",hs_dn.Integral()/bkg.Integral()
        
        for i,u in enumerate((hs_up,hs_dn)):
            u.SetLineWidth(2)
            if i == 0: u.SetLineColor(kBlue)
            if i == 1: u.SetLineColor(kRed)
        
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
        
        hs_datamc.Draw("HIST")
        hs_up.Draw("HIST SAME")
        hs_dn.Draw("HIST SAME")
        
        norm.histo['Data'].Draw('pex0same')

        if norm.signal != None:
            norm.histo[norm.signal[0]].SetLineWidth(2)
            norm.histo[norm.signal[0]].Draw("HIST SAME")

        #################################################

        leg = TLegend(0.62,0.60,0.86,0.887173,"");
        leg.AddEntry(norm.histo['Data'],"Data","lp");
        if (norm.signal != None): leg.AddEntry(norm.histo[norm.signal[0]], norm.signal[0])   
        leg.AddEntry(norm.histo['WJets'],"W#rightarrowl#nu","f");
        leg.AddEntry(norm.histo['DYJets'],"Z#rightarrow ll","F"); 
        leg.AddEntry(norm.histo['DiBoson'],"WW/WZ/ZZ","F");
        leg.AddEntry(norm.histo['QCD'], "QCD","F");
        leg.AddEntry(norm.histo['TTJets'], "Top Quark", "F"); 
        leg.AddEntry(norm.histo['GJets'],"#gamma+jets", "F"); 
        leg.AddEntry(norm.histo['ZJets'],"Z#rightarrow#nu#nu","F");
        leg.AddEntry(hs_up,unc+up,"l")
        leg.AddEntry(hs_dn,unc+dn,"l")
        leg.SetFillColor(kWhite);
        leg.SetFillStyle(0);
        leg.SetTextSize(0.025);
        leg.Draw();
        
        lumi_label = '%s' % float('%.3g' % (norm.lumi/1000.)) + " fb^{-1}"
        if (norm.options.normalize): lumi_label="Normalized"
        texS = TLatex(0.20,0.837173,("#sqrt{s} = 13 TeV, "+lumi_label));
        texS.SetNDC();
        texS.SetTextFont(42);
        texS.SetTextSize(0.040);
        texS.Draw();
        texS1 = TLatex(0.12092,0.907173,"#bf{CMS} : #it{Preliminary} ("+norm.version+")");
        texS1.SetNDC();
        texS1.SetTextFont(42);
        texS1.SetTextSize(0.040);
        texS1.Draw();
        
        c.cd();
        pad2 = TPad("pad2","pad2",0.01,0.01,0.99,0.25);
        pad2.Draw(); pad2.cd();
        pad2.SetFillColor(0); pad2.SetFrameBorderMode(0); pad2.SetBorderMode(0);
        pad2.SetTopMargin(0);
        pad2.SetBottomMargin(0.35);
        
        ######################################
        
        Ratio = GetRatio(norm.histo['Data'],hs_datamc.GetStack().Last())
        RatioUp = GetRatio(norm.histo['Data'],hs_up)
        RatioDn = GetRatio(norm.histo['Data'],hs_dn)
        
        rymin = 0.3; rymax = 1.7
        Ratio.GetYaxis().SetRangeUser(rymin,rymax);
        Ratio.SetStats(0);
        Ratio.GetYaxis().CenterTitle();
        Ratio.SetMarkerStyle(20);
        Ratio.SetMarkerSize(0.7);

        for ratio in (RatioUp,RatioDn):
            ratio.GetYaxis().SetRangeUser(rymin,rymax);
            ratio.SetStats(0);
            ratio.GetYaxis().CenterTitle();
        
        line = TLine(hs_datamc.GetXaxis().GetXmin(), 1.,hs_datamc.GetXaxis().GetXmax(), 1.);
        line.SetLineStyle(8);
        
        
        Ratio.Draw("pex0");
        Ratio.GetYaxis().SetLabelSize(0.14);
        Ratio.GetYaxis().SetTitleSize(0.12);
        Ratio.GetYaxis().SetLabelFont(42);
        Ratio.GetYaxis().SetTitleFont(42);
        Ratio.GetYaxis().SetTitleOffset(0.25);
        Ratio.GetYaxis().SetNdivisions(100);
        Ratio.GetYaxis().SetTickLength(0.05);
        
        Ratio.GetXaxis().SetLabelSize(0.15);
        Ratio.GetXaxis().SetTitleSize(0.12);
        Ratio.GetXaxis().SetLabelFont(42);
        Ratio.GetXaxis().SetTitleFont(42);
        Ratio.GetXaxis().SetTitleOffset(0.9);
        Ratio.GetXaxis().SetTickLength(0.05);

        for i,ratio in enumerate((RatioUp,RatioDn)):
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
            if i == 0: ratio.SetLineColor(kBlue)
            if i == 1: ratio.SetLineColor(kRed)
            ratio.Draw("HIST SAME ][")
        
        line.SetLineColor(kBlack);
        line.Draw("same");
        
        c.Update();
        hs_datamc.GetYaxis().SetTitle("Events");
        hs_datamc.GetYaxis().SetTitleOffset(1.5);
        
        ###########################################
        
        nbins = norm.histo['Data'].GetNbinsX();
        xmin = hs_datamc.GetXaxis().GetXmin();
        xmax = hs_datamc.GetXaxis().GetXmax();
        xwmin = xmin;
        xwmax = xmax;
        
        xaxis = TGaxis(xmin,rymin,xmax,rymin,xwmin,xwmax,510);
        xaxis.SetTitle(norm.name);
        xaxis.SetLabelFont(42);
        xaxis.SetLabelSize(0.10);
        xaxis.SetTitleFont(42);
        xaxis.SetTitleSize(0.12);
        xaxis.SetTitleOffset(1.2);
        xaxis.Draw("SAME");
        
        if (norm.name == "Cutflow"):
            xaxis.SetLabelOffset(-999)
            xaxis.SetTitle("");
            label = []
            for i in range(1,nbins+1):
                label.append(TLatex(i-0.5,rymin-0.2,hs_datamc.GetXaxis().GetBinLabel(i)));
	        label[i-1].SetTextSize(0.065);
	        label[i-1].SetTextAngle(-30.);
	        label[i-1].Draw("SAME");
                
        ############################################
        yaxis = TGaxis(xmin,rymin,xmin,rymax,rymin,rymax,6,"");
        yaxis.SetTitle("Data/MC");
        yaxis.SetLabelFont(42);
        yaxis.SetLabelSize(0.10);
        yaxis.SetTitleFont(42);
        yaxis.SetTitleSize(0.12);
        yaxis.SetTitleOffset(0.35);
        yaxis.Draw("SAME");
        
        dir = os.getcwd().split("/")[-1]
        file_path="/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots"+norm.version+"/"+dir+"Plots_EWK/PS_Weights/"
        #print file_path
        sub = variable
        directory=os.path.join(os.path.dirname(file_path),sub)
        if not os.path.exists(directory):
            os.mkdir(directory,0755)
            print directory
        c.SaveAs(directory+"/"+unc+"_"+variable+".pdf")
        c.SaveAs(directory+"/"+unc+"_"+variable+".png")
