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
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TMath.h>

// Header file for the classes stored in the TTree if any.
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class ZprimeJetsClass : ZprimeJetsCommon{
public :
  static const int nHisto = 15;
  static const int bHisto = 12;

  //CR variables
  int lepindex;
  float lepton_pt,recoil,recoilPhi;
  //CR histograms
  TH1F *h_LeptonPt[nHisto], *h_LeptonEta[nHisto],*h_LeptonPhi[nHisto],*h_recoil[nHisto],*h_recoilPhi[nHisto];
  TH2F *h_LeptonEtaPhi[nHisto],*h_j1EtaPhi[nHisto];

  TH1F *h_eleRecoSF_corr,*h_eleEffSF_corr,*h_eleTriggSF;

  ZprimeJetsClass(const char* inputFilename,const char* outputFilename,vector<const char*> filelist) : ZprimeJetsCommon(inputFilename,outputFilename,filelist) { BookHistos(outputFilename); };
  ZprimeJetsClass(const char* inputFilename,const char* outputFilename,const char* fileRange) : ZprimeJetsCommon(inputFilename,outputFilename,fileRange) { BookHistos(outputFilename); };
  virtual void     Loop(Long64_t maxEvents,int reportEvery);
  virtual void SetScalingHistos();
  virtual void BookHistos(const char* outputFilename);
  virtual void fillHistos(int histoNumber,float event_weight);
  virtual float getSF(int ele_index);
  virtual void initTree(TTree* tree);
  virtual void initVars();
  
  virtual vector<int> JetVetoDecision(int jet_index, int lepindex);
  virtual vector<int> muon_veto_looseID(int jet_index,int lepindex,float elePtCut);
  virtual vector<int> photon_veto_looseID(int jet_index,int lepindex,float phoPtCut);
  virtual vector<int> tau_veto_looseID(int jet_index,int lepindex,float tauPtCut);
  
  virtual void JetEnergyScale(float start_weight);
};

#endif
