//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  8 10:15:33 2017 by ROOT version 6.06/01
// from TTree EventTree/Event data (tag V08_00_24_00)
// found on file: /hdfs/store/user/uhussain/Zprime_Ntuples_Mar7/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/170306_174919/0000/ggtree_mc_53.root
//////////////////////////////////////////////////////////

#ifndef ZprimeJetsClass_h
#define ZprimeJetsClass_h

#include "ZprimeJetsCommon.h"
using namespace std;
class ZprimeJetsClass : ZprimeJetsCommon{
public :
  static const int nHisto = 11;
  static const int bHisto = 10;
  
  //CR variables
  int lepindex_leading, lepindex_subleading;
  float dilepton_mass,dilepton_pt,recoil,recoilPhi;
  float leptoMET_phi_to_use;
  TLorentzVector m1,m2;
  //CR histograms
  TH1F *h_leadingLeptonPt[nHisto], *h_leadingLeptonEta[nHisto],*h_leadingLeptonPhi[nHisto],*h_subleadingLeptonPt[nHisto],*h_subleadingLeptonEta[nHisto], *h_subleadingLeptonPhi[nHisto],*h_dileptonPt[nHisto],*h_dileptonM[nHisto], *h_recoil[nHisto];
  
  ZprimeJetsClass(const char* file1,const char* file2,const char* fileRange) : ZprimeJetsCommon(file1,file2,fileRange)
  { BookHistos(file2); };
  virtual void Loop(Long64_t maxEvents, int reportEvery);
  virtual void BookHistos(const char* file2);
  virtual void fillHistos(int histoNumber,float event_weight);
  virtual vector<int> JetVetoDecision(int leading_ele_index, int subleading_ele_index);
  virtual vector<int> electron_veto_tightID(int jet_index, float elePtCut);
  virtual vector<int> electron_veto_looseID(int jet_index, int leading_mu_index, int subleading_mu_index, float elePtCut);
  virtual vector<int> muon_veto_tightID(int jet_index, float muPtCut);
  virtual vector<int> muon_veto_looseID(int jet_index, int leading_ele_index, int subleading_ele_index, float muPtCut);
  virtual void initTree(TTree* tree);
  virtual void initVars();
  
  virtual void JetEnergyScale(float start_weight);
};

#endif
