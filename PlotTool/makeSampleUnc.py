from ROOT import *
from sys import argv
from PlotTool.Plot import GetRatio
import os

gROOT.SetBatch(1)
gStyle.SetPalette(kVisibleSpectrum)

include = True
label = "separate"

colors = [kTeal,kGreen,kRed,kOrange]

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
UncType = ['Red'      ,'Def'      ,'Con'  ,
           '_G2GG_muR','_G2QQ_muR','_Q2QG_muR','_X2XG_muR',
           '_G2GG_cNS','_G2QQ_cNS','_Q2QG_cNS','_X2XG_cNS']

variables = ["PF123PtFraction","ChNemPtFrac","j1Eta","j1Phi","j1pT","Pt123","j1TotPFCands","j1PID"]
name = ["P^{123}_{T} Fraction","Ch+NEM P^{123}_{T} Fraction","Leading Jet #eta","Leading Jet #phi","Leading Jet P_{T} [GeV]","P^{123}_{T} [GeV]","Leading Jet Total Number of Constituents","Leading Jet Particle ID"]

for file in argv[1:]:
    rfile = TFile.Open(file)
    for n,variable in enumerate(variables):
        norm = rfile.Get(variable+'_10')
        norm.SetMaximum(norm.GetMaximum()*100)

        unc_var = []; unc_nam = []
        for unc in UncType:
            print unc
            if 'fsr'+unc+'Hi' in UncertaintyBands: up,dn = 'Hi','Lo'
            if 'fsr'+unc+'_up'in UncertaintyBands: up,dn = '_up','_dn'
            
            unc_var = [variable+UncertaintyBands['fsr'+unc+up][id],variable+UncertaintyBands['isr'+unc+up][id],
                      variable+UncertaintyBands['fsr'+unc+dn][id],variable+UncertaintyBands['isr'+unc+dn][id]]
            unc_nam = ['fsr'+unc+up,'isr'+unc+up,
                      'fsr'+unc+dn,'isr'+unc+dn]
            # for i in unc_var_tmp: unc_var.append(i)
            # for i in unc_nam_tmp: unc_nam.append(i)
        # unc = 'all'
        # if True:
            for i,uncorrelated in enumerate(unc_var):
                unc_var[i] = rfile.Get(uncorrelated)
            unc_up,unc_dn = norm.Clone(),norm.Clone()
            for ibin in range(1,norm.GetNbinsX() + 1):
                content_up = 0
                content_dn = 0
                for hs in unc_var:
                    diff = norm.GetBinContent(ibin) - hs.GetBinContent(ibin)
                    if diff < 0: content_up += (diff)**2
                    else:        content_dn += (diff)**2
                content_up = norm.GetBinContent(ibin) + content_up**0.5
                content_dn = norm.GetBinContent(ibin) - content_dn**0.5
                unc_up.SetBinContent(ibin,content_up)
                unc_dn.SetBinContent(ibin,content_dn)
                    
        
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

            for hs in (norm,unc_up,unc_dn):
                hs.SetTitle("");
                hs.GetXaxis().SetTickLength(0);
                hs.GetXaxis().SetLabelOffset(999);
                hs.SetFillColor(0)
                hs.SetLineWidth(2)
        
            norm.SetLineColor(kGray+3)
            norm.SetFillColor(kGray)
            # unc_up.SetLineColor(kTeal-1)
            # unc_dn.SetLineColor(kRed)

            norm.Draw("HIST")
            # unc_up.Draw("HIST SAME")
            # unc_dn.Draw("HIST SAME")

            if include:
                for i,hs in enumerate(unc_var):
                    hs.SetTitle("");
                    hs.GetXaxis().SetTickLength(0);
                    hs.GetXaxis().SetLabelOffset(999);
                    hs.SetLineWidth(2)
                    if len(unc_var) <= len(colors):
                        hs.SetLineColor(colors[i])
                        hs.Draw("HIST SAME")
                    else:hs.Draw("HIST SAME PLC")
            
            leg = TLegend(0.62,0.60,0.85,0.887173,"");
            leg.AddEntry(norm,"Nominal","f")
            # leg.AddEntry(unc_up,unc+up,"l")
            # leg.AddEntry(unc_dn,unc+dn,"l")
            if include:
                for i,hs in enumerate(unc_var): leg.AddEntry(hs,unc_nam[i],"l")
            leg.SetFillColor(kWhite);
            leg.SetFillStyle(0);
            leg.SetTextSize(0.025);
            leg.Draw("same")

            texS1 = TLatex(0.12092,0.907173,"#bf{CMS} : #it{Preliminary} (2018)");
            texS1.SetNDC();
            texS1.SetTextFont(42);
            texS1.SetTextSize(0.040);
            texS1.Draw("same");
            ########################################################################
            c.cd();
            pad2 = TPad("pad2","pad2",0.01,0.01,0.99,0.25);
            pad2.Draw(); pad2.cd();
            pad2.SetFillColor(0); pad2.SetFrameBorderMode(0); pad2.SetBorderMode(0);
            pad2.SetTopMargin(0);
            pad2.SetBottomMargin(0.35);

            ratio_ls = []
            # ratio_ls.append(GetRatio(unc_up,norm))
            # ratio_ls.append(GetRatio(unc_dn,norm))
            if include:
                for hs in unc_var: ratio_ls.append(GetRatio(hs,norm))

            rymin = 0.3; rymax = 1.7
            for ratio in ratio_ls:
                ratio.GetYaxis().SetRangeUser(rymin,rymax);
                ratio.SetStats(0);
                ratio.GetYaxis().CenterTitle();
                
            line = TLine(norm.GetXaxis().GetXmin(), 1.,norm.GetXaxis().GetXmax(), 1.);
            line.SetLineStyle(8);
            
            for i,ratio in enumerate(ratio_ls):
                ratio.GetXaxis().SetTitle("")
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
                if len(ratio_ls) <= len(colors):
                    ratio.SetLineColor(colors[i])
                    ratio.Draw("HIST SAME ][")
                else:
                    ratio.Draw("HIST SAME PLC ][")

            line.SetLineColor(kBlack);
            line.Draw("same");
            c.Update()
            ################################################3
            nbins = norm.GetNbinsX();
            xmin = norm.GetXaxis().GetXmin();
            xmax = norm.GetXaxis().GetXmax();
            xwmin = xmin;
            xwmax = xmax;
            
            xaxis = TGaxis(xmin,rymin,xmax,rymin,xwmin,xwmax,510);
            xaxis.SetTitle(name[n]);
            xaxis.SetLabelFont(42);
            xaxis.SetLabelSize(0.10);
            xaxis.SetTitleFont(42);
            xaxis.SetTitleSize(0.12);
            xaxis.SetTitleOffset(1.2);
            xaxis.Draw("SAME");
                    
            ############################################
            yaxis = TGaxis(xmin,rymin,xmin,rymax,rymin,rymax,6,"");
            yaxis.SetTitle("PS/Norm");
            yaxis.SetLabelFont(42);
            yaxis.SetLabelSize(0.10);
            yaxis.SetTitleFont(42);
            yaxis.SetTitleSize(0.12);
            yaxis.SetTitleOffset(0.35);
            yaxis.Draw("SAME");
            
            dir = os.getcwd().split("/")[-1]
            file_path="/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots2018/"+dir+"Plots_EWK/PS_Weights/"+file.replace(".root","/")
            #print file_path
            if not os.path.exists(file_path):
                os.mkdir(file_path,0755)
            file_path += label+"/"
            if not os.path.exists(file_path):
                os.mkdir(file_path,0755)
            sub = variable
            directory=os.path.join(os.path.dirname(file_path),sub)
            if not os.path.exists(directory):
                os.mkdir(directory,0755)
                print directory
            c.SaveAs(directory+"/"+unc+"_"+variable+".pdf")
            c.SaveAs(directory+"/"+unc+"_"+variable+".png")
