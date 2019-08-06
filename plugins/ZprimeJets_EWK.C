#define ZprimeJetsCommon_cxx
#include "ZprimeJetsCommon.h"

void ZprimeJetsCommon::EWKUncertainty(int nhist, double event_weight) {
  // 2 Histograms
  //         up dn
  // nlo_ewk 0  1
  double nlo_ewk = 0;
  if ( sample.isW_or_ZJet() ) {
    if ( nlo_ewk_hs == NULL) {
      // EWK Uncertainty Files
      if ( sample.type == WJets ) {
	TFile* nlo_ewk_file = TFile::Open("RootFiles/WJets_NLO_EWK.root");
	nlo_ewk_hs = (TH1F*)nlo_ewk_file->Get("evj_pTV_d3kappa_EW");
      }
      else if ( sample.type == DYJets ) {
	TFile* nlo_ewk_file = TFile::Open("RootFiles/DYJets_NLO_EWK.root");
	nlo_ewk_hs = (TH1F*)nlo_ewk_file->Get("eej_pTV_d3kappa_EW");
      }
      else if ( sample.type == ZJets ) {
	TFile* nlo_ewk_file = TFile::Open("RootFiles/ZJets_NLO_EWK.root");
	nlo_ewk_hs = (TH1F*)nlo_ewk_file->Get("vvj_pTV_d3kappa_EW");
      }
    }
    nlo_ewk = nlo_ewk_hs->GetBinContent( nlo_ewk_hs->GetXaxis()->FindBin(bosonPt) );
    h_nlo_ewk->Fill(nlo_ewk);
    // cout << bosonPt << " " << nlo_ewk << endl;
  }
  double weightUp = event_weight*(1+nlo_ewk);
  double weightDn = event_weight*(1-nlo_ewk);
  
  fillHistos(nhist,weightUp); // up
  fillHistos(nhist+1,weightDn); // dn
  
}
