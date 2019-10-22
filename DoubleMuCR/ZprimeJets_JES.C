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
      
      if ((HLTJet>>4&1 == 1) || (HLTJet>>5&1 == 1) || (HLTJet>>6&1 == 1) || (HLTJet>>8&1 == 1) || !sample.isData ) {
	
	if(jetCand.size()>0) {
	  //CR code
	  //At least one of the two muons passes the tight selection
	  vector<int> mulist_leading = muon_veto_tightID(jetCand[0],20.0);
	  vector<int> mulist_subleading = muon_veto_looseID(jetCand[0],10.0);
	  if(mulist_subleading.size() == 2) {
	    bool muPairSet = false;
	    bool subleading_passes_looseIso = false;
	    TLorentzVector m1, m2;
	    for(int i=0; i<mulist_leading.size(); ++i) {
	      for(int j=0; j<mulist_subleading.size(); ++j) {
		//Event must have exactly two loose muons with opposite charge
		if(muCharge->at(mulist_leading[i])*muCharge->at(mulist_subleading[j]) == -1) {
		  m1.SetPtEtaPhiE(muPt->at(mulist_leading[i]),muEta->at(mulist_leading[i]),muPhi->at(mulist_leading[i]),muEn->at(mulist_leading[i]));
		  m2.SetPtEtaPhiE(muPt->at(mulist_subleading[j]),muEta->at(mulist_subleading[j]),muPhi->at(mulist_subleading[j]),muEn->at(mulist_subleading[j]));
		  muPairSet = true;
		  lepindex_leading = mulist_leading[i];
		  lepindex_subleading = mulist_subleading[j];
		  Float_t zero = 0.0;
		  Float_t muPhoPU = muPFNeuIso->at(lepindex_subleading) + muPFPhoIso->at(lepindex_subleading) - 0.5*muPFPUIso->at(lepindex_subleading);
		  Float_t muIso_combinedRelative = (muPFChIso->at(lepindex_subleading) + TMath::Max(zero,muPhoPU))/(muPt->at(lepindex_subleading));
		  subleading_passes_looseIso = muIso_combinedRelative < 0.25;
		  break;
		}
	      }
	      if(muPairSet)
		break;
	    }
		    
	    if(muPairSet && subleading_passes_looseIso) { 
	      TLorentzVector ll = m1 + m2;
	      dilepton_mass = ll.M();
	      dilepton_pt = ll.Pt();
			
	      TLorentzVector met_4vec;
	      met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	      TLorentzVector leptoMET_4vec = ll+met_4vec;
	      recoil = leptoMET_4vec.Pt();
	      recoilPhi = leptoMET_4vec.Phi();
	      
	      if (recoil>250) {
		//invariant mass of the two muons is betwen 60 and 120GeV
		
		if(dilepton_mass > 60 && dilepton_mass < 120) {
		  vector<int> elelist = electron_veto_looseID(jetCand[0],lepindex_subleading,lepindex_subleading,10.0);
		  vector<int> pholist = photon_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,15);
		  vector<int> taulist = tau_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,18);
		  
		  if(elelist.size() == 0 && pholist.size() == 0 && taulist.size() == 0) {
		    float metcut = (fabs(pfMET-caloMET))/recoil;
		    
		    if(metcut<0.5) {
		      
		      if(btagVeto()) {
			vector<int> jetveto = JetVetoDecision(lepindex_leading,lepindex_subleading);
			
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
