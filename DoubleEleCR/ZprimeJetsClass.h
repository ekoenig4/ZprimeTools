//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 11 16:56:08 2018 by ROOT version 6.06/01
// from TTree eventTree/event tree for analysis
// found on file: /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT100To200/MC_DYJetsToLL_HT100-200_1.root
//////////////////////////////////////////////////////////

#ifndef ZprimeJetsClass_h
#define ZprimeJetsClass_h

#include "ZprimeJetsCommon.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TSystemDirectory.h>
#include <TLorentzVector.h>
#include <TMath.h>

// Header file for the classes stored in the TTree if any.
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ZprimeJetsClass : ZprimeJetsCommon{
public :
  static const bool applyPU = true;
  static const bool applySF = true;
  static const bool applyKF = true;
  static const int nHisto = 12;
  static const int bHisto = 11;
  
  TH2F *h_eleRecoSF_highpt;
  TH2F *h_eleIDSF_loose;
  TH2F *h_eleIDSF_tight;

  //CR variables
  int lepindex_leading, lepindex_subleading;
  float dilepton_mass,dilepton_pt,Recoil;
  float leptoMET_phi_to_use;
  //CR histograms
  TH1F *h_leadingLeptonPt[nHisto], *h_leadingLeptonEta[nHisto],*h_leadingLeptonPhi[nHisto],*h_subleadingLeptonPt[nHisto],*h_subleadingLeptonEta[nHisto], *h_subleadingLeptonPhi[nHisto],*h_dileptonPt[nHisto],*h_dileptonM[nHisto], *h_recoil[nHisto];
  TH2F *h_j1EtaPhi[nHisto],*h_leadingLeptonEtaPhi[nHisto],*h_subleadingLeptonEtaPhi[nHisto];

  TH1F *h_tightEleRecoSF_corr,*h_tightEleEffSF_corr,*h_tightEleTriggSF,*h_looseEleRecoSF_corr,*h_looseEleEffSF_corr,*h_looseEleTriggSF;
  
  ZprimeJetsClass(const char* inputFilename,const char* outputFilename,const char* fileRange): ZprimeJetsCommon(inputFilename,outputFilename,fileRange)
  { BookHistos(outputFilename); };
  virtual void     Loop(Long64_t maxEvents,int reportEvery);
  virtual void BookHistos(const char* outputFilename);
  virtual void fillHistos(int histoNumber,double event_weight);
  virtual vector<int> JetVetoDecision(int leading_ele_index, int subleading_ele_index);
  virtual vector<int> electron_veto_tightID(int jet_index, float elePtCut);
  virtual vector<int> electron_veto_looseID(int jet_index, int leading_mu_index, int subleading_mu_index, float elePtCut);
  virtual vector<int> muon_veto_tightID(int jet_index, float muPtCut);
  virtual vector<int> muon_veto_looseID(int jet_index, int leading_ele_index, int subleading_ele_index, float muPtCut);
  virtual double getSF(int lepindex_leading, int lepindex_subleading);
  virtual void initTree(TTree* tree);

  virtual void JetEnergyScale(double start_weight);
};

#endif

