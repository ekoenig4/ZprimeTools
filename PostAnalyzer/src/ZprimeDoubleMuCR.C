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
    h_leadingLeptonPt[nhist]->Fill(muPt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[nhist]->Fill(muEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[nhist]->Fill(muPhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[nhist]->Fill(muPt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[nhist]->Fill(muEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[nhist]->Fill(muPhi->at(lepindex_subleading),event_weight);    
  }
  if(dilepton_pt >= 0 && dilepton_mass >= 0){  
    h_dileptonPt[nhist]->Fill(dilepton_pt,event_weight);
    h_dileptonM[nhist]->Fill(dilepton_mass,event_weight);
  }
}


bool ZprimeDoubleCR::CRSelection(vector<int> tightlist,vector<int> looselist) {
  float zero = 0.;
  for (int leading : tightlist) {
    for (int subleading : looselist) {
      //Event must have exactly two loose muons with opposite charge
      if (muCharge->at(leading)*muCharge->at(subleading) == -1) {
	float muPhoPU = muPFNeuIso->at(subleading) + muPFPhoIso->at(subleading) - 0.5*muPFPUIso->at(subleading);
	float muIso_combinedRelative = ( muPFChIso->at(subleading) + TMath::Max(zero,muPhoPU) )/muPt->at(subleading);
	  
	lep1.SetPtEtaPhiE(muPt->at(leading),muEta->at(leading),muPhi->at(leading),muE->at(leading));
	lep2.SetPtEtaPhiE(muPt->at(subleading),muEta->at(subleading),muPhi->at(subleading),muE->at(subleading));
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
	
	if ( muIso_combinedRelative < 0.25) 
	  return true;
	return false;
      }
    }
  }
  return false;
}

vector<int> ZprimeDoubleCR::JetVetoDecision(int leading, int subleading) {
  vector<int> jetindex; jetindex.clear();
			  
  vector<int> tmpcands = ZprimeAnalysis::JetVetoDecision();
  for (int ijet : tmpcands) {
    float dR_leading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

bool ZprimeDoubleCR::electron_veto(int jet_index, int leading, int subleading, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  vector<int> tmpcands = electron_looseID(jet_index,elePtCut);
  for(int iele : tmpcands) {
    float dR_leading = deltaR(eleSCEta->at(iele),eleSCPhi->at(iele),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(eleSCEta->at(iele),eleSCPhi->at(iele),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso5Cut && dR_subleading > Iso5Cut )
      ele_cands.push_back(iele);
  }
  
  return ele_cands.size() == 0;
}

bool ZprimeDoubleCR::muon_veto(int jet_index,int leading,int subleading,float muPtCut) {
  return ZprimeAnalysis::muon_veto(jet_index,muPtCut);
}

bool ZprimeDoubleCR::photon_veto(int jet_index,int leading,int subleading,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = photon_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_leading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso5Cut && dR_subleading > Iso5Cut )
      pho_cands.push_back(ipho);
  }
  return pho_cands.size() == 0;
}

bool ZprimeDoubleCR::tau_veto(int jet_index,int leading,int subleading,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = tau_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_leading = deltaR(tauEta->at(itau),tauPhi->at(itau),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(tauEta->at(itau),tauPhi->at(itau),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands.size() == 0;
}

#endif
