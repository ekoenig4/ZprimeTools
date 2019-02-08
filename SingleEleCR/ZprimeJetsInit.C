#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"

using namespace std;

#ifdef ZprimeJetsClass_cxx
vector<string> ZprimeJetsClass::split(string str,string delim) {
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

bool ZprimeJetsClass::fileSelection(string filename,string fileRange)
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

ZprimeJetsClass::ZprimeJetsClass(const char* inputFilename,const char* outputFilename,const char* fileRange) 
{
  TChain *chain = new TChain("phoJetNtuplizer/eventTree");
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
  string sampleID[Total] = {"SingleEle","WJets","ZJets","DYJets","QCD","TTJets","GJets","EWK"};
  cout<<"Sample type: "<<sampleID[sample.type]<< (sample.isInclusive ? " Inclusive" : " not Inclusive") <<endl;
  cout<<inFile<<" files added."<<endl;
  cout<<"Initializing chain."<<endl;
  Init(chain);
  BookHistos(outputFilename);
}

ZprimeJetsClass::~ZprimeJetsClass()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  output->cd();
  output->Write();
  tree->Write();
  output->Close();
}

Int_t ZprimeJetsClass::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ZprimeJetsClass::LoadTree(Long64_t entry)
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

void ZprimeJetsClass::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  phoE = 0;
  phoPx = 0;
  phoPy = 0;
  phoPz = 0;
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
  phoR9 = 0;
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
  phoMVAIDbit = 0;
  phoSeedTime = 0;
  phoSeedEnergy = 0;
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
  jetPx = 0;
  jetPy = 0;
  jetPz = 0;
  jetEn = 0;
  jetEta = 0;
  jetPhi = 0;
  jetRawPt = 0;
  jetRawEn = 0;
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
  jetLeadTrackPt = 0;
  jetLeadTrackEta = 0;
  jetLeadTrackPhi = 0;
  jetLepTrackPID = 0;
  jetLepTrackPt = 0;
  jetLepTrackEta = 0;
  jetLepTrackPhi = 0;
  jetetaWidth = 0;
  jetphiWidth = 0;
  jetnPhotons = 0;
  jetnCHPions = 0;
  jetnMisc = 0;
  jetMiscPdgId = 0;
  jetConstPt = 0;
  jetConstEt = 0;
  jetConstEta = 0;
  jetConstPhi = 0;
  jetConstPdgId = 0;
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
  elePt = 0;
  eleEta = 0;
  elePhi = 0;
  eleR9 = 0;
  eleR9Full5x5 = 0;
  eleEn = 0;
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
  eleSCRawEn = 0;
  eleSCEn = 0;
  eleSCEta = 0;
  eleSCPhi = 0;
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
  eledEtaseedAtVtx = 0;
  eleSigmaIEtaIEtaFull5x5 = 0;
  eleSigmaIPhiIPhiFull5x5 = 0;
  eleConvVeto = 0;
  eleMissHits = 0;
  elePFChIso = 0;
  elePFPhoIso = 0;
  elePFNeuIso = 0;
  elePFPUIso = 0;
  elePFClusEcalIso = 0;
  elePFClusHcalIso = 0;
  eleHEEPID = 0;
  eleMVAIsoID = 0;
  eleMVAnoIsoID = 0;
  eleIDbit = 0;
  eleMVAIsoIDbit = 0;
  eleMVAnoIsoIDbit = 0;
  eleTrkdxy = 0;
  eleKFHits = 0;
  eleKFChi2 = 0;
  eleGSFChi2 = 0;
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
  muInnervalidFraction = 0;
  musegmentCompatibility = 0;
  muchi2LocalPosition = 0;
  mutrkKink = 0;
  muBestTrkPtError = 0;
  muBestTrkPt = 0;
  muBestTrkType = 0;
  tauEta = 0;
  tauPhi = 0;
  tauPt = 0;
  tauEt = 0;
  tauCharge = 0;
  tauDecayMode = 0;
  tauP = 0;
  tauPx = 0;
  tauPy = 0;
  tauPz = 0;
  tauVz = 0;
  tauEnergy = 0;
  tauMass = 0;
  tauDxy = 0;
  tauZImpact = 0;
  tauChargedIsoPtSum = 0;
  tauNeutralIsoPtSum = 0;
  tauPuCorrPtSum = 0;
  tauNumSignalPFChargedHadrCands = 0;
  tauNumSignalPFNeutrHadrCands = 0;
  tauNumSignalPFGammaCands = 0;
  tauNumSignalPFCands = 0;
  tauNumIsolationPFChargedHadrCands = 0;
  tauNumIsolationPFNeutrHadrCands = 0;
  tauNumIsolationPFGammaCands = 0;
  tauNumIsolationPFCands = 0;
  tauLeadChargedHadronExists = 0;
  tauLeadChargedHadronEta = 0;
  tauLeadChargedHadronPhi = 0;
  tauLeadChargedHadronPt = 0;
  tauneutralIsoPtSumWeight = 0;
  taufootprintCorrection = 0;
  tauphotonPtSumOutsideSignalCone = 0;
  taudz = 0;
  taudxy = 0;
  taupfTausDiscriminationByDecayModeFinding = 0;
  taupfTausDiscriminationByDecayModeFindingNewDMs = 0;
  tauByMVA6VLooseElectronRejection = 0;
  tauByMVA6LooseElectronRejection = 0;
  tauByMVA6MediumElectronRejection = 0;
  tauByMVA6TightElectronRejection = 0;
  tauByMVA6VTightElectronRejection = 0;
  tauByLooseMuonRejection3 = 0;
  tauByTightMuonRejection3 = 0;
  tauByLooseCombinedIsolationDeltaBetaCorr3Hits = 0;
  tauByMediumCombinedIsolationDeltaBetaCorr3Hits = 0;
  tauByTightCombinedIsolationDeltaBetaCorr3Hits = 0;
  tauCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
  tauByIsolationMVArun2v1DBnewDMwLTraw = 0;
  tauByIsolationMVArun2v1DBoldDMwLTraw = 0;
  tauByIsolationMVArun2v1PWnewDMwLTraw = 0;
  tauByIsolationMVArun2v1PWoldDMwLTraw = 0;
  tauByVTightIsolationMVArun2v1DBnewDMwLT = 0;
  tauByVTightIsolationMVArun2v1DBoldDMwLT = 0;
  tauByVTightIsolationMVArun2v1PWnewDMwLT = 0;
  tauByVTightIsolationMVArun2v1PWoldDMwLT = 0;
  tauByTightIsolationMVArun2v1DBnewDMwLT = 0;
  tauByTightIsolationMVArun2v1DBoldDMwLT = 0;
  tauByTightIsolationMVArun2v1PWnewDMwLT = 0;
  tauByTightIsolationMVArun2v1PWoldDMwLT = 0;
  tauByMediumIsolationMVArun2v1DBnewDMwLT = 0;
  tauByMediumIsolationMVArun2v1DBoldDMwLT = 0;
  tauByMediumIsolationMVArun2v1PWnewDMwLT = 0;
  tauByMediumIsolationMVArun2v1PWoldDMwLT = 0;
  tauByLooseIsolationMVArun2v1DBnewDMwLT = 0;
  tauByLooseIsolationMVArun2v1DBoldDMwLT = 0;
  tauByLooseIsolationMVArun2v1PWnewDMwLT = 0;
  tauByLooseIsolationMVArun2v1PWoldDMwLT = 0;
  tauByVLooseIsolationMVArun2v1DBnewDMwLT = 0;
  tauByVLooseIsolationMVArun2v1DBoldDMwLT = 0;
  tauByVLooseIsolationMVArun2v1PWnewDMwLT = 0;
  tauByVLooseIsolationMVArun2v1PWoldDMwLT = 0;
  taubyIsolationMVArun2017v2DBoldDMwLTraw2017 = 0;
  taubyVVLooseIsolationMVArun2017v2DBoldDMwLT2017 = 0;
  taubyVLooseIsolationMVArun2017v2DBoldDMwLT2017 = 0;
  taubyLooseIsolationMVArun2017v2DBoldDMwLT2017 = 0;
  taubyMediumIsolationMVArun2017v2DBoldDMwLT2017 = 0;
  taubyTightIsolationMVArun2017v2DBoldDMwLT2017 = 0;
  taubyVTightIsolationMVArun2017v2DBoldDMwLT2017 = 0;
  taubyVVTightIsolationMVArun2017v2DBoldDMwLT2017 = 0;
  pdf = 0;
  pdfSystWeight = 0;
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

  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
  fChain->SetBranchAddress("isData", &isData, &b_isData);
  fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
  fChain->SetBranchAddress("vtxX", &vtxX, &b_vtxX);
  fChain->SetBranchAddress("vtxY", &vtxY, &b_vtxY);
  fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
  fChain->SetBranchAddress("vtxNtrks", &vtxNtrks, &b_vtxNtrks);
  fChain->SetBranchAddress("vtx_isFake", &vtx_isFake, &b_vtx_isFake);
  fChain->SetBranchAddress("vtx_ndof", &vtx_ndof, &b_vtx_ndof);
  fChain->SetBranchAddress("vtx_rho", &vtx_rho, &b_vtx_rho);
  fChain->SetBranchAddress("isGoodVtx", &isGoodVtx, &b_isGoodVtx);
  fChain->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
  fChain->SetBranchAddress("rho", &rho, &b_rho);
  fChain->SetBranchAddress("rhoCentral", &rhoCentral, &b_rhoCentral);
  fChain->SetBranchAddress("HLTEleMuX", &HLTEleMuX, &b_HLTEleMuX);
  fChain->SetBranchAddress("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled, &b_HLTEleMuXIsPrescaled);
  fChain->SetBranchAddress("HLTEleMuXRejectedByPS", &HLTEleMuXRejectedByPS, &b_HLTEleMuXRejectedByPS);
  fChain->SetBranchAddress("HLTPho", &HLTPho, &b_HLTPho);
  fChain->SetBranchAddress("HLTPhoIsPrescaled", &HLTPhoIsPrescaled, &b_HLTPhoIsPrescaled);
  fChain->SetBranchAddress("HLTPhoRejectedByPS", &HLTPhoRejectedByPS, &b_HLTPhoRejectedByPS);
  fChain->SetBranchAddress("HLTTau", &HLTTau, &b_HLTTau);
  fChain->SetBranchAddress("HLTTauIsPrescaled", &HLTTauIsPrescaled, &b_HLTTauIsPrescaled);
  fChain->SetBranchAddress("HLTTauRejectedByPS", &HLTTauRejectedByPS, &b_HLTTauRejectedByPS);
  fChain->SetBranchAddress("HLTMet", &HLTMet, &b_HLTMet);
  fChain->SetBranchAddress("HLTMetIsPrescaled", &HLTMetIsPrescaled, &b_HLTMetIsPrescaled);
  fChain->SetBranchAddress("HLTMetRejectedByPS", &HLTMetRejectedByPS, &b_HLTMetRejectedByPS);
  fChain->SetBranchAddress("HLTJet", &HLTJet, &b_HLTJet);
  fChain->SetBranchAddress("HLTJetIsPrescaled", &HLTJetIsPrescaled, &b_HLTJetIsPrescaled);
  fChain->SetBranchAddress("HLTJetRejectedByPS", &HLTJetRejectedByPS, &b_HLTJetRejectedByPS);
  fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
  fChain->SetBranchAddress("phoE", &phoE, &b_phoE);
  fChain->SetBranchAddress("phoPx", &phoPx, &b_phoPx);
  fChain->SetBranchAddress("phoPy", &phoPy, &b_phoPy);
  fChain->SetBranchAddress("phoPz", &phoPz, &b_phoPz);
  fChain->SetBranchAddress("phoEt", &phoEt, &b_phoEt);
  fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
  fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
  fChain->SetBranchAddress("phoUnCalibE", &phoUnCalibE, &b_phoUnCalibE);
  fChain->SetBranchAddress("phoUnCalibESigma", &phoUnCalibESigma, &b_phoUnCalibESigma);
  fChain->SetBranchAddress("phoCalibE", &phoCalibE, &b_phoCalibE);
  fChain->SetBranchAddress("phoCalibESigma", &phoCalibESigma, &b_phoCalibESigma);
  fChain->SetBranchAddress("phoCalibEt", &phoCalibEt, &b_phoCalibEt);
  fChain->SetBranchAddress("phoEnergyScale", &phoEnergyScale, &b_phoEnergyScale);
  fChain->SetBranchAddress("phoEnergySigma", &phoEnergySigma, &b_phoEnergySigma);
  fChain->SetBranchAddress("phoSCE", &phoSCE, &b_phoSCE);
  fChain->SetBranchAddress("phoSCRawE", &phoSCRawE, &b_phoSCRawE);
  fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
  fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
  fChain->SetBranchAddress("phoSCEtaWidth", &phoSCEtaWidth, &b_phoSCEtaWidth);
  fChain->SetBranchAddress("phoSCPhiWidth", &phoSCPhiWidth, &b_phoSCPhiWidth);
  fChain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed, &b_phohasPixelSeed);
  fChain->SetBranchAddress("phoEleVeto", &phoEleVeto, &b_phoEleVeto);
  fChain->SetBranchAddress("phoR9", &phoR9, &b_phoR9);
  fChain->SetBranchAddress("phoR9Full5x5", &phoR9Full5x5, &b_phoR9Full5x5);
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
  fChain->SetBranchAddress("phoMVAIDbit", &phoMVAIDbit, &b_phoMVAIDbit);
  fChain->SetBranchAddress("phoSeedTime", &phoSeedTime, &b_phoSeedTime);
  fChain->SetBranchAddress("phoSeedEnergy", &phoSeedEnergy, &b_phoSeedEnergy);
  fChain->SetBranchAddress("phoScale_up", &phoScale_up, &b_phoScale_up);
  fChain->SetBranchAddress("phoScale_dn", &phoScale_dn, &b_phoScale_dn);
  fChain->SetBranchAddress("phoScale_stat_up", &phoScale_stat_up, &b_phoScale_stat_up);
  fChain->SetBranchAddress("phoScale_stat_dn", &phoScale_stat_dn, &b_phoScale_stat_dn);
  fChain->SetBranchAddress("phoScale_syst_up", &phoScale_syst_up, &b_phoScale_syst_up);
  fChain->SetBranchAddress("phoScale_syst_dn", &phoScale_syst_dn, &b_phoScale_syst_dn);
  fChain->SetBranchAddress("phoScale_gain_up", &phoScale_gain_up, &b_phoScale_gain_up);
  fChain->SetBranchAddress("phoScale_gain_dn", &phoScale_gain_dn, &b_phoScale_gain_dn);
  fChain->SetBranchAddress("phoResol_up", &phoResol_up, &b_phoResol_up);
  fChain->SetBranchAddress("phoResol_dn", &phoResol_dn, &b_phoResol_dn);
  fChain->SetBranchAddress("phoResol_rho_up", &phoResol_rho_up, &b_phoResol_rho_up);
  fChain->SetBranchAddress("phoResol_rho_dn", &phoResol_rho_dn, &b_phoResol_rho_dn);
  fChain->SetBranchAddress("phoResol_phi_up", &phoResol_phi_up, &b_phoResol_phi_up);
  fChain->SetBranchAddress("phoResol_phi_dn", &phoResol_phi_dn, &b_phoResol_phi_dn);
  fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
  fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
  fChain->SetBranchAddress("jetPx", &jetPx, &b_jetPx);
  fChain->SetBranchAddress("jetPy", &jetPy, &b_jetPy);
  fChain->SetBranchAddress("jetPz", &jetPz, &b_jetPz);
  fChain->SetBranchAddress("jetEn", &jetEn, &b_jetEn);
  fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
  fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
  fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
  fChain->SetBranchAddress("jetRawEn", &jetRawEn, &b_jetRawEn);
  fChain->SetBranchAddress("jetMt", &jetMt, &b_jetMt);
  fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
  fChain->SetBranchAddress("jetMass", &jetMass, &b_jetMass);
  fChain->SetBranchAddress("jetMaxDistance", &jetMaxDistance, &b_jetMaxDistance);
  fChain->SetBranchAddress("jetPhiPhiMoment", &jetPhiPhiMoment, &b_jetPhiPhiMoment);
  fChain->SetBranchAddress("jetConstituentEtaPhiSpread", &jetConstituentEtaPhiSpread, &b_jetConstituentEtaPhiSpread);
  fChain->SetBranchAddress("jetConstituentPtDistribution", &jetConstituentPtDistribution, &b_jetConstituentPtDistribution);
  fChain->SetBranchAddress("jetPileup", &jetPileup, &b_jetPileup);
  fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
  fChain->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
  fChain->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
  fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
  fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
  fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
  fChain->SetBranchAddress("jetCEF", &jetCEF, &b_jetCEF);
  fChain->SetBranchAddress("jetNEF", &jetNEF, &b_jetNEF);
  fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
  fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
  fChain->SetBranchAddress("jetPhotonEnF", &jetPhotonEnF, &b_jetPhotonEnF);
  fChain->SetBranchAddress("jetElectronEnF", &jetElectronEnF, &b_jetElectronEnF);
  fChain->SetBranchAddress("jetMuonEnF", &jetMuonEnF, &b_jetMuonEnF);
  fChain->SetBranchAddress("jetChargedMuonEnF", &jetChargedMuonEnF, &b_jetChargedMuonEnF);
  fChain->SetBranchAddress("jetHFHAE", &jetHFHAE, &b_jetHFHAE);
  fChain->SetBranchAddress("jetHFEME", &jetHFEME, &b_jetHFEME);
  fChain->SetBranchAddress("jetNConst", &jetNConst, &b_jetNConst);
  fChain->SetBranchAddress("jetNConstituents", &jetNConstituents, &b_jetNConstituents);
  fChain->SetBranchAddress("jetNCharged", &jetNCharged, &b_jetNCharged);
  fChain->SetBranchAddress("jetNNeutral", &jetNNeutral, &b_jetNNeutral);
  fChain->SetBranchAddress("jetNChargedHad", &jetNChargedHad, &b_jetNChargedHad);
  fChain->SetBranchAddress("jetNNeutralHad", &jetNNeutralHad, &b_jetNNeutralHad);
  fChain->SetBranchAddress("jetNPhoton", &jetNPhoton, &b_jetNPhoton);
  fChain->SetBranchAddress("jetNElectron", &jetNElectron, &b_jetNElectron);
  fChain->SetBranchAddress("jetNMuon", &jetNMuon, &b_jetNMuon);
  fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
  fChain->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b, &b_jetDeepCSVTags_b);
  fChain->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb, &b_jetDeepCSVTags_bb);
  fChain->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c, &b_jetDeepCSVTags_c);
  fChain->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg, &b_jetDeepCSVTags_udsg);
  fChain->SetBranchAddress("jetLeadTrackPt", &jetLeadTrackPt, &b_jetLeadTrackPt);
  fChain->SetBranchAddress("jetLeadTrackEta", &jetLeadTrackEta, &b_jetLeadTrackEta);
  fChain->SetBranchAddress("jetLeadTrackPhi", &jetLeadTrackPhi, &b_jetLeadTrackPhi);
  fChain->SetBranchAddress("jetLepTrackPID", &jetLepTrackPID, &b_jetLepTrackPID);
  fChain->SetBranchAddress("jetLepTrackPt", &jetLepTrackPt, &b_jetLepTrackPt);
  fChain->SetBranchAddress("jetLepTrackEta", &jetLepTrackEta, &b_jetLepTrackEta);
  fChain->SetBranchAddress("jetLepTrackPhi", &jetLepTrackPhi, &b_jetLepTrackPhi);
  fChain->SetBranchAddress("jetetaWidth", &jetetaWidth, &b_jetetaWidth);
  fChain->SetBranchAddress("jetphiWidth", &jetphiWidth, &b_jetphiWidth);
  fChain->SetBranchAddress("jetnPhotons", &jetnPhotons, &b_jetnPhotons);
  fChain->SetBranchAddress("jetnCHPions", &jetnCHPions, &b_jetnCHPions);
  fChain->SetBranchAddress("jetnMisc", &jetnMisc, &b_jetnMisc);
  fChain->SetBranchAddress("jetMiscPdgId", &jetMiscPdgId, &b_jetMiscPdgId);
  fChain->SetBranchAddress("jetConstPt", &jetConstPt, &b_jetConstPt);
  fChain->SetBranchAddress("jetConstEt", &jetConstEt, &b_jetConstEt);
  fChain->SetBranchAddress("jetConstEta", &jetConstEta, &b_jetConstEta);
  fChain->SetBranchAddress("jetConstPhi", &jetConstPhi, &b_jetConstPhi);
  fChain->SetBranchAddress("jetConstPdgId", &jetConstPdgId, &b_jetConstPdgId);
  
  fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
  fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
  fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
  fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
  fChain->SetBranchAddress("eleR9", &eleR9, &b_eleR9);
  fChain->SetBranchAddress("eleR9Full5x5", &eleR9Full5x5, &b_eleR9Full5x5);
  fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
  fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
  fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
  fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
  fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
  fChain->SetBranchAddress("eleSIP", &eleSIP, &b_eleSIP);
  fChain->SetBranchAddress("eleUnCalibE", &eleUnCalibE, &b_eleUnCalibE);
  fChain->SetBranchAddress("eleUnCalibESigma", &eleUnCalibESigma, &b_eleUnCalibESigma);
  fChain->SetBranchAddress("eleCalibEecalonly", &eleCalibEecalonly, &b_eleCalibEecalonly);
  fChain->SetBranchAddress("eleCalibE", &eleCalibE, &b_eleCalibE);
  fChain->SetBranchAddress("eleCalibESigma", &eleCalibESigma, &b_eleCalibESigma);
  fChain->SetBranchAddress("eleCalibEt", &eleCalibEt, &b_eleCalibEt);
  fChain->SetBranchAddress("eleCalibEtSigma", &eleCalibEtSigma, &b_eleCalibEtSigma);
  fChain->SetBranchAddress("eleEnergyScale", &eleEnergyScale, &b_eleEnergyScale);
  fChain->SetBranchAddress("eleEnergySigma", &eleEnergySigma, &b_eleEnergySigma);
  fChain->SetBranchAddress("eleSCRawEn", &eleSCRawEn, &b_eleSCRawEn);
  fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
  fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
  fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
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
  fChain->SetBranchAddress("eledEtaseedAtVtx", &eledEtaseedAtVtx, &b_eledEtaseedAtVtx);
  fChain->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5, &b_eleSigmaIEtaIEtaFull5x5);
  fChain->SetBranchAddress("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5, &b_eleSigmaIPhiIPhiFull5x5);
  fChain->SetBranchAddress("eleConvVeto", &eleConvVeto, &b_eleConvVeto);
  fChain->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
  fChain->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
  fChain->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
  fChain->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
  fChain->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
  fChain->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso, &b_elePFClusEcalIso);
  fChain->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso, &b_elePFClusHcalIso);
  fChain->SetBranchAddress("eleHEEPID", &eleHEEPID, &b_eleHEEPID);
  fChain->SetBranchAddress("eleMVAIsoID", &eleMVAIsoID, &b_eleMVAIsoID);
  fChain->SetBranchAddress("eleMVAnoIsoID", &eleMVAnoIsoID, &b_eleMVAnoIsoID);
  fChain->SetBranchAddress("eleIDbit", &eleIDbit, &b_eleIDbit);
  fChain->SetBranchAddress("eleMVAIsoIDbit", &eleMVAIsoIDbit, &b_eleMVAIsoIDbit);
  fChain->SetBranchAddress("eleMVAnoIsoIDbit", &eleMVAnoIsoIDbit, &b_eleMVAnoIsoIDbit);
  fChain->SetBranchAddress("eleTrkdxy", &eleTrkdxy, &b_eleTrkdxy);
  fChain->SetBranchAddress("eleKFHits", &eleKFHits, &b_eleKFHits);
  fChain->SetBranchAddress("eleKFChi2", &eleKFChi2, &b_eleKFChi2);
  fChain->SetBranchAddress("eleGSFChi2", &eleGSFChi2, &b_eleGSFChi2);
  fChain->SetBranchAddress("eleScale_up", &eleScale_up, &b_eleScale_up);
  fChain->SetBranchAddress("eleScale_dn", &eleScale_dn, &b_eleScale_dn);
  fChain->SetBranchAddress("eleScale_stat_up", &eleScale_stat_up, &b_eleScale_stat_up);
  fChain->SetBranchAddress("eleScale_stat_dn", &eleScale_stat_dn, &b_eleScale_stat_dn);
  fChain->SetBranchAddress("eleScale_syst_up", &eleScale_syst_up, &b_eleScale_syst_up);
  fChain->SetBranchAddress("eleScale_syst_dn", &eleScale_syst_dn, &b_eleScale_syst_dn);
  fChain->SetBranchAddress("eleScale_gain_up", &eleScale_gain_up, &b_eleScale_gain_up);
  fChain->SetBranchAddress("eleScale_gain_dn", &eleScale_gain_dn, &b_eleScale_gain_dn);
  fChain->SetBranchAddress("eleResol_up", &eleResol_up, &b_eleResol_up);
  fChain->SetBranchAddress("eleResol_dn", &eleResol_dn, &b_eleResol_dn);
  fChain->SetBranchAddress("eleResol_rho_up", &eleResol_rho_up, &b_eleResol_rho_up);
  fChain->SetBranchAddress("eleResol_rho_dn", &eleResol_rho_dn, &b_eleResol_rho_dn);
  fChain->SetBranchAddress("eleResol_phi_up", &eleResol_phi_up, &b_eleResol_phi_up);
  fChain->SetBranchAddress("eleResol_phi_dn", &eleResol_phi_dn, &b_eleResol_phi_dn);
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
  fChain->SetBranchAddress("muInnervalidFraction", &muInnervalidFraction, &b_muInnervalidFraction);
  fChain->SetBranchAddress("musegmentCompatibility", &musegmentCompatibility, &b_musegmentCompatibility);
  fChain->SetBranchAddress("muchi2LocalPosition", &muchi2LocalPosition, &b_muchi2LocalPosition);
  fChain->SetBranchAddress("mutrkKink", &mutrkKink, &b_mutrkKink);
  fChain->SetBranchAddress("muBestTrkPtError", &muBestTrkPtError, &b_muBestTrkPtError);
  fChain->SetBranchAddress("muBestTrkPt", &muBestTrkPt, &b_muBestTrkPt);
  fChain->SetBranchAddress("muBestTrkType", &muBestTrkType, &b_muBestTrkType);
  fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
  fChain->SetBranchAddress("tauEta", &tauEta, &b_tauEta);
  fChain->SetBranchAddress("tauPhi", &tauPhi, &b_tauPhi);
  fChain->SetBranchAddress("tauPt", &tauPt, &b_tauPt);
  fChain->SetBranchAddress("tauEt", &tauEt, &b_tauEt);
  fChain->SetBranchAddress("tauCharge", &tauCharge, &b_tauCharge);
  fChain->SetBranchAddress("tauDecayMode", &tauDecayMode, &b_tauDecayMode);
  fChain->SetBranchAddress("tauP", &tauP, &b_tauP);
  fChain->SetBranchAddress("tauPx", &tauPx, &b_tauPx);
  fChain->SetBranchAddress("tauPy", &tauPy, &b_tauPy);
  fChain->SetBranchAddress("tauPz", &tauPz, &b_tauPz);
  fChain->SetBranchAddress("tauVz", &tauVz, &b_tauVz);
  fChain->SetBranchAddress("tauEnergy", &tauEnergy, &b_tauEnergy);
  fChain->SetBranchAddress("tauMass", &tauMass, &b_tauMass);
  fChain->SetBranchAddress("tauDxy", &tauDxy, &b_tauDxy);
  fChain->SetBranchAddress("tauZImpact", &tauZImpact, &b_tauZImpact);
  fChain->SetBranchAddress("tauChargedIsoPtSum", &tauChargedIsoPtSum, &b_tauChargedIsoPtSum);
  fChain->SetBranchAddress("tauNeutralIsoPtSum", &tauNeutralIsoPtSum, &b_tauNeutralIsoPtSum);
  fChain->SetBranchAddress("tauPuCorrPtSum", &tauPuCorrPtSum, &b_tauPuCorrPtSum);
  fChain->SetBranchAddress("tauNumSignalPFChargedHadrCands", &tauNumSignalPFChargedHadrCands, &b_tauNumSignalPFChargedHadrCands);
  fChain->SetBranchAddress("tauNumSignalPFNeutrHadrCands", &tauNumSignalPFNeutrHadrCands, &b_tauNumSignalPFNeutrHadrCands);
  fChain->SetBranchAddress("tauNumSignalPFGammaCands", &tauNumSignalPFGammaCands, &b_tauNumSignalPFGammaCands);
  fChain->SetBranchAddress("tauNumSignalPFCands", &tauNumSignalPFCands, &b_tauNumSignalPFCands);
  fChain->SetBranchAddress("tauNumIsolationPFChargedHadrCands", &tauNumIsolationPFChargedHadrCands, &b_tauNumIsolationPFChargedHadrCands);
  fChain->SetBranchAddress("tauNumIsolationPFNeutrHadrCands", &tauNumIsolationPFNeutrHadrCands, &b_tauNumIsolationPFNeutrHadrCands);
  fChain->SetBranchAddress("tauNumIsolationPFGammaCands", &tauNumIsolationPFGammaCands, &b_tauNumIsolationPFGammaCands);
  fChain->SetBranchAddress("tauNumIsolationPFCands", &tauNumIsolationPFCands, &b_tauNumIsolationPFCands);
  fChain->SetBranchAddress("tauLeadChargedHadronExists", &tauLeadChargedHadronExists, &b_tauLeadChargedHadronExists);
  fChain->SetBranchAddress("tauLeadChargedHadronEta", &tauLeadChargedHadronEta, &b_tauLeadChargedHadronEta);
  fChain->SetBranchAddress("tauLeadChargedHadronPhi", &tauLeadChargedHadronPhi, &b_tauLeadChargedHadronPhi);
  fChain->SetBranchAddress("tauLeadChargedHadronPt", &tauLeadChargedHadronPt, &b_tauLeadChargedHadronPt);
  fChain->SetBranchAddress("tauneutralIsoPtSumWeight", &tauneutralIsoPtSumWeight, &b_tauneutralIsoPtSumWeight);
  fChain->SetBranchAddress("taufootprintCorrection", &taufootprintCorrection, &b_taufootprintCorrection);
  fChain->SetBranchAddress("tauphotonPtSumOutsideSignalCone", &tauphotonPtSumOutsideSignalCone, &b_tauphotonPtSumOutsideSignalCone);
  fChain->SetBranchAddress("taudz", &taudz, &b_taudz);
  fChain->SetBranchAddress("taudxy", &taudxy, &b_taudxy);
  fChain->SetBranchAddress("taupfTausDiscriminationByDecayModeFinding", &taupfTausDiscriminationByDecayModeFinding, &b_taupfTausDiscriminationByDecayModeFinding);
  fChain->SetBranchAddress("taupfTausDiscriminationByDecayModeFindingNewDMs", &taupfTausDiscriminationByDecayModeFindingNewDMs, &b_taupfTausDiscriminationByDecayModeFindingNewDMs);
  fChain->SetBranchAddress("tauByMVA6VLooseElectronRejection", &tauByMVA6VLooseElectronRejection, &b_tauByMVA6VLooseElectronRejection);
  fChain->SetBranchAddress("tauByMVA6LooseElectronRejection", &tauByMVA6LooseElectronRejection, &b_tauByMVA6LooseElectronRejection);
  fChain->SetBranchAddress("tauByMVA6MediumElectronRejection", &tauByMVA6MediumElectronRejection, &b_tauByMVA6MediumElectronRejection);
  fChain->SetBranchAddress("tauByMVA6TightElectronRejection", &tauByMVA6TightElectronRejection, &b_tauByMVA6TightElectronRejection);
  fChain->SetBranchAddress("tauByMVA6VTightElectronRejection", &tauByMVA6VTightElectronRejection, &b_tauByMVA6VTightElectronRejection);
  fChain->SetBranchAddress("tauByLooseMuonRejection3", &tauByLooseMuonRejection3, &b_tauByLooseMuonRejection3);
  fChain->SetBranchAddress("tauByTightMuonRejection3", &tauByTightMuonRejection3, &b_tauByTightMuonRejection3);
  fChain->SetBranchAddress("tauByLooseCombinedIsolationDeltaBetaCorr3Hits", &tauByLooseCombinedIsolationDeltaBetaCorr3Hits, &b_tauByLooseCombinedIsolationDeltaBetaCorr3Hits);
  fChain->SetBranchAddress("tauByMediumCombinedIsolationDeltaBetaCorr3Hits", &tauByMediumCombinedIsolationDeltaBetaCorr3Hits, &b_tauByMediumCombinedIsolationDeltaBetaCorr3Hits);
  fChain->SetBranchAddress("tauByTightCombinedIsolationDeltaBetaCorr3Hits", &tauByTightCombinedIsolationDeltaBetaCorr3Hits, &b_tauByTightCombinedIsolationDeltaBetaCorr3Hits);
  fChain->SetBranchAddress("tauCombinedIsolationDeltaBetaCorrRaw3Hits", &tauCombinedIsolationDeltaBetaCorrRaw3Hits, &b_tauCombinedIsolationDeltaBetaCorrRaw3Hits);
  fChain->SetBranchAddress("tauByIsolationMVArun2v1DBnewDMwLTraw", &tauByIsolationMVArun2v1DBnewDMwLTraw, &b_tauByIsolationMVArun2v1DBnewDMwLTraw);
  fChain->SetBranchAddress("tauByIsolationMVArun2v1DBoldDMwLTraw", &tauByIsolationMVArun2v1DBoldDMwLTraw, &b_tauByIsolationMVArun2v1DBoldDMwLTraw);
  fChain->SetBranchAddress("tauByIsolationMVArun2v1PWnewDMwLTraw", &tauByIsolationMVArun2v1PWnewDMwLTraw, &b_tauByIsolationMVArun2v1PWnewDMwLTraw);
  fChain->SetBranchAddress("tauByIsolationMVArun2v1PWoldDMwLTraw", &tauByIsolationMVArun2v1PWoldDMwLTraw, &b_tauByIsolationMVArun2v1PWoldDMwLTraw);
  fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1DBnewDMwLT", &tauByVTightIsolationMVArun2v1DBnewDMwLT, &b_tauByVTightIsolationMVArun2v1DBnewDMwLT);
  fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1DBoldDMwLT", &tauByVTightIsolationMVArun2v1DBoldDMwLT, &b_tauByVTightIsolationMVArun2v1DBoldDMwLT);
  fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1PWnewDMwLT", &tauByVTightIsolationMVArun2v1PWnewDMwLT, &b_tauByVTightIsolationMVArun2v1PWnewDMwLT);
  fChain->SetBranchAddress("tauByVTightIsolationMVArun2v1PWoldDMwLT", &tauByVTightIsolationMVArun2v1PWoldDMwLT, &b_tauByVTightIsolationMVArun2v1PWoldDMwLT);
  fChain->SetBranchAddress("tauByTightIsolationMVArun2v1DBnewDMwLT", &tauByTightIsolationMVArun2v1DBnewDMwLT, &b_tauByTightIsolationMVArun2v1DBnewDMwLT);
  fChain->SetBranchAddress("tauByTightIsolationMVArun2v1DBoldDMwLT", &tauByTightIsolationMVArun2v1DBoldDMwLT, &b_tauByTightIsolationMVArun2v1DBoldDMwLT);
  fChain->SetBranchAddress("tauByTightIsolationMVArun2v1PWnewDMwLT", &tauByTightIsolationMVArun2v1PWnewDMwLT, &b_tauByTightIsolationMVArun2v1PWnewDMwLT);
  fChain->SetBranchAddress("tauByTightIsolationMVArun2v1PWoldDMwLT", &tauByTightIsolationMVArun2v1PWoldDMwLT, &b_tauByTightIsolationMVArun2v1PWoldDMwLT);
  fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1DBnewDMwLT", &tauByMediumIsolationMVArun2v1DBnewDMwLT, &b_tauByMediumIsolationMVArun2v1DBnewDMwLT);
  fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1DBoldDMwLT", &tauByMediumIsolationMVArun2v1DBoldDMwLT, &b_tauByMediumIsolationMVArun2v1DBoldDMwLT);
  fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1PWnewDMwLT", &tauByMediumIsolationMVArun2v1PWnewDMwLT, &b_tauByMediumIsolationMVArun2v1PWnewDMwLT);
  fChain->SetBranchAddress("tauByMediumIsolationMVArun2v1PWoldDMwLT", &tauByMediumIsolationMVArun2v1PWoldDMwLT, &b_tauByMediumIsolationMVArun2v1PWoldDMwLT);
  fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1DBnewDMwLT", &tauByLooseIsolationMVArun2v1DBnewDMwLT, &b_tauByLooseIsolationMVArun2v1DBnewDMwLT);
  fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1DBoldDMwLT", &tauByLooseIsolationMVArun2v1DBoldDMwLT, &b_tauByLooseIsolationMVArun2v1DBoldDMwLT);
  fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1PWnewDMwLT", &tauByLooseIsolationMVArun2v1PWnewDMwLT, &b_tauByLooseIsolationMVArun2v1PWnewDMwLT);
  fChain->SetBranchAddress("tauByLooseIsolationMVArun2v1PWoldDMwLT", &tauByLooseIsolationMVArun2v1PWoldDMwLT, &b_tauByLooseIsolationMVArun2v1PWoldDMwLT);
  fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1DBnewDMwLT", &tauByVLooseIsolationMVArun2v1DBnewDMwLT, &b_tauByVLooseIsolationMVArun2v1DBnewDMwLT);
  fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1DBoldDMwLT", &tauByVLooseIsolationMVArun2v1DBoldDMwLT, &b_tauByVLooseIsolationMVArun2v1DBoldDMwLT);
  fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1PWnewDMwLT", &tauByVLooseIsolationMVArun2v1PWnewDMwLT, &b_tauByVLooseIsolationMVArun2v1PWnewDMwLT);
  fChain->SetBranchAddress("tauByVLooseIsolationMVArun2v1PWoldDMwLT", &tauByVLooseIsolationMVArun2v1PWoldDMwLT, &b_tauByVLooseIsolationMVArun2v1PWoldDMwLT);
  fChain->SetBranchAddress("taubyIsolationMVArun2017v2DBoldDMwLTraw2017", &taubyIsolationMVArun2017v2DBoldDMwLTraw2017, &b_taubyIsolationMVArun2017v2DBoldDMwLTraw2017);
  fChain->SetBranchAddress("taubyVVLooseIsolationMVArun2017v2DBoldDMwLT2017", &taubyVVLooseIsolationMVArun2017v2DBoldDMwLT2017, &b_taubyVVLooseIsolationMVArun2017v2DBoldDMwLT2017);
  fChain->SetBranchAddress("taubyVLooseIsolationMVArun2017v2DBoldDMwLT2017", &taubyVLooseIsolationMVArun2017v2DBoldDMwLT2017, &b_taubyVLooseIsolationMVArun2017v2DBoldDMwLT2017);
  fChain->SetBranchAddress("taubyLooseIsolationMVArun2017v2DBoldDMwLT2017", &taubyLooseIsolationMVArun2017v2DBoldDMwLT2017, &b_taubyLooseIsolationMVArun2017v2DBoldDMwLT2017);
  fChain->SetBranchAddress("taubyMediumIsolationMVArun2017v2DBoldDMwLT2017", &taubyMediumIsolationMVArun2017v2DBoldDMwLT2017, &b_taubyMediumIsolationMVArun2017v2DBoldDMwLT2017);
  fChain->SetBranchAddress("taubyTightIsolationMVArun2017v2DBoldDMwLT2017", &taubyTightIsolationMVArun2017v2DBoldDMwLT2017, &b_taubyTightIsolationMVArun2017v2DBoldDMwLT2017);
  fChain->SetBranchAddress("taubyVTightIsolationMVArun2017v2DBoldDMwLT2017", &taubyVTightIsolationMVArun2017v2DBoldDMwLT2017, &b_taubyVTightIsolationMVArun2017v2DBoldDMwLT2017);
  fChain->SetBranchAddress("taubyVVTightIsolationMVArun2017v2DBoldDMwLT2017", &taubyVVTightIsolationMVArun2017v2DBoldDMwLT2017, &b_taubyVVTightIsolationMVArun2017v2DBoldDMwLT2017);
  fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
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

  if (!sample.isData) {
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
    
    fChain->SetBranchAddress("genMET", &genMET, &b_genMET);
    fChain->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
    
    fChain->SetBranchAddress("pdf", &pdf, &b_pdf);
    fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
    fChain->SetBranchAddress("processID", &processID, &b_processID);
    fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
    fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
    fChain->SetBranchAddress("pdfWeight", &pdfWeight, &b_pdfWeight);
    fChain->SetBranchAddress("pdfSystWeight", &pdfSystWeight, &b_pdfSystWeight);
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
    fChain->SetBranchAddress("mcIndex", &mcIndex, &b_mcIndex);
  }
  Notify();
}

Bool_t ZprimeJetsClass::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ZprimeJetsClass::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t ZprimeJetsClass::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef ZprimeJetsClass_cxx
