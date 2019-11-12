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
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
    h_recoilPhi[i] = new TH1F(("h_recoilPhi"+histname).c_str(), "Recoil #phi",30,-3.1416,3.1416);h_recoilPhi[i] ->Sumw2();
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
float EletriggerSF(float pt, float eta){
  float sf = 1.0;
  if(fabs(eta) >= 0.0   && fabs(eta) < 0.8){
    if(pt < 40.0) sf = 0.75;
    if(pt > 40.0 && pt < 50.0) sf = 0.92;
    if(pt > 50.0 && pt < 60.0) sf = 0.95;
    if(pt > 60.0 && pt < 70.0) sf = 0.96;
    if(pt > 70.0 && pt < 80.0) sf = 0.96;
    if(pt > 80.0 && pt < 90.0) sf = 0.97;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.97;
    if(pt > 150. && pt < 200.) sf = 0.97;
    if(pt > 200. && pt < 250.) sf = 0.98;
    if(pt > 250) sf = 0.93;
  }
  if(fabs(eta) >= 0.8   && fabs(eta) < 1.5){
    if(pt < 40.0) sf = 0.64;
    if(pt > 40.0 && pt < 50.0) sf = 0.91;
    if(pt > 50.0 && pt < 60.0) sf = 0.94;
    if(pt > 60.0 && pt < 70.0) sf = 0.95;
    if(pt > 70.0 && pt < 80.0) sf = 0.95;
    if(pt > 80.0 && pt < 90.0) sf = 0.96;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.96;
    if(pt > 150. && pt < 200.) sf = 0.96;
    if(pt > 200. && pt < 250.) sf = 0.97;
    if(pt > 250) sf = 1.0;
  }
    
  if(fabs(eta) >= 1.5   && fabs(eta) < 2. ) {
    if(pt < 40.0) sf = 0.63;
    if(pt > 40.0 && pt < 50.0) sf = 0.91;
    if(pt > 50.0 && pt < 60.0) sf = 0.94;
    if(pt > 60.0 && pt < 70.0) sf = 0.95;
    if(pt > 70.0 && pt < 80.0) sf = 0.95;
    if(pt > 80.0 && pt < 90.0) sf = 0.95;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.96;
    if(pt > 150. && pt < 200.) sf = 0.99;
    if(pt > 200. && pt < 250.) sf = 0.97;
    if(pt > 250) sf = 1.0;
  }
  if(fabs(eta) >= 2.) {
    if(pt < 40.0) sf = 0.5;
    if(pt > 40.0 && pt < 50.0) sf = 0.83;
    if(pt > 50.0 && pt < 60.0) sf = 0.89;
    if(pt > 60.0 && pt < 70.0) sf = 0.90;
    if(pt > 70.0 && pt < 80.0) sf = 0.92;
    if(pt > 80.0 && pt < 90.0) sf = 0.93;
    if(pt > 90.0 && pt < 100.) sf = 0.94;
    if(pt > 100. && pt < 150.) sf = 0.94;
    if(pt > 150. && pt < 200.) sf = 0.96;
    if(pt > 200. && pt < 250.) sf = 1.0;
    if(pt > 250) sf = 1.0;
  }
  return sf;
}

float ZprimeDoubleCR::getSF(int leading, int subleading) {
  float leading_eta = eleSCEta->at(leading); float leading_pt = elePt->at(leading);
  float subleading_eta = eleSCEta->at(subleading); float subleading_pt = elePt->at(subleading);
  
  float leadingEleRecoSF_corr= th2fmap.getBin("eleRecoSF_highpt",leading_eta,leading_pt);
  float leadingEleEffSF_corr= th2fmap.getBin("eleIDSF_tight",leading_eta,leading_pt);
  float leadingEleTriggSF = EletriggerSF(leading_pt,leading_eta);
  
  float subleadingEleRecoSF_corr= th2fmap.getBin("eleRecoSF_highpt",subleading_eta,subleading_pt);
  float subleadingEleEffSF_corr= th2fmap.getBin("eleIDSF_loose",subleading_eta,subleading_pt);
  float subleadingEleTriggSF = EletriggerSF(subleading_pt,subleading_eta);
  
  return leadingEleRecoSF_corr*leadingEleEffSF_corr*leadingEleTriggSF*subleadingEleRecoSF_corr*subleadingEleEffSF_corr*subleadingEleTriggSF;
}

vector<int> ZprimeDoubleCR::JetVetoDecision(int leading, int subleading) {
  vector<int> jetindex; jetindex.clear();
			  
  vector<int> tmpcands = ZprimeAnalysis::JetVetoDecision();
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
  
  vector<int> tmpcands = ZprimeAnalysis::muon_looseID(jet_index,muPtCut);
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

  vector<int> tmpcands = ZprimeAnalysis::photon_looseID(jet_index,phoPtCut);
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

  vector<int> tmpcands = ZprimeAnalysis::tau_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_leading = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands.size() == 0;
}

#endif