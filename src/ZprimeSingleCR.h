#ifndef ZprimeSingleCR_h
#define ZprimeSingleCR_h

#include "ZprimeAnalysis.h"

class ZprimeSingleCR : public virtual ZprimeAnalysis {
public:

  int lepindex;
  TLorentzVector lep;
  
  TH1F *h_LeptonPt[maxHisto], *h_LeptonEta[maxHisto],*h_LeptonPhi[maxHisto];
  
  void BookHistos(int i,string histname);
  void fillHistos(int nhist,float event_weight);
  virtual vector<int> electron_veto_looseID(int jet_index,int lepindex,float elePtCut);
  virtual vector<int> muon_veto_looseID(int jet_index,int lepindex,float muPtCut);
  vector<int> photon_veto_looseID(int jet_index,int lepindex,float phoPtCut);
  vector<int> tau_veto_looseID(int jet_index,int lepindex,float tauPtCut);
  vector<int> JetVetoDecision(int lepindex);
};

#endif
