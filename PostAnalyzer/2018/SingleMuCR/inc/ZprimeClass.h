//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  8 10:15:33 2017 by ROOT version 6.06/01
// from TTree EventTree/Event data (tag V08_00_24_00)
// found on file: /hdfs/store/user/uhussain/Zprime_Ntuples_Mar7/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/170306_174919/0000/ggtree_mc_53.root
//////////////////////////////////////////////////////////

#ifndef ZprimeClass_h
#define ZprimeClass_h

#include "ZprimeYear.h"
#include "ZprimeSingleCR.h"

using namespace std;
class ZprimeClass : public ZprimeYear, public ZprimeSingleCR {
public :
  static const int nHisto = 12;
  static const int bHisto = 11;
  
  ZprimeClass(const char* file1,const char* file2,int nfiles) : ZprimeYear(file1,file2,nfiles) {
    BookHistos(file2); };
  ZprimeClass(const char* file1,const char* file2,const char* fileRange) : ZprimeYear(file1,file2,fileRange) {
    BookHistos(file2); };
  ZprimeClass(const char* inputFilename,const char* outputFilename,vector<const char*> filelist) : ZprimeYear(inputFilename,outputFilename,filelist) {
    BookHistos(outputFilename);
  }
  void     Loop(Long64_t maxEvents, int reportEvery);
  void BookHistos(const char* file2);
  void BookHistos(int i,string histname) {
    ZprimeYear::BookHistos(i,histname);
    ZprimeSingleCR::BookHistos(i,histname);
  }
  void fillHistos(int nhist,float event_weight);
  void initVars() {
    ZprimeYear::initVars();
    ZprimeSingleCR::initVars();
  }
  void initTree(TTree* tree) {
    ZprimeYear::initTree(tree);
    ZprimeSingleCR::initTree(tree);
  }
  
  void JetEnergyScale(float start_weight);
};

#endif
