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
  static const int nHisto = 10;
  static const int bHisto = 8;
  
  ZprimeJetsClass(const char* file1,const char* file2,const char* fileRange) : ZprimeJetsCommon(file1,file2,fileRange)
  { BookHistos(file2); };
  virtual void Loop(Long64_t maxEvents, int reportEvery);
  virtual void BookHistos(const char* file2);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initTree(TTree* tree);

  virtual inline bool electronVeto(int jetindex,float elePtCut) { return electron_veto_looseID(jetindex,elePtCut).size() == 0; }
  virtual inline bool muonVeto(int jetindex,float muPtCut)      { return muon_veto_looseID(jetindex,muPtCut).size() == 0; }
  virtual inline bool photonVeto(int jetindex,float phoPtCut)   { return photon_veto_looseID(jetindex,phoPtCut).size() == 0; }
  virtual inline bool tauVeto(int jetindex,float tauPtCut)      { return tau_veto_looseID(jetindex,tauPtCut).size() == 0; }
  

  virtual void JetEnergyScale(float event_weight);
};

#endif
