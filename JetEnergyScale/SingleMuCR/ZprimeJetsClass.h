//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  8 10:15:33 2017 by ROOT version 6.06/01
// from TTree EventTree/Event data (tag V08_00_24_00)
// found on file: /hdfs/store/user/uhussain/Zprime_Ntuples_Mar7/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/170306_174919/0000/ggtree_mc_53.root
//////////////////////////////////////////////////////////

#ifndef ZprimeJetsClass_h
#define ZprimeJetsClass_h

#include "ZprimeJetsCommon.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <map>
#include <list>
#include <vector>
#include <bitset>
#include <TCanvas.h>
#include <TSystem.h>
#include <TPostScript.h>
#include <TH3.h>
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TMath.h>
#include <TLegend.h>
#include <TProfile.h>
#include <TGraph.h>
#include <TRef.h>
#include <TList.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>
#include <TDCacheFile.h>
#include <TLorentzVector.h>
#include "TIterator.h"
#include "string"
// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "TString.h"
#include "vector"
using namespace std;
class ZprimeJetsClass : ZprimeJetsCommon {
public :
  static const int nHisto = 13;
  static const bool applyPU = true;
  static const bool applySF = true;
  static const bool applyKF = true;

  vector<double> jetPtNorm;
  
  //CR variables
  int lepindex;
  double lepton_pt,Recoil;
  
  //CR histograms
  TH1F *h_LeptonPt[nHisto], *h_LeptonEta[nHisto],*h_LeptonPhi[nHisto],*h_recoil[nHisto];
  
  ZprimeJetsClass(const char* file1,const char* file2,const char* fileRange) : ZprimeJetsCommon(file1,file2,fileRange)
  { BookHistos(file2); };
  virtual void     Loop(Long64_t maxEvents, int reportEvery);
  virtual void BookHistos(const char* file2);
  virtual void fillHistos(int histoNumber,double event_weight);
  virtual vector<int> JetVetoDecision(int jet_index, int ele_index);
  virtual vector<int> electron_veto_tightID(int jet_index, float elePtCut);
  virtual vector<int> electron_veto_looseID(int jet_index, int mu_index,float elePtCut);
  virtual vector<int> muon_veto_tightID(int jet_index, float muPtCut);
  virtual vector<int> muon_veto_looseID(int jet_index, int ele_index,float muPtCut);
};

ZprimeJetsCommon::DataMC::DataMC(string filename) {
  string sampleID[] = {"MET","MonoZprime_Mx","WJets","ZJets","DYJets","QCD","TTJets","GJets","WW","WZ","ZZ"};
  string inclusiveID[] = {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8","DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"};
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
  if (type == ZJets || type == DYJets) PID = 23;
}
bool ZprimeJetsCommon::DataMC::isW_or_ZJet() { return type == WJets || type == ZJets || type == DYJets; }


#endif
