#ifndef ZprimeSingleCR_C
#define ZprimeSingleCR_C

#include "ZprimeSingleCR.h"
#include "VariableBins.h"
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

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
    h_LeptonPt[nhist]->Fill(elePt->at(lepindex),event_weight);
    h_LeptonEta[nhist]->Fill(eleEta->at(lepindex),event_weight);
    h_LeptonPhi[nhist]->Fill(elePhi->at(lepindex),event_weight);
  }
}

bool ZprimeSingleCR::CRSelection(vector<int> tight,vector<int> loose) {
  if (tight.size() == 1 && loose.size() == 1) {
    lepindex = tight[0];
    lep.SetPtEtaPhiE(elePt->at(lepindex),eleEta->at(lepindex),elePhi->at(lepindex),eleE->at(lepindex));
    
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

float ZprimeSingleCR::getSF(int lepindex) {
  float eta = eleSCEta->at(lepindex); float pt = elePt->at(lepindex);
  float eleRecoSF_corr= th2fmap.getBin("eleRecoSF_highpt",eta,pt);
  // std::cout<<"eleRecoSF_corr =  "<< eleRecoSF_corr<<std::endl;
  float eleEffSF_corr= th2fmap.getBin("eleIDSF_tight",eta,pt);
  // std::cout<<"eleEffSF_corr =  "<< eleEffSF_corr<<std::endl;
  float eleTriggSF = EletriggerSF(pt,eta);

  return eleRecoSF_corr * eleEffSF_corr * eleTriggSF;
}

vector<int> ZprimeSingleCR::JetVetoDecision(int lepindex) {
  vector<int> jetindex; jetindex.clear();

  vector<int> tmpcands = ZprimeAnalysis::JetVetoDecision();
  for(int ijet : tmpcands ) {
    float dR_ele = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if( dR_ele > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

bool ZprimeSingleCR::electron_veto(int jet_index,int lepindex,float elePtCut) {
  return ZprimeAnalysis::electron_veto(jet_index,elePtCut);
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate electron and jet within dR of 0.5
bool ZprimeSingleCR::muon_veto(int jet_index, int lepindex, float muPtCut)
{
  // cout << "Inside Muon Loose Veto" << endl;
  vector<int> mu_cands;
  mu_cands.clear();

  vector<int> tmpcands = muon_looseID(jet_index,muPtCut);
  for(int imu : tmpcands) {
    float dR_ele = deltaR(muEta->at(imu),muPhi->at(imu),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if ( dR_ele > Iso4Cut )
      mu_cands.push_back(imu);
  }
  
  return mu_cands.size() == 0;
}

bool ZprimeSingleCR::photon_veto(int jet_index,int lepindex,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = photon_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_ele = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if ( dR_ele > Iso5Cut )
      pho_cands.push_back(ipho);
  }
  return pho_cands.size() == 0;
}

bool ZprimeSingleCR::tau_veto(int jet_index,int lepindex,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = tau_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_ele = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if ( dR_ele > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands.size() == 0;
}
#endif
