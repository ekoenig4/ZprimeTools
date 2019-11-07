#define ZprimeJetsCommon_cxx
#include "ZprimeJetsCommon.h"

vector<int> ZprimeJetsCommon::electron_veto_tightID(int jet_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++) {
    //Electron passes Tight Electron ID cuts
    if(eleIDbit->at(i)>>3&1 == 1) {
      //Electron passes Eta cut
      if (fabs(eleSCEta->at(i)) < eleTightEtaCut) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleSCEta->at(i),eleSCPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso5Cut) {
	    
	    //Ele DZ and D0 selection
	    if ((fabs(eleSCEta->at(i)) <= eleEtaCutLow) && (fabs(eleD0->at(i)) < eleD0CutLow) && (fabs(eleDz->at(i)) < eleDzCutLow )) {
	      ele_cands.push_back(i);
	    }
	    else if( (fabs(eleSCEta->at(i)) > eleEtaCutHigh) && (fabs(eleD0->at(i)) < eleD0CutHigh) && (fabs(eleDz->at(i)) < eleDzCutHigh )){
	      ele_cands.push_back(i);
	    }
	  }
	}
      }
    }
  }
  return ele_cands;
}

vector<int> ZprimeJetsCommon::electron_veto_looseID(int jet_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++) {
    //Electron passes Loose Electron ID cuts
    if(eleIDbit->at(i)>>1&1 == 1) {
      //Electron passes eta cut
      if (fabs(eleSCEta->at(i)) < eleLooseEtaCut) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleSCEta->at(i),eleSCPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso5Cut) {
	    
	    //Ele DZ and D0 selection
	    if ((fabs(eleSCEta->at(i)) <= eleEtaCutLow) && (fabs(eleD0->at(i)) < eleD0CutLow) && (fabs(eleDz->at(i)) < eleDzCutLow )) {
	      ele_cands.push_back(i);
	    }
	    else if( (fabs(eleSCEta->at(i)) > eleEtaCutHigh) && (fabs(eleD0->at(i)) < eleD0CutHigh) && (fabs(eleDz->at(i)) < eleDzCutHigh )){
	      ele_cands.push_back(i);
	    }
	  }
	}
      }
    }
  }
  return ele_cands;
}


vector<int> ZprimeJetsCommon::muon_veto_tightID(int jet_index, float muPtCut) {
  // bool veto_passed = true; //pass veto if no good muon found
  vector<int> mu_cands;
  mu_cands.clear();

  bool pass_PFMuon = true;
  bool pass_globalMuon = true;
  // bool pass_trackerMuon = true;
  bool pass_chi2ndf = false;
  bool pass_chamberHit = false;
  bool pass_matchedStations = false;
  bool pass_dxy = false;
  bool pass_dz = false;
  bool pass_pixelHits = false;
  bool pass_trackLayers = false;
  bool pass_iso = false;
  //Explicitly stating types to avoid a TMath::Max conversion issue
  Float_t zero = 0.0;
  Float_t muPhoPU = 999.9;
  Float_t tightIso_combinedRelative = 999.9;
  for(int i = 0; i < nMu; i++) {
    // pass_globalMuon = muIsGlobalMuon->at(i);
    // pass_PFMuon = muIsPFMuon->at(i);
    // pass_trackerMuon = muIsTrackerMuon->at(i);
    pass_chi2ndf = muChi2NDF->at(i) < 10.0;
    pass_chamberHit = muMuonHits->at(i) > 0;
    pass_matchedStations = muStations->at(i) > 1;
    pass_dxy = fabs(muInnerD0->at(i)) < 0.2;
    pass_dz = fabs(muInnerDz->at(i)) < 0.5;
    pass_pixelHits = muPixelHits->at(i) > 0;
    pass_trackLayers = muTrkLayers->at(i) > 5;

    muPhoPU = muPFNeuIso->at(i) + muPFPhoIso->at(i) - 0.5*muPFPUIso->at(i);
    tightIso_combinedRelative = (muPFChIso->at(i) + TMath::Max(zero,muPhoPU))/(muPt->at(i));
    pass_iso = tightIso_combinedRelative < 0.15;
    //Muon passes Tight Muon ID
    // if(pass_iso && pass_globalMuon && pass_PFMuon && pass_chi2ndf && pass_chamberHit && pass_matchedStations && pass_dxy && pass_dz && pass_pixelHits && pass_trackLayers)
    if(pass_iso && muIDbit->at(i)>>2&1==1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < muTightEtaCut) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso4Cut)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

//For MuonCR
//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate jet within dR of 0.5
vector<int> ZprimeJetsCommon::muon_veto_looseID(int jet_index, float muPtCut)
{
  // cout << "Inside Muon Loose Veto" << endl;
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>0&1==1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < muLooseEtaCut) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //cout <<"Passed Pt Cut" << endl;
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso4Cut) {
	    mu_cands.push_back(i);
	  }
	}
      }
    }
  }
  return mu_cands;
}

vector<int> ZprimeJetsCommon::photon_veto_looseID(int jet_index,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  for (int i = 0; i < nPho; i++) {
    if ( fabs(phoSCEta->at(i)) < phoLooseEtaCut ){
      if ( phoEt->at(i) > phoPtCut ) {
	if ( deltaR(phoSCEta->at(i),phoSCPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso5Cut )
	  pho_cands.push_back(i);
      }
    }
  }
  return pho_cands;
}

vector<int> ZprimeJetsCommon::tau_veto_looseID(int jet_index,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  for (int i = 0; i < nTau; i++) {
    if ( taupfTausDiscriminationByDecayModeFinding->at(i) && tauByVLooseIsolationMVArun2v1DBoldDMwLT->at(i) ) {
      if ( fabs(tauEta->at(i)) < tauLooseEtaCut ){
	if ( tauPt->at(i) > tauPtCut ) {
	  if ( deltaR(tauEta->at(i),tauPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso4Cut )
	    tau_cands.push_back(i);
	}
      }
    }
  }
  return tau_cands;
}


vector<int> ZprimeJetsCommon::JetVetoDecision() {
  vector<int> jetindex; jetindex.clear();
  for(int i = 0; i < nJet; i++) {
    if (jetPt->at(i) > jetVetoPtCut && fabs(jetEta->at(i)) < jetVetoEtaCut && jetPFLooseId->at(i)==1)
      jetindex.push_back(i);
  }
  return jetindex;
}

bool ZprimeJetsCommon::btagVeto() {

  bool btagVeto = true;
  for(int i = 0; i < nJet; i++)
    if(jetPt->at(i) > bjetVetoPtCut && fabs(jetEta->at(i)) < bjetVetoEtaCut && jetCSV2BJetTags->at(i) > bjetVetoCSVv2Cut)
      btagVeto = false;
  return btagVeto;
}
