from ROOT import *
from Plot import datamc,GetRatio,GetUncBand
from sys import argv,path
import os

gROOT.SetBatch(1)

fsr_color = [40,8]
isr_color = [46,28]

norm = datamc()
UncertaintyBands= {
'isrRedHi':{id:'_13', eval:'muRfac=0.707'},'fsrRedHi':{id:'_14', eval:'muRfac=0.707'}, 'isrRedLo':{id:'_15', eval:'muRfac=1.414'},'fsrRedLo':{id:'_16', eval:'muRfac=1.414' },
'isrDefHi':{id:'_17', eval:'muRfac=0.5'  },'fsrDefHi':{id:'_18', eval:'muRfac=0.5'  }, 'isrDefLo':{id:'_19', eval:'muRfac=2.0'  },'fsrDefLo':{id:'_20', eval:'muRfac=2.0'   },
'isrConHi':{id:'_21', eval:'muRfac=0.25' },'fsrConHi':{id:'_22',eval:'muRfac=0.25' }, 'isrConLo':{id:'_23',eval:'muRfac=4.0'  },'fsrConLo':{id:'_24',eval:'uRfac=4.0'  },
'fsr_G2GG_muR_dn':{id:'_25',eval:'G2GG:muRfac=0.5'},
'fsr_G2GG_muR_up':{id:'_26',eval:'G2GG:muRfac=2.0'},
'fsr_G2QQ_muR_dn':{id:'_27',eval:'G2QQ:muRfac=0.5'},
'fsr_G2QQ_muR_up':{id:'_28',eval:'G2QQ:muRfac=2.0'},
'fsr_Q2QG_muR_dn':{id:'_29',eval:'Q2QG:muRfac=0.5'},
'fsr_Q2QG_muR_up':{id:'_30',eval:'Q2QG:muRfac=2.0'},
'fsr_X2XG_muR_dn':{id:'_31',eval:'X2XG:muRfac=0.5'},
'fsr_X2XG_muR_up':{id:'_32',eval:'X2XG:muRfac=2.0'},
'fsr_G2GG_cNS_dn':{id:'_33',eval:'G2GG:cNS=-2.0'  },
'fsr_G2GG_cNS_up':{id:'_34',eval:'G2GG:cNS=2.0'   },
'fsr_G2QQ_cNS_dn':{id:'_35',eval:'G2QQ:cNS=-2.0'  },
'fsr_G2QQ_cNS_up':{id:'_36',eval:'G2QQ:cNS=2.0'   },
'fsr_Q2QG_cNS_dn':{id:'_37',eval:'Q2QG:cNS=-2.0'  },
'fsr_Q2QG_cNS_up':{id:'_38',eval:'Q2QG:cNS=2.0'   },
'fsr_X2XG_cNS_dn':{id:'_39',eval:'X2XG:cNS=-2.0'  },
'fsr_X2XG_cNS_up':{id:'_40',eval:'X2XG:cNS=2.0'   },
'isr_G2GG_muR_dn':{id:'_41',eval:'G2GG:muRfac=0.5'},
'isr_G2GG_muR_up':{id:'_42',eval:'G2GG:muRfac=2.0'},
'isr_G2QQ_muR_dn':{id:'_43',eval:'G2QQ:muRfac=0.5'},
'isr_G2QQ_muR_up':{id:'_44',eval:'G2QQ:muRfac=2.0'},
'isr_Q2QG_muR_dn':{id:'_45',eval:'Q2QG:muRfac=0.5'},
'isr_Q2QG_muR_up':{id:'_46',eval:'Q2QG:muRfac=2.0'},
'isr_X2XG_muR_dn':{id:'_47',eval:'X2XG:muRfac=0.5'},
'isr_X2XG_muR_up':{id:'_48',eval:'X2XG:muRfac=2.0'},
'isr_G2GG_cNS_dn':{id:'_49',eval:'G2GG:cNS=-2.0'  },
'isr_G2GG_cNS_up':{id:'_50',eval:'G2GG:cNS=2.0'   },
'isr_G2QQ_cNS_dn':{id:'_51',eval:'G2QQ:cNS=-2.0'  },
'isr_G2QQ_cNS_up':{id:'_52',eval:'G2QQ:cNS=2.0'   },
'isr_Q2QG_cNS_dn':{id:'_53',eval:'Q2QG:cNS=-2.0'  },
'isr_Q2QG_cNS_up':{id:'_54',eval:'Q2QG:cNS=2.0'   },
'isr_X2XG_cNS_dn':{id:'_55',eval:'X2XG:cNS=-2.0'  },
'isr_X2XG_cNS_up':{id:'_56',eval:'X2XG:cNS=2.0'   }}
_UncType = ['Red'      ,'Def'      ,'Con','Split']
UncType = []
for unc in _UncType:
    UncType.append(unc)
        
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
        if unc != 'Split':
            up,dn = 'Hi','Lo'
            types = ('',)
            variants = (unc,)
        else:
            up,dn = '_up','_dn'
            types = ('_muR','_cNS')
            variants = ('_G2GG','_G2QQ','_Q2QG')
        unc_up = []
        unc_dn = []
        unc_nm = []
        for i,sr in enumerate(('fsr','isr')):
            unc_up.append([])
            unc_dn.append([])
            for type in types:
                for variant in variants:
                    unc_up[i].append(variable+UncertaintyBands[sr+variant+type+up][id])
                    unc_dn[i].append(variable+UncertaintyBands[sr+variant+type+dn][id])
            unc_nm.append(sr+unc)
        fsr_hs = []; isr_hs = [];
        fsr_up = []; isr_up = [];
        fsr_dn = []; isr_dn = [];
        fsr_nm = []; isr_nm = [];
        for i in range(len(unc_nm)):
            norm.setUnc(unc_up[i],unc_dn[i])
            up,dn = norm.getUnc()
            if i%2 == 0:
                fsr_up.append(up)
                fsr_dn.append(dn)
                fsr_hs.append(GetUncBand(up,dn))
                fsr_nm.append(unc_nm[i])
            else:
                isr_up.append(up)
                isr_dn.append(dn)
                isr_hs.append(GetUncBand(up,dn))
                isr_nm.append(unc_nm[i])

        for i,hs in enumerate(fsr_hs):
            hs.SetFillColor(fsr_color[i])
            hs.SetLineColor(fsr_color[i])
            hs.SetFillStyle(3005)
        for i,hs in enumerate(isr_hs):
            hs.SetFillColor(isr_color[i])
            hs.SetLineColor(isr_color[i])
            hs.SetFillStyle(3004) 
        
        
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
        for hsList in (fsr_hs,isr_hs):
            for hs in hsList:
                hs.Draw("5 SAME")
        
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
        for i,hs in enumerate(fsr_hs): leg.AddEntry(hs,fsr_nm[i],"f")
        for i,hs in enumerate(isr_hs): leg.AddEntry(hs,isr_nm[i],"f")
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
        sumOfBkg = norm.getSumOfBkg()

        fsrBand = []; isrBand = []
        fsrup_ratio = []; isrup_ratio = []
        fsrdn_ratio = []; isrdn_ratio = []
        for i in range(len(fsr_up)):
            ratioFsrUp = GetRatio(fsr_up[i],sumOfBkg)
            ratioFsrDn = GetRatio(fsr_dn[i],sumOfBkg)
            ratioIsrUp = GetRatio(isr_up[i],sumOfBkg)
            ratioIsrDn = GetRatio(isr_dn[i],sumOfBkg)

            fsrBand.append(GetUncBand(ratioFsrUp,ratioFsrDn))
            isrBand.append(GetUncBand(ratioIsrUp,ratioIsrDn))

            fsrup_ratio.append(ratioFsrUp)
            fsrdn_ratio.append(ratioFsrDn)
            isrup_ratio.append(ratioIsrUp)
            isrdn_ratio.append(ratioIsrDn)
            
        
        rymin = 0.3; rymax = 1.7
        Ratio.GetYaxis().SetRangeUser(rymin,rymax)
        Ratio.SetStats(0)
        Ratio.GetYaxis().CenterTitle()
        Ratio.SetMarkerStyle(20);
        Ratio.SetMarkerSize(0.7);

        for i,hs in enumerate(fsrBand):
            hs.SetFillColor(fsr_color[i])
            hs.SetLineColor(fsr_color[i])
            hs.SetFillStyle(3005)
        for i,hs in enumerate(isrBand):
            hs.SetFillColor(isr_color[i])
            hs.SetLineColor(isr_color[i])
            hs.SetFillStyle(3004) 
    
        line = TLine(hs_datamc.GetXaxis().GetXmin(), 1.,hs_datamc.GetXaxis().GetXmax(), 1.);
        line.SetLineStyle(8);
        
        Ratio.Draw("AXIS SAME")

        for rlist in (isrBand,fsrBand):
            for ratio in rlist:
                ratio.GetYaxis().SetLabelSize(0.14);
                ratio.GetYaxis().SetTitleSize(0.12);
                ratio.GetYaxis().SetLabelFont(42);
                ratio.GetYaxis().SetTitleFont(42);
                ratio.GetYaxis().SetTitleOffset(0.25);
                ratio.GetYaxis().SetNdivisions(100);
                ratio.GetYaxis().SetTickLength(0.05);
                
                ratio.GetXaxis().SetLabelSize(0);
                ratio.GetXaxis().SetTitleSize(0);
                ratio.GetXaxis().SetLabelFont(42);
                ratio.GetXaxis().SetTitleFont(42);
                ratio.GetXaxis().SetTitleOffset(999);
                ratio.GetXaxis().SetTickLength(0.05);
                ratio.SetTitle("")
                ratio.Draw("5 SAME")
        
        Ratio.GetYaxis().SetLabelSize(0.14);
        Ratio.GetYaxis().SetTitleSize(0.12);
        Ratio.GetYaxis().SetLabelFont(42);
        Ratio.GetYaxis().SetTitleFont(42);
        Ratio.GetYaxis().SetTitleOffset(0.25);
        Ratio.GetYaxis().SetNdivisions(100);
        Ratio.GetYaxis().SetTickLength(0.05);
        
        Ratio.GetXaxis().SetLabelSize(0);
        Ratio.GetXaxis().SetTitleSize(0);
        Ratio.GetXaxis().SetLabelFont(42);
        Ratio.GetXaxis().SetTitleFont(42);
        Ratio.GetXaxis().SetTitleOffset(999);
        Ratio.GetXaxis().SetTickLength(0.05);
        Ratio.SetTitle("")
        Ratio.Draw("pex0 SAME")
        
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
