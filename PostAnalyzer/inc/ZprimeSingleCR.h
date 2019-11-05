#ifndef ZprimeSingleCR_h
#define ZprimeSingleCR_h

#include "ZprimeAnalysis.h"

class ZprimeSingleCR : public virtual ZprimeAnalysis {
public:

  int lepindex;
  TLorentzVector lep;
  float lepton_pt;

  TH1F *h_lepMET_MT;
  TH1F *h_LeptonPt[maxHisto], *h_LeptonEta[maxHisto],*h_LeptonPhi[maxHisto];
  
  virtual void BookHistos(int i,std::string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initVars();
  std::vector<int> electron_veto_looseID(int jet_index,float elePtCut);
  std::vector<int> electron_veto_looseID(int jet_index,int lepindex,float elePtCut);
  std::vector<int> muon_veto_looseID(int jet_index,float muPtCut);
  std::vector<int> muon_veto_looseID(int jet_index,int lepindex,float muPtCut);
  std::vector<int> photon_veto_looseID(int jet_index,int lepindex,float phoPtCut);
  std::vector<int> tau_veto_looseID(int jet_index,int lepindex,float tauPtCut);
  std::vector<int> JetVetoDecision(int lepindex);
  bool CRSelection(std::vector<int> tight,std::vector<int> loose);
};

#endif
