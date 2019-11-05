#ifndef ZprimeYear_h
#define ZprimeYear_h

#include "ZprimeAnalysis.h"

class ZprimeYear : public virtual ZprimeAnalysis {
public:

  ZprimeYear(const char * inputFilename,const char * outputFilename,const char * fileRange);
  virtual void BookHistos(int i,string histname);
  virtual void fillHistos(int nhist,float event_weight);
  virtual void SetScalingHistos();
  virtual void Init(TTree* tree);
  virtual float getKFactor(float bosonPt);
  virtual bool eleTightID(int);
  virtual bool eleLooseID(int);
  virtual bool muTightID(int);
  virtual bool muLooseID(int);
  virtual bool jetSelectionID(int);
};

#endif
