#ifndef HISTOCOLLECTION_H
#define HISTOCOLLECTION_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <functional>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <map>
#include <list>
#include <vector>
#include <bitset>
#include <TCanvas.h>
#include <TSystem.h>
#include <TPostScript.h>
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TMath.h>
#include <TLegend.h>
#include <TProfile.h>
#include <TGraph.h>
#include <TRef.h>
#include <TList.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>
#include <TDCacheFile.h>
#include <TLorentzVector.h>
#include "TIterator.h"
#include "string"
// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "TString.h"
#include "vector"

using namespace std;

class HistoCollection {
private:
  map<string,TH1F*> histomap;
public:
  HistoCollection() {};
  void add(string name,TH1F* histo) { histomap[name] = histo; }
  float getBin(string name,float x) { histomap[name]->GetBinContent( histomap[name]->GetXaxis()->FindBin(x) ); }
  bool contains(string name) { return histomap.find(name) != histomap.end(); }
};

#endif
