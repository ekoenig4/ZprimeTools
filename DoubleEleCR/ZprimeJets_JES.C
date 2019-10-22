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

  int lepindex_leadingNorm = lepindex_leading;
  int lepindex_subleadingNorm = lepindex_subleading;
  float dilepton_ptNorm = dilepton_pt;
  float dilepton_massNorm = dilepton_mass;
  float recoilNorm = recoil;
  float recoilPhiNorm = recoilPhi;
  
  
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
    //cout<<"|caloMET-pfMET|/pfMET: "<<metcut<<endl;
    //CR Variables
    lepindex_leading = -1;
    lepindex_subleading = -1;
    dilepton_pt = dilepton_mass = recoil = -99; 
    
    if ((metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData) && inclusiveCut()) { 
      
      if ((HLTEleMuX>>4&1 == 1) || (HLTEleMuX>>38&1 == 1) || (HLTPho >>7&1 ==1) || !sample.isData) {
	
	if(jetCand.size()>0) {
	  //CR code
	  //At least one of the two electrons passes the tight selection
	  vector<int> elelist = electron_veto_looseID(jetCand[0],0,0,10.0);
	  vector<int> elelist_leading = electron_veto_tightID(jetCand[0],40.0);
	  vector<int> elelist_subleading = electron_veto_looseID(jetCand[0],0,0,10.0);
	  
	  if(elelist.size() == 2) {
	    bool elePairSet = false;
	    TLorentzVector e1, e2;
                    
	    for(int i=0; i<elelist_leading.size(); ++i) {
	      for(int j=0; j<elelist_subleading.size(); ++j) {
		//Event must have exactly two loose electrons with opposite charge
		if(eleCharge->at(elelist_leading[i])*eleCharge->at(elelist_subleading[j]) == -1)
		  {
		    e1.SetPtEtaPhiE(elePt->at(elelist_leading[i]),eleSCEta->at(elelist_leading[i]),eleSCPhi->at(elelist_leading[i]),eleEn->at(elelist_leading[i]));
		    e2.SetPtEtaPhiE(elePt->at(elelist_subleading[j]),eleSCEta->at(elelist_subleading[j]),eleSCPhi->at(elelist_subleading[j]),eleEn->at(elelist_subleading[j]));
		    elePairSet = true;
		    lepindex_leading = elelist_leading[i];
		    lepindex_subleading = elelist_subleading[j];
		    break;
		  }
	      }
	      if(elePairSet)
		break;
	    }
                    
	    if(elePairSet) { 
	      TLorentzVector ll = e1+e2;
	      dilepton_mass = ll.M();
	      dilepton_pt = ll.Pt();
                      
	      TLorentzVector met_4vec;
	      met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	      TLorentzVector leptoMET_4vec = ll+met_4vec;
	      recoil = fabs(leptoMET_4vec.Pt());
	      recoilPhi = leptoMET_4vec.Phi();
	      float metcut = (fabs(pfMET-caloMET))/recoil;
	      
	      if (recoil>250) {
		//invariant mass of the two electrons is betwen 60 and 120GeV
		
		if(dilepton_mass > 60 && dilepton_mass < 120) {
		  vector<int> mulist = muon_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,10.0);
		  
		  if(mulist.size() == 0) {
		    
		    if(metcut<0.5) {
		      
		      if(btagVeto()) {
			vector<int> jetveto = JetVetoDecision(lepindex_leading,lepindex_subleading);
			float minDPhiJetMET_first4 = TMath::Pi();
			for (int i = 0; i < jetveto.size(); i++) {
			  float dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
			  if (dPhiJetMet < minDPhiJetMET_first4) {
			    if (i < 4)
			      minDPhiJetMET_first4 = dPhiJetMet;
			  }
			}
			
			if(dPhiJetMETcut(jetveto,recoilPhi)) {
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
      }
    }
  }
    
  jetCand     .clear();
  for (int cand : jetCandNorm) jetCand.push_back(cand);
  AllPFCand(jetCand);
  for (int i = 0; i < jetPtNorm.size(); i++) jetPt->at(i) = jetPtNorm[i];
  pfMET = pfMETNorm;
  pfMETPhi = pfMETPhiNorm;

  lepindex_leading = lepindex_leadingNorm;
  lepindex_subleading = lepindex_subleadingNorm;
  dilepton_pt = dilepton_ptNorm;
  dilepton_mass = dilepton_massNorm;
  recoil = recoilNorm;
  recoilPhi = recoilPhiNorm;
}//Closing the Loop function
