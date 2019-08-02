#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"

void ZprimeJetsClass::JetEnergyScale(int nhist,double start_weight) {
  // 2 Histograms
  //     up  dn
  //jes  0   1
  vector<int> jetCandNorm;
  for(int cand : jetCand) jetCandNorm.push_back(cand);
  vector<double> jetPtNorm;
  for (double pt : (*jetPt)) jetPtNorm.push_back(pt);
  double pfMETNorm = pfMET;
  double pfMETPhiNorm = pfMETPhi;
  
  int unclist[2] = {1,-1};
  for (int unc : unclist) {
    jetCand     .clear();
    j1PFConsEt  .clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    double event_weight = start_weight;
    
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
      
    if ( (metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData) && inclusiveCut() ) { 
	
      if ((HLTJet>>4&1 == 1) || (HLTJet>>5&1 == 1) || (HLTJet>>6&1 == 1) || (HLTJet>>8&1 == 1) || !sample.isData) {//Mono-jet triggers
	  
	if(jetCand.size()>0) {
	    
	  if (pfMET>250) {
	    double metcut = (fabs(pfMET-caloMET))/pfMET;
	      
	    if(metcut<0.5) {
		
	      if(electron_veto_looseID(jetCand[0],10) &&  muon_veto_looseID(jetCand[0],10)) {
		
		if(btagVeto()) {
		  vector<int> jetveto = JetVetoDecision();
		  double minDPhiJetMET_first4 = TMath::Pi();
		  for (int i = 0; i < jetveto.size(); i++) {
		    double dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
		    if (dPhiJetMet < minDPhiJetMET_first4) {
		      if (i < 4)
			minDPhiJetMET_first4 = dPhiJetMet;
		    }
		  }
		    
		  if(dPhiJetMETcut(jetveto)) {
		    if (unc == 1)  fillHistos(nhist,event_weight); //up
		    if (unc == -1) fillHistos(nhist + 1,event_weight);//down
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
