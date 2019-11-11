#ifndef ZprimeDoubleCR_h
#define ZprimeDoubleCR_h

#include "ZprimeAnalysis.h"

class ZprimeDoubleCR : public virtual ZprimeAnalysis {
public:

  int lepindex_leading, lepindex_subleading;
  float dilepton_mass,dilepton_pt;
  TLorentzVector lep1,lep2;
  TH1F *h_leadingLeptonPt[maxHisto], *h_leadingLeptonEta[maxHisto],*h_leadingLeptonPhi[maxHisto],*h_subleadingLeptonPt[maxHisto],*h_subleadingLeptonEta[maxHisto], *h_subleadingLeptonPhi[maxHisto],*h_dileptonPt[maxHisto],*h_dileptonM[maxHisto];
  
  virtual void BookHistos(int i,std::string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initVars();
  inline bool isW_or_ZJet() { return sample.type == WJets || sample.type == ZJets || sample.type == DYJets; }
  bool electron_veto(int jet_index,int leading,int subleading,float elePtCut);
  bool muon_veto(int jet_index,int leading,int subleading,float muPtCut);
  bool photon_veto(int jet_index,int leading,int subleading,float phoPtCut);
  bool tau_veto(int jet_index,int leading,int subleading,float tauPtCut);
  vector<int> JetVetoDecision(int leading,int subleading);
  bool CRSelection(std::vector<int> tight,std::vector<int> loose);
  float getSF(int leading,int subleading);
};

#endif
