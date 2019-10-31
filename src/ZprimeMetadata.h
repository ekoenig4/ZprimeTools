#ifndef ZprimeMetadata_h
#define ZprimeMetadata_h
#include <stdio.h>
#include <iostream>
#include <string>

#include "ZprimeEnums.h"

using namespace std;

struct DataMC {
  Type type;
  Region region;
  int year;
  bool isInclusive;
  bool isData;
  int PID;
  void setInfo(string filename);
  bool isW_or_ZJet();
  inline const char * GetTypeName() { return TypeName[type]; }
  inline const char * GetRegionName() { return RegionName[region]; }
  inline int GetYear() { return year; }
};

#endif
