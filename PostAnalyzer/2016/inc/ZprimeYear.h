#ifndef ZprimeYear_h
#define ZprimeYear_h

#include "ZprimeAnalysis.h"

class ZprimeYear : public virtual ZprimeAnalysis {
public:

  vector<bool>   *jetPFLooseID;
  vector<vector<double> > *JetsPFConsPt;
  vector<vector<double> > *JetsPFConsEta;
  vector<vector<double> > *JetsPFConsPhi;
  vector<vector<double> > *JetsPFConsEt;
  vector<vector<int> > *JetsPFConsPID;
  TBranch        *b_jetPFLooseID; //!
  TBranch        *b_JetsPFConsPt;   //!
  TBranch        *b_JetsPFConsEta;   //!
  TBranch        *b_JetsPFConsPhi;   //!
  TBranch        *b_JetsPFConsEt;   //!
  TBranch        *b_JetsPFConsPID;   //!
  
  ZprimeYear(const char * inputFilename,const char * outputFilename,const char * fileRange);
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
  virtual bool jetSelectionID(int);
  virtual float getCSV2Cut();
};

#endif
