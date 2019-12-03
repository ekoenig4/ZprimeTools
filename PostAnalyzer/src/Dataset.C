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

bool contains_substr(string str,string delim) {
  return strstr(str.c_str(),delim.c_str()) != NULL;
}

const std::string Dataset::datalist[] = {"egamma","met","singleele","singlepho","signal","zjets_nlo","zjets","wjets_nlo","wjets","dyjets_nlo","dyjets","gjets","st","ttjets","ewk","qcd"};
const std::map<std::string,Type> Dataset::typemap = {
  {"egamma",Data},{"met",Data},{"singleele",Data},{"singlepho",Data},{"signal",Signal},{"zjets_nlo",ZJets},{"zjets",ZJets},
  {"wjets_nlo",WJets},{"wjets",WJets},{"dyjets_nlo",DYJets},{"dyjets",DYJets},
  {"qcd",QCD},{"st",ST},{"ttjets",TTJets},{"gjets",GJets},{"ewk",EWK}
};
Dataset::SubsetList Dataset::dataset;

Dataset::SubsetList::SubsetList() {
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
    if ( contains_substr(filename,".txt") ) {
      addDataset(ntuples,filename);
    }
  }
}

void Dataset::SubsetList::addDataset(string path,string filename) {
  ifstream infile( (path+filename).c_str() );
  if (!infile.is_open()) {
    cout << "Unable to read " << path+filename << endl;
    return;
  }
  string data = filename.erase( filename.length()-4,4 );
  string line;
  Subset subset; string subname;
  while ( infile >> line ) {
    if ( contains_substr(line,"#") ) continue;
    if ( contains_substr(line,">>") ) {
      subname = line.erase(0,2);
      subset[subname] = vector<string>();
    } else {
      if ( isDir(line) ) {
	subset[subname].push_back(line);
      }
    }
  }
  (*this)[data] = subset;
}

Dataset::Dataset() {
  type = nType;
  region = nRegion;
  year = 0;
  isInclusive = false;
  isData = false;
  isSignal = false;
  PID = 0;
}

void Dataset::setTypeInfo(string path) {
  for (string data : datalist) {
    Subset subset = dataset[data];
    for (auto& sub : subset) {
      for (string directory : sub.second) {
	if ( contains_substr(path,directory) ) {
	  type = typemap.find(data)->second;
	  if ( type == WJets || type == DYJets ) {
	    isInclusive = contains_substr(sub.first,"MLM");
	  } else {
	    isInclusive = false;
	  }
	}
      }
    }
  }
}

void Dataset::setInfo(string path) {
  setTypeInfo(path);
  isData = (type == Data);
  isSignal = (type == Signal);
  if (type == WJets) PID = 24;
  if (type == ZJets || type == DYJets) PID = 23;
}

void Dataset::printDataset() {
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
