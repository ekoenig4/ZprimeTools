//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  8 10:15:33 2017 by ROOT version 6.06/01
// from TTree EventTree/Event data (tag V08_00_24_00)
// found on file: /hdfs/store/user/uhussain/Zprime_Ntuples_Mar7/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/170306_174919/0000/ggtree_mc_53.root
//////////////////////////////////////////////////////////

#ifndef ZprimeJetsCommon_h
#define ZprimeJetsCommon_h

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

#include "ZprimeJetsCutConfig.h"

#include "ScaleUnc.h"
#include "ShapeUnc.h"

using namespace std;
class ZprimeJetsCommon {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  TFile *output;
  static const int maxHisto = 50;
  TTree *tree;

  static const bool debug = false;
  enum Type { Data,Signal,WJets,ZJets,DYJets,QCD,TTJets,GJets,WW,WZ,ZZ,Total };
  
  struct DataMC {
    Type type;
    string name[Total];
    bool isInclusive;
    bool isData;
    int PID;
    DataMC(){
      string name[Total] = {"Data","Signal","WJets","ZJets","DYJets","QCD","TTJets","GJets","WW","WZ","ZZ"};
      for (int i = 0; i < Total; i++) this->name[i] = name[i];
    };
    DataMC(string filename);
    bool isW_or_ZJet();
    inline string getName() { return name[type]; }
  } sample;
  
  struct TH1FCollection : public map<string,TH1F*> {
    float getBin(string name,float x) {
      TH1F* histo = (*this)[name];
      return histo->GetBinContent( histo->GetXaxis()->FindBin(x) );
    }
  } th1fmap;
  
  struct TH2FCollection : public map<string,TH2F*> {
    float getBin(string name,float x,float y) {
      TH2F* histo = (*this)[name];
      return histo->GetBinContent( histo->GetXaxis()->FindBin(x),histo->GetYaxis()->FindBin(y) );
    }
  } th2fmap;
  
  ScaleUncCollection* scaleUncs;
  ShapeUncCollection* shapeUncs;
  
  float bosonPt;

  float weight;
  float kfactor;
  
  //Declaring these jet Vectors and jet substructure vectors
  vector<int> jetCand;
  vector<double>j1PFConsEt;
  vector<double>j1PFConsPt;
  vector<double>j1PFConsEta;
  vector<double>j1PFConsPhi;
  vector<int>j1PFConsPID;
  float j1TotConsPt;

  float j1Mass;

  float Pt123Fraction,Pt123,PtRawFrac,j1pT;

  float hadronPt[3];
  
  float ChNemPtFrac,ChNemPt,ChNemPt123;
   
  //getPFCandidates
  int TotalPFCandidates, ChargedPFCandidates,NeutralPFCandidates,GammaPFCandidates;
  int LeptonPFCandidates;
   
  TH1F *h_nVtx[maxHisto],*h_nVtx2[maxHisto],*h_metcut,*h_lepMET_MT,*h_dphimin,*h_metFilters,*h_kfactor,*h_pfMETall[maxHisto],*h_pfMET200[maxHisto],*h_nJets[maxHisto],*h_pfMET[maxHisto],*h_pfMETPhi[maxHisto];
  TH1F *h_j1Pt[maxHisto], *h_j1Eta[maxHisto], *h_j1Phi[maxHisto], *h_j1etaWidth[maxHisto], *h_j1phiWidth[maxHisto],*h_j1nCons[maxHisto], *h_PF123PtFraction[maxHisto],*h_Pt123[maxHisto],*h_j1TotConsPt[maxHisto]; 
  TH1F *h_j1TotPFCands[maxHisto], *h_j1ChPFCands[maxHisto], *h_j1NeutPFCands[maxHisto], *h_j1GammaPFCands[maxHisto], *h_j1CHF[maxHisto], *h_j1NHF[maxHisto], *h_j1ChMultiplicity[maxHisto], *h_j1NeutMultiplicity[maxHisto],*h_j1Mt[maxHisto];
  TH1F *h_j1Mass[maxHisto],*h_j1JEC[maxHisto],*h_j1PID[maxHisto],*h_j1Lepton[maxHisto];

  TH1F *h_PtRawFrac[maxHisto];
  TH1F *h_ChNemPtFrac[maxHisto],*h_ChNemPt[maxHisto],*h_ChNemPt123[maxHisto];
  TH1F *h_ChPercCons[maxHisto],*h_NhPercCons[maxHisto],*h_GammaPercCons[maxHisto];
  TH1F *h_ChargedPt[maxHisto],*h_NeutralPt[maxHisto],*h_PhotonPt[maxHisto];
  TH1F *h_ChPercPt[maxHisto],*h_NhPercPt[maxHisto],*h_GammaPercPt[maxHisto];

  TH1F *h_genHT[maxHisto],*h_eventWeight[maxHisto],*h_puTrueReWeight,*h_puTrueUnWeight;
  TH1F *h_genBosonPt,*h_genBosonPtwK;
  
  TH1D *h_cutflow;
  
  // Uncertainty Plots
  TH2F *h_TrackerPtUnc,*h_EcalPtUnc,*h_HcalPtUnc;
  TH1F *h_nlo_ewk;
  
  // Fixed size dimensions of array or collections stored in the TTree if any.
  // Declaration of leaf types
  Int_t           run;
  Long64_t        event;
  Int_t           lumis;
  Bool_t          isData;
  Int_t           nVtx;
  Int_t           nGoodVtx;
  Int_t           nTrksPV;
  Bool_t          isPVGood;
  Float_t         vtx;
  Float_t         vty;
  Float_t         vtz;
  Float_t         rho;
  Float_t         rhoCentral;
  ULong64_t       HLTEleMuX;
  ULong64_t       HLTPho;
  ULong64_t       HLTJet;
  ULong64_t       HLTEleMuXIsPrescaled;
  ULong64_t       HLTPhoIsPrescaled;
  ULong64_t       HLTJetIsPrescaled;
  vector<int>     *phoPrescale;
  vector<float>   *pdf;
  Float_t         pthat;
  Float_t         processID;
  Float_t         genWeight;
  Float_t         genHT;
  TString         *EventTag;
  Int_t           nPUInfo;
  vector<int>     *nPU;
  vector<int>     *puBX;
  vector<float>   *puTrue;
  Int_t           nMC;
  vector<int>     *mcPID;
  vector<float>   *mcVtx;
  vector<float>   *mcVty;
  vector<float>   *mcVtz;
  vector<float>   *mcPt;
  vector<float>   *mcMass;
  vector<float>   *mcEta;
  vector<float>   *mcPhi;
  vector<float>   *mcE;
  vector<float>   *mcEt;
  vector<int>     *mcGMomPID;
  vector<int>     *mcMomPID;
  vector<float>   *mcMomPt;
  vector<float>   *mcMomMass;
  vector<float>   *mcMomEta;
  vector<float>   *mcMomPhi;
  vector<unsigned short> *mcStatusFlag;
  vector<int>     *mcParentage;
  vector<int>     *mcStatus;
  vector<float>   *mcCalIsoDR03;
  vector<float>   *mcTrkIsoDR03;
  vector<float>   *mcCalIsoDR04;
  vector<float>   *mcTrkIsoDR04;
  Float_t         genMET;
  Float_t         genMETPhi;
  
  Int_t           metFilters;
  Float_t         pfMET;
  Float_t         caloMET;
  //ROOT::Math::DisplacementVector2D<ROOT::Math::Cartesian2D<float>,ROOT::Math::DefaultCoordinateSystemTag> *caloMet;
  Float_t         fCoordinates_fX;
  Float_t         fCoordinates_fY;
  Float_t         pfMETPhi;
  Float_t         pfMETsumEt;
  Float_t         pfMETmEtSig;
  Float_t         pfMETSig;
  Float_t         pfMET_T1JERUp;
  Float_t         pfMET_T1JERDo;
  Float_t         pfMET_T1JESUp;
  Float_t         pfMET_T1JESDo;
  Float_t         pfMET_T1UESUp;
  Float_t         pfMET_T1UESDo;
  Float_t         pfMETPhi_T1JESUp;
  Float_t         pfMETPhi_T1JESDo;
  Float_t         pfMETPhi_T1UESUp;
  Float_t         pfMETPhi_T1UESDo;
  Int_t           nPho;
  vector<float>   *phoE;
  vector<float>   *phoEt;
  vector<float>   *phoEta;
  vector<float>   *phoPhi;
  vector<float>   *phoCalibE;
  vector<float>   *phoCalibEt;
  vector<float>   *phoSCE;
  vector<float>   *phoSCRawE;
  vector<float>   *phoESEnP1;
  vector<float>   *phoESEnP2;
  vector<float>   *phoSCEta;
  vector<float>   *phoSCPhi;
  vector<float>   *phoSCEtaWidth;
  vector<float>   *phoSCPhiWidth;
  vector<float>   *phoSCBrem;
  vector<int>     *phohasPixelSeed;
  vector<int>     *phoEleVeto;
  vector<float>   *phoR9;
  vector<float>   *phoHoverE;
  vector<float>   *phoE1x3;
  vector<float>   *phoE1x5;
  vector<float>   *phoE2x2;
  vector<float>   *phoE2x5Max;
  vector<float>   *phoE5x5;
  vector<float>   *phoESEffSigmaRR;
  vector<float>   *phoSigmaIEtaIEtaFull5x5;
  vector<float>   *phoSigmaIEtaIPhiFull5x5;
  vector<float>   *phoSigmaIPhiIPhiFull5x5;
  vector<float>   *phoE1x3Full5x5;
  vector<float>   *phoE1x5Full5x5;
  vector<float>   *phoE2x2Full5x5;
  vector<float>   *phoE2x5MaxFull5x5;
  vector<float>   *phoE5x5Full5x5;
  vector<float>   *phoR9Full5x5;
  vector<float>   *phoPFChIso;
  vector<float>   *phoPFPhoIso;
  vector<float>   *phoPFNeuIso;
  vector<float>   *phoPFChWorstIso;
  vector<float>   *phoCITKChIso;
  vector<float>   *phoCITKPhoIso;
  vector<float>   *phoCITKNeuIso;
  vector<float>   *phoIDMVA;
  vector<unsigned int> *phoFiredSingleTrgs;
  vector<unsigned int> *phoFiredDoubleTrgs;
  vector<unsigned int> *phoFiredL1Trgs;
  vector<float>   *phoSeedTime;
  vector<float>   *phoSeedEnergy;
  vector<unsigned short> *phoxtalBits;
  vector<unsigned short> *phoIDbit;
  Int_t           npfPho;
  vector<float>   *pfphoEt;
  vector<float>   *pfphoEta;
  vector<float>   *pfphoPhi;
  Int_t           nEle;
  vector<int>     *eleCharge;
  vector<int>     *eleChargeConsistent;
  vector<float>   *eleEn;
  vector<float>   *eleSCEn;
  vector<float>   *eleESEnP1;
  vector<float>   *eleESEnP2;
  vector<float>   *eleD0;
  vector<float>   *eleDz;
  vector<float>   *eleSIP;
  vector<float>   *elePt;
  vector<float>   *eleEta;
  vector<float>   *elePhi;
  vector<float>   *eleR9;
  vector<float>   *eleCalibPt;
  vector<float>   *eleCalibEn;
  vector<float>   *eleSCEta;
  vector<float>   *eleSCPhi;
  vector<float>   *eleSCRawEn;
  vector<float>   *eleSCEtaWidth;
  vector<float>   *eleSCPhiWidth;
  vector<float>   *eleHoverE;
  vector<float>   *eleEoverP;
  vector<float>   *eleEoverPout;
  vector<float>   *eleEoverPInv;
  vector<float>   *eleBrem;
  vector<float>   *eledEtaAtVtx;
  vector<float>   *eledPhiAtVtx;
  vector<float>   *eledEtaAtCalo;
  vector<float>   *eleSigmaIEtaIEtaFull5x5;
  vector<float>   *eleSigmaIPhiIPhiFull5x5;
  vector<int>     *eleConvVeto;
  vector<int>     *eleMissHits;
  vector<float>   *eleESEffSigmaRR;
  vector<float>   *elePFChIso;
  vector<float>   *elePFPhoIso;
  vector<float>   *elePFNeuIso;
  vector<float>   *elePFPUIso;
  vector<float>   *elePFClusEcalIso;
  vector<float>   *elePFClusHcalIso;
  vector<float>   *elePFMiniIso;
  vector<float>   *eleIDMVA;
  vector<float>   *eleIDMVAHZZ;
  vector<float>   *eledEtaseedAtVtx;
  vector<float>   *eleE1x5;
  vector<float>   *eleE2x5;
  vector<float>   *eleE5x5;
  vector<float>   *eleE1x5Full5x5;
  vector<float>   *eleE2x5Full5x5;
  vector<float>   *eleE5x5Full5x5;
  vector<float>   *eleR9Full5x5;
  vector<int>     *eleEcalDrivenSeed;
  vector<float>   *eleDr03EcalRecHitSumEt;
  vector<float>   *eleDr03HcalDepth1TowerSumEt;
  vector<float>   *eleDr03HcalDepth2TowerSumEt;
  vector<float>   *eleDr03HcalTowerSumEt;
  vector<float>   *eleDr03TkSumPt;
  vector<float>   *elecaloEnergy;
  vector<float>   *eleTrkdxy;
  vector<float>   *eleKFHits;
  vector<float>   *eleKFChi2;
  vector<float>   *eleGSFChi2;
  vector<vector<float> > *eleGSFPt;
  vector<vector<float> > *eleGSFEta;
  vector<vector<float> > *eleGSFPhi;
  vector<vector<float> > *eleGSFCharge;
  vector<vector<int> > *eleGSFHits;
  vector<vector<int> > *eleGSFMissHits;
  vector<vector<int> > *eleGSFNHitsMax;
  vector<vector<float> > *eleGSFVtxProb;
  vector<vector<float> > *eleGSFlxyPV;
  vector<vector<float> > *eleGSFlxyBS;
  vector<vector<float> > *eleBCEn;
  vector<vector<float> > *eleBCEta;
  vector<vector<float> > *eleBCPhi;
  vector<vector<float> > *eleBCS25;
  vector<vector<float> > *eleBCS15;
  vector<vector<float> > *eleBCSieie;
  vector<vector<float> > *eleBCSieip;
  vector<vector<float> > *eleBCSipip;
  vector<unsigned int> *eleFiredSingleTrgs;
  vector<unsigned int> *eleFiredDoubleTrgs;
  vector<unsigned int> *eleFiredL1Trgs;
  vector<unsigned short> *eleIDbit;
  Int_t           npfHF;
  vector<float>   *pfHFEn;
  vector<float>   *pfHFECALEn;
  vector<float>   *pfHFHCALEn;
  vector<float>   *pfHFPt;
  vector<float>   *pfHFEta;
  vector<float>   *pfHFPhi;
  vector<float>   *pfHFIso;
  Int_t           nTau;
  vector<bool>    *taupfTausDiscriminationByDecayModeFinding;
  vector<bool>    *taupfTausDiscriminationByDecayModeFindingNewDMs;
  vector<bool>    *tauByMVA6VLooseElectronRejection;
  vector<bool>    *tauByMVA6LooseElectronRejection;
  vector<bool>    *tauByMVA6MediumElectronRejection;
  vector<bool>    *tauByMVA6TightElectronRejection;
  vector<bool>    *tauByMVA6VTightElectronRejection;
  vector<bool>    *tauByLooseMuonRejection3;
  vector<bool>    *tauByTightMuonRejection3;
  vector<bool>    *tauByLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<bool>    *tauByMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<bool>    *tauByTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<float>   *tauCombinedIsolationDeltaBetaCorrRaw3Hits;
  vector<float>   *tauByIsolationMVArun2v1DBnewDMwLTraw;
  vector<float>   *tauByIsolationMVArun2v1DBoldDMwLTraw;
  vector<float>   *tauByIsolationMVArun2v1PWnewDMwLTraw;
  vector<float>   *tauByIsolationMVArun2v1PWoldDMwLTraw;
  vector<bool>    *tauByVTightIsolationMVArun2v1DBnewDMwLT;
  vector<bool>    *tauByVTightIsolationMVArun2v1DBoldDMwLT;
  vector<bool>    *tauByVTightIsolationMVArun2v1PWnewDMwLT;
  vector<bool>    *tauByVTightIsolationMVArun2v1PWoldDMwLT;
  vector<bool>    *tauByTightIsolationMVArun2v1DBnewDMwLT;
  vector<bool>    *tauByTightIsolationMVArun2v1DBoldDMwLT;
  vector<bool>    *tauByTightIsolationMVArun2v1PWnewDMwLT;
  vector<bool>    *tauByTightIsolationMVArun2v1PWoldDMwLT;
  vector<bool>    *tauByMediumIsolationMVArun2v1DBnewDMwLT;
  vector<bool>    *tauByMediumIsolationMVArun2v1DBoldDMwLT;
  vector<bool>    *tauByMediumIsolationMVArun2v1PWnewDMwLT;
  vector<bool>    *tauByMediumIsolationMVArun2v1PWoldDMwLT;
  vector<bool>    *tauByLooseIsolationMVArun2v1DBnewDMwLT;
  vector<bool>    *tauByLooseIsolationMVArun2v1DBoldDMwLT;
  vector<bool>    *tauByLooseIsolationMVArun2v1PWnewDMwLT;
  vector<bool>    *tauByLooseIsolationMVArun2v1PWoldDMwLT;
  vector<bool>    *tauByVLooseIsolationMVArun2v1DBnewDMwLT;
  vector<bool>    *tauByVLooseIsolationMVArun2v1DBoldDMwLT;
  vector<bool>    *tauByVLooseIsolationMVArun2v1PWnewDMwLT;
  vector<bool>    *tauByVLooseIsolationMVArun2v1PWoldDMwLT;
  vector<float>   *tauEta;
  vector<float>   *tauPhi;
  vector<float>   *tauPt;
  vector<float>   *tauEt;
  vector<float>   *tauCharge;
  vector<float>   *tauP;
  vector<float>   *tauPx;
  vector<float>   *tauPy;
  vector<float>   *tauPz;
  vector<float>   *tauVz;
  vector<float>   *tauEnergy;
  vector<float>   *tauMass;
  vector<float>   *tauDxy;
  vector<float>   *tauZImpact;
  vector<int>     *tauDecayMode;
  vector<bool>    *tauLeadChargedHadronExists;
  vector<float>   *tauLeadChargedHadronEta;
  vector<float>   *tauLeadChargedHadronPhi;
  vector<float>   *tauLeadChargedHadronPt;
  vector<float>   *tauChargedIsoPtSum;
  vector<float>   *tauNeutralIsoPtSum;
  vector<float>   *tauPuCorrPtSum;
  vector<int>     *tauNumSignalPFChargedHadrCands;
  vector<int>     *tauNumSignalPFNeutrHadrCands;
  vector<int>     *tauNumSignalPFGammaCands;
  vector<int>     *tauNumSignalPFCands;
  vector<int>     *tauNumIsolationPFChargedHadrCands;
  vector<int>     *tauNumIsolationPFNeutrHadrCands;
  vector<int>     *tauNumIsolationPFGammaCands;
  vector<int>     *tauNumIsolationPFCands;
  vector<float>   *taufootprintCorrection;
  vector<float>   *tauphotonPtSumOutsideSignalCone;
  vector<float>   *taudz;
  vector<float>   *taudxy;
  Int_t           nMu;
  vector<float>   *muPt;
  vector<float>   *muEn;
  vector<float>   *muEta;
  vector<float>   *muPhi;
  vector<int>     *muCharge;
  vector<int>     *muType;
  vector<unsigned short> *muIDbit;
  vector<float>   *muD0;
  vector<float>   *muDz;
  vector<float>   *muSIP;
  vector<float>   *muChi2NDF;
  vector<float>   *muInnerD0;
  vector<float>   *muInnerDz;
  vector<int>     *muTrkLayers;
  vector<int>     *muPixelLayers;
  vector<int>     *muPixelHits;
  vector<int>     *muMuonHits;
  vector<int>     *muStations;
  vector<int>     *muMatches;
  vector<int>     *muTrkQuality;
  vector<float>   *muIsoTrk;
  vector<float>   *muPFChIso;
  vector<float>   *muPFPhoIso;
  vector<float>   *muPFNeuIso;
  vector<float>   *muPFPUIso;
  vector<float>   *muPFMiniIso;
  vector<unsigned int> *muFiredTrgs;
  vector<unsigned int> *muFiredL1Trgs;
  vector<float>   *muInnervalidFraction;
  vector<float>   *musegmentCompatibility;
  vector<float>   *muchi2LocalPosition;
  vector<float>   *mutrkKink;
  vector<float>   *muBestTrkPtError;
  vector<float>   *muBestTrkPt;
  Int_t           nJet;
  vector<double>  *jetetaWidth;
  vector<double>  *jetphiWidth;
  vector<double>  *jetnPhotons;
  vector<double>  *jetnCHPions;
  vector<double>  *jetnMisc;
  vector<vector<int> > *jetMiscPID;
  vector<vector<double> > *JetsPFConsPt;
  vector<vector<double> > *JetsPFConsEta;
  vector<vector<double> > *JetsPFConsPhi;
  vector<vector<double> > *JetsPFConsEt;
  vector<vector<int> > *JetsPFConsPID;
  vector<float>   *jetPt;
  vector<float>   *jetEn;
  vector<float>   *jetEta;
  vector<float>   *jetPhi;
  vector<float>   *jetRawPt;
  vector<float>   *jetRawEn;
  vector<float>   *jetMt;
  vector<float>   *jetArea;
  vector<float>   *jetLeadTrackPt;
  vector<float>   *jetLeadTrackEta;
  vector<float>   *jetLeadTrackPhi;
  vector<int>     *jetLepTrackPID;
  vector<float>   *jetLepTrackPt;
  vector<float>   *jetLepTrackEta;
  vector<float>   *jetLepTrackPhi;
  vector<float>   *jetCSV2BJetTags;
  vector<float>   *jetJetProbabilityBJetTags;
  vector<float>   *jetpfCombinedMVAV2BJetTags;
  
  vector<int>     *jetPartonID;
  vector<int>     *jetHadFlvr;
  vector<float>   *jetGenJetEn;
  vector<float>   *jetGenJetPt;
  vector<float>   *jetGenJetEta;
  vector<float>   *jetGenJetPhi;
  vector<int>     *jetGenPartonID;
  vector<float>   *jetGenEn;
  vector<float>   *jetGenPt;
  vector<float>   *jetGenEta;
  vector<float>   *jetGenPhi;
  vector<int>     *jetGenPartonMomID;
  vector<float>   *jetP4Smear;
  vector<float>   *jetP4SmearUp;
  vector<float>   *jetP4SmearDo;
  
  vector<bool>    *jetPFLooseId;
  vector<int>     *jetID;
  vector<float>   *jetPUID;
  vector<int>     *jetPUFullID;
  vector<float>   *jetJECUnc;
  vector<unsigned int> *jetFiredTrgs;
  vector<float>   *jetCHF;
  vector<float>   *jetNHF;
  vector<float>   *jetCEF;
  vector<float>   *jetNEF;
  vector<int>     *jetNCH;
  vector<int>     *jetNNP;
  vector<float>   *jetMUF;
  vector<float>   *jetVtxPt;
  vector<float>   *jetVtxMass;
  vector<float>   *jetVtxNtrks;
  vector<float>   *jetVtx3DVal;
  vector<float>   *jetVtx3DSig;
  Int_t           nAK8Jet;
  vector<float>   *AK8JetPt;
  vector<float>   *AK8JetEn;
  vector<float>   *AK8JetRawPt;
  vector<float>   *AK8JetRawEn;
  vector<float>   *AK8JetEta;
  vector<float>   *AK8JetPhi;
  vector<float>   *AK8JetMass;
  vector<float>   *AK8Jet_tau1;
  vector<float>   *AK8Jet_tau2;
  vector<float>   *AK8Jet_tau3;
  vector<float>   *AK8JetCHF;
  vector<float>   *AK8JetNHF;
  vector<float>   *AK8JetCEF;
  vector<float>   *AK8JetNEF;
  vector<int>     *AK8JetNCH;
  vector<int>     *AK8JetNNP;
  vector<float>   *AK8JetMUF;
  vector<int>     *AK8Jetnconstituents;
  vector<bool>    *AK8JetPFLooseId;
  vector<bool>    *AK8JetPFTightLepVetoId;
  vector<float>   *AK8JetSoftDropMass;
  vector<float>   *AK8JetSoftDropMassCorr;
  vector<float>   *AK8JetPrunedMass;
  vector<float>   *AK8JetPrunedMassCorr;
  vector<float>   *AK8JetpfBoostedDSVBTag;
  vector<float>   *AK8JetDSVnewV4;
  vector<float>   *AK8JetCSV;
  vector<float>   *AK8JetJECUnc;
  vector<float>   *AK8JetL2L3corr;
  vector<float>   *AK8puppiPt;
  vector<float>   *AK8puppiMass;
  vector<float>   *AK8puppiEta;
  vector<float>   *AK8puppiPhi;
  vector<float>   *AK8puppiTau1;
  vector<float>   *AK8puppiTau2;
  vector<float>   *AK8puppiTau3;
  vector<float>   *AK8puppiSDL2L3corr;
  vector<float>   *AK8puppiSDMass;
  vector<float>   *AK8puppiSDMassL2L3Corr;
  vector<int>     *nAK8SDSJ;
  vector<vector<float> > *AK8SDSJPt;
  vector<vector<float> > *AK8SDSJEta;
  vector<vector<float> > *AK8SDSJPhi;
  vector<vector<float> > *AK8SDSJMass;
  vector<vector<float> > *AK8SDSJE;
  vector<vector<int> > *AK8SDSJCharge;
  vector<vector<int> > *AK8SDSJFlavour;
  vector<vector<float> > *AK8SDSJCSV;
  vector<int>     *nAK8puppiSDSJ;
  vector<vector<float> > *AK8puppiSDSJPt;
  vector<vector<float> > *AK8puppiSDSJEta;
  vector<vector<float> > *AK8puppiSDSJPhi;
  vector<vector<float> > *AK8puppiSDSJMass;
  vector<vector<float> > *AK8puppiSDSJE;
  vector<vector<int> > *AK8puppiSDSJCharge;
  vector<vector<int> > *AK8puppiSDSJFlavour;
  vector<vector<float> > *AK8puppiSDSJCSV;

  // List of branches
  TBranch        *b_run;   //!
  TBranch        *b_event;   //!
  TBranch        *b_lumis;   //!
  TBranch        *b_isData;   //!
  TBranch        *b_nVtx;   //!
  TBranch        *b_nGoodVtx;   //!
  TBranch        *b_nTrksPV;   //!
  TBranch        *b_isPVGood;   //!
  TBranch        *b_vtx;   //!
  TBranch        *b_vty;   //!
  TBranch        *b_vtz;   //!
  TBranch        *b_rho;   //!
  TBranch        *b_rhoCentral;   //!
  TBranch        *b_HLTEleMuX;   //!
  TBranch        *b_HLTPho;   //!
  TBranch        *b_HLTJet;   //!
  TBranch        *b_HLTEleMuXIsPrescaled;   //!
  TBranch        *b_HLTPhoIsPrescaled;   //!
  TBranch        *b_HLTJetIsPrescaled;   //!
  TBranch        *b_phoPrescale;   //!
  TBranch        *b_pdf;   //!
  TBranch        *b_pthat;   //!
  TBranch        *b_processID;   //!
  TBranch        *b_genWeight;   //!
  TBranch        *b_genHT;   //!
  TBranch        *b_EventTag;   //!
  TBranch        *b_nPUInfo;   //!
  TBranch        *b_nPU;   //!
  TBranch        *b_puBX;   //!
  TBranch        *b_puTrue;   //!
  TBranch        *b_nMC;   //!
  TBranch        *b_mcPID;   //!
  TBranch        *b_mcVtx;   //!
  TBranch        *b_mcVty;   //!
  TBranch        *b_mcVtz;   //!
  TBranch        *b_mcPt;   //!
  TBranch        *b_mcMass;   //!
  TBranch        *b_mcEta;   //!
  TBranch        *b_mcPhi;   //!
  TBranch        *b_mcE;   //!
  TBranch        *b_mcEt;   //!
  TBranch        *b_mcGMomPID;   //!
  TBranch        *b_mcMomPID;   //!
  TBranch        *b_mcMomPt;   //!
  TBranch        *b_mcMomMass;   //!
  TBranch        *b_mcMomEta;   //!
  TBranch        *b_mcMomPhi;   //!
  TBranch        *b_mcStatusFlag;   //!
  TBranch        *b_mcParentage;   //!
  TBranch        *b_mcStatus;   //!
  TBranch        *b_mcCalIsoDR03;   //!
  TBranch        *b_mcTrkIsoDR03;   //!
  TBranch        *b_mcCalIsoDR04;   //!
  TBranch        *b_mcTrkIsoDR04;   //!
  TBranch        *b_genMET;   //!
  TBranch        *b_genMETPhi;   //!
  TBranch        *b_metFilters;   //!
  TBranch        *b_pfMET;   //!
  TBranch        *b_caloMET;   //!
  TBranch        *b_caloMet_fCoordinates_fX;   //!
  TBranch        *b_caloMet_fCoordinates_fY;   //!
  TBranch        *b_pfMETPhi;   //!
  TBranch        *b_pfMETsumEt;   //!
  TBranch        *b_pfMETmEtSig;   //!
  TBranch        *b_pfMETSig;   //!
  TBranch        *b_pfMET_T1JERUp;   //!
  TBranch        *b_pfMET_T1JERDo;   //!
  TBranch        *b_pfMET_T1JESUp;   //!
  TBranch        *b_pfMET_T1JESDo;   //!
  TBranch        *b_pfMET_T1UESUp;   //!
  TBranch        *b_pfMET_T1UESDo;   //!
  TBranch        *b_pfMETPhi_T1JESUp;   //!
  TBranch        *b_pfMETPhi_T1JESDo;   //!
  TBranch        *b_pfMETPhi_T1UESUp;   //!
  TBranch        *b_pfMETPhi_T1UESDo;   //!
  TBranch        *b_nPho;   //!
  TBranch        *b_phoE;   //!
  TBranch        *b_phoEt;   //!
  TBranch        *b_phoEta;   //!
  TBranch        *b_phoPhi;   //!
  TBranch        *b_phoCalibE;   //!
  TBranch        *b_phoCalibEt;   //!
  TBranch        *b_phoSCE;   //!
  TBranch        *b_phoSCRawE;   //!
  TBranch        *b_phoESEnP1;   //!
  TBranch        *b_phoESEnP2;   //!
  TBranch        *b_phoSCEta;   //!
  TBranch        *b_phoSCPhi;   //!
  TBranch        *b_phoSCEtaWidth;   //!
  TBranch        *b_phoSCPhiWidth;   //!
  TBranch        *b_phoSCBrem;   //!
  TBranch        *b_phohasPixelSeed;   //!
  TBranch        *b_phoEleVeto;   //!
  TBranch        *b_phoR9;   //!
  TBranch        *b_phoHoverE;   //!
  TBranch        *b_phoE1x3;   //!
  TBranch        *b_phoE1x5;   //!
  TBranch        *b_phoE2x2;   //!
  TBranch        *b_phoE2x5Max;   //!
  TBranch        *b_phoE5x5;   //!
  TBranch        *b_phoESEffSigmaRR;   //!
  TBranch        *b_phoSigmaIEtaIEtaFull5x5;   //!
  TBranch        *b_phoSigmaIEtaIPhiFull5x5;   //!
  TBranch        *b_phoSigmaIPhiIPhiFull5x5;   //!
  TBranch        *b_phoE1x3Full5x5;   //!
  TBranch        *b_phoE1x5Full5x5;   //!
  TBranch        *b_phoE2x2Full5x5;   //!
  TBranch        *b_phoE2x5MaxFull5x5;   //!
  TBranch        *b_phoE5x5Full5x5;   //!
  TBranch        *b_phoR9Full5x5;   //!
  TBranch        *b_phoPFChIso;   //!
  TBranch        *b_phoPFPhoIso;   //!
  TBranch        *b_phoPFNeuIso;   //!
  TBranch        *b_phoPFChWorstIso;   //!
  TBranch        *b_phoCITKChIso;   //!
  TBranch        *b_phoCITKPhoIso;   //!
  TBranch        *b_phoCITKNeuIso;   //!
  TBranch        *b_phoIDMVA;   //!
  TBranch        *b_phoFiredSingleTrgs;   //!
  TBranch        *b_phoFiredDoubleTrgs;   //!
  TBranch        *b_phoFiredL1Trgs;   //!
  TBranch        *b_phoSeedTime;   //!
  TBranch        *b_phoSeedEnergy;   //!
  TBranch        *b_phoxtalBits;   //!
  TBranch        *b_phoIDbit;   //!
  TBranch        *b_npfPho;   //!
  TBranch        *b_pfphoEt;   //!
  TBranch        *b_pfphoEta;   //!
  TBranch        *b_pfphoPhi;   //!
  TBranch        *b_nEle;   //!
  TBranch        *b_eleCharge;   //!
  TBranch        *b_eleChargeConsistent;   //!
  TBranch        *b_eleEn;   //!
  TBranch        *b_eleSCEn;   //!
  TBranch        *b_eleESEnP1;   //!
  TBranch        *b_eleESEnP2;   //!
  TBranch        *b_eleD0;   //!
  TBranch        *b_eleDz;   //!
  TBranch        *b_eleSIP;   //!
  TBranch        *b_elePt;   //!
  TBranch        *b_eleEta;   //!
  TBranch        *b_elePhi;   //!
  TBranch        *b_eleR9;   //!
  TBranch        *b_eleCalibPt;   //!
  TBranch        *b_eleCalibEn;   //!
  TBranch        *b_eleSCEta;   //!
  TBranch        *b_eleSCPhi;   //!
  TBranch        *b_eleSCRawEn;   //!
  TBranch        *b_eleSCEtaWidth;   //!
  TBranch        *b_eleSCPhiWidth;   //!
  TBranch        *b_eleHoverE;   //!
  TBranch        *b_eleEoverP;   //!
  TBranch        *b_eleEoverPout;   //!
  TBranch        *b_eleEoverPInv;   //!
  TBranch        *b_eleBrem;   //!
  TBranch        *b_eledEtaAtVtx;   //!
  TBranch        *b_eledPhiAtVtx;   //!
  TBranch        *b_eledEtaAtCalo;   //!
  TBranch        *b_eleSigmaIEtaIEtaFull5x5;   //!
  TBranch        *b_eleSigmaIPhiIPhiFull5x5;   //!
  TBranch        *b_eleConvVeto;   //!
  TBranch        *b_eleMissHits;   //!
  TBranch        *b_eleESEffSigmaRR;   //!
  TBranch        *b_elePFChIso;   //!
  TBranch        *b_elePFPhoIso;   //!
  TBranch        *b_elePFNeuIso;   //!
  TBranch        *b_elePFPUIso;   //!
  TBranch        *b_elePFClusEcalIso;   //!
  TBranch        *b_elePFClusHcalIso;   //!
  TBranch        *b_elePFMiniIso;   //!
  TBranch        *b_eleIDMVA;   //!
  TBranch        *b_eleIDMVAHZZ;   //!
  TBranch        *b_eledEtaseedAtVtx;   //!
  TBranch        *b_eleE1x5;   //!
  TBranch        *b_eleE2x5;   //!
  TBranch        *b_eleE5x5;   //!
  TBranch        *b_eleE1x5Full5x5;   //!
  TBranch        *b_eleE2x5Full5x5;   //!
  TBranch        *b_eleE5x5Full5x5;   //!
  TBranch        *b_eleR9Full5x5;   //!
  TBranch        *b_eleEcalDrivenSeed;   //!
  TBranch        *b_eleDr03EcalRecHitSumEt;   //!
  TBranch        *b_eleDr03HcalDepth1TowerSumEt;   //!
  TBranch        *b_eleDr03HcalDepth2TowerSumEt;   //!
  TBranch        *b_eleDr03HcalTowerSumEt;   //!
  TBranch        *b_eleDr03TkSumPt;   //!
  TBranch        *b_elecaloEnergy;   //!
  TBranch        *b_eleTrkdxy;   //!
  TBranch        *b_eleKFHits;   //!
  TBranch        *b_eleKFChi2;   //!
  TBranch        *b_eleGSFChi2;   //!
  TBranch        *b_eleGSFPt;   //!
  TBranch        *b_eleGSFEta;   //!
  TBranch        *b_eleGSFPhi;   //!
  TBranch        *b_eleGSFCharge;   //!
  TBranch        *b_eleGSFHits;   //!
  TBranch        *b_eleGSFMissHits;   //!
  TBranch        *b_eleGSFNHitsMax;   //!
  TBranch        *b_eleGSFVtxProb;   //!
  TBranch        *b_eleGSFlxyPV;   //!
  TBranch        *b_eleGSFlxyBS;   //!
  TBranch        *b_eleBCEn;   //!
  TBranch        *b_eleBCEta;   //!
  TBranch        *b_eleBCPhi;   //!
  TBranch        *b_eleBCS25;   //!
  TBranch        *b_eleBCS15;   //!
  TBranch        *b_eleBCSieie;   //!
  TBranch        *b_eleBCSieip;   //!
  TBranch        *b_eleBCSipip;   //!
  TBranch        *b_eleFiredSingleTrgs;   //!
  TBranch        *b_eleFiredDoubleTrgs;   //!
  TBranch        *b_eleFiredL1Trgs;   //!
  TBranch        *b_eleIDbit;   //!
  TBranch        *b_npfHF;   //!
  TBranch        *b_pfHFEn;   //!
  TBranch        *b_pfHFECALEn;   //!
  TBranch        *b_pfHFHCALEn;   //!
  TBranch        *b_pfHFPt;   //!
  TBranch        *b_pfHFEta;   //!
  TBranch        *b_pfHFPhi;   //!
  TBranch        *b_pfHFIso;   //!
  TBranch        *b_nTau;   //!
  TBranch        *b_taupfTausDiscriminationByDecayModeFinding;   //!
  TBranch        *b_taupfTausDiscriminationByDecayModeFindingNewDMs;   //!
  TBranch        *b_tauByMVA6VLooseElectronRejection;   //!
  TBranch        *b_tauByMVA6LooseElectronRejection;   //!
  TBranch        *b_tauByMVA6MediumElectronRejection;   //!
  TBranch        *b_tauByMVA6TightElectronRejection;   //!
  TBranch        *b_tauByMVA6VTightElectronRejection;   //!
  TBranch        *b_tauByLooseMuonRejection3;   //!
  TBranch        *b_tauByTightMuonRejection3;   //!
  TBranch        *b_tauByLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
  TBranch        *b_tauByMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
  TBranch        *b_tauByTightCombinedIsolationDeltaBetaCorr3Hits;   //!
  TBranch        *b_tauCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
  TBranch        *b_tauByIsolationMVArun2v1DBnewDMwLTraw;   //!
  TBranch        *b_tauByIsolationMVArun2v1DBoldDMwLTraw;   //!
  TBranch        *b_tauByIsolationMVArun2v1PWnewDMwLTraw;   //!
  TBranch        *b_tauByIsolationMVArun2v1PWoldDMwLTraw;   //!
  TBranch        *b_tauByVTightIsolationMVArun2v1DBnewDMwLT;   //!
  TBranch        *b_tauByVTightIsolationMVArun2v1DBoldDMwLT;   //!
  TBranch        *b_tauByVTightIsolationMVArun2v1PWnewDMwLT;   //!
  TBranch        *b_tauByVTightIsolationMVArun2v1PWoldDMwLT;   //!
  TBranch        *b_tauByTightIsolationMVArun2v1DBnewDMwLT;   //!
  TBranch        *b_tauByTightIsolationMVArun2v1DBoldDMwLT;   //!
  TBranch        *b_tauByTightIsolationMVArun2v1PWnewDMwLT;   //!
  TBranch        *b_tauByTightIsolationMVArun2v1PWoldDMwLT;   //!
  TBranch        *b_tauByMediumIsolationMVArun2v1DBnewDMwLT;   //!
  TBranch        *b_tauByMediumIsolationMVArun2v1DBoldDMwLT;   //!
  TBranch        *b_tauByMediumIsolationMVArun2v1PWnewDMwLT;   //!
  TBranch        *b_tauByMediumIsolationMVArun2v1PWoldDMwLT;   //!
  TBranch        *b_tauByLooseIsolationMVArun2v1DBnewDMwLT;   //!
  TBranch        *b_tauByLooseIsolationMVArun2v1DBoldDMwLT;   //!
  TBranch        *b_tauByLooseIsolationMVArun2v1PWnewDMwLT;   //!
  TBranch        *b_tauByLooseIsolationMVArun2v1PWoldDMwLT;   //!
  TBranch        *b_tauByVLooseIsolationMVArun2v1DBnewDMwLT;   //!
  TBranch        *b_tauByVLooseIsolationMVArun2v1DBoldDMwLT;   //!
  TBranch        *b_tauByVLooseIsolationMVArun2v1PWnewDMwLT;   //!
  TBranch        *b_tauByVLooseIsolationMVArun2v1PWoldDMwLT;   //!
  TBranch        *b_tauEta;   //!
  TBranch        *b_tauPhi;   //!
  TBranch        *b_tauPt;   //!
  TBranch        *b_tauEt;   //!
  TBranch        *b_tauCharge;   //!
  TBranch        *b_tauP;   //!
  TBranch        *b_tauPx;   //!
  TBranch        *b_tauPy;   //!
  TBranch        *b_tauPz;   //!
  TBranch        *b_tauVz;   //!
  TBranch        *b_tauEnergy;   //!
  TBranch        *b_tauMass;   //!
  TBranch        *b_tauDxy;   //!
  TBranch        *b_tauZImpact;   //!
  TBranch        *b_tauDecayMode;   //!
  TBranch        *b_tauLeadChargedHadronExists;   //!
  TBranch        *b_tauLeadChargedHadronEta;   //!
  TBranch        *b_tauLeadChargedHadronPhi;   //!
  TBranch        *b_tauLeadChargedHadronPt;   //!
  TBranch        *b_tauChargedIsoPtSum;   //!
  TBranch        *b_tauNeutralIsoPtSum;   //!
  TBranch        *b_tauPuCorrPtSum;   //!
  TBranch        *b_tauNumSignalPFChargedHadrCands;   //!
  TBranch        *b_tauNumSignalPFNeutrHadrCands;   //!
  TBranch        *b_tauNumSignalPFGammaCands;   //!
  TBranch        *b_tauNumSignalPFCands;   //!
  TBranch        *b_tauNumIsolationPFChargedHadrCands;   //!
  TBranch        *b_tauNumIsolationPFNeutrHadrCands;   //!
  TBranch        *b_tauNumIsolationPFGammaCands;   //!
  TBranch        *b_tauNumIsolationPFCands;   //!
  TBranch        *b_taufootprintCorrection;   //!
  TBranch        *b_tauphotonPtSumOutsideSignalCone;   //!
  TBranch        *b_taudz;   //!
  TBranch        *b_taudxy;   //!
  TBranch        *b_nMu;   //!
  TBranch        *b_muPt;   //!
  TBranch        *b_muEn;   //!
  TBranch        *b_muEta;   //!
  TBranch        *b_muPhi;   //!
  TBranch        *b_muCharge;   //!
  TBranch        *b_muType;   //!
  TBranch        *b_muIDbit;   //!
  TBranch        *b_muD0;   //!
  TBranch        *b_muDz;   //!
  TBranch        *b_muSIP;   //!
  TBranch        *b_muChi2NDF;   //!
  TBranch        *b_muInnerD0;   //!
  TBranch        *b_muInnerDz;   //!
  TBranch        *b_muTrkLayers;   //!
  TBranch        *b_muPixelLayers;   //!
  TBranch        *b_muPixelHits;   //!
  TBranch        *b_muMuonHits;   //!
  TBranch        *b_muStations;   //!
  TBranch        *b_muMatches;   //!
  TBranch        *b_muTrkQuality;   //!
  TBranch        *b_muIsoTrk;   //!
  TBranch        *b_muPFChIso;   //!
  TBranch        *b_muPFPhoIso;   //!
  TBranch        *b_muPFNeuIso;   //!
  TBranch        *b_muPFPUIso;   //!
  TBranch        *b_muPFMiniIso;   //!
  TBranch        *b_muFiredTrgs;   //!
  TBranch        *b_muFiredL1Trgs;   //!
  TBranch        *b_muInnervalidFraction;   //!
  TBranch        *b_musegmentCompatibility;   //!
  TBranch        *b_muchi2LocalPosition;   //!
  TBranch        *b_mutrkKink;   //!
  TBranch        *b_muBestTrkPtError;   //!
  TBranch        *b_muBestTrkPt;   //!
  TBranch        *b_nJet;   //!
  TBranch        *b_jetetaWidth;   //!
  TBranch        *b_jetphiWidth;   //!
  TBranch        *b_jetnPhotons;   //!
  TBranch        *b_jetnCHPions;   //!
  TBranch        *b_jetnMisc;   //!
  TBranch        *b_jetMiscPID;   //!
  TBranch        *b_JetsPFConsPt;   //!
  TBranch        *b_JetsPFConsEta;   //!
  TBranch        *b_JetsPFConsPhi;   //!
  TBranch        *b_JetsPFConsEt;   //!
  TBranch        *b_JetsPFConsPID;   //!
  TBranch        *b_jetPt;   //!
  TBranch        *b_jetEn;   //!
  TBranch        *b_jetEta;   //!
  TBranch        *b_jetPhi;   //!
  TBranch        *b_jetRawPt;   //!
  TBranch        *b_jetRawEn;   //!
  TBranch        *b_jetMt;   //!
  TBranch        *b_jetArea;   //!
  TBranch        *b_jetLeadTrackPt;   //!
  TBranch        *b_jetLeadTrackEta;   //!
  TBranch        *b_jetLeadTrackPhi;   //!
  TBranch        *b_jetLepTrackPID;   //!
  TBranch        *b_jetLepTrackPt;   //!
  TBranch        *b_jetLepTrackEta;   //!
  TBranch        *b_jetLepTrackPhi;   //!
  TBranch        *b_jetCSV2BJetTags;   //!
  TBranch        *b_jetJetProbabilityBJetTags;   //!
  TBranch        *b_jetpfCombinedMVAV2BJetTags;   //!
  TBranch        *b_jetPartonID;   //!
  TBranch        *b_jetHadFlvr;   //!
  TBranch        *b_jetGenJetEn;   //!
  TBranch        *b_jetGenJetPt;   //!
  TBranch        *b_jetGenJetEta;   //!
  TBranch        *b_jetGenJetPhi;   //!
  TBranch        *b_jetGenPartonID;   //!
  TBranch        *b_jetGenEn;   //!
  TBranch        *b_jetGenPt;   //!
  TBranch        *b_jetGenEta;   //!
  TBranch        *b_jetGenPhi;   //!
  TBranch        *b_jetGenPartonMomID;   //!
  TBranch        *b_jetP4Smear;   //!
  TBranch        *b_jetP4SmearUp;   //!
  TBranch        *b_jetP4SmearDo;   //!
  TBranch        *b_jetPFLooseId;   //!
  TBranch        *b_jetID;   //!
  TBranch        *b_jetPUID;   //!
  TBranch        *b_jetPUFullID;   //!
  TBranch        *b_jetJECUnc;   //!
  TBranch        *b_jetFiredTrgs;   //!
  TBranch        *b_jetCHF;   //!
  TBranch        *b_jetNHF;   //!
  TBranch        *b_jetCEF;   //!
  TBranch        *b_jetNEF;   //!
  TBranch        *b_jetNCH;   //!
  TBranch        *b_jetNNP;   //!
  TBranch        *b_jetMUF;   //!
  TBranch        *b_jetVtxPt;   //!
  TBranch        *b_jetVtxMass;   //!
  TBranch        *b_jetVtxNtrks;   //!
  TBranch        *b_jetVtx3DVal;   //!
  TBranch        *b_jetVtx3DSig;   //!
  TBranch        *b_nAK8Jet;   //!
  TBranch        *b_AK8JetPt;   //!
  TBranch        *b_AK8JetEn;   //!
  TBranch        *b_AK8JetRawPt;   //!
  TBranch        *b_AK8JetRawEn;   //!
  TBranch        *b_AK8JetEta;   //!
  TBranch        *b_AK8JetPhi;   //!
  TBranch        *b_AK8JetMass;   //!
  TBranch        *b_AK8Jet_tau1;   //!
  TBranch        *b_AK8Jet_tau2;   //!
  TBranch        *b_AK8Jet_tau3;   //!
  TBranch        *b_AK8JetCHF;   //!
  TBranch        *b_AK8JetNHF;   //!
  TBranch        *b_AK8JetCEF;   //!
  TBranch        *b_AK8JetNEF;   //!
  TBranch        *b_AK8JetNCH;   //!
  TBranch        *b_AK8JetNNP;   //!
  TBranch        *b_AK8JetMUF;   //!
  TBranch        *b_AK8Jetnconstituents;   //!
  TBranch        *b_AK8JetPFLooseId;   //!
  TBranch        *b_AK8JetPFTightLepVetoId;   //!
  TBranch        *b_AK8JetSoftDropMass;   //!
  TBranch        *b_AK8JetSoftDropMassCorr;   //!
  TBranch        *b_AK8JetPrunedMass;   //!
  TBranch        *b_AK8JetPrunedMassCorr;   //!
  TBranch        *b_AK8JetpfBoostedDSVBTag;   //!
  TBranch        *b_AK8JetDSVnewV4;   //!
  TBranch        *b_AK8JetCSV;   //!
  TBranch        *b_AK8JetJECUnc;   //!
  TBranch        *b_AK8JetL2L3corr;   //!
  TBranch        *b_AK8puppiPt;   //!
  TBranch        *b_AK8puppiMass;   //!
  TBranch        *b_AK8puppiEta;   //!
  TBranch        *b_AK8puppiPhi;   //!
  TBranch        *b_AK8puppiTau1;   //!
  TBranch        *b_AK8puppiTau2;   //!
  TBranch        *b_AK8puppiTau3;   //!
  TBranch        *b_AK8puppiSDL2L3corr;   //!
  TBranch        *b_AK8puppiSDMass;   //!
  TBranch        *b_AK8puppiSDMassL2L3Corr;   //!
  TBranch        *b_nAK8SDSJ;   //!
  TBranch        *b_AK8SDSJPt;   //!
  TBranch        *b_AK8SDSJEta;   //!
  TBranch        *b_AK8SDSJPhi;   //!
  TBranch        *b_AK8SDSJMass;   //!
  TBranch        *b_AK8SDSJE;   //!
  TBranch        *b_AK8SDSJCharge;   //!
  TBranch        *b_AK8SDSJFlavour;   //!
  TBranch        *b_AK8SDSJCSV;   //!
  TBranch        *b_nAK8puppiSDSJ;   //!
  TBranch        *b_AK8puppiSDSJPt;   //!
  TBranch        *b_AK8puppiSDSJEta;   //!
  TBranch        *b_AK8puppiSDSJPhi;   //!
  TBranch        *b_AK8puppiSDSJMass;   //!
  TBranch        *b_AK8puppiSDSJE;   //!
  TBranch        *b_AK8puppiSDSJCharge;   //!
  TBranch        *b_AK8puppiSDSJFlavour;   //!
  TBranch        *b_AK8puppiSDSJCSV;   //!

  
  ZprimeJetsCommon(const char* file1,const char* file2,const char* fileRange);
  virtual ~ZprimeJetsCommon();
  virtual vector<string> split(string str, string delim);
  virtual bool fileSelection(string filename, string fileRange);
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);;
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual void SetScalingHistos();
  virtual void BookCommon(int i,string histname);
  virtual void fillCommon(int nhist,float event_weight);
  virtual void fillHistos(int nhist,float event_weight) { /*Should be overriden by region*/ };
  virtual float deltaR(float eta1, float phi1, float eta2, float phi2);
  virtual float DeltaPhi(float phi1, float phi2);
  virtual vector<int> getJetCand(float jetPtCut, float jetEtaCut, float jetNHFCut, float jetCHFCut);
  virtual bool dPhiJetMETcut(vector<int> jets,float metPhi);
  virtual float dPhiJetMETmin(vector<int> jets,float metPhi);
  virtual vector<int>getPFCandidates();
  virtual void getPt123Frac();
  virtual void AllPFCand(vector<int> jetCand);
  virtual void ApplyPileup(float &event_weight);
  virtual void ApplyKFactor(float &event_weight);
  virtual void ApplySF(float &event_weight,float sf);
  virtual void SetBoson(int PID);
  virtual void SetKFactors(float bosonPt);
  virtual float getKFactor(float bosonPt);
  virtual bool inclusiveCut();
  virtual void initTree(TTree* tree) { /*Should be overriden by region*/ };
  virtual void initVars();

  virtual vector<int> electron_veto_tightID(int jet_index,float elePtCut);
  virtual vector<int> electron_veto_looseID(int jet_index,float elePtCut);
  
  virtual vector<int> muon_veto_tightID(int jet_index,float muPtCut);
  virtual vector<int> muon_veto_looseID(int jet_index,float muPtCut);

  virtual vector<int> photon_veto_looseID(int jet_index,float phoPtCut);
  virtual vector<int> tau_veto_looseID(int jet_index,float tauPtCut);

  virtual vector<int> JetVetoDecision();
  virtual bool btagVeto();

  virtual void JetEnergyScale(float start_weight) { /*Should be overriden by region*/ };
  virtual void PFUncertainty(float event_weight);
  virtual void QCDVariations(float event_weight);
};

#endif
