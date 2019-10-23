#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"

void ZprimeJetsClass::JetEnergyScale(float start_weight) {
  // 2 Histograms
  //     up  dn
  //jes  0   1
  string uncname = "JES";
  if ( !shapeUncs->contains(uncname) ) {
    shapeUncs->addUnc(uncname);
    
    initTree(shapeUncs->getTreeUp(uncname));
    initTree(shapeUncs->getTreeDn(uncname));
  }
  
  vector<int> jetCandNorm;
  for(int cand : jetCand) jetCandNorm.push_back(cand);
  vector<float> jetPtNorm;
  for (float pt : (*jetPt)) jetPtNorm.push_back(pt);
  float pfMETNorm = pfMET;
  float pfMETPhiNorm = pfMETPhi;
  
  int unclist[2] = {1,-1};
  for (int unc : unclist) {
    jetCand     .clear();
    j1PFConsEt  .clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    float event_weight = start_weight;
    
    for (int i = 0; i < nJet; i++)
      jetPt->at(i) = jetPtNorm[i]*(1+unc*jetJECUnc->at(i));
    if (unc == 1) {
      pfMET = pfMET_T1JESUp;
      pfMETPhi = pfMETPhi_T1JESUp;
    }
    if (unc == -1) {
      pfMET = pfMET_T1JESDo;
      pfMETPhi = pfMETPhi_T1JESDo;
    }
    
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand);
    
    if (metFilters == 0 && inclusiveCut()) {
      
      if (HLTMet>>7&1 == 1 || HLTMet>>8&1 == 1 || HLTMet>>10&1 == 1 || !sample.isData) {
	
	if (jetCand.size() > 0) {
	  
	  if (pfMET > 250) {
	    float metcut = (fabs(pfMET-caloMET)/pfMET);
	    
	    if (metcut < 0.5) {
	      
	      if (electronVeto(jetCand[0],10.) && muonVeto(jetCand[0],10.) && photonVeto(jetCand[0],15) && tauVeto(jetCand[0],18)) {
		
		if (btagVeto()) {
		  vector<int> jetveto = JetVetoDecision();
		  
		  if (dPhiJetMETcut(jetveto,pfMETPhi)) {
		    weight = event_weight;
		    if (unc == 1)  shapeUncs->fillUp(uncname);// up
		    if (unc == -1) shapeUncs->fillDn(uncname);// down
		  }
		}   
	      }	
	    }
	  }
	}	    
      }
    }
  }

  jetCand     .clear();
  for (int cand : jetCandNorm) jetCand.push_back(cand);
  AllPFCand(jetCand);
  for (int i = 0; i < jetPtNorm.size(); i++) jetPt->at(i) = jetPtNorm[i];
  pfMET = pfMETNorm;
  pfMETPhi = pfMETPhiNorm;
  
}//Closing the Loop function
