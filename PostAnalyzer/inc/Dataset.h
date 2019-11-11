#ifndef Dataset_h
#define Dataset_h

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "ZprimeEnums.h"

class Dataset {
  typedef std::map<std::string,std::vector<std::string>> Subset;
  std::map<std::string,Subset> dataset;
  void addDataset(std::string path,std::string filename);
public:
  static const std::string datalist[10];
  static const std::map<std::string,Type> typemap;

  Type type;
  Region region;
  int year;
  bool isInclusive;
  bool isData;
  bool isSignal;
  int PID;

  Dataset();
  void printDataset();

  void setInfo(std::string path);
  void setTypeInfo(std::string path);
  inline const char* GetTypeName() { return TypeName[type]; }
  inline const char* GetRegionName() { return RegionName[region]; }
  inline int GetYear() { return year; }
};

#endif
