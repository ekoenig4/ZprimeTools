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
class ZprimeJetsClass : public ZprimeJetsCommon{
public:
  static const int nHisto = 30;
  
  ZprimeJetsClass(const char* file1,const char* file2,const char* fileRange) : ZprimeJetsCommon(file1,file2,fileRange)
  { BookHistos(file2); };
  virtual void Loop(Long64_t maxEvents, int reportEvery);
  virtual void BookHistos(const char* file2);
  virtual void fillHistos(int histoNumber,double event_weight);
  virtual vector<int> JetVetoDecision();
  virtual bool electron_veto_looseID(int jet_index, float elePtCut);
  virtual bool muon_veto_looseID(int jet_index, float muPtCut);

  virtual void JetEnergyScale(int nhist,double event_weight,function<bool()> cut = [](){return true;});
};

#endif
