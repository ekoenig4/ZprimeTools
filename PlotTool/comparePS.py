from ROOT import *
from Plot import datamc,GetRatio,GetUncBand
from sys import argv,path
import os

gROOT.SetBatch(1)

colors = {'Red':kRed,'Def':kBlue,'Con':kGreen,
           '_G2GG':kCyan,'_G2QQ':kOrange,'_Q2QG':kViolet}

norm = datamc(show=0)
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

fname = "psWeightComparison"

_UncType = ['Red'      ,'Def'      ,'Con',
           '_G2GG','_G2QQ','_Q2QG']
UncType = []
for unc in _UncType[:3]:
    UncType.append(unc)


c = TCanvas("c", "canvas",800,800);
gStyle.SetOptStat(0);
gStyle.SetLegendBorderSize(0);
#c.SetLeftMargin(0.15);
# c.SetLogy();
#c.cd();

histo = {}
label = []
for unc in UncType:
    for sr in ('fsr','isr'):
        if sr+unc+'Hi' in UncertaintyBands:
            up = 'Hi'; dn = 'Lo'
            types = ('',)
        else:
            up = '_up'; dn = '_dn'
            types = ('_muR','_cNS')
        for type in types:
            print sr+unc+type
            var_up = 'psWeight'+str(int(UncertaintyBands[sr+unc+type+up][id].split('_')[1])-11)
            label.append(sr+unc+type+up)
            norm.initiate(var_up)
            histo[sr+unc+type+up] = norm.getSumOfBkg()
            histo[sr+unc+type+up].Scale(1/histo[sr+unc+type+up].Integral())
            var_dn = 'psWeight'+str(int(UncertaintyBands[sr+unc+type+dn][id].split('_')[1])-11)
            label.append(sr+unc+type+dn)
            norm.initiate(var_dn)
            histo[sr+unc+type+dn] = norm.getSumOfBkg()
            histo[sr+unc+type+dn].Scale(1/histo[sr+unc+type+dn].Integral())
            
            print var_up,var_dn
###############################################################################################
leg = TLegend(0.62,0.3,0.86,0.887173,"");
maximum = max(map(lambda hs: histo[hs].GetMaximum(),label))
for unc in label:
    if 'isr' in unc:
        histo[unc].SetFillStyle(3004)
    if 'fsr' in unc:
        histo[unc].SetFillStyle(3005)
    if 'up' in unc or 'Hi' in unc:
        histo[unc].SetLineStyle(1)
    if 'dn' in unc or 'Lo' in unc:
        histo[unc].SetLineStyle(7)
    if 'cNS' in unc:
        histo[unc].SetMarkerStyle(34)
    else:
        histo[unc].SetMarkerStyle(1)
    for sample in colors:
        if sample in unc:
            histo[unc].SetLineColor(colors[sample])
            histo[unc].SetFillColor(colors[sample])
            histo[unc].SetMarkerColor(colors[sample]-3)
    histo[unc].GetXaxis().SetTitle("Weight")
    histo[unc].SetLineWidth(3)
    histo[unc].SetMaximum(maximum*1.1)
    if 'cNS' not in unc: histo[unc].Draw("HIST SAME")
    else: histo[unc].Draw("HIST *H SAME")
    leg.AddEntry(histo[unc],unc,'f')
leg.SetFillColor(kWhite);
leg.SetFillStyle(0);
leg.SetTextSize(0.025);
leg.Draw("same")
###############################################################################################
dir = os.getcwd().split("/")[-1]
file_path="/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots"+norm.version+"/"+dir+"Plots_EWK/PS_Weights/"
#print file_path
sub = ''
directory=os.path.join(os.path.dirname(file_path),sub)
if not os.path.exists(directory):
    os.mkdir(directory,0755)
    print directory
c.SaveAs(directory+"/"+fname+".pdf")
c.SaveAs(directory+"/"+fname+".png")
            
        
