#ifndef ZprimeGammaCR_h
#define ZprimeGammaCR_h

#include "ZprimeAnalysis.h"

class ZprimeGammaCR : public virtual ZprimeAnalysis {
public:
  static const std::string REGION;
  int lepindex;
  TLorentzVector lep;
  float lepton_pt;
  
  TH1F *h_PhotonEt[maxHisto], *h_PhotonEta[maxHisto],*h_PhotonPhi[maxHisto];
  
  virtual void BookHistos(int i,std::string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initVars();
  inline bool isW_or_ZJet() { return sample.type == WJets || sample.type == ZJets || sample.type == DYJets; }
  bool electron_veto(int jet_index,int lepindex,float elePtCut);
  bool muon_veto(int jet_index,int lepindex,float muPtCut);
  bool tau_veto(int jet_index,int lepindex,float tauPtCut);
  vector<int> jet_veto(int lepindex);
  bool bjet_veto(int lepindex);
  virtual float getSF(int lepindex);
  bool CRSelection(std::vector<int> tight,std::vector<int> loose);
};

#endif
