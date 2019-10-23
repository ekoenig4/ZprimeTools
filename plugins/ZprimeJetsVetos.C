#define ZprimeJetsCommon_cxx
#include "ZprimeJetsCommon.h"


vector<int> ZprimeJetsCommon::electron_veto_tightID(int jet_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();
  for(int i = 0; i < nEle; i++) {
    //Electron passes Tight Electron ID cuts
    if(eleIDbit->at(i)>>2&1 == 1) {
      //Electron passes Eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5) {
	    
	    //Ele DZ and D0 selection
	    if ((fabs(eleSCEta->at(i)) <= 1.479) && (fabs(eleD0->at(i)) < 0.05) && (fabs(eleDz->at(i)) < 0.1 )) {
	      ele_cands.push_back(i);
	    }
	    else if( (fabs(eleSCEta->at(i)) > 1.479) && (fabs(eleD0->at(i)) < 0.1) && (fabs(eleDz->at(i)) < 0.2 )){
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
    if(eleIDbit->at(i)>>0&1 == 1) {
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5) {
	    
	    //Ele DZ and D0 selection
	    if ((fabs(eleSCEta->at(i)) <= 1.479) && (fabs(eleD0->at(i)) < 0.05) && (fabs(eleDz->at(i)) < 0.1 )) {
	      ele_cands.push_back(i);
	    }
	    else if( (fabs(eleSCEta->at(i)) > 1.479) && (fabs(eleD0->at(i)) < 0.1) && (fabs(eleDz->at(i)) < 0.2 )){
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

  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>3&1 == 1 && muIDbit->at(i)>>9&1 == 1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate photon within dR of 0.5
vector<int> ZprimeJetsCommon::muon_veto_looseID(int jet_index, float muPtCut) {
  vector<int> mu_cands;
  mu_cands.clear();
  
  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>0&1==1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //cout <<"Passed Pt Cut" << endl;
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5) {
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
    if ( fabs(phoSCEta->at(i)) < 2.4 ){
      if ( phoEt->at(i) > phoPtCut ) {
	if ( deltaR(phoSCEta->at(i),phoSCPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5 )
	  pho_cands.push_back(i);
      }
    }
  }
  return pho_cands;
}

vector<int> ZprimeJetsCommon::tau_veto_looseID(int jet_index,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  for (int i = 0; i < nTau; i++) {
    if ( tau_IDbits->at(i)>>0&1 == 1 && tau_IDbits->at(i)>>13&1 == 1 ) {
      if ( fabs(tau_Eta->at(i)) < 2.3 ){
	if ( tau_Pt->at(i) > tauPtCut ) {
	  if ( deltaR(tau_Eta->at(i),tau_Phi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5 )
	    tau_cands.push_back(i);
	}
      }
    }
  }
  return tau_cands;
}


vector<int> ZprimeJetsCommon::JetVetoDecision() {
  vector<int> jetindex;
  for(int i = 0; i < nJet; i++){
    bool tightJetID = false;
    bool loosePUID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if((*jetPUFullID)[i]&(1<<2)) loosePUID=true;
    if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID && loosePUID)
      jetindex.push_back(i);
  }
  return jetindex;
}

bool ZprimeJetsCommon::btagVeto() {
  bool btagVeto = true;
  for(int i = 0; i < nJet; i++)
    if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && jetCSV2BJetTags->at(i) > 0.8838)
      btagVeto = false;
  return btagVeto;
}
