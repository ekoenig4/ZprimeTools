#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"
void ZprimeJetsClass::JetEnergyScale(double start_weight) {
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
  vector<double> jetPtNorm;
  for (double pt : (*jetPt)) jetPtNorm.push_back(pt);
  double pfMETNorm = pfMET;
  double pfMETPhiNorm = pfMETPhi;

  int lepindexNorm = lepindex;
  double recoilNorm = recoil;
  double recoilPhiNorm = recoilPhi;
  
  
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
    recoil=recoilPhi=-99;
    //CR Variables
    lepindex = -1;
    recoil = -99;
    
    if (metFilters == 0 && inclusiveCut()) {
      
      if (HLTMet>>7&1 == 1 || HLTMet>>8&1 == 1 || HLTMet>>10&1 == 1 || !sample.isData) {
	
	if (jetCand.size() > 0) {
	  vector<int> mulist = muon_veto_tightID(jetCand[0],20.0);
	  vector<int> looseMu = muon_veto_looseID(jetCand[0],0,10.);
	  
	  if (mulist.size() ==1 && looseMu.size() == 1) {
	    if (!sample.isData && applySF) {
	      double sf = getSF(mulist[0]);
	      event_weight *= sf;
	    }
	    lepindex = mulist[0];
	    TLorentzVector lep_4vec;
	    lep_4vec.SetPtEtaPhiE(muPt->at(mulist[0]),muEta->at(mulist[0]),muPhi->at(mulist[0]),muE->at(mulist[0]));
	    lepton_pt = lep_4vec.Pt();
	    TLorentzVector met_4vec;
	    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	    TLorentzVector leptoMET_4vec = lep_4vec + met_4vec;
	    double leptoMET = fabs(leptoMET_4vec.Pt());
	    recoilPhi = leptoMET_4vec.Phi();
	    recoil = leptoMET;
	    
	    if (leptoMET > 250) {
	      vector<int> elelist = electron_veto_looseID(jetCand[0],lepindex,10.);
	      
	      if (elelist.size() == 0) {
		float dPhiLepMet = DeltaPhi(muPhi->at(lepindex),pfMETPhi);
		float lepMET_MT = sqrt(2*muPt->at(lepindex)*pfMET*(1-TMath::Cos(dPhiLepMet)));
		
		if (lepMET_MT < 160) {
		  double metcut = (fabs(pfMET - caloMET))/recoil;
		  
		  if (metcut < 0.5) {
		    
		    if (btagVeto()) {
		      vector<int> jetveto = JetVetoDecision(jetCand[0],lepindex);
		      
		      if (dPhiJetMETcut(jetveto,recoilPhi)) {
			
			if (getEleHEMVeto(40)) {
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

  lepindex = lepindexNorm;
  recoil = recoilNorm;
  recoilPhi = recoilPhiNorm;
}//Closing the Loop function
