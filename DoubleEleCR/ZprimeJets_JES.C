#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"
void ZprimeJetsClass::JetEnergyScale(int nhist,double start_weight,function<bool()> cut) {
  // 2 Histograms
  //     up  dn
  //jes  0   1
  vector<int> jetCandNorm;
  for(int cand : jetCand) jetCandNorm.push_back(cand);
  vector<double> jetPtNorm;
  for (double pt : (*jetPt)) jetPtNorm.push_back(pt);
  double pfMETNorm = pfMET;
  double pfMETPhiNorm = pfMETPhi;

  int lepindex_leadingNorm = lepindex_leading;
  int lepindex_subleadingNorm = lepindex_subleading;
  double dilepton_ptNorm = dilepton_pt;
  double dilepton_massNorm = dilepton_mass;
  double RecoilNorm = Recoil;
  
  
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
    //cout<<"|caloMET-pfMET|/pfMET: "<<metcut<<endl;
    //CR Variables
    lepindex_leading = -1;
    lepindex_subleading = -1;
    dilepton_pt = dilepton_mass = Recoil = -99; 
    
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
		    e1.SetPtEtaPhiE(elePt->at(elelist_leading[i]),eleEta->at(elelist_leading[i]),elePhi->at(elelist_leading[i]),eleEn->at(elelist_leading[i]));
		    e2.SetPtEtaPhiE(elePt->at(elelist_subleading[j]),eleEta->at(elelist_subleading[j]),elePhi->at(elelist_subleading[j]),eleEn->at(elelist_subleading[j]));
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
	      Double_t leptoMET = fabs(leptoMET_4vec.Pt());
	      Double_t leptoMET_phi = leptoMET_4vec.Phi();
	      Recoil = leptoMET;
	      double metcut = (fabs(pfMET-caloMET))/Recoil;
	      
	      if (leptoMET>250) {
		//invariant mass of the two electrons is betwen 60 and 120GeV
		
		if(dilepton_mass > 60 && dilepton_mass < 120) {
		  vector<int> mulist = muon_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,10.0);
		  
		  if(mulist.size() == 0) {
		    
		    if(metcut<0.5) {
		      
		      if(btagVeto()) {
			vector<int> jetveto = JetVetoDecision(lepindex_leading,lepindex_subleading);
			double minDPhiJetMET_first4 = TMath::Pi();
			for (int i = 0; i < jetveto.size(); i++) {
			  double dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
			  if (dPhiJetMet < minDPhiJetMET_first4) {
			    if (i < 4)
			      minDPhiJetMET_first4 = dPhiJetMet;
			  }
			}
			
			if(dPhiJetMETcut(jetveto)) {
			  if ( cut() ) {
			    if (unc == 1)  fillHistos(nhist,event_weight); // up
			    if (unc == -1) fillHistos(nhist+1,event_weight);// down
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
  Recoil = RecoilNorm;
}//Closing the Loop function
