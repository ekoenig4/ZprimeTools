#ifndef COLLECTIONS_H
#define COLLECTIONS_H

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
#include <TLorentzVector.h>
#include "TIterator.h"
#include "string"
// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "TString.h"
#include "vector"

using namespace std;

struct TH1FCollection : public map<string,TH1F*> {
  float getBin(string name,float x) {
    TH1F* histo = (*this)[name];
    return histo->GetBinContent( histo->GetXaxis()->FindBin(x) );
  }
};
  
struct TH2FCollection : public map<string,TH2F*> {
  float getBin(string name,float x,float y) {
    TH2F* histo = (*this)[name];
    return histo->GetBinContent( histo->GetXaxis()->FindBin(x),histo->GetYaxis()->FindBin(y) );
  }
};

class ShapeUncCollection {
 private:
  TDirectory* dir;
  struct ShapeUnc {
    TTree* treeUp;
    TTree* treeDn;
    string name;
    ShapeUnc(string name,TTree* treeUp,TTree* treeDn) {
      this->name = name;
      this->treeUp = treeUp;
      this->treeDn = treeDn;
    }
    void fillUp() { treeUp->Fill(); }
    void fillDn() { treeDn->Fill(); }
  };
  map<string,ShapeUnc*> uncmap;
 public:
  void setDir(TDirectory* dir) { this->dir = dir; }
  void addUnc(string name) {
    dir->cd();
    TTree* treeUp = new TTree( (name+"Up").c_str(), (name+"Up").c_str());
    TTree* treeDn = new TTree( (name+"Down").c_str(), (name+"Down").c_str());
    uncmap[name] = new ShapeUnc(name,treeUp,treeDn);
  }
  TTree* getTreeUp(string name) { return uncmap[name]->treeUp; }
  TTree* getTreeDn(string name) { return uncmap[name]->treeDn; }
  void fillUp(string name) { uncmap[name]->fillUp(); }
  void fillDn(string name) { uncmap[name]->fillDn(); }
  bool contains(string name) { return uncmap.find(name) != uncmap.end(); }
};


class ScaleUncCollection {
 private:
  TTree* tree;
  struct ScaleUnc {
    string name;
    TH1F* histo;
    float up;
    float dn;
    ScaleUnc(string name,TH1F* histo) {
      this->name = name;
      this->histo = histo;
      up = dn = 0;
    }
    void setUnc(float up,float dn) {
      this->up = up;
      this->dn = dn;
    }
    float getBin(float x) { return histo->GetBinContent( histo->GetXaxis()->FindBin(x) ); }
  };
  map<string,ScaleUnc*> uncmap;
 public:
  void setTree(TTree* tree) { this->tree = tree; }
  void addUnc(string name,TH1F* histo) {
    uncmap[name] = new ScaleUnc(name,histo);
    tree->Branch( (name+"Up").c_str(),&uncmap[name]->up, (name+"Up").c_str());
    tree->Branch( (name+"Down").c_str(),&uncmap[name]->dn, (name+"Down").c_str());
  }
  TH1F* getHisto(string name) { return uncmap[name]->histo; }
  float getBin(string name, float x) { return uncmap[name]->getBin(x); }
  void setUnc(string name,float up,float dn) { uncmap[name]->setUnc(up,dn); }
  bool contains(string name) { return uncmap.find(name) != uncmap.end(); }
};

#endif
