//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 11 16:56:08 2018 by ROOT version 6.06/01
// from TTree eventTree/event tree for analysis
// found on file: /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT100To200/MC_DYJetsToLL_HT100-200_1.root
//////////////////////////////////////////////////////////

#ifndef ZprimeYear_h
#define ZprimeYear_h

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

class ZprimeYear : ZprimeJetsCommon{
public :
  static const int nHisto = 13;
  static const int bHisto = 10;

  //CR variables
  int lepindex_leading, lepindex_subleading;
  float dilepton_mass,dilepton_pt,recoil,recoilPhi;
  //CR histograms
  TH1F *h_leadingLeptonPt[nHisto], *h_leadingLeptonEta[nHisto],*h_leadingLeptonPhi[nHisto],*h_subleadingLeptonPt[nHisto],*h_subleadingLeptonEta[nHisto], *h_subleadingLeptonPhi[nHisto],*h_dileptonPt[nHisto],*h_dileptonM[nHisto], *h_recoil[nHisto],*h_recoilPhi[nHisto];

  TH1F *h_tightMuISO,*h_tightMuID,*h_looseMuISO,*h_looseMuID;
  
  ZprimeYear(const char* inputFilename,const char* outputFilename,const char* fileRange): ZprimeJetsCommon(inputFilename,outputFilename,fileRange)
  { BookHistos(outputFilename); };
  virtual void     Loop(Long64_t maxEvents,int reportEvery);
  virtual void SetScalingHistos();
  virtual void BookHistos(const char* outputFilename);
  virtual void fillHistos(int histoNumber,float event_weight);
  virtual float getSF(int lepindex_leading,int lepindex_subleading);
  virtual void initTree(TTree* tree);
  virtual void initVars();

  virtual vector<int> JetVetoDecision(int leading, int subleading);
  virtual vector<int> electron_veto_looseID(int jet_index,int leading,int subleading,float elePtCut);
  virtual vector<int> photon_veto_looseID(int jet_index,int leading,int subleading,float phoPtCut);
  virtual vector<int> tau_veto_looseID(int jet_index,int leading,int subleading,float tauPtCut);
  
  virtual void JetEnergyScale(float start_weight);
};

#endif
