#ifndef ZprimeDataMC_h
#define ZprimeDataMC_h
#include <stdio.h>
#include <iostream>
#include <string>

#include "ZprimeEnums.h"

struct DataMC {
  Type type;
  Region region;
  int year;
  bool isInclusive;
  bool isData;
  int PID;
  void setInfo(std::string filename);
  bool isW_or_ZJet();
  inline const char * GetTypeName() { return TypeName[type]; }
  inline const char * GetRegionName() { return RegionName[region]; }
  inline int GetYear() { return year; }
};

#endif
