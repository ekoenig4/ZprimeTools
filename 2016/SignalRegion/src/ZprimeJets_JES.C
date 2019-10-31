#define ZprimeYear_cxx
#include "ZprimeClass.h"

void ZprimeClass::JetEnergyScale(float start_weight) {
  // 2 Histograms
  //     up  dn
  //jes  0   1
  string uncname = "JES";
  if ( !shapeUncs.contains(uncname) ) {
    shapeUncs.addUnc(uncname);
    
    initTree(shapeUncs.getTreeUp(uncname));
    initTree(shapeUncs.getTreeDn(uncname));
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
    
    jetCand = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
    SetJetPFInfo(jetCand);
      
    if ( (metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData) && inclusiveCut() ) { 
	
      if ((HLTJet>>4&1 == 1) || (HLTJet>>5&1 == 1) || (HLTJet>>6&1 == 1) || (HLTJet>>8&1 == 1) || !sample.isData) {//Mono-jet triggers
	  
	if(jetCand.size()>0) {
	    
	  if (pfMET > recoilCut) {
	    float metcut = (fabs(pfMET-caloMET))/pfMET;
	      
	    if(metcut < metRatioCut) {

	      bool noLeptonID = electronVeto(jetCand[0],eleLoosePtCut) && muonVeto(jetCand[0],muLoosePtCut) && photonVeto(jetCand[0],phoLoosePtCut);
	      if( noLeptonID ) {
		
		if(btagVeto()) {
		  vector<int> jetveto = JetVetoDecision();
		  float minDPhiJetMET_first4 = TMath::Pi();
		  for (int i = 0; i < jetveto.size(); i++) {
		    float dPhiJetMet = deltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
		    if (dPhiJetMet < minDPhiJetMET_first4) {
		      if (i < 4)
			minDPhiJetMET_first4 = dPhiJetMet;
		    }
		  }
		    
		  if(dPhiJetMET(jetveto,pfMET)) {
		    weight = event_weight;
		    if (unc == 1)  shapeUncs.fillUp(uncname);// up
		    if (unc == -1) shapeUncs.fillDn(uncname);// down
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
  SetJetPFInfo(jetCand);
  for (int i = 0; i < jetPtNorm.size(); i++) jetPt->at(i) = jetPtNorm[i];
  pfMET = pfMETNorm;
  pfMETPhi = pfMETPhiNorm;
  
}//Closing the Loop function
