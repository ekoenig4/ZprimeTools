#ifndef ZprimeSingleCR_C
#define ZprimeSingleCR_C

#include "ZprimeSingleCR.h"
#include "VariableBins.h"

void ZprimeSingleCR::BookHistos(int i,string histname) {
  if (i == -1) {
    
  } else {
    h_LeptonPt[i] = new TH1F(("h_LeptonPt"+histname).c_str(),"h_LeptonPt",24,LeptonPtBins);h_LeptonPt[i]->Sumw2();
    h_LeptonEta[i] = new TH1F(("h_LeptonEta"+histname).c_str(),"h_LeptonEta",30,-3.0,3.0);h_LeptonEta[i]->Sumw2();
    h_LeptonPhi[i] = new TH1F(("h_LeptonPhi"+histname).c_str(),"h_LeptonPhi",30,-3.1416,3.1416);h_LeptonPhi[i]->Sumw2();
  }
}

void ZprimeSingleCR::fillHistos(int nhist,float event_weight) {
  //CR Histograms
  if(lepindex >= 0){ 
    h_LeptonPt[nhist]->Fill(muPt->at(lepindex),event_weight);
    h_LeptonEta[nhist]->Fill(muEta->at(lepindex),event_weight);
    h_LeptonPhi[nhist]->Fill(muPhi->at(lepindex),event_weight);
  }
}

vector<int> ZprimeSingleCR::JetVetoDecision(int lepindex) {
  vector<int> jetindex; jetindex.clear();

  vector<int> tmpcands = ZprimeAnalysis::JetVetoDecision();
  for(int ijet : tmpcands ) {
    float dR_mu = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(lepindex),muPhi->at(lepindex));
    if( dR_mu > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

vector<int> ZprimeSingleCR::electron_veto_looseID(int jet_index, int lepindex, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  vector<int> tmpcands = ZprimeAnalysis::electron_veto_looseID(jet_index,elePtCut);
  for(int iele : tmpcands) {
    float dR_mu = deltaR(eleSCEta->at(iele),eleSCPhi->at(iele),muEta->at(lepindex),muPhi->at(lepindex));
    if ( dR_mu > Iso5Cut )
      ele_cands.push_back(iele);
  }
  
  return ele_cands;
}

vector<int> ZprimeSingleCR::photon_veto_looseID(int jet_index,int lepindex,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = ZprimeAnalysis::photon_veto_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_mu = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),muEta->at(lepindex),muPhi->at(lepindex));
    if ( dR_mu > Iso5Cut )
      pho_cands.push_back(ipho);
  }
  return pho_cands;
}

vector<int> ZprimeSingleCR::tau_veto_looseID(int jet_index,int lepindex,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = ZprimeAnalysis::tau_veto_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_mu = deltaR(tauEta->at(itau),tauPhi->at(itau),muEta->at(lepindex),muPhi->at(lepindex));
    if ( dR_mu > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands;
}
#endif
