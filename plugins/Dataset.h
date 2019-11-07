#ifndef Dataset_h
#define Dataset_h

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "ZprimeEnums.h"
struct TypeInfo {
  Type type;
  bool isInclusive = false;
};

class Dataset {
  typedef std::map<std::string,std::vector<std::string>> Subset;
  std::map<std::string,Subset> dataset;
  void addDataset(std::string path,std::string filename);
public:
  static const std::string datalist[10];
  static const std::map<std::string,Type> typemap;
  Dataset();
  TypeInfo getTypeInfo(std::string path);
  std::string toString();
};

#endif
