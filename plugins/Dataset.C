#ifndef Dataset_C
#define Dataset_C

#include <sys/stat.h>
#include <TSystemDirectory.h>
#include <TList.h>
#include <fstream>

#include "Dataset.h"

using namespace std;

bool isDir(const string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

bool contains(string str,string delim) {
  return strstr(str.c_str(),delim.c_str()) != NULL;
}

const std::string Dataset::datalist[] = {"egamma","met","signal","zjets","wjets","dyjets","gjets","ttjets","ewk","qcd"};
const std::map<std::string,Type> Dataset::typemap = {
  {"egamma",Data},{"met",Data},{"signal",Signal},{"zjets",ZJets},{"wjets",WJets},{"dyjets",DYJets},{"qcd",QCD},{"ttjets",TTJets},{"gjets",GJets},{"ewk",EWK}
};

Dataset::Dataset() {
  string ntuples;
  string ntuple_path1 = "ntuples/";
  string ntuple_path2 = "../datasets/ntuples/";
  if ( isDir(ntuple_path1) ) ntuples = ntuple_path1;
  else if ( isDir(ntuple_path2) ) ntuples = ntuple_path2;
  cout << "Using path " << ntuples << " for datasets." << endl;
  TSystemDirectory dir(ntuples.c_str(),ntuples.c_str());
  TList* filelist = dir.GetListOfFiles();
  TIter fileiter(filelist);
  TSystemFile* file;
  while ( (file = (TSystemFile*)fileiter()) ) {
    string filename = (string)file->GetName();
    if ( contains(filename,".txt") ) {
      addDataset(ntuples,filename);
    }
  }
}

void Dataset::addDataset(string path,string filename) {
  ifstream infile( (path+filename).c_str() );
  if (!infile.is_open()) {
    cout << "Unable to read " << path+filename << endl;
    return;
  }
  string data = filename.erase( filename.length()-4,4 );
  string line;
  Subset subset; string subname;
  while ( infile >> line ) {
    if ( contains(line,"#") ) continue;
    if ( contains(line,">>") ) {
      subname = line.erase(0,2);
      subset[subname] = vector<string>();
    } else {
      if ( isDir(line) ) {
	subset[subname].push_back(line);
      }
    }
  }
  dataset[data] = subset;
}

TypeInfo Dataset::getTypeInfo(string path) {
  TypeInfo typeinfo;
  for (string data : datalist) {
    Subset subset = dataset[data];
    for (auto& sub : subset) {
      for (string directory : sub.second) {
	if ( contains(path,directory) ) {
	  Type type = typemap.find(data)->second;
	  typeinfo.type = type;
	  if ( type == WJets || type == DYJets ) {
	    typeinfo.isInclusive = contains(sub.first,"MLM");
	  } else {
	    typeinfo.isInclusive = false;
	  }
	}
      }
    }
  }
  return typeinfo;
}

string Dataset::toString() {
  for (string data : datalist) {
    Subset subset = dataset[data];
    for (auto& sub : subset) {
      cout << data << "----" << sub.first << endl;
      for (string directory : sub.second) {
	cout << "------" << directory << endl;
      }
    }
  }
}

#endif
