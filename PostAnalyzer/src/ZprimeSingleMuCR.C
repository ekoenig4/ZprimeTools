#ifndef ZprimeSingleCR_C
#define ZprimeSingleCR_C

#include "ZprimeSingleCR.h"
#include "VariableBins.h"
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

const string ZprimeSingleCR::REGION = "SingleMuCR";

void ZprimeSingleCR::initVars() {
  lepindex = lepton_pt = -1;
}

void ZprimeSingleCR::BookHistos(int i,string histname) {
  if (i == -1) {
    h_lepMET_MT = new TH1F("h_lepMET_MT","h_lepMET_MT; transverse mass of the lepton-Emiss system",40,0,400);h_lepMET_MT->Sumw2();
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

bool ZprimeSingleCR::CRSelection(vector<int> tight,vector<int> loose) {
  if (tight.size() == 1 && loose.size() == 1) {
    lepindex = tight[0];
    
    lep.SetPtEtaPhiE(muPt->at(lepindex),muEta->at(lepindex),muPhi->at(lepindex),muE->at(lepindex));

    lepton_pt = lep.Pt(); 
    TLorentzVector met_4vec;
    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
    TLorentzVector leptoMET_4vec = lep+met_4vec;
    recoil = fabs(leptoMET_4vec.Pt());
    recoilPhi = leptoMET_4vec.Phi();
    return true;
  }
  return false;
}

float ZprimeSingleCR::getSF(int lepindex) {
  float eta = muEta->at(lepindex);
  float pt = muPt->at(lepindex);

  float tightMuISO_SF_corr;
  float tightMuID_SF_corr;
    
  if ( th2fmap.contains("tightMuSF_ISO_abseta") ) {
    // Use abseta instead of eta
    tightMuISO_SF_corr = th2fmap.getBin("tightMuSF_ISO_abseta",pt,fabs(eta));
    tightMuID_SF_corr = th2fmap.getBin("tightMuSF_ID_abseta",pt,fabs(eta));
  } else {
    // Use eta
    tightMuISO_SF_corr = th2fmap.getBin("tightMuSF_ISO",pt,eta);
    tightMuID_SF_corr = th2fmap.getBin("tightMuSF_ID",pt,eta);
  }
  
  
  return tightMuISO_SF_corr*tightMuID_SF_corr;
}

vector<int> ZprimeSingleCR::jet_veto(int lepindex) {
  vector<int> jetindex; jetindex.clear();

  vector<int> tmpcands = ZprimeAnalysis::jet_looseID();
  for(int ijet : tmpcands ) {
    float dR_mu = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(lepindex),muPhi->at(lepindex));
    if( dR_mu > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

bool ZprimeSingleCR::electron_veto(int jet_index, int lepindex, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  vector<int> tmpcands = electron_looseID(jet_index,elePtCut);
  for(int iele : tmpcands) {
    float dR_mu = deltaR(eleSCEta->at(iele),eleSCPhi->at(iele),muEta->at(lepindex),muPhi->at(lepindex));
    if ( dR_mu > Iso5Cut )
      ele_cands.push_back(iele);
  }
  
  return ele_cands.size() == 0;
}

bool ZprimeSingleCR::muon_veto(int jet_index,int lepindex,float muPtCut) {
  return ZprimeAnalysis::muon_veto(jet_index,muPtCut);
}

bool ZprimeSingleCR::photon_veto(int jet_index,int lepindex,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = photon_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_mu = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),muEta->at(lepindex),muPhi->at(lepindex));
    if ( dR_mu > Iso5Cut )
      pho_cands.push_back(ipho);
  }
  return pho_cands.size() == 0;
}

bool ZprimeSingleCR::tau_veto(int jet_index,int lepindex,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = tau_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_mu = deltaR(tauEta->at(itau),tauPhi->at(itau),muEta->at(lepindex),muPhi->at(lepindex));
    if ( dR_mu > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands.size() == 0;
}

bool ZprimeSingleCR::bjet_veto(int lepindex) {
  vector<int> bjet_cands; bjet_cands.clear();

  vector<int> tmpcands = bjet_looseID();
  for (int ijet : tmpcands) {
    float dR_mu = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(lepindex),muPhi->at(lepindex));
    if ( dR_mu > Iso4Cut )
      bjet_cands.push_back(ijet);
  }
  return bjet_cands.size() == 0;
}
#endif
