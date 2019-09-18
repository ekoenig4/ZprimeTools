#define ZprimeJetsCommon_cxx
#include "ZprimeJetsCommon.h"

using namespace std;

#ifdef ZprimeJetsCommon_cxx
vector<string> ZprimeJetsCommon::split(string str,string delim) {
  vector<string> splitString;
  char strChar[str.size() + 1];
  strcpy(strChar,str.c_str());
  char *token = strtok(strChar,delim.c_str());
  while (token != NULL) {
    splitString.push_back(string(token));
    token = strtok(NULL,delim.c_str());
  }
  return splitString;
}

bool ZprimeJetsCommon::fileSelection(string filename,string fileRange)
{
  if (fileRange == "-1") return true;
  int numPos;
  for (int i = filename.size(); i > 0; --i) {
    if (filename[i] == '_') {
      numPos = i+1;
      break;
    }
  }
  filename.erase(filename.begin(),filename.begin()+numPos);
  int fileNum = atoi(filename.c_str());
  //1-100/200-250/300-300
  vector<string> rangeOfFiles = split(fileRange,"/");
  for (int i = 0; i < rangeOfFiles.size(); i++) {
    vector<string> range = split(rangeOfFiles[i],"-");
    if (atoi(range[0].c_str()) <= fileNum && fileNum <= atoi(range[1].c_str())) {
      return true;
    }
  }
  return false;
}

ZprimeJetsCommon::ZprimeJetsCommon(const char* inputFilename,const char* outputFilename,const char* fileRange) 
{
  TChain *chain = new TChain("ggNtuplizer/EventTree");
  TString path = inputFilename;
  TSystemDirectory sourceDir("hi",path);
  TList* fileList = sourceDir.GetListOfFiles();
  TIter nextlist(fileList);
  TSystemFile* filename;
  int fileNumber = 0;
  int maxFiles = -1;
  int inFile=0;
  sample = DataMC(string(inputFilename));
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
  string sampleID[Total] = {"Data","Signal","WJets","ZJets","DYJets","QCD","TTJets","GJets","WW","WZ","ZZ"};
  cout<<"Sample type: "<<sampleID[sample.type]<< (sample.isInclusive ? " Inclusive" : " not Inclusive") <<endl;
  cout<<"isW_or_ZJets: "<<sample.isW_or_ZJet() << endl;
  cout<<inFile<<" files added."<<endl;
  cout<<"Initializing chain."<<endl;
  Init(chain);
}

ZprimeJetsCommon::~ZprimeJetsCommon()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  output->cd();
  output->Write();
  output->Close();
}

Int_t ZprimeJetsCommon::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ZprimeJetsCommon::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void ZprimeJetsCommon::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  pdf = 0;
  EventTag = 0;
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
  mcGMomPID = 0;
  mcMomPID = 0;
  mcMomPt = 0;
  mcMomMass = 0;
  mcMomEta = 0;
  mcMomPhi = 0;
  mcStatusFlag = 0;
  mcParentage = 0;
  mcStatus = 0;
  mcCalIsoDR03 = 0;
  mcTrkIsoDR03 = 0;
  mcCalIsoDR04 = 0;
  mcTrkIsoDR04 = 0;
  phoPrescale = 0;
  phoE = 0;
  phoEt = 0;
  phoEta = 0;
  phoPhi = 0;
  phoCalibE = 0;
  phoCalibEt = 0;
  phoSCE = 0;
  phoSCRawE = 0;
  phoESEnP1 = 0;
  phoESEnP2 = 0;
  phoSCEta = 0;
  phoSCPhi = 0;
  phoSCEtaWidth = 0;
  phoSCPhiWidth = 0;
  phoSCBrem = 0;
  phohasPixelSeed = 0;
  phoEleVeto = 0;
  phoR9 = 0;
  phoHoverE = 0;
  phoE1x3 = 0;
  phoE1x5 = 0;
  phoE2x2 = 0;
  phoE2x5Max = 0;
  phoE5x5 = 0;
  phoESEffSigmaRR = 0;
  phoSigmaIEtaIEtaFull5x5 = 0;
  phoSigmaIEtaIPhiFull5x5 = 0;
  phoSigmaIPhiIPhiFull5x5 = 0;
  phoE1x3Full5x5 = 0;
  phoE1x5Full5x5 = 0;
  phoE2x2Full5x5 = 0;
  phoE2x5MaxFull5x5 = 0;
  phoE5x5Full5x5 = 0;
  phoR9Full5x5 = 0;
  phoPFChIso = 0;
  phoPFPhoIso = 0;
  phoPFNeuIso = 0;
  phoPFChWorstIso = 0;
  phoCITKChIso = 0;
  phoCITKPhoIso = 0;
  phoCITKNeuIso = 0;
  phoIDMVA = 0;
  phoFiredSingleTrgs = 0;
  phoFiredDoubleTrgs = 0;
  phoFiredL1Trgs = 0;
  phoSeedTime = 0;
  phoSeedEnergy = 0;
  phoxtalBits = 0;
  phoIDbit = 0;
  pfphoEt = 0;
  pfphoEta = 0;
  pfphoPhi = 0;
  eleCharge = 0;
  eleChargeConsistent = 0;
  eleEn = 0;
  eleSCEn = 0;
  eleESEnP1 = 0;
  eleESEnP2 = 0;
  eleD0 = 0;
  eleDz = 0;
  eleSIP = 0;
  elePt = 0;
  eleEta = 0;
  elePhi = 0;
  eleR9 = 0;
  eleCalibPt = 0;
  eleCalibEn = 0;
  eleSCEta = 0;
  eleSCPhi = 0;
  eleSCRawEn = 0;
  eleSCEtaWidth = 0;
  eleSCPhiWidth = 0;
  eleHoverE = 0;
  eleEoverP = 0;
  eleEoverPout = 0;
  eleEoverPInv = 0;
  eleBrem = 0;
  eledEtaAtVtx = 0;
  eledPhiAtVtx = 0;
  eledEtaAtCalo = 0;
  eleSigmaIEtaIEtaFull5x5 = 0;
  eleSigmaIPhiIPhiFull5x5 = 0;
  eleConvVeto = 0;
  eleMissHits = 0;
  eleESEffSigmaRR = 0;
  elePFChIso = 0;
  elePFPhoIso = 0;
  elePFNeuIso = 0;
  elePFPUIso = 0;
  elePFClusEcalIso = 0;
  elePFClusHcalIso = 0;
  elePFMiniIso = 0;
  eleIDMVA = 0;
  eleIDMVAHZZ = 0;
  eledEtaseedAtVtx = 0;
  eleE1x5 = 0;
  eleE2x5 = 0;
  eleE5x5 = 0;
  eleE1x5Full5x5 = 0;
  eleE2x5Full5x5 = 0;
  eleE5x5Full5x5 = 0;
  eleR9Full5x5 = 0;
  eleEcalDrivenSeed = 0;
  eleDr03EcalRecHitSumEt = 0;
  eleDr03HcalDepth1TowerSumEt = 0;
  eleDr03HcalDepth2TowerSumEt = 0;
  eleDr03HcalTowerSumEt = 0;
  eleDr03TkSumPt = 0;
  elecaloEnergy = 0;
  eleTrkdxy = 0;
  eleKFHits = 0;
  eleKFChi2 = 0;
  eleGSFChi2 = 0;
  eleGSFPt = 0;
  eleGSFEta = 0;
  eleGSFPhi = 0;
  eleGSFCharge = 0;
  eleGSFHits = 0;
  eleGSFMissHits = 0;
  eleGSFNHitsMax = 0;
  eleGSFVtxProb = 0;
  eleGSFlxyPV = 0;
  eleGSFlxyBS = 0;
  eleBCEn = 0;
  eleBCEta = 0;
  eleBCPhi = 0;
  eleBCS25 = 0;
  eleBCS15 = 0;
  eleBCSieie = 0;
  eleBCSieip = 0;
  eleBCSipip = 0;
  eleFiredSingleTrgs = 0;
  eleFiredDoubleTrgs = 0;
  eleFiredL1Trgs = 0;
  eleIDbit = 0;
  pfHFEn = 0;
  pfHFECALEn = 0;
  pfHFHCALEn = 0;
  pfHFPt = 0;
  pfHFEta = 0;
  pfHFPhi = 0;
  pfHFIso = 0;
  muPt = 0;
  muEn = 0;
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
  muIsoTrk = 0;
  muPFChIso = 0;
  muPFPhoIso = 0;
  muPFNeuIso = 0;
  muPFPUIso = 0;
  muPFMiniIso = 0;
  muFiredTrgs = 0;
  muFiredL1Trgs = 0;
  muInnervalidFraction = 0;
  musegmentCompatibility = 0;
  muchi2LocalPosition = 0;
  mutrkKink = 0;
  muBestTrkPtError = 0;
  muBestTrkPt = 0; 
  jetetaWidth = 0;
  jetphiWidth = 0;
  jetnPhotons = 0;
  jetnCHPions = 0;
  jetnMisc = 0;
  jetMiscPID = 0;
  JetsPFConsPt = 0;
  JetsPFConsEta = 0;
  JetsPFConsPhi = 0;
  JetsPFConsEt = 0;
  JetsPFConsPID = 0;
  jetPt = 0;
  jetEn = 0;
  jetEta = 0;
  jetPhi = 0;
  jetRawPt = 0;
  jetRawEn = 0;
  jetMt = 0;
  jetArea = 0;
  jetLeadTrackPt = 0;
  jetLeadTrackEta = 0;
  jetLeadTrackPhi = 0;
  jetLepTrackPID = 0;
  jetLepTrackPt = 0;
  jetLepTrackEta = 0;
  jetLepTrackPhi = 0;
  jetCSV2BJetTags = 0;
  jetJetProbabilityBJetTags = 0;
  jetpfCombinedMVAV2BJetTags = 0;
  jetPartonID = 0;
  jetHadFlvr = 0;
  jetGenJetEn = 0;
  jetGenJetPt = 0;
  jetGenJetEta = 0;
  jetGenJetPhi = 0;
  jetGenPartonID = 0;
  jetGenEn = 0;
  jetGenPt = 0;
  jetGenEta = 0;
  jetGenPhi = 0;
  jetGenPartonMomID = 0;
  jetP4Smear = 0;
  jetP4SmearUp = 0;
  jetP4SmearDo = 0;
  jetPFLooseId = 0;
  jetID = 0;
  jetPUID = 0;
  jetPUFullID = 0;
  jetJECUnc = 0;
  jetFiredTrgs = 0;
  jetCHF = 0;
  jetNHF = 0;
  jetCEF = 0;
  jetNEF = 0;
  jetNCH = 0;
  jetNNP = 0;
  jetMUF = 0;
  jetVtxPt = 0;
  jetVtxMass = 0;
  jetVtxNtrks = 0;
  jetVtx3DVal = 0;
  jetVtx3DSig = 0;
  AK8JetPt = 0;
  AK8JetEn = 0;
  AK8JetRawPt = 0;
  AK8JetRawEn = 0;
  AK8JetEta = 0;
  AK8JetPhi = 0;
  AK8JetMass = 0;
  AK8Jet_tau1 = 0;
  AK8Jet_tau2 = 0;
  AK8Jet_tau3 = 0;
  AK8JetCHF = 0;
  AK8JetNHF = 0;
  AK8JetCEF = 0;
  AK8JetNEF = 0;
  AK8JetNCH = 0;
  AK8JetNNP = 0;
  AK8JetMUF = 0;
  AK8Jetnconstituents = 0;
  AK8JetPFLooseId = 0;
  AK8JetPFTightLepVetoId = 0;
  AK8JetSoftDropMass = 0;
  AK8JetSoftDropMassCorr = 0;
  AK8JetPrunedMass = 0;
  AK8JetPrunedMassCorr = 0;
  AK8JetpfBoostedDSVBTag = 0;
  AK8JetDSVnewV4 = 0;
  AK8JetCSV = 0;
  AK8JetJECUnc = 0;
  AK8JetL2L3corr = 0;
  AK8puppiPt = 0;
  AK8puppiMass = 0;
  AK8puppiEta = 0;
  AK8puppiPhi = 0;
  AK8puppiTau1 = 0;
  AK8puppiTau2 = 0;
  AK8puppiTau3 = 0;
  AK8puppiSDL2L3corr = 0;
  AK8puppiSDMass = 0;
  AK8puppiSDMassL2L3Corr = 0;
  nAK8SDSJ = 0;
  AK8SDSJPt = 0;
  AK8SDSJEta = 0;
  AK8SDSJPhi = 0;
  AK8SDSJMass = 0;
  AK8SDSJE = 0;
  AK8SDSJCharge = 0;
  AK8SDSJFlavour = 0;
  AK8SDSJCSV = 0;
  nAK8puppiSDSJ = 0;
  AK8puppiSDSJPt = 0;
  AK8puppiSDSJEta = 0;
  AK8puppiSDSJPhi = 0;
  AK8puppiSDSJMass = 0;
  AK8puppiSDSJE = 0;
  AK8puppiSDSJCharge = 0;
  AK8puppiSDSJFlavour = 0;
  AK8puppiSDSJCSV = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
  fChain->SetBranchAddress("isData", &isData, &b_isData);
  fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
  fChain->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
  fChain->SetBranchAddress("nTrksPV", &nTrksPV, &b_nTrksPV);
  fChain->SetBranchAddress("isPVGood", &isPVGood, &b_isPVGood);
  fChain->SetBranchAddress("vtx", &vtx, &b_vtx);
  fChain->SetBranchAddress("vty", &vty, &b_vty);
  fChain->SetBranchAddress("vtz", &vtz, &b_vtz);
  fChain->SetBranchAddress("rho", &rho, &b_rho);
  fChain->SetBranchAddress("rhoCentral", &rhoCentral, &b_rhoCentral);
  fChain->SetBranchAddress("HLTEleMuX", &HLTEleMuX, &b_HLTEleMuX);
  fChain->SetBranchAddress("HLTPho", &HLTPho, &b_HLTPho);
  fChain->SetBranchAddress("HLTJet", &HLTJet, &b_HLTJet);
  fChain->SetBranchAddress("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled, &b_HLTEleMuXIsPrescaled);
  fChain->SetBranchAddress("HLTPhoIsPrescaled", &HLTPhoIsPrescaled, &b_HLTPhoIsPrescaled);
  fChain->SetBranchAddress("HLTJetIsPrescaled", &HLTJetIsPrescaled, &b_HLTJetIsPrescaled);
  
  fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
  fChain->SetBranchAddress("pfMET", &pfMET, &b_pfMET);
  fChain->SetBranchAddress("caloMET", &caloMET, &b_caloMET);
  fChain->SetBranchAddress("fCoordinates.fX", &fCoordinates_fX, &b_caloMet_fCoordinates_fX);
  fChain->SetBranchAddress("fCoordinates.fY", &fCoordinates_fY, &b_caloMet_fCoordinates_fY);
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
  fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
  fChain->SetBranchAddress("phoE", &phoE, &b_phoE);
  fChain->SetBranchAddress("phoEt", &phoEt, &b_phoEt);
  fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
  fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
  fChain->SetBranchAddress("phoCalibE", &phoCalibE, &b_phoCalibE);
  fChain->SetBranchAddress("phoCalibEt", &phoCalibEt, &b_phoCalibEt);
  fChain->SetBranchAddress("phoSCE", &phoSCE, &b_phoSCE);
  fChain->SetBranchAddress("phoSCRawE", &phoSCRawE, &b_phoSCRawE);
  fChain->SetBranchAddress("phoESEnP1", &phoESEnP1, &b_phoESEnP1);
  fChain->SetBranchAddress("phoESEnP2", &phoESEnP2, &b_phoESEnP2);
  fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
  fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
  fChain->SetBranchAddress("phoSCEtaWidth", &phoSCEtaWidth, &b_phoSCEtaWidth);
  fChain->SetBranchAddress("phoSCPhiWidth", &phoSCPhiWidth, &b_phoSCPhiWidth);
  fChain->SetBranchAddress("phoSCBrem", &phoSCBrem, &b_phoSCBrem);
  fChain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed, &b_phohasPixelSeed);
  fChain->SetBranchAddress("phoEleVeto", &phoEleVeto, &b_phoEleVeto);
  fChain->SetBranchAddress("phoR9", &phoR9, &b_phoR9);
  fChain->SetBranchAddress("phoHoverE", &phoHoverE, &b_phoHoverE);
  fChain->SetBranchAddress("phoE1x3", &phoE1x3, &b_phoE1x3);
  fChain->SetBranchAddress("phoE1x5", &phoE1x5, &b_phoE1x5);
  fChain->SetBranchAddress("phoE2x2", &phoE2x2, &b_phoE2x2);
  fChain->SetBranchAddress("phoE2x5Max", &phoE2x5Max, &b_phoE2x5Max);
  fChain->SetBranchAddress("phoE5x5", &phoE5x5, &b_phoE5x5);
  fChain->SetBranchAddress("phoESEffSigmaRR", &phoESEffSigmaRR, &b_phoESEffSigmaRR);
  fChain->SetBranchAddress("phoSigmaIEtaIEtaFull5x5", &phoSigmaIEtaIEtaFull5x5, &b_phoSigmaIEtaIEtaFull5x5);
  fChain->SetBranchAddress("phoSigmaIEtaIPhiFull5x5", &phoSigmaIEtaIPhiFull5x5, &b_phoSigmaIEtaIPhiFull5x5);
  fChain->SetBranchAddress("phoSigmaIPhiIPhiFull5x5", &phoSigmaIPhiIPhiFull5x5, &b_phoSigmaIPhiIPhiFull5x5);
  fChain->SetBranchAddress("phoE1x3Full5x5", &phoE1x3Full5x5, &b_phoE1x3Full5x5);
  fChain->SetBranchAddress("phoE1x5Full5x5", &phoE1x5Full5x5, &b_phoE1x5Full5x5);
  fChain->SetBranchAddress("phoE2x2Full5x5", &phoE2x2Full5x5, &b_phoE2x2Full5x5);
  fChain->SetBranchAddress("phoE2x5MaxFull5x5", &phoE2x5MaxFull5x5, &b_phoE2x5MaxFull5x5);
  fChain->SetBranchAddress("phoE5x5Full5x5", &phoE5x5Full5x5, &b_phoE5x5Full5x5);
  fChain->SetBranchAddress("phoR9Full5x5", &phoR9Full5x5, &b_phoR9Full5x5);
  fChain->SetBranchAddress("phoPFChIso", &phoPFChIso, &b_phoPFChIso);
  fChain->SetBranchAddress("phoPFPhoIso", &phoPFPhoIso, &b_phoPFPhoIso);
  fChain->SetBranchAddress("phoPFNeuIso", &phoPFNeuIso, &b_phoPFNeuIso);
  fChain->SetBranchAddress("phoPFChWorstIso", &phoPFChWorstIso, &b_phoPFChWorstIso);
  fChain->SetBranchAddress("phoCITKChIso", &phoCITKChIso, &b_phoCITKChIso);
  fChain->SetBranchAddress("phoCITKPhoIso", &phoCITKPhoIso, &b_phoCITKPhoIso);
  fChain->SetBranchAddress("phoCITKNeuIso", &phoCITKNeuIso, &b_phoCITKNeuIso);
  fChain->SetBranchAddress("phoIDMVA", &phoIDMVA, &b_phoIDMVA);
  fChain->SetBranchAddress("phoFiredSingleTrgs", &phoFiredSingleTrgs, &b_phoFiredSingleTrgs);
  fChain->SetBranchAddress("phoFiredDoubleTrgs", &phoFiredDoubleTrgs, &b_phoFiredDoubleTrgs);
  fChain->SetBranchAddress("phoFiredL1Trgs", &phoFiredL1Trgs, &b_phoFiredL1Trgs);
  fChain->SetBranchAddress("phoSeedTime", &phoSeedTime, &b_phoSeedTime);
  fChain->SetBranchAddress("phoSeedEnergy", &phoSeedEnergy, &b_phoSeedEnergy);
  fChain->SetBranchAddress("phoxtalBits", &phoxtalBits, &b_phoxtalBits);
  fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
  fChain->SetBranchAddress("npfPho", &npfPho, &b_npfPho);
  fChain->SetBranchAddress("pfphoEt", &pfphoEt, &b_pfphoEt);
  fChain->SetBranchAddress("pfphoEta", &pfphoEta, &b_pfphoEta);
  fChain->SetBranchAddress("pfphoPhi", &pfphoPhi, &b_pfphoPhi);
  fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
  fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
  fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
  fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
  fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
  fChain->SetBranchAddress("eleESEnP1", &eleESEnP1, &b_eleESEnP1);
  fChain->SetBranchAddress("eleESEnP2", &eleESEnP2, &b_eleESEnP2);
  fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
  fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
  fChain->SetBranchAddress("eleSIP", &eleSIP, &b_eleSIP);
  fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
  fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
  fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
  fChain->SetBranchAddress("eleR9", &eleR9, &b_eleR9);
  fChain->SetBranchAddress("eleCalibPt", &eleCalibPt, &b_eleCalibPt);
  fChain->SetBranchAddress("eleCalibEn", &eleCalibEn, &b_eleCalibEn);
  fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
  fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
  fChain->SetBranchAddress("eleSCRawEn", &eleSCRawEn, &b_eleSCRawEn);
  fChain->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth, &b_eleSCEtaWidth);
  fChain->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth, &b_eleSCPhiWidth);
  fChain->SetBranchAddress("eleHoverE", &eleHoverE, &b_eleHoverE);
  fChain->SetBranchAddress("eleEoverP", &eleEoverP, &b_eleEoverP);
  fChain->SetBranchAddress("eleEoverPout", &eleEoverPout, &b_eleEoverPout);
  fChain->SetBranchAddress("eleEoverPInv", &eleEoverPInv, &b_eleEoverPInv);
  fChain->SetBranchAddress("eleBrem", &eleBrem, &b_eleBrem);
  fChain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx, &b_eledEtaAtVtx);
  fChain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx, &b_eledPhiAtVtx);
  fChain->SetBranchAddress("eledEtaAtCalo", &eledEtaAtCalo, &b_eledEtaAtCalo);
  fChain->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5, &b_eleSigmaIEtaIEtaFull5x5);
  fChain->SetBranchAddress("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5, &b_eleSigmaIPhiIPhiFull5x5);
  fChain->SetBranchAddress("eleConvVeto", &eleConvVeto, &b_eleConvVeto);
  fChain->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
  fChain->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR, &b_eleESEffSigmaRR);
  fChain->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
  fChain->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
  fChain->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
  fChain->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
  fChain->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso, &b_elePFClusEcalIso);
  fChain->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso, &b_elePFClusHcalIso);
  fChain->SetBranchAddress("elePFMiniIso", &elePFMiniIso, &b_elePFMiniIso);
  fChain->SetBranchAddress("eleIDMVA", &eleIDMVA, &b_eleIDMVA);
  fChain->SetBranchAddress("eleIDMVAHZZ", &eleIDMVAHZZ, &b_eleIDMVAHZZ);
  fChain->SetBranchAddress("eledEtaseedAtVtx", &eledEtaseedAtVtx, &b_eledEtaseedAtVtx);
  fChain->SetBranchAddress("eleE1x5", &eleE1x5, &b_eleE1x5);
  fChain->SetBranchAddress("eleE2x5", &eleE2x5, &b_eleE2x5);
  fChain->SetBranchAddress("eleE5x5", &eleE5x5, &b_eleE5x5);
  fChain->SetBranchAddress("eleE1x5Full5x5", &eleE1x5Full5x5, &b_eleE1x5Full5x5);
  fChain->SetBranchAddress("eleE2x5Full5x5", &eleE2x5Full5x5, &b_eleE2x5Full5x5);
  fChain->SetBranchAddress("eleE5x5Full5x5", &eleE5x5Full5x5, &b_eleE5x5Full5x5);
  fChain->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5, &b_eleR9Full5x5);
  fChain->SetBranchAddress("eleEcalDrivenSeed", &eleEcalDrivenSeed, &b_eleEcalDrivenSeed);
  fChain->SetBranchAddress("eleDr03EcalRecHitSumEt", &eleDr03EcalRecHitSumEt, &b_eleDr03EcalRecHitSumEt);
  fChain->SetBranchAddress("eleDr03HcalDepth1TowerSumEt", &eleDr03HcalDepth1TowerSumEt, &b_eleDr03HcalDepth1TowerSumEt);
  fChain->SetBranchAddress("eleDr03HcalDepth2TowerSumEt", &eleDr03HcalDepth2TowerSumEt, &b_eleDr03HcalDepth2TowerSumEt);
  fChain->SetBranchAddress("eleDr03HcalTowerSumEt", &eleDr03HcalTowerSumEt, &b_eleDr03HcalTowerSumEt);
  fChain->SetBranchAddress("eleDr03TkSumPt", &eleDr03TkSumPt, &b_eleDr03TkSumPt);
  fChain->SetBranchAddress("elecaloEnergy", &elecaloEnergy, &b_elecaloEnergy);
  fChain->SetBranchAddress("eleTrkdxy", &eleTrkdxy, &b_eleTrkdxy);
  fChain->SetBranchAddress("eleKFHits", &eleKFHits, &b_eleKFHits);
  fChain->SetBranchAddress("eleKFChi2", &eleKFChi2, &b_eleKFChi2);
  fChain->SetBranchAddress("eleGSFChi2", &eleGSFChi2, &b_eleGSFChi2);
  fChain->SetBranchAddress("eleGSFPt", &eleGSFPt, &b_eleGSFPt);
  fChain->SetBranchAddress("eleGSFEta", &eleGSFEta, &b_eleGSFEta);
  fChain->SetBranchAddress("eleGSFPhi", &eleGSFPhi, &b_eleGSFPhi);
  fChain->SetBranchAddress("eleGSFCharge", &eleGSFCharge, &b_eleGSFCharge);
  fChain->SetBranchAddress("eleGSFHits", &eleGSFHits, &b_eleGSFHits);
  fChain->SetBranchAddress("eleGSFMissHits", &eleGSFMissHits, &b_eleGSFMissHits);
  fChain->SetBranchAddress("eleGSFNHitsMax", &eleGSFNHitsMax, &b_eleGSFNHitsMax);
  fChain->SetBranchAddress("eleGSFVtxProb", &eleGSFVtxProb, &b_eleGSFVtxProb);
  fChain->SetBranchAddress("eleGSFlxyPV", &eleGSFlxyPV, &b_eleGSFlxyPV);
  fChain->SetBranchAddress("eleGSFlxyBS", &eleGSFlxyBS, &b_eleGSFlxyBS);
  fChain->SetBranchAddress("eleBCEn", &eleBCEn, &b_eleBCEn);
  fChain->SetBranchAddress("eleBCEta", &eleBCEta, &b_eleBCEta);
  fChain->SetBranchAddress("eleBCPhi", &eleBCPhi, &b_eleBCPhi);
  fChain->SetBranchAddress("eleBCS25", &eleBCS25, &b_eleBCS25);
  fChain->SetBranchAddress("eleBCS15", &eleBCS15, &b_eleBCS15);
  fChain->SetBranchAddress("eleBCSieie", &eleBCSieie, &b_eleBCSieie);
  fChain->SetBranchAddress("eleBCSieip", &eleBCSieip, &b_eleBCSieip);
  fChain->SetBranchAddress("eleBCSipip", &eleBCSipip, &b_eleBCSipip);
  fChain->SetBranchAddress("eleFiredSingleTrgs", &eleFiredSingleTrgs, &b_eleFiredSingleTrgs);
  fChain->SetBranchAddress("eleFiredDoubleTrgs", &eleFiredDoubleTrgs, &b_eleFiredDoubleTrgs);
  fChain->SetBranchAddress("eleFiredL1Trgs", &eleFiredL1Trgs, &b_eleFiredL1Trgs);
  fChain->SetBranchAddress("eleIDbit", &eleIDbit, &b_eleIDbit);
  fChain->SetBranchAddress("npfHF", &npfHF, &b_npfHF);
  fChain->SetBranchAddress("pfHFEn", &pfHFEn, &b_pfHFEn);
  fChain->SetBranchAddress("pfHFECALEn", &pfHFECALEn, &b_pfHFECALEn);
  fChain->SetBranchAddress("pfHFHCALEn", &pfHFHCALEn, &b_pfHFHCALEn);
  fChain->SetBranchAddress("pfHFPt", &pfHFPt, &b_pfHFPt);
  fChain->SetBranchAddress("pfHFEta", &pfHFEta, &b_pfHFEta);
  fChain->SetBranchAddress("pfHFPhi", &pfHFPhi, &b_pfHFPhi);
  fChain->SetBranchAddress("pfHFIso", &pfHFIso, &b_pfHFIso);
  fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
  fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
  fChain->SetBranchAddress("muEn", &muEn, &b_muEn);
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
  fChain->SetBranchAddress("muIsoTrk", &muIsoTrk, &b_muIsoTrk);
  fChain->SetBranchAddress("muPFChIso", &muPFChIso, &b_muPFChIso);
  fChain->SetBranchAddress("muPFPhoIso", &muPFPhoIso, &b_muPFPhoIso);
  fChain->SetBranchAddress("muPFNeuIso", &muPFNeuIso, &b_muPFNeuIso);
  fChain->SetBranchAddress("muPFPUIso", &muPFPUIso, &b_muPFPUIso);
  fChain->SetBranchAddress("muPFMiniIso", &muPFMiniIso, &b_muPFMiniIso);
  fChain->SetBranchAddress("muFiredTrgs", &muFiredTrgs, &b_muFiredTrgs);
  fChain->SetBranchAddress("muFiredL1Trgs", &muFiredL1Trgs, &b_muFiredL1Trgs);
  fChain->SetBranchAddress("muInnervalidFraction", &muInnervalidFraction, &b_muInnervalidFraction);
  fChain->SetBranchAddress("musegmentCompatibility", &musegmentCompatibility, &b_musegmentCompatibility);
  fChain->SetBranchAddress("muchi2LocalPosition", &muchi2LocalPosition, &b_muchi2LocalPosition);
  fChain->SetBranchAddress("mutrkKink", &mutrkKink, &b_mutrkKink);
  fChain->SetBranchAddress("muBestTrkPtError", &muBestTrkPtError, &b_muBestTrkPtError);
  fChain->SetBranchAddress("muBestTrkPt", &muBestTrkPt, &b_muBestTrkPt);
  fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
  fChain->SetBranchAddress("jetetaWidth", &jetetaWidth, &b_jetetaWidth);
  fChain->SetBranchAddress("jetphiWidth", &jetphiWidth, &b_jetphiWidth);
  fChain->SetBranchAddress("jetnPhotons", &jetnPhotons, &b_jetnPhotons);
  fChain->SetBranchAddress("jetnCHPions", &jetnCHPions, &b_jetnCHPions);
  fChain->SetBranchAddress("jetnMisc", &jetnMisc, &b_jetnMisc);
  fChain->SetBranchAddress("jetMiscPID", &jetMiscPID, &b_jetMiscPID);
  fChain->SetBranchAddress("JetsPFConsPt", &JetsPFConsPt, &b_JetsPFConsPt);
  fChain->SetBranchAddress("JetsPFConsEta", &JetsPFConsEta, &b_JetsPFConsEta);
  fChain->SetBranchAddress("JetsPFConsPhi", &JetsPFConsPhi, &b_JetsPFConsPhi);
  fChain->SetBranchAddress("JetsPFConsEt", &JetsPFConsEt, &b_JetsPFConsEt);
  fChain->SetBranchAddress("JetsPFConsPID", &JetsPFConsPID, &b_JetsPFConsPID);
  fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
  fChain->SetBranchAddress("jetEn", &jetEn, &b_jetEn);
  fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
  fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
  fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
  fChain->SetBranchAddress("jetRawEn", &jetRawEn, &b_jetRawEn);
  fChain->SetBranchAddress("jetMt", &jetMt, &b_jetMt);
  fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
  fChain->SetBranchAddress("jetLeadTrackPt", &jetLeadTrackPt, &b_jetLeadTrackPt);
  fChain->SetBranchAddress("jetLeadTrackEta", &jetLeadTrackEta, &b_jetLeadTrackEta);
  fChain->SetBranchAddress("jetLeadTrackPhi", &jetLeadTrackPhi, &b_jetLeadTrackPhi);
  fChain->SetBranchAddress("jetLepTrackPID", &jetLepTrackPID, &b_jetLepTrackPID);
  fChain->SetBranchAddress("jetLepTrackPt", &jetLepTrackPt, &b_jetLepTrackPt);
  fChain->SetBranchAddress("jetLepTrackEta", &jetLepTrackEta, &b_jetLepTrackEta);
  fChain->SetBranchAddress("jetLepTrackPhi", &jetLepTrackPhi, &b_jetLepTrackPhi);
  fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
  fChain->SetBranchAddress("jetJetProbabilityBJetTags", &jetJetProbabilityBJetTags, &b_jetJetProbabilityBJetTags);
  fChain->SetBranchAddress("jetpfCombinedMVAV2BJetTags", &jetpfCombinedMVAV2BJetTags, &b_jetpfCombinedMVAV2BJetTags);
  fChain->SetBranchAddress("jetPFLooseId", &jetPFLooseId, &b_jetPFLooseId);
  fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
  fChain->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
  fChain->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
  fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
  fChain->SetBranchAddress("jetFiredTrgs", &jetFiredTrgs, &b_jetFiredTrgs);
  fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
  fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
  fChain->SetBranchAddress("jetCEF", &jetCEF, &b_jetCEF);
  fChain->SetBranchAddress("jetNEF", &jetNEF, &b_jetNEF);
  fChain->SetBranchAddress("jetNCH", &jetNCH, &b_jetNCH);
  fChain->SetBranchAddress("jetNNP", &jetNNP, &b_jetNNP);
  fChain->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
  fChain->SetBranchAddress("jetVtxPt", &jetVtxPt, &b_jetVtxPt);
  fChain->SetBranchAddress("jetVtxMass", &jetVtxMass, &b_jetVtxMass);
  fChain->SetBranchAddress("jetVtxNtrks", &jetVtxNtrks, &b_jetVtxNtrks);
  fChain->SetBranchAddress("jetVtx3DVal", &jetVtx3DVal, &b_jetVtx3DVal);
  fChain->SetBranchAddress("jetVtx3DSig", &jetVtx3DSig, &b_jetVtx3DSig);
  
  //Data specific variables
  if (sample.isData) {
    fChain->SetBranchAddress("phoPrescale", &phoPrescale, &b_phoPrescale);
    fChain->SetBranchAddress("nAK8Jet", &nAK8Jet, &b_nAK8Jet);
    fChain->SetBranchAddress("AK8JetPt", &AK8JetPt, &b_AK8JetPt);
    fChain->SetBranchAddress("AK8JetEn", &AK8JetEn, &b_AK8JetEn);
    fChain->SetBranchAddress("AK8JetRawPt", &AK8JetRawPt, &b_AK8JetRawPt);
    fChain->SetBranchAddress("AK8JetRawEn", &AK8JetRawEn, &b_AK8JetRawEn);
    fChain->SetBranchAddress("AK8JetEta", &AK8JetEta, &b_AK8JetEta);
    fChain->SetBranchAddress("AK8JetPhi", &AK8JetPhi, &b_AK8JetPhi);
    fChain->SetBranchAddress("AK8JetMass", &AK8JetMass, &b_AK8JetMass);
    fChain->SetBranchAddress("AK8Jet_tau1", &AK8Jet_tau1, &b_AK8Jet_tau1);
    fChain->SetBranchAddress("AK8Jet_tau2", &AK8Jet_tau2, &b_AK8Jet_tau2);
    fChain->SetBranchAddress("AK8Jet_tau3", &AK8Jet_tau3, &b_AK8Jet_tau3);
    fChain->SetBranchAddress("AK8JetCHF", &AK8JetCHF, &b_AK8JetCHF);
    fChain->SetBranchAddress("AK8JetNHF", &AK8JetNHF, &b_AK8JetNHF);
    fChain->SetBranchAddress("AK8JetCEF", &AK8JetCEF, &b_AK8JetCEF);
    fChain->SetBranchAddress("AK8JetNEF", &AK8JetNEF, &b_AK8JetNEF);
    fChain->SetBranchAddress("AK8JetNCH", &AK8JetNCH, &b_AK8JetNCH);
    fChain->SetBranchAddress("AK8JetNNP", &AK8JetNNP, &b_AK8JetNNP);
    fChain->SetBranchAddress("AK8JetMUF", &AK8JetMUF, &b_AK8JetMUF);
    fChain->SetBranchAddress("AK8Jetnconstituents", &AK8Jetnconstituents, &b_AK8Jetnconstituents);
    fChain->SetBranchAddress("AK8JetPFLooseId", &AK8JetPFLooseId, &b_AK8JetPFLooseId);
    fChain->SetBranchAddress("AK8JetPFTightLepVetoId", &AK8JetPFTightLepVetoId, &b_AK8JetPFTightLepVetoId);
    fChain->SetBranchAddress("AK8JetSoftDropMass", &AK8JetSoftDropMass, &b_AK8JetSoftDropMass);
    fChain->SetBranchAddress("AK8JetSoftDropMassCorr", &AK8JetSoftDropMassCorr, &b_AK8JetSoftDropMassCorr);
    fChain->SetBranchAddress("AK8JetPrunedMass", &AK8JetPrunedMass, &b_AK8JetPrunedMass);
    fChain->SetBranchAddress("AK8JetPrunedMassCorr", &AK8JetPrunedMassCorr, &b_AK8JetPrunedMassCorr);
    fChain->SetBranchAddress("AK8JetpfBoostedDSVBTag", &AK8JetpfBoostedDSVBTag, &b_AK8JetpfBoostedDSVBTag);
    fChain->SetBranchAddress("AK8JetDSVnewV4", &AK8JetDSVnewV4, &b_AK8JetDSVnewV4);
    fChain->SetBranchAddress("AK8JetCSV", &AK8JetCSV, &b_AK8JetCSV);
    fChain->SetBranchAddress("AK8JetJECUnc", &AK8JetJECUnc, &b_AK8JetJECUnc);
    fChain->SetBranchAddress("AK8JetL2L3corr", &AK8JetL2L3corr, &b_AK8JetL2L3corr);
    fChain->SetBranchAddress("AK8puppiPt", &AK8puppiPt, &b_AK8puppiPt);
    fChain->SetBranchAddress("AK8puppiMass", &AK8puppiMass, &b_AK8puppiMass);
    fChain->SetBranchAddress("AK8puppiEta", &AK8puppiEta, &b_AK8puppiEta);
    fChain->SetBranchAddress("AK8puppiPhi", &AK8puppiPhi, &b_AK8puppiPhi);
    fChain->SetBranchAddress("AK8puppiTau1", &AK8puppiTau1, &b_AK8puppiTau1);
    fChain->SetBranchAddress("AK8puppiTau2", &AK8puppiTau2, &b_AK8puppiTau2);
    fChain->SetBranchAddress("AK8puppiTau3", &AK8puppiTau3, &b_AK8puppiTau3);
    fChain->SetBranchAddress("AK8puppiSDL2L3corr", &AK8puppiSDL2L3corr, &b_AK8puppiSDL2L3corr);
    fChain->SetBranchAddress("AK8puppiSDMass", &AK8puppiSDMass, &b_AK8puppiSDMass);
    fChain->SetBranchAddress("AK8puppiSDMassL2L3Corr", &AK8puppiSDMassL2L3Corr, &b_AK8puppiSDMassL2L3Corr);
    fChain->SetBranchAddress("nAK8SDSJ", &nAK8SDSJ, &b_nAK8SDSJ);
    fChain->SetBranchAddress("AK8SDSJPt", &AK8SDSJPt, &b_AK8SDSJPt);
    fChain->SetBranchAddress("AK8SDSJEta", &AK8SDSJEta, &b_AK8SDSJEta);
    fChain->SetBranchAddress("AK8SDSJPhi", &AK8SDSJPhi, &b_AK8SDSJPhi);
    fChain->SetBranchAddress("AK8SDSJMass", &AK8SDSJMass, &b_AK8SDSJMass);
    fChain->SetBranchAddress("AK8SDSJE", &AK8SDSJE, &b_AK8SDSJE);
    fChain->SetBranchAddress("AK8SDSJCharge", &AK8SDSJCharge, &b_AK8SDSJCharge);
    fChain->SetBranchAddress("AK8SDSJFlavour", &AK8SDSJFlavour, &b_AK8SDSJFlavour);
    fChain->SetBranchAddress("AK8SDSJCSV", &AK8SDSJCSV, &b_AK8SDSJCSV);
    fChain->SetBranchAddress("nAK8puppiSDSJ", &nAK8puppiSDSJ, &b_nAK8puppiSDSJ);
    fChain->SetBranchAddress("AK8puppiSDSJPt", &AK8puppiSDSJPt, &b_AK8puppiSDSJPt);
    fChain->SetBranchAddress("AK8puppiSDSJEta", &AK8puppiSDSJEta, &b_AK8puppiSDSJEta);
    fChain->SetBranchAddress("AK8puppiSDSJPhi", &AK8puppiSDSJPhi, &b_AK8puppiSDSJPhi);
    fChain->SetBranchAddress("AK8puppiSDSJMass", &AK8puppiSDSJMass, &b_AK8puppiSDSJMass);
    fChain->SetBranchAddress("AK8puppiSDSJE", &AK8puppiSDSJE, &b_AK8puppiSDSJE);
    fChain->SetBranchAddress("AK8puppiSDSJCharge", &AK8puppiSDSJCharge, &b_AK8puppiSDSJCharge);
    fChain->SetBranchAddress("AK8puppiSDSJFlavour", &AK8puppiSDSJFlavour, &b_AK8puppiSDSJFlavour);
    fChain->SetBranchAddress("AK8puppiSDSJCSV", &AK8puppiSDSJCSV, &b_AK8puppiSDSJCSV);
  }
  //Monte Carlo specific variables
  else {
    fChain->SetBranchAddress("pdf", &pdf, &b_pdf);
    fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
    fChain->SetBranchAddress("processID", &processID, &b_processID);
    fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
    fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
    fChain->SetBranchAddress("EventTag", &EventTag, &b_EventTag);
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
    fChain->SetBranchAddress("mcGMomPID", &mcGMomPID, &b_mcGMomPID);
    fChain->SetBranchAddress("mcMomPID", &mcMomPID, &b_mcMomPID);
    fChain->SetBranchAddress("mcMomPt", &mcMomPt, &b_mcMomPt);
    fChain->SetBranchAddress("mcMomMass", &mcMomMass, &b_mcMomMass);
    fChain->SetBranchAddress("mcMomEta", &mcMomEta, &b_mcMomEta);
    fChain->SetBranchAddress("mcMomPhi", &mcMomPhi, &b_mcMomPhi);
    fChain->SetBranchAddress("mcStatusFlag", &mcStatusFlag, &b_mcStatusFlag);
    fChain->SetBranchAddress("mcParentage", &mcParentage, &b_mcParentage);
    fChain->SetBranchAddress("mcStatus", &mcStatus, &b_mcStatus);
    fChain->SetBranchAddress("mcCalIsoDR03", &mcCalIsoDR03, &b_mcCalIsoDR03);
    fChain->SetBranchAddress("mcTrkIsoDR03", &mcTrkIsoDR03, &b_mcTrkIsoDR03);
    fChain->SetBranchAddress("mcCalIsoDR04", &mcCalIsoDR04, &b_mcCalIsoDR04);
    fChain->SetBranchAddress("mcTrkIsoDR04", &mcTrkIsoDR04, &b_mcTrkIsoDR04);
    fChain->SetBranchAddress("genMET", &genMET, &b_genMET);
    fChain->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
    fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
    fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
    fChain->SetBranchAddress("jetGenJetEn", &jetGenJetEn, &b_jetGenJetEn);
    fChain->SetBranchAddress("jetGenJetPt", &jetGenJetPt, &b_jetGenJetPt);
    fChain->SetBranchAddress("jetGenJetEta", &jetGenJetEta, &b_jetGenJetEta);
    fChain->SetBranchAddress("jetGenJetPhi", &jetGenJetPhi, &b_jetGenJetPhi);
    fChain->SetBranchAddress("jetGenPartonID", &jetGenPartonID, &b_jetGenPartonID);
    fChain->SetBranchAddress("jetGenEn", &jetGenEn, &b_jetGenEn);
    fChain->SetBranchAddress("jetGenPt", &jetGenPt, &b_jetGenPt);
    fChain->SetBranchAddress("jetGenEta", &jetGenEta, &b_jetGenEta);
    fChain->SetBranchAddress("jetGenPhi", &jetGenPhi, &b_jetGenPhi);
    fChain->SetBranchAddress("jetGenPartonMomID", &jetGenPartonMomID, &b_jetGenPartonMomID);
    fChain->SetBranchAddress("jetP4Smear", &jetP4Smear, &b_jetP4Smear);
    fChain->SetBranchAddress("jetP4SmearUp", &jetP4SmearUp, &b_jetP4SmearUp);
    fChain->SetBranchAddress("jetP4SmearDo", &jetP4SmearDo, &b_jetP4SmearDo);
  }
  Notify();
}

Bool_t ZprimeJetsCommon::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ZprimeJetsCommon::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t ZprimeJetsCommon::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef ZprimeJetsCommon_cxx
