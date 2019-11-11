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
  static const int nHisto = 9;
  static const int bHisto = 8;
  
  ZprimeClass(const char* inputFilename,const char* outputFilename,const char* fileRange) : ZprimeYear(inputFilename,outputFilename,fileRange) {
    BookHistos(outputFilename);
  }
  virtual void Loop(Long64_t maxEvents, int reportEvery);
  virtual void BookHistos(const char* file2);
  virtual void fillHistos(int nhist,float event_weight);
  
  virtual void JetEnergyScale(float event_weight);
};

#endif
