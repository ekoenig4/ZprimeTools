#ifndef ZprimeSingleCR_h
#define ZprimeSingleCR_h

#include "ZprimeAnalysis.h"

class ZprimeSingleCR : public virtual ZprimeAnalysis {
public:
  static const std::string REGION;
  int lepindex;
  TLorentzVector lep;
  float lepton_pt,lepton_eta,lepton_phi;

  TH1F *h_lepMET_MT;
  TH1F *h_LeptonPt[maxHisto], *h_LeptonEta[maxHisto],*h_LeptonPhi[maxHisto];
  
  virtual void BookHistos(int i,std::string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initVars();
  virtual void initTree(TTree* tree);
  inline bool isW_or_ZJet() { return ZprimeAnalysis::isW_or_ZJet() || sample.type == DYJets || sample.type == DYJets_NLO; }
  bool electron_veto(int jet_index,int lepindex,float elePtCut);
  bool muon_veto(int jet_index,int lepindex,float muPtCut);
  bool photon_veto(int jet_index,int lepindex,float phoPtCut);
  bool tau_veto(int jet_index,int lepindex,float tauPtCut);
  vector<int> jet_veto(int lepindex);
  bool bjet_veto(int lepindex);
  virtual float getSF(int lepindex);
  bool CRSelection(std::vector<int> tight,std::vector<int> loose);
};

#endif
