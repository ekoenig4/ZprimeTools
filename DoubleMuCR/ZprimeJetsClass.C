#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char* argv[]) { 
  if (argc == 1) {
    printf("Running Test\n");
    argv[1] = "/hdfs/store/user/ekoenig/MonoZprimeJet/NTuples/2018/MC2018_Autumn18_June2019/DYJets/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/0000/";
    argv[2] = "test.root";
    argv[3] = "5000";
    argv[4] = "100";
    argv[5] = "1-1";
  }
  Long64_t maxEvents = atof(argv[3]);
  if (maxEvents < -1LL)
    {
      cout<<"Please enter a valid value for maxEvents (parameter 3)."<<endl;
      return 1;
    }
  int reportEvery = atof(argv[4]);
  if (reportEvery < 1)
    {
      cout<<"Please enter a valid value for reportEvery (parameter 4)."<<endl;
      return 1;
    }
  ZprimeJetsClass t(argv[1],argv[2],argv[5]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

double ZprimeJetsClass::getSF(int lepindex_leading,int lepindex_subleading) {
  double leadingMuPt = muPt->at(lepindex_leading);
  double leadingMuEta = fabs(muEta->at(lepindex_leading));
  if (leadingMuPt >= 120) leadingMuPt = 119.9;
  else if (leadingMuPt <= 15) leadingMuPt = 15.1;
  if (leadingMuEta >= 2.4) leadingMuEta = 2.39;
  
  
  double subleadingMuPt = muPt->at(lepindex_subleading);
  double subleadingMuEta = fabs(muEta->at(lepindex_subleading));
  if (subleadingMuPt >= 120) subleadingMuPt = 119.9;
  else if (subleadingMuPt <= 15) subleadingMuPt = 15.1;
  if (subleadingMuEta >= 2.4) subleadingMuEta = 2.39;

  double tightMuISO_PtBin = h_tightMuSF_ISO->GetXaxis()->FindBin(leadingMuPt); double tightMuISO_EtaBin = h_tightMuSF_ISO->GetYaxis()->FindBin(leadingMuEta);
  double tightMuID_PtBin  = h_tightMuSF_ID->GetXaxis()->FindBin(leadingMuPt);  double tightMuID_EtaBin  = h_tightMuSF_ID->GetYaxis()->FindBin(leadingMuEta);
  double looseMuISO_PtBin = h_looseMuSF_ISO->GetXaxis()->FindBin(subleadingMuPt); double looseMuISO_EtaBin = h_looseMuSF_ISO->GetYaxis()->FindBin(subleadingMuEta);
  double looseMuID_PtBin  = h_looseMuSF_ID->GetXaxis()->FindBin(subleadingMuPt);  double looseMuID_EtaBin = h_looseMuSF_ID->GetYaxis()->FindBin(subleadingMuEta);
  
  double tightMuISO_SF_corr = h_tightMuSF_ISO->GetBinContent(tightMuISO_PtBin,tightMuISO_EtaBin);
  double tightMuID_SF_corr = h_tightMuSF_ID->GetBinContent(tightMuID_PtBin,tightMuID_EtaBin);
  double looseMuISO_SF_corr = h_looseMuSF_ISO->GetBinContent(looseMuISO_PtBin,looseMuISO_EtaBin);
  double looseMuID_SF_corr = h_looseMuSF_ID->GetBinContent(looseMuISO_PtBin,looseMuISO_EtaBin);
  
  h_tightMuISO->Fill(tightMuISO_SF_corr);
  h_tightMuID->Fill(tightMuID_SF_corr);
  h_looseMuISO->Fill(looseMuISO_SF_corr);
  h_looseMuID->Fill(looseMuID_SF_corr);
  
  return tightMuISO_SF_corr*tightMuID_SF_corr*looseMuISO_SF_corr*looseMuID_SF_corr;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, ndilepton, nNoElectrons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection,eleHEMVeto;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = ndilepton = nNoElectrons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = eleHEMVeto = 0;

  if (!sample.isData) {
    //This is the PU histogram obtained from Nick's recipe
    TFile *weights = TFile::Open("RootFiles/PU_Central.root");
    TH1F* PU = (TH1F*)weights->Get("pileup");
    histomap["PU"] = PU;
    
    if (sample.isW_or_ZJet()) {
      //This is the root file with EWK Corrections
      TFile *file = new TFile("RootFiles/kfactors.root");
      TH1F *ewkCorrection,*NNLOCorrection;
      if (sample.type == WJets) {
	ewkCorrection = (TH1F*)file->Get("EWKcorr/W");
	NNLOCorrection = (TH1F*)file->Get("WJets_LO/inv_pt");
      } else {
	ewkCorrection = (TH1F*)file->Get("EWKcorr/Z");
	NNLOCorrection = (TH1F*)file->Get("ZJets_LO/inv_pt");
      }
      histomap["ewkCorrection"] = ewkCorrection;
      histomap["NNLOCorrection"] = NNLOCorrection;
    }
    
    TFile *f_muSF_ISO = new TFile("RootFiles/RunABCD_SF_ISO.root");
    TFile *f_muSF_ID = new TFile("RootFiles/RunABCD_SF_ID.root");
    h_tightMuSF_ISO = (TH2F*)f_muSF_ISO->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");
    h_looseMuSF_ISO = (TH2F*)f_muSF_ISO->Get("NUM_LooseRelIso_DEN_LooseID_pt_abseta");
    h_tightMuSF_ID = (TH2F*)f_muSF_ID->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");
    h_looseMuSF_ID = (TH2F*)f_muSF_ID->Get("NUM_LooseID_DEN_TrackerMuons_pt_abseta");
  }

  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  cout<<"Running over "<<nTotal<<" events."<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    jetCand     .clear();
    j1PFConsPt  .clear();
    j1PFConsEt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    double event_weight = 1.;
    double gen_weight = 1;
    double nokfactor = 1;
    double nogen = 1;
    noweight = 1;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      if (applyPU) {
	float pileup = histomap.getBin("PU",puTrue->at(0));
	h_pileup->Fill(pileup);
	event_weight = pileup;
	nokfactor = pileup;
	gen_weight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;
	event_weight *= gen_weight;
	nokfactor *= gen_weight;
	noweight *= gen_weight;
	nogen *= pileup;
      }
      if(sample.isW_or_ZJet()) {
	//check which mc particle is W boson
	for(int i=0; i<nMC;i++){
	  if((*mcPID)[i] == sample.PID && mcStatusFlag->at(i)>>2&1 == 1){
	    int bosonPID = (*mcPID)[i];
	    bosonPt = (*mcPt)[i];
	    double kfactor = getKfactor(bosonPt);
	    if ( sample.PID == 23 ) {
	      h_genZPt->Fill(bosonPt,gen_weight);
	      h_genZPtwK->Fill(bosonPt,gen_weight*kfactor);
	    }
	    if ( sample.PID == 24 ) {
	      h_genWPt->Fill(bosonPt,gen_weight);
	      h_genWPtwK->Fill(bosonPt,gen_weight*kfactor);
	    }
	    event_weight *= kfactor;
	    noweight *= kfactor;
	    nogen *= kfactor;
	  }
	}
      }
    }

    double weightNorm = event_weight;
    
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand);
    //CR Variables
    lepindex_leading = -1;
    lepindex_subleading = -1;
    dilepton_pt = dilepton_mass = Recoil=-99;
    nTotalEvents+=gen_weight;
    fillHistos(0,gen_weight);
    for (int bit = 0; bit < 8; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metFilters->Fill(bit + 1,event_weight);
    
    if (metFilters==0 && inclusiveCut()) { 
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      
      if (HLTMet>>7&1 == 1 || HLTMet>>8&1 == 1 || HLTMet>>10&1 == 1 || !sample.isData){
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	
	if(jetCand.size()>0){
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  //CR code
	  //At least one of the two muons passes the tight selection
	  vector<int> mulist = muon_veto_looseID(jetCand[0],0,0,10.0);
	  vector<int> mulist_leading = muon_veto_tightID(jetCand[0],20.0);
	  vector<int> mulist_subleading = muon_veto_looseID(jetCand[0],0,0,10.0);
	  
	  if(mulist.size()>0 && mulist.size() == 2){
	    bool muPairSet = false;
	    bool subleading_passes_looseIso = false;
	    TLorentzVector m1, m2;
	    for(int i=0; i<mulist_leading.size(); ++i){
	      for(int j=0; j<mulist_subleading.size(); ++j){
		//Event must have exactly two loose muons with opposite charge
		if(muCharge->at(mulist_leading[i])*muCharge->at(mulist_subleading[j]) == -1){
		  m1.SetPtEtaPhiE(muPt->at(mulist_leading[i]),muEta->at(mulist_leading[i]),muPhi->at(mulist_leading[i]),muE->at(mulist_leading[i]));
		  m2.SetPtEtaPhiE(muPt->at(mulist_subleading[j]),muEta->at(mulist_subleading[j]),muPhi->at(mulist_subleading[j]),muE->at(mulist_subleading[j]));
		  muPairSet = true;
		  lepindex_leading = mulist_leading[i];
		  lepindex_subleading = mulist_subleading[j];
		  Float_t zero = 0.0;
		  Float_t muPhoPU = muPFNeuIso->at(lepindex_subleading) + muPFPhoIso->at(lepindex_subleading) - 0.5*muPFPUIso->at(lepindex_subleading);
		  Float_t muIso_combinedRelative = (muPFChIso->at(lepindex_subleading) + TMath::Max(zero,muPhoPU))/(muPt->at(lepindex_subleading));
		  subleading_passes_looseIso = muIso_combinedRelative < 0.25;
		  break;
		}
	      }
	      if(muPairSet)
		break;
	    }
		    
	    if(muPairSet && subleading_passes_looseIso){ 
	      nCRSelection+=event_weight;
	      fillHistos(4,event_weight);
	      if (!sample.isData && applySF) {
		double sf = getSF(lepindex_leading,lepindex_subleading);
		event_weight *= sf;
		nokfactor *= sf;
		noweight *= sf;
		nogen *= sf;
	      }
	      TLorentzVector ll = m1 + m2;
	      dilepton_mass = ll.M();
	      dilepton_pt = ll.Pt();
			
	      TLorentzVector met_4vec;
	      met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	      TLorentzVector leptoMET_4vec = ll+met_4vec;
	      Double_t leptoMET = leptoMET_4vec.Pt();
	      Double_t leptoMET_phi = leptoMET_4vec.Phi();
	      Recoil = leptoMET;
	      
	      if (leptoMET>250){
		nMET200+=event_weight;
		fillHistos(5,event_weight);
		//invariant mass of the two muons is betwen 60 and 120GeV
		
		if(dilepton_mass > 60 && dilepton_mass < 120){
		  ndilepton+=event_weight;
		  fillHistos(6,event_weight);
		  vector<int> elelist = electron_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,10.0);
		  
		  if(elelist.size() == 0){
		    nNoElectrons+=event_weight;
		    fillHistos(7,event_weight);
		    double metcut = (fabs(pfMET - caloMET))/Recoil;
		    h_metcut->Fill(metcut,event_weight);
		    
		    if(metcut < 0.5){
		      nMETcut+=event_weight;
		      fillHistos(8,event_weight);
		      
		      if(btagVeto()){
			nbtagVeto+=event_weight;
			fillHistos(9,event_weight);
			vector<int> jetveto = JetVetoDecision(lepindex_leading,lepindex_subleading);
			double minDPhiJetMET_first4 = TMath::Pi();
			for(int j = 0; j < jetveto.size(); j++){
			  double minDPhiJetMET = DeltaPhi(jetPhi->at(jetveto[j]),pfMETPhi);
			  if(minDPhiJetMET < minDPhiJetMET_first4)
			    if(j < 4)
			      minDPhiJetMET_first4 = minDPhiJetMET;
			}
			h_dphimin->Fill(minDPhiJetMET_first4,event_weight);
			
			if(dPhiJetMETcut(jetveto)){
			  nDphiJetMET+=event_weight;
			  fillHistos(10,event_weight);
			  
			  if (getEleHEMVeto(40)) {
			    eleHEMVeto+=event_weight;
			    PSWeights(nogen); // 44 Histograms
			    QCDVariations(event_weight);
			    fillHistos(11,event_weight);

			    PFUncertainty(event_weight); // 6 Histograms
			  }
			}   
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }

    JetEnergyScale(weightNorm); // 2 Histograms

    if (jentry%reportEvery == 0){
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
    }
  }
   
  h_cutflow->SetBinContent(1,nTotalEvents); 
  h_cutflow->SetBinContent(2,nFilters);
  h_cutflow->SetBinContent(3,nHLT);
  h_cutflow->SetBinContent(4,nJetSelection);
  h_cutflow->SetBinContent(5,nCRSelection);
  h_cutflow->SetBinContent(6,nMET200);
  h_cutflow->SetBinContent(7,ndilepton);
  h_cutflow->SetBinContent(8,nNoElectrons);
  h_cutflow->SetBinContent(9,nMETcut);
  h_cutflow->SetBinContent(10,nbtagVeto);
  h_cutflow->SetBinContent(11,nDphiJetMET);
  h_cutflow->SetBinContent(12,eleHEMVeto);
   
}//Closing the Loop function

void ZprimeJetsClass::initTree(TTree* tree) {
  tree->Branch("weight",&weight);
  tree->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
  tree->Branch("h_recoil",&Recoil,"Recoil (GeV)");
  tree->Branch("jetPt",&l_jetPt,"Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt",&ChNemPt,"Ch + NEM Leading Jet P_{T} (GeV)");
}

void ZprimeJetsClass::BookHistos(const char* outputFilename) {
  
  output = new TFile(outputFilename, "RECREATE");
  output->cd();
  
  
  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float LeadingLeptonPtBins[25] = {20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  float subLeadingLeptonPtBins[26] = {10.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  h_cutflow = new TH1D("h_cutflow","h_cutflow",12,0,12);h_cutflow->Sumw2();
  h_cutflow->GetXaxis()->SetBinLabel(1,"Total Events");
  h_cutflow->GetXaxis()->SetBinLabel(2,"metFilters");
  h_cutflow->GetXaxis()->SetBinLabel(3,"Trigger");
  h_cutflow->GetXaxis()->SetBinLabel(4,"GoodJet");
  h_cutflow->GetXaxis()->SetBinLabel(5,"CRSelection"); 
  h_cutflow->GetXaxis()->SetBinLabel(6,"leptoMetCut");
  h_cutflow->GetXaxis()->SetBinLabel(7,"dileptonMassCut");
  h_cutflow->GetXaxis()->SetBinLabel(8,"NoElectrons");
  h_cutflow->GetXaxis()->SetBinLabel(9,"caloMET cut");
  h_cutflow->GetXaxis()->SetBinLabel(10,"B-JetVeto");
  h_cutflow->GetXaxis()->SetBinLabel(11,"DeltaPhiCut");
  h_cutflow->GetXaxis()->SetBinLabel(12,"EleHEMVeto");

  h_tightMuISO = new TH1F("h_tightMuISO","tightMuISO Scale Factor;tightMuISO Scale Factor",50,0.95,1.05); h_tightMuISO->Sumw2();
  h_tightMuID = new TH1F("h_tightMuID","tightMuID Scale Factor;tightMuID Scale Factor",50,0.95,1.05); h_tightMuID->Sumw2();
  h_looseMuISO = new TH1F("h_looseMuISO","looseMuISO Scale Factor;looseMuISO Scale Factor",50,0.95,1.05); h_looseMuISO->Sumw2();
  h_looseMuID = new TH1F("h_looseMuID","looseMuID Scale Factor;looseMuID Scale Factor",50,0.95,1.05); h_looseMuID->Sumw2();

  BookCommon(-1,"");
  for(int i = 0; i<nHisto; i++){
    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    auto dir = output->mkdir( ("ZprimeJet"+histname).c_str() );
    dir->cd();
    if (i == bHisto) {
      auto treedir = dir->mkdir("trees");
      treedir->cd();
      tree = new TTree("norm","norm");
      initTree(tree);
      scaleUncs = new ScaleUncCollection(tree);
      shapeUncs = new ShapeUncCollection(treedir);
      dir->cd();
    }
    //Common Histograms
    BookCommon(i,histname);
    //CR Histograms
    h_leadingLeptonPt[i] = new TH1F(("h_leadingLeptonPt"+histname).c_str(),"h_leadingLeptonPt",24,LeadingLeptonPtBins);h_leadingLeptonPt[i]->Sumw2();
    h_leadingLeptonEta[i] = new TH1F(("h_leadingLeptonEta"+histname).c_str(),"h_leadingLeptonEta",30,-3.0,3.0);h_leadingLeptonEta[i]->Sumw2();
    h_leadingLeptonPhi[i] = new TH1F(("h_leadingLeptonPhi"+histname).c_str(),"h_leadingLeptonPhi",20,-3.1416,3.1416);h_leadingLeptonPhi[i]->Sumw2();
    h_leadingLeptonEtaPhi[i] = new TH2F(("h_leadingLeptonEtaPhi"+histname).c_str(),"h_leadingLeptonEtaPhi",50,-3.0,3.0,50,-3.1416,3.1416);
    h_subleadingLeptonPt[i] = new TH1F(("h_subleadingLeptonPt"+histname).c_str(),"h_subleadingLeptonPt",25,subLeadingLeptonPtBins);h_subleadingLeptonPt[i]->Sumw2();
    h_subleadingLeptonEta[i] = new TH1F(("h_subleadingLeptonEta"+histname).c_str(),"h_subleadingLeptonEta",30,-3.0,3.0);h_subleadingLeptonEta[i]->Sumw2();
    h_subleadingLeptonPhi[i] = new TH1F(("h_subleadingLeptonPhi"+histname).c_str(),"h_subleadingLeptonPhi",20,-3.1416,3.1416);h_subleadingLeptonPhi[i]->Sumw2();
    h_subleadingLeptonEtaPhi[i] = new TH2F(("h_subleadingLeptonEtaPhi"+histname).c_str(),"h_subleadingLeptonEtaPhi",50,-3.0,3.0,50,-3.1416,3.1416);
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
    h_dileptonPt[i] = new TH1F(("h_dileptonPt"+histname).c_str(),"h_dileptonPt",30,0.,1500.);h_dileptonPt[i]->Sumw2();
    h_dileptonM[i] = new TH1F(("h_dileptonM"+histname).c_str(),"h_dileptonM",24,60.,120.);h_dileptonM[i]->Sumw2();
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight){
  fillCommon(histoNumber,event_weight);
  //CR Histograms
  if(lepindex_leading >= 0 && lepindex_subleading >= 0){
    h_leadingLeptonPt[histoNumber]->Fill(muPt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[histoNumber]->Fill(muEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[histoNumber]->Fill(muPhi->at(lepindex_leading),event_weight);
    h_leadingLeptonEtaPhi[histoNumber]->Fill(muEta->at(lepindex_leading),muPhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[histoNumber]->Fill(muPt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[histoNumber]->Fill(muEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[histoNumber]->Fill(muPhi->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEtaPhi[histoNumber]->Fill(muEta->at(lepindex_subleading),muPhi->at(lepindex_subleading),event_weight);
  }
  if(dilepton_pt >= 0 && dilepton_mass >= 0){
    h_recoil[histoNumber]->Fill(Recoil,event_weight);
    h_dileptonPt[histoNumber]->Fill(dilepton_pt,event_weight);
    h_dileptonM[histoNumber]->Fill(dilepton_mass,event_weight);
  }
  weight = event_weight;
  if (histoNumber == bHisto) tree->Fill();
}

vector<int> ZprimeJetsClass::JetVetoDecision(int leading_lep_index, int subleading_lep_index) {

  bool jetVeto=true;
  vector<int> jetindex;

  for(int i = 0; i < nJet; i++){
    double deltar_leading = deltaR(jetEta->at(i),jetPhi->at(i),muEta->at(leading_lep_index),muPhi->at(leading_lep_index));
    double deltar_subleading = deltaR(jetEta->at(i),jetPhi->at(i),muEta->at(subleading_lep_index),muPhi->at(subleading_lep_index));
    bool tightJetID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if(deltar_leading>0.4 && deltar_subleading>0.4 && jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID)
      jetindex.push_back(i);
  }
  return jetindex;
}

vector<int> ZprimeJetsClass::electron_veto_tightID(int jet_index, float elePtCut){
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++){
    //Electron passes Tight Electron ID cuts
    if(eleIDbit->at(i)>>2&1 == 1){
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut){
	  //Electron does not overlap photon
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    ele_cands.push_back(i);
	}
      }
    }
  }
  return ele_cands;
}

vector<int> ZprimeJetsClass::muon_veto_tightID(int jet_index, float muPtCut){
  // bool veto_passed = true; //pass veto if no good muon found
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++){
    if(muIDbit->at(i)>>3&1 == 1 && muIDbit->at(i)>>9&1 == 1){
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut){
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

vector<int> ZprimeJetsClass::electron_veto_looseID(int jet_index, int leading_mu_index, int subleading_mu_index, float elePtCut){
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++){
    //Electron passes Loose Electron ID cuts
    if(eleIDbit->at(i)>>0&1 == 1){
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut){
	  //Electron does not overlap photon
	  double dR_leading = deltaR(eleEta->at(i),elePhi->at(i),muEta->at(leading_mu_index),muPhi->at(leading_mu_index));
	  double dR_subleading = deltaR(eleEta->at(i),elePhi->at(i),muEta->at(subleading_mu_index),muPhi->at(subleading_mu_index));
	  if(dR_leading > 0.5 && dR_subleading > 0.5 && deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    ele_cands.push_back(i);
	}
      }
    }
  }
  return ele_cands;
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate photon within dR of 0.5
vector<int> ZprimeJetsClass::muon_veto_looseID(int jet_index, int leading_ele_index, int subleading_ele_index, float muPtCut){
  vector<int> mu_cands;
  mu_cands.clear();
  
  for(int i = 0; i < nMu; i++){
    if(muIDbit->at(i)>>0&1 == 1){
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut){
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }  
  }
  return mu_cands;
}

