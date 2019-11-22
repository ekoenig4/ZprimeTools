#ifndef ZprimeYear_h
#define ZprimeYear_h

#include "ZprimeAnalysis.h"

class ZprimeYear : public virtual ZprimeAnalysis {
public:
  static const std::string SRDATA;
  
  ZprimeYear(const char* inputFilename,const char* outputFilename,int nfiles);
  ZprimeYear(const char* inputFilename,const char* outputFilename,vector<const char*> filelist);
  ZprimeYear(const char* inputFilename,const char* outputFilename,const char* fileRange);
  int getNfiles(TChain *chain,TString path,int nfiles);
  int getFilesByNumber(TChain *chain,TString path,const char* fileRange);
  int getFilesByList(TChain *chain,TString path,vector<const char*> filelist);
  virtual void BookHistos(int i,string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initVars();
  virtual void SetScalingHistos();
  virtual void Init(TTree* tree);
  virtual float getKFactor(float bosonPt);
  virtual void SetPFVectors(int jetCand);
  virtual bool eleTightID(int);
  virtual bool eleLooseID(int);
  virtual bool muTightID(int);
  virtual bool muLooseID(int);
  virtual bool tauLooseID(int);
  virtual bool phoTightID(int);
  virtual bool phoLooseID(int);
  virtual bool jetSelectionID(int);
  virtual bool bjetSelectionID(int);
  virtual bool MET_Filters();
  virtual bool MET_Triggers();
  virtual bool EGamma_Triggers();
};

#endif
