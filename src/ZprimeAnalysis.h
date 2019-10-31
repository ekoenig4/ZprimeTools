#ifndef ZprimeAnalysis_h
#define ZprimeAnalysis_h

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

#include "Collections.h"
#include "Utilities.h"
#include "ZprimeCutConfig.h"
#include "VariableBins.h"
#include "ZprimeMetadata.h"

using namespace std;

class ZprimeAnalysis {
 public:
  TTree *fChain;
  Int_t  fCurrent;

  TFile *output;
  static const int maxHisto = 50;
  TTree *tree;

  static const bool debug = false;

  DataMC sample;
  TH1FCollection th1fmap;
  TH2FCollection th2fmap;
  ScaleUncCollection scaleUncs;
  ShapeUncCollection shapeUncs;

  /* Event Weight Variables */
  float weight;
  float kfactor;
  float sf;
  float pileup;

  /* Selected Boson Variables */
  float bosonPt;

  /* Selected Jet Variables */
  vector<int> jetCand;
  vector<float> j1PFConsEt;
  vector<float>j1PFConsPt;
  vector<float>j1PFConsEta;
  vector<float>j1PFConsPhi;
  vector<int>j1PFConsPID;

  float Pt123Fraction,Pt123,j1pT;
  float ChNemPtFrac,ChNemPt,ChNemPt123;
  float TotalPFCands,ChargedPFCands,NeutralPFCands,GammaPFCands,MiscPFCands;
  float pfHadronPt[4];

  /* CR Variables */
  float recoil,recoilPhi;

  /* Histograms */
  TH1F *h_cutflow,*h_metcut,*h_lepMET_MT,*h_dphimin,*h_metfilters,*h_kfactor,*h_pileup,*h_genWeight,*h_sf,*h_bosonPt,*h_puTrueReWeight,*h_puTrueUnWeight;
  /* MET Histograms */
  TH1F *h_pfMETall[maxHisto],*h_pfMET200[maxHisto],*h_pfMET[maxHisto],*h_pfMETPhi[maxHisto],*h_recoil[maxHisto],*h_recoilPhi[maxHisto];
  /* Jet Histograms */
  TH1F *h_nJets[maxHisto];
  TH1F *h_j1pT[maxHisto],*h_j1Eta[maxHisto],*h_j1Phi[maxHisto],*h_j1etaWidth[maxHisto],*h_j1phiWidth[maxHisto],*h_j1CHF[maxHisto],*h_j1NHF[maxHisto],*h_j1ChMult[maxHisto],*h_j1NhMult[maxHisto],*h_j1Mt[maxHisto];
  /* PF Jet Histograms */
  TH1F *h_Pt123Fraction[maxHisto],*h_Pt123[maxHisto],*h_ChNemPtFrac[maxHisto],*h_ChNemPt[maxHisto],*h_ChNemPt123[maxHisto];
  TH1F *h_j1TotPFCands[maxHisto], *h_j1ChPFCands[maxHisto], *h_j1NeutPFCands[maxHisto], *h_j1GammaPFCands[maxHisto],*h_j1MiscPFCands[maxHisto];
  TH1F *h_ChPercCons[maxHisto],*h_NhPercCons[maxHisto],*h_GammaPercCons[maxHisto],*h_MiscPercCons[maxHisto];
  TH1F *h_ChargedPt[maxHisto],*h_NeutralPt[maxHisto],*h_PhotonPt[maxHisto],*h_MiscPt[maxHisto];
  TH1F *h_ChPercPt[maxHisto],*h_NhPercPt[maxHisto],*h_GammaPercPt[maxHisto],*h_MiscPercPt[maxHisto];
  /* Event Histograms */
  TH1F *h_nVtx[maxHisto],*h_nVtx2[maxHisto],*h_eventWeight[maxHisto],*h_genHT[maxHisto];

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types

  /* Event Info */
  Int_t           run;
  Long64_t        event;
  Int_t           lumis;
  Bool_t          isData;
  Int_t           nVtx;
  Float_t         vtxX;
  Float_t         vtxY;
  Float_t         vtxZ;
  Int_t           vtxNtrks;
  Bool_t          vtx_isFake;
  Int_t           vtx_ndof;
  Float_t         vtx_rho;
  Bool_t          isGoodVtx;
  Int_t           nGoodVtx;
  Float_t         rho;
  Float_t         rhoCentral;
  Double_t        prefiringweight;
  Double_t        prefiringweightup;
  Double_t        prefiringweightdown;
  ULong64_t       HLTEleMuX;
  ULong64_t       HLTEleMuXIsPrescaled;
  ULong64_t       HLTEleMuXRejectedByPS;
  ULong64_t       HLTPho;
  ULong64_t       HLTPhoIsPrescaled;
  ULong64_t       HLTPhoRejectedByPS;
  ULong64_t       HLTTau;
  ULong64_t       HLTTauIsPrescaled;
  ULong64_t       HLTTauRejectedByPS;
  ULong64_t       HLTMet;
  ULong64_t       HLTMetIsPrescaled;
  ULong64_t       HLTMetRejectedByPS;
  ULong64_t       HLTJet;
  ULong64_t       HLTJetIsPrescaled;
  ULong64_t       HLTJetRejectedByPS;
  /* Generator Info */
  vector<float>   *pdf;
  Float_t         pthat;
  Float_t         processID;
  Float_t         genWeight;
  Float_t         genHT;
  Float_t         pdfWeight;
  vector<float>   *pdfSystWeight;
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
  vector<int>     *mcStatus;
  vector<unsigned short> *mcStatusFlag;
  vector<int>     *mcIndex;
  /* MET Info */
  Float_t         genMET;
  Float_t         genMETPhi;
  UShort_t        metFilters;
  Float_t         caloMET;
  Float_t         caloMETPhi;
  Float_t         caloMETsumEt;
  Float_t         pfMET;
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
  /* Jet Info */
  Int_t           nJet;
  vector<float>   *jetPt;
  vector<float>   *jetE;
  vector<float>   *jetEta;
  vector<float>   *jetPhi;
  vector<float>   *jetRawPt;
  vector<float>   *jetRawE;
  vector<float>   *jetMt;
  vector<float>   *jetArea;
  vector<float>   *jetMass;
  vector<float>   *jetMaxDistance;
  vector<float>   *jetPhiPhiMoment;
  vector<float>   *jetConstituentEtaPhiSpread;
  vector<float>   *jetConstituentPtDistribution;
  vector<float>   *jetPileup;
  vector<unsigned short> *jetID;
  vector<unsigned short> *jetPFLooseID;
  vector<float>   *jetPUID;
  vector<int>     *jetPUFullID;
  vector<int>     *jetPartonID;
  vector<int>     *jetHadFlvr;
  vector<float>   *jetJECUnc;
  vector<float>   *jetCEF;
  vector<float>   *jetNEF;
  vector<float>   *jetCHF;
  vector<float>   *jetNHF;
  vector<int>     *jetPhotonEnF;
  vector<int>     *jetElectronEnF;
  vector<float>   *jetMuonEnF;
  vector<float>   *jetChargedMuonEnF;
  vector<float>   *jetHFHAE;
  vector<float>   *jetHFEME;
  vector<int>     *jetNConst;
  vector<int>     *jetNConstituents;
  vector<int>     *jetNCharged;
  vector<int>     *jetNNeutral;
  vector<int>     *jetNChargedHad;
  vector<int>     *jetNNeutralHad;
  vector<int>     *jetNPhoton;
  vector<int>     *jetNElectron;
  vector<int>     *jetNMuon;
  vector<float>   *jetCSV2BJetTags;
  vector<float>   *jetDeepCSVTags_b;
  vector<float>   *jetDeepCSVTags_bb;
  vector<float>   *jetDeepCSVTags_c;
  vector<float>   *jetDeepCSVTags_udsg;
  vector<float>   *jetDeepFlavour_b;
  vector<float>   *jetDeepFlavour_bb;
  vector<float>   *jetDeepFlavour_lepb;
  vector<float>   *jetDeepFlavour_c;
  vector<float>   *jetDeepFlavour_uds;
  vector<float>   *jetDeepFlavour_g;
  vector<float>   *jetetaWidth;
  vector<float>   *jetphiWidth;
  vector<vector<float> > *jetConstPt;
  vector<vector<float> > *jetConstEt;
  vector<vector<float> > *jetConstEta;
  vector<vector<float> > *jetConstPhi;
  vector<vector<int> > *jetConstPID;
  /* Electron Info */
  Int_t           nEle;
  vector<float>   *elePt;
  vector<float>   *eleEta;
  vector<float>   *elePhi;
  vector<float>   *eleR9Full5x5;
  vector<float>   *eleE;
  vector<int>     *eleCharge;
  vector<int>     *eleChargeConsistent;
  vector<float>   *eleD0;
  vector<float>   *eleDz;
  vector<float>   *eleSIP;
  vector<float>   *eleUnCalibE;
  vector<float>   *eleUnCalibESigma;
  vector<float>   *eleCalibEecalonly;
  vector<float>   *eleCalibE;
  vector<float>   *eleCalibESigma;
  vector<float>   *eleCalibEt;
  vector<float>   *eleCalibEtSigma;
  vector<float>   *eleEnergyScale;
  vector<float>   *eleEnergySigma;
  vector<float>   *eleSCRawE;
  vector<float>   *eleSCE;
  vector<float>   *eleSCEta;
  vector<float>   *eleSCPhi;
  vector<float>   *eleSCEtaWidth;
  vector<float>   *eleSCPhiWidth;
  vector<float>   *eleHoverE;
  vector<float>   *eleEoverP;
  vector<float>   *eleEoverPInv;
  vector<float>   *eleBrem;
  vector<float>   *eledEtaAtVtx;
  vector<float>   *eledPhiAtVtx;
  vector<float>   *eledEtaseedAtVtx;
  vector<float>   *eleSigmaIEtaIEtaFull5x5;
  vector<float>   *eleSigmaIPhiIPhiFull5x5;
  vector<int>     *eleConvVeto;
  vector<int>     *eleMissHits;
  vector<float>   *elePFChIso;
  vector<float>   *elePFPhoIso;
  vector<float>   *elePFNeuIso;
  vector<ULong64_t> *eleFiredSingleTrgs;
  vector<ULong64_t> *eleFiredDoubleTrgs;
  vector<ULong64_t> *eleFiredL1Trgs;
  vector<float>   *eleHEEPID;
  vector<float>   *eleMVAIsoID;
  vector<float>   *eleMVAnoIsoID;
  vector<unsigned short> *eleIDbit;
  vector<float>   *eleScale_up;
  vector<float>   *eleScale_dn;
  vector<float>   *eleScale_stat_up;
  vector<float>   *eleScale_stat_dn;
  vector<float>   *eleScale_syst_up;
  vector<float>   *eleScale_syst_dn;
  vector<float>   *eleScale_gain_up;
  vector<float>   *eleScale_gain_dn;
  vector<float>   *eleResol_up;
  vector<float>   *eleResol_dn;
  vector<float>   *eleResol_rho_up;
  vector<float>   *eleResol_rho_dn;
  vector<float>   *eleResol_phi_up;
  vector<float>   *eleResol_phi_dn;
  /* Muon Info */
  Int_t           nMu;
  vector<float>   *muPt;
  vector<float>   *muE;
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
  vector<float>   *muInnervalidFraction;
  vector<float>   *muIsoTrk;
  vector<float>   *muPFChIso;
  vector<float>   *muPFPhoIso;
  vector<float>   *muPFNeuIso;
  vector<float>   *muPFPUIso;
  vector<ULong64_t> *muFiredTrgs;
  vector<ULong64_t> *muFiredL1Trgs;
  /* Photon Info */
  
  Int_t           nPho;
  vector<float>   *phoE;
  vector<float>   *phoEt;
  vector<float>   *phoEta;
  vector<float>   *phoPhi;
  vector<float>   *phoUnCalibE;
  vector<float>   *phoUnCalibESigma;
  vector<float>   *phoCalibE;
  vector<float>   *phoCalibESigma;
  vector<float>   *phoCalibEt;
  vector<float>   *phoEnergyScale;
  vector<float>   *phoEnergySigma;
  vector<float>   *phoSCE;
  vector<float>   *phoSCRawE;
  vector<float>   *phoSCEta;
  vector<float>   *phoSCPhi;
  vector<float>   *phoSCEtaWidth;
  vector<float>   *phoSCPhiWidth;
  vector<int>     *phohasPixelSeed;
  vector<int>     *phoEleVeto;
  vector<float>   *phoR9Full5x5;
  vector<float>   *phoHoverE;
  vector<float>   *phoSigmaIEtaIEtaFull5x5;
  vector<float>   *phoSigmaIEtaIPhiFull5x5;
  vector<float>   *phoSigmaIPhiIPhiFull5x5;
  vector<float>   *phoPFChIso;
  vector<float>   *phoPFChWorstIso;
  vector<float>   *phoPFPhoIso;
  vector<float>   *phoPFNeuIso;
  vector<float>   *phoIDMVA;
  vector<unsigned short> *phoIDbit;
  vector<float>   *phoSeedTime;
  vector<float>   *phoSeedEnergy;
  vector<ULong64_t> *phoFiredSingleTrgs;
  vector<ULong64_t> *phoFiredDoubleTrgs;
  vector<ULong64_t> *phoFiredTripleTrgs;
  vector<ULong64_t> *phoFiredL1Trgs;
  vector<float>   *phoScale_up;
  vector<float>   *phoScale_dn;
  vector<float>   *phoScale_stat_up;
  vector<float>   *phoScale_stat_dn;
  vector<float>   *phoScale_syst_up;
  vector<float>   *phoScale_syst_dn;
  vector<float>   *phoScale_gain_up;
  vector<float>   *phoScale_gain_dn;
  vector<float>   *phoResol_up;
  vector<float>   *phoResol_dn;
  vector<float>   *phoResol_rho_up;
  vector<float>   *phoResol_rho_dn;
  vector<float>   *phoResol_phi_up;
  vector<float>   *phoResol_phi_dn;
  /* Tau Info */
  Int_t           nTau;
  vector<float>   *tauPt;
  vector<float>   *tauEt;
  vector<float>   *tauEta;
  vector<float>   *tauPhi;
  vector<float>   *tauCharge;
  vector<int>     *tauDecayMode;
  vector<float>   *tauP;
  vector<float>   *tauVz;
  vector<float>   *tauEnergy;
  vector<float>   *tauMass;
  vector<float>   *tauDxy;
  vector<float>   *tauZImpact;
  vector<float>   *taubyCombinedIsolationDeltaBetaCorrRaw3Hits;
  vector<float>   *tauchargedIsoPtSum;
  vector<float>   *tauneutralIsoPtSum;
  vector<float>   *tauneutralIsoPtSumWeight;
  vector<float>   *taufootprintCorrection;
  vector<float>   *tauphotonPtSumOutsideSignalCone;
  vector<float>   *taupuCorrPtSum;
  vector<int>     *tauNumSignalPFChargedHadrCands;
  vector<int>     *tauNumSignalPFNeutrHadrCands;
  vector<int>     *tauNumSignalPFGammaCands;
  vector<int>     *tauNumSignalPFCands;
  vector<int>     *tauNumIsolationPFChargedHadrCands;
  vector<int>     *tauNumIsolationPFNeutrHadrCands;
  vector<int>     *tauNumIsolationPFGammaCands;
  vector<int>     *tauNumIsolationPFCands;
  vector<float>   *tauLeadChargedHadronEta;
  vector<float>   *tauLeadChargedHadronPhi;
  vector<float>   *tauLeadChargedHadronPt;
  vector<float>   *tauLeadChargedHadron_dz;
  vector<float>   *tauLeadChargedHadron_dxy;
  vector<unsigned int> *tauIDbits;
  vector<float>   *taubyIsolationMVArun2017v2DBoldDMwLTraw2017;
  /* AK8 Jet Info */
  Int_t           nak8Jet;
  vector<float>   *ak8JetPt;
  vector<float>   *ak8JetE;
  vector<float>   *ak8JetEta;
  vector<float>   *ak8JetPhi;
  vector<float>   *ak8JetMass;
  vector<float>   *ak8JetCEF;
  vector<float>   *ak8JetNEF;
  vector<float>   *ak8JetCHF;
  vector<float>   *ak8JetNHF;
  vector<int>     *ak8JetNCH;
  vector<int>     *ak8JetNNP;
  vector<int>     *ak8JetMUF;
  vector<float>   *ak8Jet_tau1;
  vector<float>   *ak8Jet_tau2;
  vector<float>   *ak8Jet_tau3;
  vector<float>   *ak8Jet_PrunedMass;
  vector<float>   *ak8Jet_SoftDropMass;
  vector<float>   *ak8Jet_PuppiSoftDropMass;
  vector<float>   *ak8Jet_PuppiTau1;
  vector<float>   *ak8Jet_PuppiTau2;
  vector<float>   *ak8Jet_PuppiTau3;
  vector<float>   *ak8JetCHS_pt;
  vector<float>   *ak8JetCHS_eta;
  vector<float>   *ak8JetCHS_phi;
  vector<float>   *ak8JetCHS_mass;
  vector<float>   *ak8Jet_nb1AK8PuppiSoftDropN2;
  vector<float>   *ak8Jet_nb1AK8PuppiSoftDropN3;
  vector<float>   *ak8Jet_nb2AK8PuppiSoftDropN2;
  vector<float>   *ak8Jet_nb2AK8PuppiSoftDropN3;
  vector<float>   *ak8Jet_CSVv2Tags;
  vector<float>   *ak8Jet_DeepCSVTags_b;
  vector<float>   *ak8Jet_DeepCSVTags_bb;
  vector<float>   *ak8Jet_BoostedDSVTags_bb;
  vector<float>   *ak8JetJECUnc;

  // List of branches
  /* Event Info */
  TBranch        *b_run;   //!
  TBranch        *b_event;   //!
  TBranch        *b_lumis;   //!
  TBranch        *b_isData;   //!
  TBranch        *b_nVtx;   //!
  TBranch        *b_vtxX;   //!
  TBranch        *b_vtxY;   //!
  TBranch        *b_vtxZ;   //!
  TBranch        *b_vtxNtrks;   //!
  TBranch        *b_vtx_isFake;   //!
  TBranch        *b_vtx_ndof;   //!
  TBranch        *b_vtx_rho;   //!
  TBranch        *b_isGoodVtx;   //!
  TBranch        *b_nGoodVtx;   //!
  TBranch        *b_rho;   //!
  TBranch        *b_rhoCentral;   //!
  TBranch        *b_prefiringweight;   //!
  TBranch        *b_prefiringweightup;   //!
  TBranch        *b_prefiringweightdown;   //!
  TBranch        *b_HLTEleMuX;   //!
  TBranch        *b_HLTEleMuXIsPrescaled;   //!
  TBranch        *b_HLTEleMuXRejectedByPS;   //!
  TBranch        *b_HLTPho;   //!
  TBranch        *b_HLTPhoIsPrescaled;   //!
  TBranch        *b_HLTPhoRejectedByPS;   //!
  TBranch        *b_HLTTau;   //!
  TBranch        *b_HLTTauIsPrescaled;   //!
  TBranch        *b_HLTTauRejectedByPS;   //!
  TBranch        *b_HLTMet;   //!
  TBranch        *b_HLTMetIsPrescaled;   //!
  TBranch        *b_HLTMetRejectedByPS;   //!
  TBranch        *b_HLTJet;   //!
  TBranch        *b_HLTJetIsPrescaled;   //!
  TBranch        *b_HLTJetRejectedByPS;   //!
  /* Generator Info */
  TBranch        *b_pdf;   //!
  TBranch        *b_pthat;   //!
  TBranch        *b_processID;   //!
  TBranch        *b_genWeight;   //!
  TBranch        *b_genHT;   //!
  TBranch        *b_pdfWeight;   //!
  TBranch        *b_pdfSystWeight;   //!
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
  TBranch        *b_mcStatus;   //!
  TBranch        *b_mcStatusFlag;   //!
  TBranch        *b_mcIndex;   //!
  /* MET Info */
  TBranch        *b_genMET;   //!
  TBranch        *b_genMETPhi;   //!
  TBranch        *b_metFilters;   //!
  TBranch        *b_caloMET;   //!
  TBranch        *b_caloMETPhi;   //!
  TBranch        *b_caloMETsumEt;   //!
  TBranch        *b_pfMET;   //!
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
  /* Jet Info */
  TBranch        *b_nJet;   //!
  TBranch        *b_jetPt;   //!
  TBranch        *b_jetE;   //!
  TBranch        *b_jetEta;   //!
  TBranch        *b_jetPhi;   //!
  TBranch        *b_jetRawPt;   //!
  TBranch        *b_jetRawE;   //!
  TBranch        *b_jetMt;   //!
  TBranch        *b_jetArea;   //!
  TBranch        *b_jetMass;   //!
  TBranch        *b_jetMaxDistance;   //!
  TBranch        *b_jetPhiPhiMoment;   //!
  TBranch        *b_jetConstituentEtaPhiSpread;   //!
  TBranch        *b_jetConstituentPtDistribution;   //!
  TBranch        *b_jetPileup;   //!
  TBranch        *b_jetID;   //!
  TBranch        *b_jetPFLooseID; //!
  TBranch        *b_jetPUID;   //!
  TBranch        *b_jetPUFullID;   //!
  TBranch        *b_jetPartonID;   //!
  TBranch        *b_jetHadFlvr;   //!
  TBranch        *b_jetJECUnc;   //!
  TBranch        *b_jetCEF;   //!
  TBranch        *b_jetNEF;   //!
  TBranch        *b_jetCHF;   //!
  TBranch        *b_jetNHF;   //!
  TBranch        *b_jetPhotonEnF;   //!
  TBranch        *b_jetElectronEnF;   //!
  TBranch        *b_jetMuonEnF;   //!
  TBranch        *b_jetChargedMuonEnF;   //!
  TBranch        *b_jetHFHAE;   //!
  TBranch        *b_jetHFEME;   //!
  TBranch        *b_jetNConst;   //!
  TBranch        *b_jetNConstituents;   //!
  TBranch        *b_jetNCharged;   //!
  TBranch        *b_jetNNeutral;   //!
  TBranch        *b_jetNChargedHad;   //!
  TBranch        *b_jetNNeutralHad;   //!
  TBranch        *b_jetNPhoton;   //!
  TBranch        *b_jetNElectron;   //!
  TBranch        *b_jetNMuon;   //!
  TBranch        *b_jetCSV2BJetTags;   //!
  TBranch        *b_jetDeepCSVTags_b;   //!
  TBranch        *b_jetDeepCSVTags_bb;   //!
  TBranch        *b_jetDeepCSVTags_c;   //!
  TBranch        *b_jetDeepCSVTags_udsg;   //!
  TBranch        *b_jetDeepFlavour_b;   //!
  TBranch        *b_jetDeepFlavour_bb;   //!
  TBranch        *b_jetDeepFlavour_lepb;   //!
  TBranch        *b_jetDeepFlavour_c;   //!
  TBranch        *b_jetDeepFlavour_uds;   //!
  TBranch        *b_jetDeepFlavour_g;   //!
  TBranch        *b_jetetaWidth;   //!
  TBranch        *b_jetphiWidth;   //!
  TBranch        *b_jetConstPt;   //!
  TBranch        *b_jetConstEt;   //!
  TBranch        *b_jetConstEta;   //!
  TBranch        *b_jetConstPhi;   //!
  TBranch        *b_jetConstPID;   //!
  /* Electron Info */
  TBranch        *b_nEle;   //!
  TBranch        *b_elePt;   //!
  TBranch        *b_eleEta;   //!
  TBranch        *b_elePhi;   //!
  TBranch        *b_eleR9Full5x5;   //!
  TBranch        *b_eleE;   //!
  TBranch        *b_eleCharge;   //!
  TBranch        *b_eleChargeConsistent;   //!
  TBranch        *b_eleD0;   //!
  TBranch        *b_eleDz;   //!
  TBranch        *b_eleSIP;   //!
  TBranch        *b_eleUnCalibE;   //!
  TBranch        *b_eleUnCalibESigma;   //!
  TBranch        *b_eleCalibEecalonly;   //!
  TBranch        *b_eleCalibE;   //!
  TBranch        *b_eleCalibESigma;   //!
  TBranch        *b_eleCalibEt;   //!
  TBranch        *b_eleCalibEtSigma;   //!
  TBranch        *b_eleEnergyScale;   //!
  TBranch        *b_eleEnergySigma;   //!
  TBranch        *b_eleSCRawE;   //!
  TBranch        *b_eleSCE;   //!
  TBranch        *b_eleSCEta;   //!
  TBranch        *b_eleSCPhi;   //!
  TBranch        *b_eleSCEtaWidth;   //!
  TBranch        *b_eleSCPhiWidth;   //!
  TBranch        *b_eleHoverE;   //!
  TBranch        *b_eleEoverP;   //!
  TBranch        *b_eleEoverPInv;   //!
  TBranch        *b_eleBrem;   //!
  TBranch        *b_eledEtaAtVtx;   //!
  TBranch        *b_eledPhiAtVtx;   //!
  TBranch        *b_eledEtaseedAtVtx;   //!
  TBranch        *b_eleSigmaIEtaIEtaFull5x5;   //!
  TBranch        *b_eleSigmaIPhiIPhiFull5x5;   //!
  TBranch        *b_eleConvVeto;   //!
  TBranch        *b_eleMissHits;   //!
  TBranch        *b_elePFChIso;   //!
  TBranch        *b_elePFPhoIso;   //!
  TBranch        *b_elePFNeuIso;   //!
  TBranch        *b_eleFiredSingleTrgs;   //!
  TBranch        *b_eleFiredDoubleTrgs;   //!
  TBranch        *b_eleFiredL1Trgs;   //!
  TBranch        *b_eleHEEPID;   //!
  TBranch        *b_eleMVAIsoID;   //!
  TBranch        *b_eleMVAnoIsoID;   //!
  TBranch        *b_eleIDbit;   //!
  TBranch        *b_eleScale_up;   //!
  TBranch        *b_eleScale_dn;   //!
  TBranch        *b_eleScale_stat_up;   //!
  TBranch        *b_eleScale_stat_dn;   //!
  TBranch        *b_eleScale_syst_up;   //!
  TBranch        *b_eleScale_syst_dn;   //!
  TBranch        *b_eleScale_gain_up;   //!
  TBranch        *b_eleScale_gain_dn;   //!
  TBranch        *b_eleResol_up;   //!
  TBranch        *b_eleResol_dn;   //!
  TBranch        *b_eleResol_rho_up;   //!
  TBranch        *b_eleResol_rho_dn;   //!
  TBranch        *b_eleResol_phi_up;   //!
  TBranch        *b_eleResol_phi_dn;   //!
  /* Muon Info */
  TBranch        *b_nMu;   //!
  TBranch        *b_muPt;   //!
  TBranch        *b_muE;   //!
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
  TBranch        *b_muInnervalidFraction;   //!
  TBranch        *b_muIsoTrk;   //!
  TBranch        *b_muPFChIso;   //!
  TBranch        *b_muPFPhoIso;   //!
  TBranch        *b_muPFNeuIso;   //!
  TBranch        *b_muPFPUIso;   //!
  TBranch        *b_muFiredTrgs;   //!
  TBranch        *b_muFiredL1Trgs;   //!
  /* Photon Info */
  TBranch        *b_nPho;   //!
  TBranch        *b_phoE;   //!
  TBranch        *b_phoEt;   //!
  TBranch        *b_phoEta;   //!
  TBranch        *b_phoPhi;   //!
  TBranch        *b_phoUnCalibE;   //!
  TBranch        *b_phoUnCalibESigma;   //!
  TBranch        *b_phoCalibE;   //!
  TBranch        *b_phoCalibESigma;   //!
  TBranch        *b_phoCalibEt;   //!
  TBranch        *b_phoEnergyScale;   //!
  TBranch        *b_phoEnergySigma;   //!
  TBranch        *b_phoSCE;   //!
  TBranch        *b_phoSCRawE;   //!
  TBranch        *b_phoSCEta;   //!
  TBranch        *b_phoSCPhi;   //!
  TBranch        *b_phoSCEtaWidth;   //!
  TBranch        *b_phoSCPhiWidth;   //!
  TBranch        *b_phohasPixelSeed;   //!
  TBranch        *b_phoEleVeto;   //!
  TBranch        *b_phoR9Full5x5;   //!
  TBranch        *b_phoHoverE;   //!
  TBranch        *b_phoSigmaIEtaIEtaFull5x5;   //!
  TBranch        *b_phoSigmaIEtaIPhiFull5x5;   //!
  TBranch        *b_phoSigmaIPhiIPhiFull5x5;   //!
  TBranch        *b_phoPFChIso;   //!
  TBranch        *b_phoPFChWorstIso;   //!
  TBranch        *b_phoPFPhoIso;   //!
  TBranch        *b_phoPFNeuIso;   //!
  TBranch        *b_phoIDMVA;   //!
  TBranch        *b_phoIDbit;   //!
  TBranch        *b_phoSeedTime;   //!
  TBranch        *b_phoSeedEnergy;   //!
  TBranch        *b_phoFiredSingleTrgs;   //!
  TBranch        *b_phoFiredDoubleTrgs;   //!
  TBranch        *b_phoFiredTripleTrgs;   //!
  TBranch        *b_phoFiredL1Trgs;   //!
  TBranch        *b_phoScale_up;   //!
  TBranch        *b_phoScale_dn;   //!
  TBranch        *b_phoScale_stat_up;   //!
  TBranch        *b_phoScale_stat_dn;   //!
  TBranch        *b_phoScale_syst_up;   //!
  TBranch        *b_phoScale_syst_dn;   //!
  TBranch        *b_phoScale_gain_up;   //!
  TBranch        *b_phoScale_gain_dn;   //!
  TBranch        *b_phoResol_up;   //!
  TBranch        *b_phoResol_dn;   //!
  TBranch        *b_phoResol_rho_up;   //!
  TBranch        *b_phoResol_rho_dn;   //!
  TBranch        *b_phoResol_phi_up;   //!
  TBranch        *b_phoResol_phi_dn;   //!
  /* Tau Info */
  TBranch        *b_nTau;   //!
  TBranch        *b_tauPt;   //!
  TBranch        *b_tauEt;   //!
  TBranch        *b_tauEta;   //!
  TBranch        *b_tauPhi;   //!
  TBranch        *b_tauCharge;   //!
  TBranch        *b_tauDecayMode;   //!
  TBranch        *b_tauP;   //!
  TBranch        *b_tauVz;   //!
  TBranch        *b_tauEnergy;   //!
  TBranch        *b_tauMass;   //!
  TBranch        *b_tauDxy;   //!
  TBranch        *b_tauZImpact;   //!
  TBranch        *b_taubyCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
  TBranch        *b_tauchargedIsoPtSum;   //!
  TBranch        *b_tauneutralIsoPtSum;   //!
  TBranch        *b_tauneutralIsoPtSumWeight;   //!
  TBranch        *b_taufootprintCorrection;   //!
  TBranch        *b_tauphotonPtSumOutsideSignalCone;   //!
  TBranch        *b_taupuCorrPtSum;   //!
  TBranch        *b_tauNumSignalPFChargedHadrCands;   //!
  TBranch        *b_tauNumSignalPFNeutrHadrCands;   //!
  TBranch        *b_tauNumSignalPFGammaCands;   //!
  TBranch        *b_tauNumSignalPFCands;   //!
  TBranch        *b_tauNumIsolationPFChargedHadrCands;   //!
  TBranch        *b_tauNumIsolationPFNeutrHadrCands;   //!
  TBranch        *b_tauNumIsolationPFGammaCands;   //!
  TBranch        *b_tauNumIsolationPFCands;   //!
  TBranch        *b_tauLeadChargedHadronEta;   //!
  TBranch        *b_tauLeadChargedHadronPhi;   //!
  TBranch        *b_tauLeadChargedHadronPt;   //!
  TBranch        *b_tauLeadChargedHadron_dz;   //!
  TBranch        *b_tauLeadChargedHadron_dxy;   //!
  TBranch        *b_tauIDbits;   //!
  TBranch        *b_taubyIsolationMVArun2017v2DBoldDMwLTraw2017;   //!
  /* AK8 Jet Info */
  TBranch        *b_nak8Jet;   //!
  TBranch        *b_ak8JetPt;   //!
  TBranch        *b_ak8JetE;   //!
  TBranch        *b_ak8JetEta;   //!
  TBranch        *b_ak8JetPhi;   //!
  TBranch        *b_ak8JetMass;   //!
  TBranch        *b_ak8JetCEF;   //!
  TBranch        *b_ak8JetNEF;   //!
  TBranch        *b_ak8JetCHF;   //!
  TBranch        *b_ak8JetNHF;   //!
  TBranch        *b_ak8JetNCH;   //!
  TBranch        *b_ak8JetNNP;   //!
  TBranch        *b_ak8JetMUF;   //!
  TBranch        *b_ak8Jet_tau1;   //!
  TBranch        *b_ak8Jet_tau2;   //!
  TBranch        *b_ak8Jet_tau3;   //!
  TBranch        *b_ak8Jet_PrunedMass;   //!
  TBranch        *b_ak8Jet_SoftDropMass;   //!
  TBranch        *b_ak8Jet_PuppiSoftDropMass;   //!
  TBranch        *b_ak8Jet_PuppiTau1;   //!
  TBranch        *b_ak8Jet_PuppiTau2;   //!
  TBranch        *b_ak8Jet_PuppiTau3;   //!
  TBranch        *b_ak8JetCHS_pt;   //!
  TBranch        *b_ak8JetCHS_eta;   //!
  TBranch        *b_ak8JetCHS_phi;   //!
  TBranch        *b_ak8JetCHS_mass;   //!
  TBranch        *b_ak8Jet_nb1AK8PuppiSoftDropN2;   //!
  TBranch        *b_ak8Jet_nb1AK8PuppiSoftDropN3;   //!
  TBranch        *b_ak8Jet_nb2AK8PuppiSoftDropN2;   //!
  TBranch        *b_ak8Jet_nb2AK8PuppiSoftDropN3;   //!
  TBranch        *b_ak8Jet_CSVv2Tags;   //!
  TBranch        *b_ak8Jet_DeepCSVTags_b;   //!
  TBranch        *b_ak8Jet_DeepCSVTags_bb;   //!
  TBranch        *b_ak8Jet_BoostedDSVTags_bb;   //!
  TBranch        *b_ak8JetJECUnc;   //!

  virtual ~ZprimeAnalysis();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);

  virtual void SetScalingHistos();
  virtual void initTree(TTree* tree);
  virtual void initVars();
  virtual void BookHistos(int nhist,string histname);
  virtual void fillHistos(int nhisto,float event_weight);

  virtual vector<int> getJetCand(float,float,float,float);
  virtual void SetPtFrac();
  virtual void SetJetPFInfo(vector<int> jetCand);

  virtual bool dPhiJetMET(vector<int>,float);
  virtual void SetBoson(int PID);
  virtual float getKFactor(float bosonPt) { return 1; };
  virtual void SetKFactors(float bosonPt);
  virtual void ApplyKFactor(float &event_weight);
  virtual void ApplyPileup(float &event_weight);
  virtual void SetSF(float sf);
  virtual void ApplySF(float &event_weight);

  virtual bool inclusiveCut();
  virtual vector<int> electron_veto_tightID(int jetCand,float elePtCut);
  virtual vector<int> electron_veto_looseID(int jetCand,float elePtCut);
  virtual bool eleTightID(int);
  virtual bool eleLooseID(int);
  virtual vector<int> muon_veto_tightID(int jetCand,float muPtCut);
  virtual vector<int> muon_veto_looseID(int jetCand,float muPtCut);
  virtual bool muTightID(int);
  virtual bool muLooseID(int);
  virtual vector<int> photon_veto_looseID(int jetCand,float phoPtCut);
  virtual bool phoLooseID(int);
  virtual vector<int> tau_veto_looseID(int jetCand,float tauPtCut);
  virtual bool tauLooseID(int);
  virtual vector<int> JetVetoDecision();
  virtual bool jetSelectionID(int);
  virtual bool btagVeto();
};

#endif
