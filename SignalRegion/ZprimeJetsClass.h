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
  static const int nHisto = 12;
  static const int bHisto = 9;

  ZprimeJetsClass(const char* inputFilename,const char* outputFilename,vector<const char*> filelist) : ZprimeJetsCommon(inputFilename,outputFilename,filelist) { BookHistos(outputFilename); };
  ZprimeJetsClass(const char* inputFilename,const char* outputFilename,const char* fileRange) : ZprimeJetsCommon(inputFilename,outputFilename,fileRange) { BookHistos(outputFilename); };
  virtual void     Loop(Long64_t maxEvents,int reportEvery);
  virtual void BookHistos(const char* outputFilename);
  virtual void fillHistos(int histoNumber,float event_weight);
  virtual void initTree(TTree* tree);

  virtual inline bool electronVeto(int jetindex,float elePtCut) { return electron_veto_looseID(jetindex,elePtCut).size() == 0; }
  virtual inline bool muonVeto(int jetindex,float muPtCut)      { return muon_veto_looseID(jetindex,muPtCut).size() == 0; }
  virtual inline bool photonVeto(int jetindex,float phoPtCut)   { return photon_veto_looseID(jetindex,phoPtCut).size() == 0; }
  virtual inline bool tauVeto(int jetindex,float tauPtCut)      { return tau_veto_looseID(jetindex,tauPtCut).size() == 0; }
  
  virtual void JetEnergyScale(float start_weight);
};

#endif

