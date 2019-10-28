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

  int lepindexNorm = lepindex;
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
    
    jetCand = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
    AllPFCand(jetCand);
    recoil=recoilPhi=-99;
    //CR Variables
    lepindex = -1;
    recoil = -99;
    
    if (metFilters == 0 && inclusiveCut()) {
      
      if (HLTEleMuX>>5&1 == 1 || HLTEleMuX>>6&1 == 1 || HLTPho>>11&1 == 1 || !sample.isData) {
	
	if (jetCand.size() > 0) {
	  vector<int> elelist = electron_veto_tightID(jetCand[0],eleTightPtCut);
	  vector<int> looseEle = electron_veto_looseID(jetCand[0],eleLoosePtCut);
	  
	  if (elelist.size() ==1 && looseEle.size() == 1) {
	    lepindex = elelist[0];
	    if (!sample.isData) {
	      float sf = getSF(elelist[0]);
	      event_weight *= sf;
	    }
	    TLorentzVector lep_4vec;
	    lep_4vec.SetPtEtaPhiE(elePt->at(lepindex),eleEta->at(lepindex),elePhi->at(lepindex),eleE->at(lepindex));
	    lepton_pt = lep_4vec.Pt();
	    TLorentzVector met_4vec;
	    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	    TLorentzVector leptoMET_4vec = lep_4vec + met_4vec;
	    float leptoMET = fabs(leptoMET_4vec.Pt());
	    recoilPhi = leptoMET_4vec.Phi();
	    recoil = leptoMET;
	    
	    if (leptoMET > recoilCut) {
	      vector<int> mulist = muon_veto_looseID(jetCand[0],lepindex,muLoosePtCut);
	      vector<int> pholist = photon_veto_looseID(jetCand[0],lepindex,phoLoosePtCut);
	      vector<int> taulist = tau_veto_looseID(jetCand[0],lepindex,tauLoosePtCut);
	      
	      if (mulist.size() == 0 && pholist.size() == 0 && taulist.size() == 0) {
		float dPhiLepMet = DeltaPhi(elePhi->at(lepindex),pfMETPhi);
		float lepMET_MT = sqrt(2*elePt->at(lepindex)*pfMET*(1-TMath::Cos(dPhiLepMet)));
		
		if (pfMET > pfMET50Cut) {
		  float metcut = (fabs(pfMET-caloMET))/recoil;
		  
		  if (metcut < metRatioCut) {
		    
		    if (btagVeto()) {
		      vector<int> jetveto = JetVetoDecision(jetCand[0],lepindex);
		      
		      if (dPhiJetMETcut(jetveto,recoilPhi)) {
			
			if (getEleHEMVeto(eleHEMVetoPtCut)) {
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

  lepindex = lepindex;
  recoil = recoilNorm;
  recoilPhi = recoilPhiNorm;
}//Closing the Loop function
