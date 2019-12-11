//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  8 10:15:33 2017 by ROOT version 6.06/01
// from TTree EventTree/Event data (tag V08_00_24_00)
// found on file: /hdfs/store/user/uhussain/Zprime_Ntuples_Mar7/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/170306_174919/0000/ggtree_mc_53.root
//////////////////////////////////////////////////////////

#ifndef ZprimeJetsClass_h
#define ZprimeJetsClass_h

#include "ZprimeYear.h"

class ZprimeClass : public virtual ZprimeYear {
public:
  
  vector<double>  *psWeight;
  TBranch        *b_psWeight;   //!
  static const int nHisto = 1;
  static const int bHisto = 0;

  string pswlist[22];
  map<string,pair<int,int>> pswmap;
  map<string,TH1F*> h_psWeights;
  
  ZprimeClass(const char* file1,const char* file2,int nfiles) : ZprimeYear(file1,file2,nfiles) {
    Init(fChain);
    BookHistos(file2); };
  ZprimeClass(const char* inputFilename,const char* outputFilename,const char* fileRange) : ZprimeYear(inputFilename,outputFilename,fileRange) {
    Init(fChain);
    BookHistos(outputFilename);
  }
  ZprimeClass(const char* inputFilename,const char* outputFilename,vector<const char*> filelist) : ZprimeYear(inputFilename,outputFilename,filelist) {
    Init(fChain);
    BookHistos(outputFilename);
  }
  virtual void Loop(Long64_t maxEvents, int reportEvery);
  virtual void BookHistos(const char* file2);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void Init(TTree* tree);
};

#endif
