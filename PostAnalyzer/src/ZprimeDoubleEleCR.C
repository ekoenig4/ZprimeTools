#ifndef ZprimeDoubleCR_C
#define ZprimeDoubleCR_C

#include "ZprimeDoubleCR.h"
#include "VariableBins.h"
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

void ZprimeDoubleCR::initVars() {
  lepindex_leading = lepindex_subleading = -1;
  dilepton_mass = dilepton_pt = -1;
}

void ZprimeDoubleCR::BookHistos(int i,string histname) {
  if (i == -1) {
    
  } else {
    h_leadingLeptonPt[i] = new TH1F(("h_leadingLeptonPt"+histname).c_str(),"h_leadingLeptonPt",24,LeadingLeptonPtBins);h_leadingLeptonPt[i]->Sumw2();
    h_leadingLeptonEta[i] = new TH1F(("h_leadingLeptonEta"+histname).c_str(),"h_leadingLeptonEta",30,-3.0,3.0);h_leadingLeptonEta[i]->Sumw2();
    h_leadingLeptonPhi[i] = new TH1F(("h_leadingLeptonPhi"+histname).c_str(),"h_leadingLeptonPhi",30,-3.1416,3.1416);h_leadingLeptonPhi[i]->Sumw2();
    h_subleadingLeptonPt[i] = new TH1F(("h_subleadingLeptonPt"+histname).c_str(),"h_subleadingLeptonPt",25,subLeadingLeptonPtBins);h_subleadingLeptonPt[i]->Sumw2();
    h_subleadingLeptonEta[i] = new TH1F(("h_subleadingLeptonEta"+histname).c_str(),"h_subleadingLeptonEta",30,-3.0,3.0);h_subleadingLeptonEta[i]->Sumw2();
    h_subleadingLeptonPhi[i] = new TH1F(("h_subleadingLeptonPhi"+histname).c_str(),"h_subleadingLeptonPhi",30,-3.1416,3.1416);h_subleadingLeptonPhi[i]->Sumw2();
    h_dileptonPt[i] = new TH1F(("h_dileptonPt"+histname).c_str(),"h_dileptonPt",30,0.,1500.);h_dileptonPt[i]->Sumw2();
    h_dileptonM[i] = new TH1F(("h_dileptonM"+histname).c_str(),"h_dileptonM",24,60.,120.);h_dileptonM[i]->Sumw2();
  }
}

void ZprimeDoubleCR::fillHistos(int nhist,float event_weight) {
  if(lepindex_leading >= 0 && lepindex_subleading >= 0){ 
    h_leadingLeptonPt[nhist]->Fill(elePt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[nhist]->Fill(eleEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[nhist]->Fill(elePhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[nhist]->Fill(elePt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[nhist]->Fill(eleEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[nhist]->Fill(elePhi->at(lepindex_subleading),event_weight);    
  }
  if(dilepton_pt >= 0 && dilepton_mass >= 0){  
    h_dileptonPt[nhist]->Fill(dilepton_pt,event_weight);
    h_dileptonM[nhist]->Fill(dilepton_mass,event_weight);
  }
}

bool ZprimeDoubleCR::CRSelection(vector<int> tightlist,vector<int> looselist) {
  for (int leading : tightlist) {
    for (int subleading : looselist) {
      //Event must have exactly two loose electrons with opposite charge
      if (eleCharge->at(leading)*eleCharge->at(subleading) == -1) {
	lep1.SetPtEtaPhiE(elePt->at(leading),eleEta->at(leading),elePhi->at(leading),eleE->at(leading));
	lep2.SetPtEtaPhiE(elePt->at(subleading),eleEta->at(subleading),elePhi->at(subleading),eleE->at(subleading));
	lepindex_leading = leading;
	lepindex_subleading = subleading;
	TLorentzVector ll = lep1 + lep2;
	dilepton_mass = ll.M();
	dilepton_pt = ll.Pt();
	
	TLorentzVector met_4vec;
	met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	TLorentzVector leptoMET_4vec = ll+met_4vec;
	recoil = fabs(leptoMET_4vec.Pt());
	recoilPhi = leptoMET_4vec.Phi();
	return true;
      }
    }
  }
  return false;
}

float ZprimeDoubleCR::getSF(int leading, int subleading) {
  float leading_eta = eleSCEta->at(leading); float leading_pt = elePt->at(leading);
  float subleading_eta = eleSCEta->at(subleading); float subleading_pt = elePt->at(subleading);
  
  float leadingEleRecoSF_corr= th2fmap.getBin("eleRecoSF_highpt",leading_eta,leading_pt);
  float leadingEleEffSF_corr= th2fmap.getBin("eleIDSF_tight",leading_eta,leading_pt);
  float leadingEleTriggSF = th2fmap.getBin("eleTriggSF",fabs(leading_eta),leading_pt);
  
  float subleadingEleRecoSF_corr= th2fmap.getBin("eleRecoSF_highpt",subleading_eta,subleading_pt);
  float subleadingEleEffSF_corr= th2fmap.getBin("eleIDSF_loose",subleading_eta,subleading_pt);
  float subleadingEleTriggSF = th2fmap.getBin("eleTriggSF",fabs(subleading_eta),subleading_pt);
  
  return leadingEleRecoSF_corr*leadingEleEffSF_corr*leadingEleTriggSF*subleadingEleRecoSF_corr*subleadingEleEffSF_corr*subleadingEleTriggSF;
}

vector<int> ZprimeDoubleCR::jet_veto(int leading, int subleading) {
  vector<int> jetindex; jetindex.clear();
			  
  vector<int> tmpcands = jet_looseID();
  for (int ijet : tmpcands) {
    float dR_leading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

bool ZprimeDoubleCR::electron_veto(int jet_index,int leading,int subleading,float elePtCut) {
  return ZprimeAnalysis::electron_veto(jet_index,elePtCut);
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate electrons and jet within dR of 0.5
bool ZprimeDoubleCR::muon_veto(int jet_index, int leading, int subleading, float muPtCut) {
  vector<int> mu_cands;
  mu_cands.clear();
  
  vector<int> tmpcands = muon_looseID(jet_index,muPtCut);
  for(int imu : tmpcands) {
    float dR_leading = deltaR(muEta->at(imu),muPhi->at(imu),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(muEta->at(imu),muPhi->at(imu),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut)
      mu_cands.push_back(imu);
  }
  
  return mu_cands.size() == 0;
}

bool ZprimeDoubleCR::photon_veto(int jet_index,int leading,int subleading,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = photon_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_leading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso5Cut && dR_subleading > Iso5Cut )
      pho_cands.push_back(ipho);
  }
  return pho_cands.size() == 0;
}

bool ZprimeDoubleCR::tau_veto(int jet_index,int leading,int subleading,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = tau_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_leading = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands.size() == 0;
}

bool ZprimeDoubleCR::bjet_veto(int leading,int subleading) {
  vector<int> bjet_cands; bjet_cands.clear();

  vector<int> tmpcands = bjet_looseID();
  for (int ijet : tmpcands) {
    float dR_leading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      bjet_cands.push_back(ijet);
  }
  return bjet_cands.size() == 0;
}

#endif
