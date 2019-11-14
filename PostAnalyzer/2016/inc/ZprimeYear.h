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
  vector<bool>    *taupfTausDiscriminationByDecayModeFinding;
  vector<bool>    *tauByVLooseIsolationMVArun2v1DBoldDMwLT;
  TBranch        *b_jetPFLooseID; //!
  TBranch        *b_JetsPFConsPt;   //!
  TBranch        *b_JetsPFConsEta;   //!
  TBranch        *b_JetsPFConsPhi;   //!
  TBranch        *b_JetsPFConsEt;   //!
  TBranch        *b_JetsPFConsPID;   //!
  TBranch        *b_taupfTausDiscriminationByDecayModeFinding;   //!
  TBranch        *b_tauByVLooseIsolationMVArun2v1DBoldDMwLT;   //!
  
  ZprimeYear(const char * inputFilename,const char * outputFilename,const char * fileRange);
  virtual void BookHistos(int i,string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void initVars();
  virtual void SetScalingHistos();
  virtual TH2F* MergeMuonSF(TH2F*,TH2F*);
  virtual void Init(TTree* tree);
  virtual float getKFactor(float bosonPt);
  virtual void SetPFVectors(int jetCand);
  virtual bool eleTightID(int);
  virtual bool eleLooseID(int);
  virtual bool muTightID(int);
  virtual bool muLooseID(int);
  virtual bool tauLooseID(int);
  virtual bool phoLooseID(int);
  virtual bool jetSelectionID(int);
  virtual bool btagSelectionID(int);
  virtual bool MET_Filters();
  virtual bool MET_Triggers();
  virtual bool EGamma_Triggers();
  
};

#endif
