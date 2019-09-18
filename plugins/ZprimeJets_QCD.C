#define ZprimeJetsCommon_cxx
#include "ZprimeJetsCommon.h"

void ZprimeJetsCommon::QCDVariations(double event_weight) {
  /* 32 Histograms
     up  dn
     LO           1   2
     K_LO         3   4
     d1K_LO       5   6
     d2K_LO       7   8 
     K_NLO        9  10
     d1K_NLO     11  12
     d2K_NLO     13  14
     d3K_NLO     15  16
     K_NLO_EW    17  18
     K_NNLO_Sud  19  20
     K_EW        21  22
     d1K_EW      23  24
     d2K_EW      25  26
     d3K_EW      27  28
     dK_NLO_mix  29  30 
     gammaind_LO 31  32
  */
  string qcd_uncs[16] = {"LO","K_LO","d1K_LO","d2K_LO","K_NLO","d1K_NLO","d2K_NLO","d3K_NLO","kappa_NLO_EW","kappa_NNLO_Sud","kappa_EW","d1kappa_EW","d2kappa_EW","d3kappa_EW","dK_NLO_mix","gammaind_LO"};
  string uncname = "QCD_";
  // Initializing
  if ( !scaleUncs->contains(uncname+qcd_uncs[0]) ) {
    for (int i = 0; i < 16; i++) {
      string name = uncname + qcd_uncs[i];
      TH1F* histo = NULL;
      if (sample.isW_or_ZJet()) {
	TFile* file = NULL;
	string prefix = "";
	if (sample.type == WJets) {
	  file = TFile::Open("RootFiles/WJets_NLO_EWK.root");
	  prefix = "evj_pTV_";
	} else if (sample.type == ZJets) {
	  file = TFile::Open("RootFiles/ZJets_NLO_EWK.root");
	  prefix = "vvj_pTV_";
	} else if (sample.type == DYJets) {
	  file = TFile::Open("RootFiles/DYJets_NLO_EWK.root");
	  prefix = "eej_pTV_";
	}
	histo = (TH1F*)file->Get( (prefix+qcd_uncs[i]).c_str() );
      }
      scaleUncs->addUnc(name,histo);
    }
  }

  if (sample.isW_or_ZJet()) {
    for (int i = 0; i < 16; i++) {
      string name = uncname + qcd_uncs[i];
      TH1F* histo = scaleUncs->getHisto(name);
      float unc = histo->GetBinContent( histo->GetXaxis()->FindBin(bosonPt) );

      float weightUp = event_weight*(1+unc);
      float weightDn = event_weight*(1-unc);
      scaleUncs->setUnc(name,weightUp,weightDn);
    }
  }
}
