#ifndef ZprimeDoubleCR_h
#define ZprimeDoubleCR_h

#include "ZprimeAnalysis.h"

class ZprimeDoubleCR : public virtual ZprimeAnalysis {
public:

  int lepindex_leading, lepindex_subleading;
  float dilepton_mass,dilepton_pt;
  TLorentzVector lep1,lep2;
  TH1F *h_leadingLeptonPt[maxHisto], *h_leadingLeptonEta[maxHisto],*h_leadingLeptonPhi[maxHisto],*h_subleadingLeptonPt[maxHisto],*h_subleadingLeptonEta[maxHisto], *h_subleadingLeptonPhi[maxHisto],*h_dileptonPt[maxHisto],*h_dileptonM[maxHisto];
  
  void BookHistos(int i,std::string histname);
  void fillHistos(int nhist,float event_weight);
  virtual std::vector<int> electron_veto_looseID(int jet_index,int leading,int subleading,float elePtCut);
  virtual std::vector<int> muon_veto_looseID(int jet_index,int leading,int subleading,float muPtCut);
  std::vector<int> photon_veto_looseID(int jet_index,int leading,int subleading,float phoPtCut);
  std::vector<int> tau_veto_looseID(int jet_index,int leading,int subleading,float tauPtCut);
  std::vector<int> JetVetoDecision(int leading,int subleading);
  bool CRSelection(std::vector<int> tight,std::vector<int> loose);
  
};

#endif
