#ifndef ZprimeGammaCR_C
#define ZprimeGammaCR_C

#include "ZprimeGammaCR.h"
#include "VariableBins.h"
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

const string ZprimeGammaCR::REGION = "GammaCR";

void ZprimeGammaCR::initVars() {
  lepindex = lepton_pt = -1;
}

void ZprimeGammaCR::BookHistos(int i,string histname) {
  if (i == -1) {
    
  } else {
    auto Name = [histname](string name) { return (name+histname); };
    h_PhotonEt[i]  = MakeTH1F(new TH1F(Name("PhotonEt").c_str() ,"PhotonEt;Photon E_{T}" ,nLeadingLeptonPtBins,LeadingLeptonPtBins));
    h_PhotonEta[i] = MakeTH1F(new TH1F(Name("PhotonEta").c_str(),"PhotonEta;Photon #eta" ,nEtaBins,lEta,uEta));
    h_PhotonPhi[i] = MakeTH1F(new TH1F(Name("PhotonPhi").c_str(),"PhotonPhi;Photon #phi" ,nPhiBins,lPhi,uPhi));
  }
}

void ZprimeGammaCR::fillHistos(int nhist,float event_weight) {
  //CR Histograms
  if(lepindex >= 0){
    h_PhotonEt[nhist] ->Fill(phoEt->at(lepindex),event_weight);
    h_PhotonEta[nhist]->Fill(phoEta->at(lepindex),event_weight);
    h_PhotonPhi[nhist]->Fill(phoPhi->at(lepindex),event_weight);
  }
}

bool ZprimeGammaCR::CRSelection(vector<int> tight,vector<int> loose) {
  if (tight.size() == 1 && loose.size() == 1) {
    lepindex = tight[0];
    lep.SetPtEtaPhiE(phoEt->at(lepindex),phoEta->at(lepindex),phoPhi->at(lepindex),phoE->at(lepindex));
    
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

float ZprimeGammaCR::getSF(int lepindex) {
  float eta = phoSCEta->at(lepindex); float pt = phoEt->at(lepindex);
  // float phoRecoSF_corr= th2fmap.getBin("phoRecoSF_highpt",eta,pt);
  // std::cout<<"phoRecoSF_corr =  "<< phoRecoSF_corr<<std::endl;
  float phoEffSF_corr= th2fmap.getBin("phoIDSF_tight",eta,pt);
  // std::cout<<"phoEffSF_corr =  "<< phoEffSF_corr<<std::endl;
  // float phoTriggSF = th2fmap.getBin("phoTriggSF",fabs(eta),pt);

  return phoEffSF_corr;
}

vector<int> ZprimeGammaCR::jet_veto(int lepindex) {
  vector<int> jetindex; jetindex.clear();

  vector<int> tmpcands = jet_looseID();
  for(int ijet : tmpcands ) {
    float dR_pho = deltaR(jetEta->at(ijet),jetPhi->at(ijet),phoSCEta->at(lepindex),phoSCPhi->at(lepindex));
    if( dR_pho > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}


bool ZprimeGammaCR::electron_veto(int jet_index, int lepindex, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  vector<int> tmpcands = electron_looseID(jet_index,elePtCut);
  for(int iele : tmpcands) {
    float dR_pho = deltaR(eleSCEta->at(iele),eleSCPhi->at(iele),phoEta->at(lepindex),phoPhi->at(lepindex));
    if ( dR_pho > Iso5Cut )
      ele_cands.push_back(iele);
  }
  
  return ele_cands.size() == 0;
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate phoctron and jet within dR of 0.5
bool ZprimeGammaCR::muon_veto(int jet_index, int lepindex, float muPtCut)
{
  // cout << "Inside Muon Loose Veto" << endl;
  vector<int> mu_cands;
  mu_cands.clear();

  vector<int> tmpcands = muon_looseID(jet_index,muPtCut);
  for(int imu : tmpcands) {
    float dR_pho = deltaR(muEta->at(imu),muPhi->at(imu),phoSCEta->at(lepindex),phoSCPhi->at(lepindex));
    if ( dR_pho > Iso4Cut )
      mu_cands.push_back(imu);
  }
  
  return mu_cands.size() == 0;
}

bool ZprimeGammaCR::tau_veto(int jet_index,int lepindex,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = tau_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_pho = deltaR(tauEta->at(itau),tauPhi->at(itau),phoSCEta->at(lepindex),phoSCPhi->at(lepindex));
    if ( dR_pho > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands.size() == 0;
}

bool ZprimeGammaCR::bjet_veto(int lepindex) {
  vector<int> bjet_cands; bjet_cands.clear();

  vector<int> tmpcands = bjet_looseID();
  for (int ijet : tmpcands) {
    float dR_pho = deltaR(jetEta->at(ijet),jetPhi->at(ijet),phoSCEta->at(lepindex),phoSCPhi->at(lepindex));
    if ( dR_pho > Iso4Cut )
      bjet_cands.push_back(ijet);
  }
  return bjet_cands.size() == 0;
}
#endif
