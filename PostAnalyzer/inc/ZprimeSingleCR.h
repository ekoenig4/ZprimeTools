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
  inline bool isW_or_ZJet() { return sample.type == WJets || sample.type == ZJets || sample.type == DYJets; }
  bool electron_veto(int jet_index,int lepindex,float elePtCut);
  bool muon_veto(int jet_index,int lepindex,float muPtCut);
  bool photon_veto(int jet_index,int lepindex,float phoPtCut);
  bool tau_veto(int jet_index,int lepindex,float tauPtCut);
  vector<int> JetVetoDecision(int lepindex);
  bool CRSelection(std::vector<int> tight,std::vector<int> loose);
};

#endif
