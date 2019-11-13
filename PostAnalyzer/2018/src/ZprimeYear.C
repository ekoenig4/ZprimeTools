#ifndef ZprimeYear_C
#define ZprimeYear_C
#include "ZprimeYear.h"
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

void ZprimeYear::initVars() {
  ZprimeAnalysis::initVars();
}

void ZprimeYear::BookHistos(int i,string histname) {
  ZprimeAnalysis::BookHistos(i,histname);
}

void ZprimeYear::fillHistos(int nhist,float event_weight) {
  ZprimeAnalysis::fillHistos(nhist,event_weight);
}

void ZprimeYear::SetScalingHistos() {
  ZprimeAnalysis::SetScalingHistos();
  if (isW_or_ZJet()) {
    //This is the root file with EWK Corrections
    TFile* f_kfactor_16 = TFile::Open("RootFiles/kfactors.root");
    TFile* f_nlo_qcd_17 = TFile::Open("RootFiles/2017_gen_v_pt_stat1_qcd_sf.root");
    TFile* f_nnlo_qcd_17 = TFile::Open("RootFiles/lindert_qcd_nnlo_sf.root");

    TH1F *LO_QCD,*NLO_QCD_EWK,*NNLO_QCD,*NLO_QCD,*NLO_EWK;
    if ( sample.type == WJets ) {
      NLO_EWK = (TH1F*)TFile::Open("RootFiles/merged_kfactors_wjets.root")->Get("kfactor_monojet_ewk");
      NLO_QCD = (TH1F*)f_nlo_qcd_17->Get("wjet_dilep");
      NNLO_QCD = (TH1F*)f_nnlo_qcd_17->Get("evj");
      LO_QCD = (TH1F*)f_kfactor_16->Get("WJets_LO/inv_pt");
      NLO_QCD_EWK = (TH1F*)f_kfactor_16->Get("EWKcorr/W");
    } else {
      NLO_EWK = (TH1F*)TFile::Open("RootFiles/merged_kfactors_zjets.root")->Get("kfactor_monojet_ewk");
      NLO_QCD = (TH1F*)f_nlo_qcd_17->Get("dy_dilep");
      NNLO_QCD = (TH1F*)f_nnlo_qcd_17->Get("eej");
      LO_QCD = (TH1F*)f_kfactor_16->Get("ZJets_LO/inv_pt");
      NLO_QCD_EWK = (TH1F*)f_kfactor_16->Get("EWKcorr/Z");
    }
    th1fmap["LO_QCD"] = LO_QCD;
    th1fmap["NLO_QCD_EWK"] = NLO_QCD_EWK;
    th1fmap["NNLO_QCD"] = NNLO_QCD;
    th1fmap["NLO_QCD"] = NLO_QCD;
    th1fmap["NLO_EWK"] = NLO_EWK;
  }
  // Electron Scale Factors
  TFile *f_eleReconstrucSF_highpt=new TFile("RootFiles/egammaEffi.txt_EGM2D_updatedAll.root");
  TFile *f_eleIDeffSF_loose=new TFile("RootFiles/2018_ElectronLoose.root");
  TFile *f_eleIDeffSF_tight=new TFile("RootFiles/2018_ElectronTight.root");
  th2fmap["eleRecoSF_highpt"]=(TH2F*) f_eleReconstrucSF_highpt->Get("EGamma_SF2D");
  th2fmap["eleIDSF_loose"]=(TH2F*) f_eleIDeffSF_loose->Get("EGamma_SF2D");
  th2fmap["eleIDSF_tight"]=(TH2F*) f_eleIDeffSF_tight->Get("EGamma_SF2D");

  // Muon Scale Factors
  TFile *f_muSF_ISO = new TFile("RootFiles/RunABCD_SF_ISO.root");
  TFile *f_muSF_ID = new TFile("RootFiles/RunABCD_SF_ID.root");
  th2fmap["tightMuSF_ISO"] =  (TH2F*)f_muSF_ISO->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");
  th2fmap["looseMuSF_ISO"] =  (TH2F*)f_muSF_ISO->Get("NUM_LooseRelIso_DEN_LooseID_pt_abseta");	      
  th2fmap["tightMuSF_ID"] =  (TH2F*)f_muSF_ID->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");	      
  th2fmap["looseMuSF_ID"] =  (TH2F*)f_muSF_ID->Get("NUM_LooseID_DEN_TrackerMuons_pt_abseta");
}

float ZprimeYear::getKFactor(float bosonPt) {
  float nlo_ewk = th1fmap.getBin("NLO_EWK",bosonPt);
  float nlo_qcd = th1fmap.getBin("NLO_QCD",bosonPt);
  float nnlo_qcd = th1fmap.getBin("NNLO_QCD",bosonPt);
  float kfactor = nlo_ewk * nlo_qcd * nnlo_qcd;
  return kfactor;
}

void ZprimeYear::SetPFVectors(int jetCand) {
  j1PFConsPt =  jetConstPt->at(jetCand);
  j1PFConsEt =  jetConstEt->at(jetCand);
  j1PFConsEta = jetConstEta->at(jetCand);
  j1PFConsPhi = jetConstPhi->at(jetCand);
  j1PFConsPID = jetConstPID->at(jetCand);
}

bool ZprimeYear::eleTightID(int iele) {
  return (eleIDbit->at(iele)>>2&1) == 1;
}

bool ZprimeYear::eleLooseID(int iele) {
  return (eleIDbit->at(iele)>>0&1) == 1;
}

bool ZprimeYear::muTightID(int imu) {
  return (muIDbit->at(imu)>>3&1) == 1 && (muIDbit->at(imu)>>9&1) == 1;
}

bool ZprimeYear::muLooseID(int imu) {
  return (muIDbit->at(imu)>>0&1) == 1;
}

bool ZprimeYear::tauLooseID(int itau) {
  unsigned int tauIDbit = tauIDbits->at(itau);
  return (tauIDbit>>0&1) == 1 && (tauIDbit>>13&1) == 1;
}

bool ZprimeYear::phoLooseID(int ipho) {
  return true;
}

bool ZprimeYear::jetSelectionID(int ijet) {
  return (jetID->at(ijet)>>0&1) == 1 && (jetPUFullID->at(ijet)&(1<<2));
}

float ZprimeYear::getCSV2Cut() { return bjetVetoCSVv2Cut_17; }

bool ZprimeYear::getJetHEMVeto(float jetPtCut){

  bool pass = true;
  for(int p=0;p<nJet;p++)
    {
      bool kinematic = (*jetPt)[p] > jetPtCut && (*jetEta)[p] < -1.4 && (*jetEta)[p] > -3.0 && (*jetPhi)[p] > -1.57 && (*jetPhi)[p] < -0.87 ;
      bool tightJetID = false;
      if ((*jetID)[p]>>0&1 == 1) tightJetID = true;
      if(kinematic) // not chekcing ID here.                                                                                                                                         
        pass = false;
    }

  return pass;
}

bool ZprimeYear::getEleHEMVeto(float elePtCut){

  bool pass = true;
  for(int p=0;p<nEle;p++)
    {
      bool kinematic = (*elePt)[p] > elePtCut && (*eleEta)[p] < -1.4 && (*eleEta)[p] > -3.0 && (*elePhi)[p] > -1.57 && (*elePhi)[p] < -0.87 ;
      if(kinematic) // not chekcing ID here.                                                                                                                                         
        pass = false;
    }

  return pass;
}

void ZprimeYear::PSWeights(float event_weight) {
  return; // new MC don't have psweights...
  /* 44 Histograms
     up  dn
     isrRed        0   2
     fsrRed        1   3
     isrDef        4   6
     fsrDef        5   7
     isrCon        8  10 
     fsrCon        9  11
     fsr_G2GG_muR  12 13
     fsr_G2QQ_muR  14 15
     fsr_Q2QG_muR  16 17
     fsr_X2XG_muR  18 19
     fsr_G2GG_cNS  20 21
     fsr_G2QQ_cNS  22 23
     fsr_Q2QG_cNS  24 25
     fsr_X2XG_cNS  26 27 
     isr_G2GG_muR  28 29
     isr_G2QQ_muR  30 31
     isr_Q2QG_muR  32 33
     isr_X2XG_muR  34 35
     isr_G2GG_cNS  36 37
     isr_G2QQ_cNS  38 39
     isr_Q2QG_cNS  40 41
     isr_X2XG_cNS  42 43
  */
  
  string psw_uncs[22] = { "isrRed",   
			  "fsrRed",      
			  "isrDef",    
			  "fsrDef",  
			  "isrCon",
			  "fsrCon",      
			  "fsr_G2GG_muR",
			  "fsr_G2QQ_muR",
			  "fsr_Q2QG_muR",
			  "fsr_X2XG_muR",
			  "fsr_G2GG_cNS",
			  "fsr_G2QQ_cNS",
			  "fsr_Q2QG_cNS",
			  "fsr_X2XG_cNS",
			  "isr_G2GG_muR",
			  "isr_G2QQ_muR",
			  "isr_Q2QG_muR",
			  "isr_X2XG_muR",
			  "isr_G2GG_cNS",
			  "isr_G2QQ_cNS",
			  "isr_Q2QG_cNS",
			  "isr_X2XG_cNS"  };
  
  string uncname = "PSW_";
  // Initializing
  if ( !scaleUncs.contains(uncname+psw_uncs[0]) ) {
    for (int i = 0; i < 22; i++) {
      string name = uncname + psw_uncs[i];
      scaleUncs.addUnc(name,NULL);
    }
  }
  
  int nPS = 22;
  for (int i = 0; i < nPS; i++) {
    string name = uncname + psw_uncs[i];
    float weightUp = event_weight;
    float weightDn = event_weight;
    if ( !sample.isData && !sample.isSignal ) {
      if ( i < 2 ) {
	weightUp *= psWeight->at(2 + i);
	weightDn *= psWeight->at(2 + i + 2);
      } else if ( i < 4 ) {
	weightUp *= psWeight->at(2 + i + 2);
	weightDn *= psWeight->at(2 + i + 4);
      } else if ( i < 6 ) {
	weightUp *= psWeight->at(2 + i + 4);
	weightDn *= psWeight->at(2 + i + 6);
      } else {
	weightUp *= psWeight->at(2 + 2*i);
	weightDn *= psWeight->at(2 + 2*i + 1);
      }
    }
    scaleUncs.setUnc(name,weightUp,weightDn);
  }
}

int ZprimeYear::getFilesByNumber(TChain *chain,TString path,const char* fileRange) {
  TSystemDirectory sourceDir("hi",path);
  TList* fileList = sourceDir.GetListOfFiles();
  TIter nextlist(fileList);
  TSystemFile* filename;
  int fileNumber = 0;
  int maxFiles = -1;
  int inFile=0;
  while ((filename = (TSystemFile*)nextlist()) && fileNumber >  maxFiles)
    {
      //Debug
      if (debug) {
	cout<<"file path found: "<<(path+filename->GetName())<<endl;
	cout<<"name: "<<(filename->GetName())<<endl;
	cout<<"fileNumber: "<<fileNumber<<endl;
      }
      
      TString dataset = ".root";
      TString  FullPathInputFile = (path+filename->GetName());
      TString name = filename->GetName();
      if (name.Contains(dataset))
	{
	  string fname = string(name);
	  fname.erase(fname.end()-5,fname.end());
	  bool isin = fileSelection(fname,string(fileRange));
	  if(isin)
	    {
	      if (debug)
		cout<<"Adding FullPathInputFile to chain:"<<FullPathInputFile<<endl<<endl;
	      chain->Add(FullPathInputFile);
	      inFile++;
	    }
	}
      fileNumber++;
    }
  return inFile;
}

int ZprimeYear::getFilesByList(TChain *chain,TString path,vector<const char*> filelist) {
  int inFile=0;
  TSystemFile* filename;
  for (const char* fname : filelist) {
    filename = new TSystemFile(fname,path);
    TString FullPathInputFile = (path+filename->GetName());
    if (debug) {
      cout<<"file path found: "<<FullPathInputFile<<endl;
      cout<<"name:"<<filename->GetName()<<endl;
      cout<<"fileNumber"<<inFile<<endl;
      cout <<"Adding FullPathInputFile to chain:"<<FullPathInputFile<<endl<<endl;
    }
    chain->Add(FullPathInputFile);
    inFile++;
  }
  return inFile;
}

ZprimeYear::ZprimeYear(const char* inputFilename,const char* outputFilename,vector<const char*> filelist) {
  TChain *chain = new TChain("phoJetNtuplizer/eventTree");
  TString path = inputFilename;
  sample.setInfo(string(inputFilename));
  int inFile = 0;
  if ( filelist.size() == 0 )
    inFile = getFilesByNumber(chain,path,"-1");
  else
    inFile = getFilesByList(chain,path,filelist);
  cout<<"Sample type: "<< sample.GetTypeName() << (sample.isInclusive ? " Inclusive" : " not Inclusive") <<endl;
  cout<<inFile<<" files added."<<endl;
  cout<<"Initializing chain."<<endl;
  Init(chain);
}

ZprimeYear::ZprimeYear(const char* inputFilename,const char* outputFilename,const char* fileRange) 
{
  TChain *chain = new TChain("phoJetNtuplizer/eventTree");
  TString path = inputFilename;
  sample.setInfo(string(inputFilename));
  int inFile = getFilesByNumber(chain,path,fileRange);
  cout<<"Sample type: "<< sample.GetTypeName() << (sample.isInclusive ? " Inclusive" : " not Inclusive") <<endl;
  cout<<inFile<<" files added."<<endl;
  cout<<"Initializing chain."<<endl;
  Init(chain);
}

void ZprimeYear::Init(TTree *tree) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  phoE = 0;
  phoEt = 0;
  phoEta = 0;
  phoPhi = 0;
  phoUnCalibE = 0;
  phoUnCalibESigma = 0;
  phoCalibE = 0;
  phoCalibESigma = 0;
  phoCalibEt = 0;
  phoEnergyScale = 0;
  phoEnergySigma = 0;
  phoSCE = 0;
  phoSCRawE = 0;
  phoSCEta = 0;
  phoSCPhi = 0;
  phoSCEtaWidth = 0;
  phoSCPhiWidth = 0;
  phohasPixelSeed = 0;
  phoEleVeto = 0;
  phoR9Full5x5 = 0;
  phoHoverE = 0;
  phoSigmaIEtaIEtaFull5x5 = 0;
  phoSigmaIEtaIPhiFull5x5 = 0;
  phoSigmaIPhiIPhiFull5x5 = 0;
  phoPFChIso = 0;
  phoPFChWorstIso = 0;
  phoPFPhoIso = 0;
  phoPFNeuIso = 0;
  phoIDMVA = 0;
  phoIDbit = 0;
  phoSeedTime = 0;
  phoSeedEnergy = 0;
  phoFiredSingleTrgs = 0;
  phoFiredDoubleTrgs = 0;
  phoFiredTripleTrgs = 0;
  phoFiredL1Trgs = 0;
  phoScale_up = 0;
  phoScale_dn = 0;
  phoScale_stat_up = 0;
  phoScale_stat_dn = 0;
  phoScale_syst_up = 0;
  phoScale_syst_dn = 0;
  phoScale_gain_up = 0;
  phoScale_gain_dn = 0;
  phoResol_up = 0;
  phoResol_dn = 0;
  phoResol_rho_up = 0;
  phoResol_rho_dn = 0;
  phoResol_phi_up = 0;
  phoResol_phi_dn = 0;
  jetPt = 0;
  jetE = 0;
  jetEta = 0;
  jetPhi = 0;
  jetRawPt = 0;
  jetRawE = 0;
  jetMt = 0;
  jetArea = 0;
  jetMass = 0;
  jetMaxDistance = 0;
  jetPhiPhiMoment = 0;
  jetConstituentEtaPhiSpread = 0;
  jetConstituentPtDistribution = 0;
  jetPileup = 0;
  jetID = 0;
  jetPUID = 0;
  jetPUFullID = 0;
  jetPartonID = 0;
  jetHadFlvr = 0;
  jetJECUnc = 0;
  jetCEF = 0;
  jetNEF = 0;
  jetCHF = 0;
  jetNHF = 0;
  jetPhotonEnF = 0;
  jetElectronEnF = 0;
  jetMuonEnF = 0;
  jetChargedMuonEnF = 0;
  jetHFHAE = 0;
  jetHFEME = 0;
  jetNConst = 0;
  jetNConstituents = 0;
  jetNCharged = 0;
  jetNNeutral = 0;
  jetNChargedHad = 0;
  jetNNeutralHad = 0;
  jetNPhoton = 0;
  jetNElectron = 0;
  jetNMuon = 0;
  jetCSV2BJetTags = 0;
  jetDeepCSVTags_b = 0;
  jetDeepCSVTags_bb = 0;
  jetDeepCSVTags_c = 0;
  jetDeepCSVTags_udsg = 0;
  jetDeepFlavour_b = 0;
  jetDeepFlavour_bb = 0;
  jetDeepFlavour_lepb = 0;
  jetDeepFlavour_c = 0;
  jetDeepFlavour_uds = 0;
  jetDeepFlavour_g = 0;
  jetetaWidth = 0;
  jetphiWidth = 0;
  jetConstPt = 0;
  jetConstEt = 0;
  jetConstEta = 0;
  jetConstPhi = 0;
  jetConstPID = 0;
  ak8JetPt = 0;
  ak8JetE = 0;
  ak8JetEta = 0;
  ak8JetPhi = 0;
  ak8JetMass = 0;
  ak8JetCEF = 0;
  ak8JetNEF = 0;
  ak8JetCHF = 0;
  ak8JetNHF = 0;
  ak8JetNCH = 0;
  ak8JetNNP = 0;
  ak8JetMUF = 0;
  ak8Jet_tau1 = 0;
  ak8Jet_tau2 = 0;
  ak8Jet_tau3 = 0;
  ak8Jet_PrunedMass = 0;
  ak8Jet_SoftDropMass = 0;
  ak8Jet_PuppiSoftDropMass = 0;
  ak8Jet_PuppiTau1 = 0;
  ak8Jet_PuppiTau2 = 0;
  ak8Jet_PuppiTau3 = 0;
  ak8JetCHS_pt = 0;
  ak8JetCHS_eta = 0;
  ak8JetCHS_phi = 0;
  ak8JetCHS_mass = 0;
  ak8Jet_nb1AK8PuppiSoftDropN2 = 0;
  ak8Jet_nb1AK8PuppiSoftDropN3 = 0;
  ak8Jet_nb2AK8PuppiSoftDropN2 = 0;
  ak8Jet_nb2AK8PuppiSoftDropN3 = 0;
  ak8Jet_CSVv2Tags = 0;
  ak8Jet_DeepCSVTags_b = 0;
  ak8Jet_DeepCSVTags_bb = 0;
  ak8Jet_BoostedDSVTags_bb = 0;
  ak8JetJECUnc = 0;
  elePt = 0;
  eleEta = 0;
  elePhi = 0;
  eleR9Full5x5 = 0;
  eleE = 0;
  eleCharge = 0;
  eleChargeConsistent = 0;
  eleD0 = 0;
  eleDz = 0;
  eleSIP = 0;
  eleUnCalibE = 0;
  eleUnCalibESigma = 0;
  eleCalibEecalonly = 0;
  eleCalibE = 0;
  eleCalibESigma = 0;
  eleCalibEt = 0;
  eleCalibEtSigma = 0;
  eleEnergyScale = 0;
  eleEnergySigma = 0;
  eleSCRawE = 0;
  eleSCE = 0;
  eleSCEta = 0;
  eleSCPhi = 0;
  eleSCEtaWidth = 0;
  eleSCPhiWidth = 0;
  eleHoverE = 0;
  eleEoverP = 0;
  eleEoverPInv = 0;
  eleBrem = 0;
  eledEtaAtVtx = 0;
  eledPhiAtVtx = 0;
  eledEtaseedAtVtx = 0;
  eleSigmaIEtaIEtaFull5x5 = 0;
  eleSigmaIPhiIPhiFull5x5 = 0;
  eleConvVeto = 0;
  eleMissHits = 0;
  elePFChIso = 0;
  elePFPhoIso = 0;
  elePFNeuIso = 0;
  eleFiredSingleTrgs = 0;
  eleFiredDoubleTrgs = 0;
  eleFiredL1Trgs = 0;
  eleHEEPID = 0;
  eleMVAIsoID = 0;
  eleMVAnoIsoID = 0;
  eleIDbit = 0;
  eleScale_up = 0;
  eleScale_dn = 0;
  eleScale_stat_up = 0;
  eleScale_stat_dn = 0;
  eleScale_syst_up = 0;
  eleScale_syst_dn = 0;
  eleScale_gain_up = 0;
  eleScale_gain_dn = 0;
  eleResol_up = 0;
  eleResol_dn = 0;
  eleResol_rho_up = 0;
  eleResol_rho_dn = 0;
  eleResol_phi_up = 0;
  eleResol_phi_dn = 0;
  muPt = 0;
  muE = 0;
  muEta = 0;
  muPhi = 0;
  muCharge = 0;
  muType = 0;
  muIDbit = 0;
  muD0 = 0;
  muDz = 0;
  muSIP = 0;
  muChi2NDF = 0;
  muInnerD0 = 0;
  muInnerDz = 0;
  muTrkLayers = 0;
  muPixelLayers = 0;
  muPixelHits = 0;
  muMuonHits = 0;
  muStations = 0;
  muMatches = 0;
  muTrkQuality = 0;
  muInnervalidFraction = 0;
  muIsoTrk = 0;
  muPFChIso = 0;
  muPFPhoIso = 0;
  muPFNeuIso = 0;
  muPFPUIso = 0;
  muFiredTrgs = 0;
  muFiredL1Trgs = 0;
  tauPt = 0;
  tauEt = 0;
  tauEta = 0;
  tauPhi = 0;
  tauCharge = 0;
  tauDecayMode = 0;
  tauP = 0;
  tauVz = 0;
  tauEnergy = 0;
  tauMass = 0;
  tauDxy = 0;
  tauZImpact = 0;
  taubyCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
  tauchargedIsoPtSum = 0;
  tauneutralIsoPtSum = 0;
  tauneutralIsoPtSumWeight = 0;
  taufootprintCorrection = 0;
  tauphotonPtSumOutsideSignalCone = 0;
  taupuCorrPtSum = 0;
  tauNumSignalPFChargedHadrCands = 0;
  tauNumSignalPFNeutrHadrCands = 0;
  tauNumSignalPFGammaCands = 0;
  tauNumSignalPFCands = 0;
  tauNumIsolationPFChargedHadrCands = 0;
  tauNumIsolationPFNeutrHadrCands = 0;
  tauNumIsolationPFGammaCands = 0;
  tauNumIsolationPFCands = 0;
  tauLeadChargedHadronEta = 0;
  tauLeadChargedHadronPhi = 0;
  tauLeadChargedHadronPt = 0;
  tauLeadChargedHadron_dz = 0;
  tauLeadChargedHadron_dxy = 0;
  tauIDbits = 0;
  taubyIsolationMVArun2017v2DBoldDMwLTraw2017 = 0;
  pdf = 0;
  pdfSystWeight = 0;
  psWeight = 0;
  nPU = 0;
  puBX = 0;
  puTrue = 0;
  mcPID = 0;
  mcVtx = 0;
  mcVty = 0;
  mcVtz = 0;
  mcPt = 0;
  mcMass = 0;
  mcEta = 0;
  mcPhi = 0;
  mcE = 0;
  mcEt = 0;
  mcStatus = 0;
  mcStatusFlag = 0;
  mcIndex = 0;
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  /* Event Info */
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
  fChain->SetBranchAddress("isData", &isData, &b_isData);
  fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
  fChain->SetBranchAddress("vtxX", &vtxX, &b_vtxX);
  fChain->SetBranchAddress("vtxY", &vtxY, &b_vtxY);
  fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
  fChain->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
  fChain->SetBranchAddress("rho", &rho, &b_rho);
  fChain->SetBranchAddress("rhoCentral", &rhoCentral, &b_rhoCentral);
  fChain->SetBranchAddress("HLTEleMuX", &HLTEleMuX, &b_HLTEleMuX);
  fChain->SetBranchAddress("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled, &b_HLTEleMuXIsPrescaled);
  fChain->SetBranchAddress("HLTPho", &HLTPho, &b_HLTPho);
  fChain->SetBranchAddress("HLTPhoIsPrescaled", &HLTPhoIsPrescaled, &b_HLTPhoIsPrescaled);
  fChain->SetBranchAddress("HLTMet", &HLTMet, &b_HLTMet);
  fChain->SetBranchAddress("HLTMetIsPrescaled", &HLTMetIsPrescaled, &b_HLTMetIsPrescaled);
  fChain->SetBranchAddress("HLTMetRejectedByPS", &HLTMetRejectedByPS, &b_HLTMetRejectedByPS);
  fChain->SetBranchAddress("HLTJet", &HLTJet, &b_HLTJet);
  fChain->SetBranchAddress("HLTJetIsPrescaled", &HLTJetIsPrescaled, &b_HLTJetIsPrescaled);
  /* MET Info */
  fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
  fChain->SetBranchAddress("caloMET", &caloMET, &b_caloMET);
  fChain->SetBranchAddress("pfMET", &pfMET, &b_pfMET);
  fChain->SetBranchAddress("pfMETPhi", &pfMETPhi, &b_pfMETPhi);
  fChain->SetBranchAddress("pfMETsumEt", &pfMETsumEt, &b_pfMETsumEt);
  fChain->SetBranchAddress("pfMETmEtSig", &pfMETmEtSig, &b_pfMETmEtSig);
  fChain->SetBranchAddress("pfMETSig", &pfMETSig, &b_pfMETSig);
  fChain->SetBranchAddress("pfMET_T1JERUp", &pfMET_T1JERUp, &b_pfMET_T1JERUp);
  fChain->SetBranchAddress("pfMET_T1JERDo", &pfMET_T1JERDo, &b_pfMET_T1JERDo);
  fChain->SetBranchAddress("pfMET_T1JESUp", &pfMET_T1JESUp, &b_pfMET_T1JESUp);
  fChain->SetBranchAddress("pfMET_T1JESDo", &pfMET_T1JESDo, &b_pfMET_T1JESDo);
  fChain->SetBranchAddress("pfMET_T1UESUp", &pfMET_T1UESUp, &b_pfMET_T1UESUp);
  fChain->SetBranchAddress("pfMET_T1UESDo", &pfMET_T1UESDo, &b_pfMET_T1UESDo);
  fChain->SetBranchAddress("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp, &b_pfMETPhi_T1JESUp);
  fChain->SetBranchAddress("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo, &b_pfMETPhi_T1JESDo);
  fChain->SetBranchAddress("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp, &b_pfMETPhi_T1UESUp);
  fChain->SetBranchAddress("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo, &b_pfMETPhi_T1UESDo);
  /* Jet Info */
  fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
  fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
  fChain->SetBranchAddress("jetE", &jetE, &b_jetE);
  fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
  fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
  fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
  fChain->SetBranchAddress("jetRawE", &jetRawE, &b_jetRawE);
  fChain->SetBranchAddress("jetMt", &jetMt, &b_jetMt);
  fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
  fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
  fChain->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
  fChain->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
  fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
  fChain->SetBranchAddress("jetCEF", &jetCEF, &b_jetCEF);
  fChain->SetBranchAddress("jetNEF", &jetNEF, &b_jetNEF);
  fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
  fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
  fChain->SetBranchAddress("jetNChargedHad", &jetNChargedHad, &b_jetNChargedHad);
  fChain->SetBranchAddress("jetNNeutralHad", &jetNNeutralHad, &b_jetNNeutralHad);
  fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
  fChain->SetBranchAddress("jetetaWidth", &jetetaWidth, &b_jetetaWidth);
  fChain->SetBranchAddress("jetphiWidth", &jetphiWidth, &b_jetphiWidth);
  fChain->SetBranchAddress("jetConstPt", &jetConstPt, &b_jetConstPt);
  fChain->SetBranchAddress("jetConstEt", &jetConstEt, &b_jetConstEt);
  fChain->SetBranchAddress("jetConstEta", &jetConstEta, &b_jetConstEta);
  fChain->SetBranchAddress("jetConstPhi", &jetConstPhi, &b_jetConstPhi);
  fChain->SetBranchAddress("jetConstPdgId", &jetConstPID, &b_jetConstPID);
  /* Electron Info */
  fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
  fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
  fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
  fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
  fChain->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5, &b_eleR9Full5x5);
  fChain->SetBranchAddress("eleE", &eleE, &b_eleE);
  fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
  fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
  fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
  fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
  fChain->SetBranchAddress("eleSIP", &eleSIP, &b_eleSIP);
  fChain->SetBranchAddress("eleCalibE", &eleCalibE, &b_eleCalibE);
  fChain->SetBranchAddress("eleSCRawE", &eleSCRawE, &b_eleSCRawE);
  fChain->SetBranchAddress("eleSCE", &eleSCE, &b_eleSCE);
  fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
  fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
  fChain->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth, &b_eleSCEtaWidth);
  fChain->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth, &b_eleSCPhiWidth);
  fChain->SetBranchAddress("eleHoverE", &eleHoverE, &b_eleHoverE);
  fChain->SetBranchAddress("eleEoverP", &eleEoverP, &b_eleEoverP);
  fChain->SetBranchAddress("eleEoverPInv", &eleEoverPInv, &b_eleEoverPInv);
  fChain->SetBranchAddress("eleBrem", &eleBrem, &b_eleBrem);
  fChain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx, &b_eledEtaAtVtx);
  fChain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx, &b_eledPhiAtVtx);
  fChain->SetBranchAddress("eleIDbit", &eleIDbit, &b_eleIDbit);
  /* Muon Info */
  fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
  fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
  fChain->SetBranchAddress("muE", &muE, &b_muE);
  fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
  fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
  fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
  fChain->SetBranchAddress("muType", &muType, &b_muType);
  fChain->SetBranchAddress("muIDbit", &muIDbit, &b_muIDbit);
  fChain->SetBranchAddress("muD0", &muD0, &b_muD0);
  fChain->SetBranchAddress("muDz", &muDz, &b_muDz);
  fChain->SetBranchAddress("muSIP", &muSIP, &b_muSIP);
  fChain->SetBranchAddress("muChi2NDF", &muChi2NDF, &b_muChi2NDF);
  fChain->SetBranchAddress("muInnerD0", &muInnerD0, &b_muInnerD0);
  fChain->SetBranchAddress("muInnerDz", &muInnerDz, &b_muInnerDz);
  fChain->SetBranchAddress("muTrkLayers", &muTrkLayers, &b_muTrkLayers);
  fChain->SetBranchAddress("muPixelLayers", &muPixelLayers, &b_muPixelLayers);
  fChain->SetBranchAddress("muPixelHits", &muPixelHits, &b_muPixelHits);
  fChain->SetBranchAddress("muMuonHits", &muMuonHits, &b_muMuonHits);
  fChain->SetBranchAddress("muStations", &muStations, &b_muStations);
  fChain->SetBranchAddress("muMatches", &muMatches, &b_muMatches);
  fChain->SetBranchAddress("muTrkQuality", &muTrkQuality, &b_muTrkQuality);
  fChain->SetBranchAddress("muInnervalidFraction", &muInnervalidFraction, &b_muInnervalidFraction);
  fChain->SetBranchAddress("muIsoTrk", &muIsoTrk, &b_muIsoTrk);
  fChain->SetBranchAddress("muPFChIso", &muPFChIso, &b_muPFChIso);
  fChain->SetBranchAddress("muPFPhoIso", &muPFPhoIso, &b_muPFPhoIso);
  fChain->SetBranchAddress("muPFNeuIso", &muPFNeuIso, &b_muPFNeuIso);
  fChain->SetBranchAddress("muPFPUIso", &muPFPUIso, &b_muPFPUIso);
  fChain->SetBranchAddress("muFiredTrgs", &muFiredTrgs, &b_muFiredTrgs);
  fChain->SetBranchAddress("muFiredL1Trgs", &muFiredL1Trgs, &b_muFiredL1Trgs);
  /* Photon Info */
  fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
  fChain->SetBranchAddress("phoE", &phoE, &b_phoE);
  fChain->SetBranchAddress("phoEt", &phoEt, &b_phoEt);
  fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
  fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
  fChain->SetBranchAddress("phoCalibE", &phoCalibE, &b_phoCalibE);
  fChain->SetBranchAddress("phoCalibEt", &phoCalibEt, &b_phoCalibEt);
  fChain->SetBranchAddress("phoSCE", &phoSCE, &b_phoSCE);
  fChain->SetBranchAddress("phoSCRawE", &phoSCRawE, &b_phoSCRawE);
  fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
  fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
  fChain->SetBranchAddress("phoSCEtaWidth", &phoSCEtaWidth, &b_phoSCEtaWidth);
  fChain->SetBranchAddress("phoSCPhiWidth", &phoSCPhiWidth, &b_phoSCPhiWidth);
  fChain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed, &b_phohasPixelSeed);
  fChain->SetBranchAddress("phoEleVeto", &phoEleVeto, &b_phoEleVeto);
  fChain->SetBranchAddress("phoHoverE", &phoHoverE, &b_phoHoverE);
  fChain->SetBranchAddress("phoSigmaIEtaIEtaFull5x5", &phoSigmaIEtaIEtaFull5x5, &b_phoSigmaIEtaIEtaFull5x5);
  fChain->SetBranchAddress("phoSigmaIEtaIPhiFull5x5", &phoSigmaIEtaIPhiFull5x5, &b_phoSigmaIEtaIPhiFull5x5);
  fChain->SetBranchAddress("phoSigmaIPhiIPhiFull5x5", &phoSigmaIPhiIPhiFull5x5, &b_phoSigmaIPhiIPhiFull5x5);
  fChain->SetBranchAddress("phoPFChIso", &phoPFChIso, &b_phoPFChIso);
  fChain->SetBranchAddress("phoPFChWorstIso", &phoPFChWorstIso, &b_phoPFChWorstIso);
  fChain->SetBranchAddress("phoPFPhoIso", &phoPFPhoIso, &b_phoPFPhoIso);
  fChain->SetBranchAddress("phoPFNeuIso", &phoPFNeuIso, &b_phoPFNeuIso);
  fChain->SetBranchAddress("phoIDMVA", &phoIDMVA, &b_phoIDMVA);
  fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
  fChain->SetBranchAddress("phoSeedTime", &phoSeedTime, &b_phoSeedTime);
  fChain->SetBranchAddress("phoSeedEnergy", &phoSeedEnergy, &b_phoSeedEnergy);
  fChain->SetBranchAddress("phoFiredSingleTrgs", &phoFiredSingleTrgs, &b_phoFiredSingleTrgs);
  fChain->SetBranchAddress("phoFiredDoubleTrgs", &phoFiredDoubleTrgs, &b_phoFiredDoubleTrgs);
  fChain->SetBranchAddress("phoFiredL1Trgs", &phoFiredL1Trgs, &b_phoFiredL1Trgs);
  /* Tau Info */
  fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
  fChain->SetBranchAddress("tau_Pt", &tauPt, &b_tauPt);
  fChain->SetBranchAddress("tau_Et", &tauEt, &b_tauEt);
  fChain->SetBranchAddress("tau_Eta", &tauEta, &b_tauEta);
  fChain->SetBranchAddress("tau_Phi", &tauPhi, &b_tauPhi);
  fChain->SetBranchAddress("tau_Charge", &tauCharge, &b_tauCharge);
  fChain->SetBranchAddress("tau_DecayMode", &tauDecayMode, &b_tauDecayMode);
  fChain->SetBranchAddress("tau_P", &tauP, &b_tauP);
  fChain->SetBranchAddress("tau_Vz", &tauVz, &b_tauVz);
  fChain->SetBranchAddress("tau_Energy", &tauEnergy, &b_tauEnergy);
  fChain->SetBranchAddress("tau_Mass", &tauMass, &b_tauMass);
  fChain->SetBranchAddress("tau_Dxy", &tauDxy, &b_tauDxy);
  fChain->SetBranchAddress("tau_ZImpact", &tauZImpact, &b_tauZImpact);
  fChain->SetBranchAddress("tau_byCombinedIsolationDeltaBetaCorrRaw3Hits", &taubyCombinedIsolationDeltaBetaCorrRaw3Hits, &b_taubyCombinedIsolationDeltaBetaCorrRaw3Hits);
  fChain->SetBranchAddress("tau_chargedIsoPtSum", &tauchargedIsoPtSum, &b_tauchargedIsoPtSum);
  fChain->SetBranchAddress("tau_neutralIsoPtSum", &tauneutralIsoPtSum, &b_tauneutralIsoPtSum);
  fChain->SetBranchAddress("tau_neutralIsoPtSumWeight", &tauneutralIsoPtSumWeight, &b_tauneutralIsoPtSumWeight);
  fChain->SetBranchAddress("tau_footprintCorrection", &taufootprintCorrection, &b_taufootprintCorrection);
  fChain->SetBranchAddress("tau_photonPtSumOutsideSignalCone", &tauphotonPtSumOutsideSignalCone, &b_tauphotonPtSumOutsideSignalCone);
  fChain->SetBranchAddress("tau_puCorrPtSum", &taupuCorrPtSum, &b_taupuCorrPtSum);
  fChain->SetBranchAddress("tau_NumSignalPFChargedHadrCands", &tauNumSignalPFChargedHadrCands, &b_tauNumSignalPFChargedHadrCands);
  fChain->SetBranchAddress("tau_NumSignalPFNeutrHadrCands", &tauNumSignalPFNeutrHadrCands, &b_tauNumSignalPFNeutrHadrCands);
  fChain->SetBranchAddress("tau_NumSignalPFGammaCands", &tauNumSignalPFGammaCands, &b_tauNumSignalPFGammaCands);
  fChain->SetBranchAddress("tau_NumSignalPFCands", &tauNumSignalPFCands, &b_tauNumSignalPFCands);
  fChain->SetBranchAddress("tau_NumIsolationPFChargedHadrCands", &tauNumIsolationPFChargedHadrCands, &b_tauNumIsolationPFChargedHadrCands);
  fChain->SetBranchAddress("tau_NumIsolationPFNeutrHadrCands", &tauNumIsolationPFNeutrHadrCands, &b_tauNumIsolationPFNeutrHadrCands);
  fChain->SetBranchAddress("tau_NumIsolationPFGammaCands", &tauNumIsolationPFGammaCands, &b_tauNumIsolationPFGammaCands);
  fChain->SetBranchAddress("tau_NumIsolationPFCands", &tauNumIsolationPFCands, &b_tauNumIsolationPFCands);
  fChain->SetBranchAddress("tau_LeadChargedHadronEta", &tauLeadChargedHadronEta, &b_tauLeadChargedHadronEta);
  fChain->SetBranchAddress("tau_LeadChargedHadronPhi", &tauLeadChargedHadronPhi, &b_tauLeadChargedHadronPhi);
  fChain->SetBranchAddress("tau_LeadChargedHadronPt", &tauLeadChargedHadronPt, &b_tauLeadChargedHadronPt);
  fChain->SetBranchAddress("tau_LeadChargedHadron_dz", &tauLeadChargedHadron_dz, &b_tauLeadChargedHadron_dz);
  fChain->SetBranchAddress("tau_LeadChargedHadron_dxy", &tauLeadChargedHadron_dxy, &b_tauLeadChargedHadron_dxy);
  fChain->SetBranchAddress("tau_IDbits", &tauIDbits, &b_tauIDbits);
  fChain->SetBranchAddress("tau_byIsolationMVArun2017v2DBoldDMwLTraw2017", &taubyIsolationMVArun2017v2DBoldDMwLTraw2017, &b_taubyIsolationMVArun2017v2DBoldDMwLTraw2017);
  /* AK8 Jet Info */
  /* Generator Info */
  if (!sample.isData) {
    fChain->SetBranchAddress("genMET", &genMET, &b_genMET);
    fChain->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
    fChain->SetBranchAddress("pdf", &pdf, &b_pdf);
    fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
    fChain->SetBranchAddress("processID", &processID, &b_processID);
    fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
    fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
    fChain->SetBranchAddress("nPUInfo", &nPUInfo, &b_nPUInfo);
    fChain->SetBranchAddress("nPU", &nPU, &b_nPU);
    fChain->SetBranchAddress("puBX", &puBX, &b_puBX);
    fChain->SetBranchAddress("puTrue", &puTrue, &b_puTrue);
    fChain->SetBranchAddress("nMC", &nMC, &b_nMC);
    fChain->SetBranchAddress("mcPID", &mcPID, &b_mcPID);
    fChain->SetBranchAddress("mcVtx", &mcVtx, &b_mcVtx);
    fChain->SetBranchAddress("mcVty", &mcVty, &b_mcVty);
    fChain->SetBranchAddress("mcVtz", &mcVtz, &b_mcVtz);
    fChain->SetBranchAddress("mcPt", &mcPt, &b_mcPt);
    fChain->SetBranchAddress("mcMass", &mcMass, &b_mcMass);
    fChain->SetBranchAddress("mcEta", &mcEta, &b_mcEta);
    fChain->SetBranchAddress("mcPhi", &mcPhi, &b_mcPhi);
    fChain->SetBranchAddress("mcE", &mcE, &b_mcE);
    fChain->SetBranchAddress("mcEt", &mcEt, &b_mcEt);
    fChain->SetBranchAddress("mcStatus", &mcStatus, &b_mcStatus);
    fChain->SetBranchAddress("mcStatusFlag", &mcStatusFlag, &b_mcStatusFlag);
    if (!sample.isSignal){
      fChain->SetBranchAddress("psWeight", &psWeight, &b_psWeight);
    }
  }
}

#endif
