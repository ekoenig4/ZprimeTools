#ifndef ZprimeDoubleCR_h
#define ZprimeDoubleCR_h

#include "ZprimeAnalysis.h"

class ZprimeDoubleCR : public virtual ZprimeAnalysis {
public:

  int lepindex_leading, lepindex_subleading;
  float dilepton_mass,dilepton_pt;
  TLorentzVector lep1,lep2;
  TH1F *h_leadingLeptonPt[maxHisto], *h_leadingLeptonEta[maxHisto],*h_leadingLeptonPhi[maxHisto],*h_subleadingLeptonPt[maxHisto],*h_subleadingLeptonEta[maxHisto], *h_subleadingLeptonPhi[maxHisto],*h_dileptonPt[maxHisto],*h_dileptonM[maxHisto];
  
  void BookHistos(int i,string histname);
  void fillHistos(int nhist,float event_weight);
  virtual vector<int> electron_veto_looseID(int jet_index,int leading,int subleading,float elePtCut);
  virtual vector<int> muon_veto_looseID(int jet_index,int leading,int subleading,float muPtCut);
  vector<int> photon_veto_looseID(int jet_index,int leading,int subleading,float phoPtCut);
  vector<int> tau_veto_looseID(int jet_index,int leading,int subleading,float tauPtCut);
  vector<int> JetVetoDecision(int leading,int subleading);
  bool CRSelection(vector<int> tight,vector<int> loose);
  
};

#endif
