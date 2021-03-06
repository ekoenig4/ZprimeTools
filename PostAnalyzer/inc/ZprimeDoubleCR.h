#ifndef ZprimeDoubleCR_h
#define ZprimeDoubleCR_h

#include "ZprimeAnalysis.h"

class ZprimeDoubleCR : public virtual ZprimeAnalysis {
public:
  static const std::string REGION;
  int lepindex_leading, lepindex_subleading;
  float dilepton_mass,dilepton_pt;
  TLorentzVector lep1,lep2;
  float leadingLepton_pt,leadingLepton_eta,leadingLepton_phi;
  float subleadingLepton_pt,subleadingLepton_eta,subleadingLepton_phi;
  TH1F *h_leadingLeptonPt[maxHisto], *h_leadingLeptonEta[maxHisto],*h_leadingLeptonPhi[maxHisto],*h_subleadingLeptonPt[maxHisto],*h_subleadingLeptonEta[maxHisto], *h_subleadingLeptonPhi[maxHisto],*h_dileptonPt[maxHisto],*h_dileptonM[maxHisto],*h_dileptonMall[maxHisto];
  
  virtual void BookHistos(int i,std::string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initVars();
  virtual void initTree(TTree* tree);
  inline bool isW_or_ZJet() { return ZprimeAnalysis::isW_or_ZJet() || sample.type == DYJets || sample.type == DYJets_NLO; }
  bool electron_veto(int jet_index,int leading,int subleading,float elePtCut);
  bool muon_veto(int jet_index,int leading,int subleading,float muPtCut);
  bool photon_veto(int jet_index,int leading,int subleading,float phoPtCut);
  bool tau_veto(int jet_index,int leading,int subleading,float tauPtCut);
  vector<int> jet_veto(int leading,int subleading);
  bool bjet_veto(int leading,int subleading);
  bool CRSelection(std::vector<int> tight,std::vector<int> loose);
  float getSF(int leading,int subleading);
};

#endif
