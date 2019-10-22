//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 11 16:56:08 2018 by ROOT version 6.06/01
// from TTree eventTree/event tree for analysis
// found on file: /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT100To200/MC_DYJetsToLL_HT100-200_1.root
//////////////////////////////////////////////////////////

#ifndef ZprimeJetsClass_h
#define ZprimeJetsClass_h

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

class ZprimeJetsClass {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  const char * output;
  TTree *tree;

  bool debug = true;
  enum Type { Data,WJets,ZJets,DYJets,QCD,TTJets,GJets,WW,WZ,ZZ,Total };
  struct DataMC {
    Type type;
    bool isInclusive;
    bool isData;
    int PID;
    DataMC(){}
    DataMC(string filename) {
      string sampleID[] = {"Run2017","WJets","ZJets","DYJets","QCD","TTJets","GJets","WW","WZ","ZZ"};
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
      if (type == ZJets || type == DYJets) PID = 23;
    }
    bool isW_or_ZJet() { return type == WJets || type == ZJets || type == DYJets; }
  } sample;
  // Declaration of leaf types
  Int_t           run;
  Long64_t        event;
  Int_t           lumis;
  Bool_t          isData;

  // List of branches
  TBranch        *b_run;   //!
  TBranch        *b_event;   //!
  TBranch        *b_lumis;   //!
  TBranch        *b_isData;   //!
  
  ZprimeJetsClass(const char* inputFilename,const char* outputFilename,const char* fileRange);
  virtual ~ZprimeJetsClass();
  virtual vector<string> split(string str,string delim);
  virtual bool fileSelection(string filename,string fileRange);
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(Long64_t maxEvents,int reportEvery);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif