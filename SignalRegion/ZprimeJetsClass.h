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
  static const bool applyPU = true;
  static const int nHisto = 11;

  ZprimeJetsClass(const char* inputFilename,const char* outputFilename,const char* fileRange): ZprimeJetsCommon(inputFilename,outputFilename,fileRange)
  { BookHistos(outputFilename); };
  virtual void     Loop(Long64_t maxEvents,int reportEvery);
  virtual void BookHistos(const char* outputFilename);
  virtual void fillHistos(int histoNumber,double event_weight);
  virtual vector<int> JetVetoDecision();
  virtual bool electron_veto_looseID(int jet_index, float elePtCut);
  virtual bool muon_veto_looseID(int jet_index, float muPtCut);
};

ZprimeJetsCommon::DataMC::DataMC(string filename) {
  string sampleID[] = {"Run2018","WJets","ZJets","DYJets","QCD","TTJets","GJets","WW","WZ","ZZ"};
  string inclusiveID[] = {"WJetsToLNu_Incl","DYJetsToLL_Incl"};
  for (int i = 0; i < Total; i++)
    if (filename.find(sampleID[i]) != string::npos) {
      type = static_cast<Type>(i);
    }
  isData = (type == Data);
  isInclusive = false;
  if (type == WJets || type == DYJets)
    for (int i = 0; i < 2; i++)
      if (filename.find(inclusiveID[i]) != string::npos)
	isInclusive = true;
  if (type == WJets) PID = 24;
  if (type == ZJets) PID = 23;
}

bool ZprimeJetsCommon::DataMC::isW_or_ZJet() { return type == WJets || type == ZJets; }

#endif

