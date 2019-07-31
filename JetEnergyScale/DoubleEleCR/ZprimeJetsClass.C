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

double EletriggerSF(float pt, float eta){
  double sf = 1.0;
  if(fabs(eta) >= 0.0   && fabs(eta) < 0.8){
    if(pt < 40.0) sf = 0.75;
    if(pt > 40.0 && pt < 50.0) sf = 0.92;
    if(pt > 50.0 && pt < 60.0) sf = 0.95;
    if(pt > 60.0 && pt < 70.0) sf = 0.96;
    if(pt > 70.0 && pt < 80.0) sf = 0.96;
    if(pt > 80.0 && pt < 90.0) sf = 0.97;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.97;
    if(pt > 150. && pt < 200.) sf = 0.97;
    if(pt > 200. && pt < 250.) sf = 0.98;
    if(pt > 250) sf = 0.93;
  }
  if(fabs(eta) >= 0.8   && fabs(eta) < 1.5){
    if(pt < 40.0) sf = 0.64;
    if(pt > 40.0 && pt < 50.0) sf = 0.91;
    if(pt > 50.0 && pt < 60.0) sf = 0.94;
    if(pt > 60.0 && pt < 70.0) sf = 0.95;
    if(pt > 70.0 && pt < 80.0) sf = 0.95;
    if(pt > 80.0 && pt < 90.0) sf = 0.96;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.96;
    if(pt > 150. && pt < 200.) sf = 0.96;
    if(pt > 200. && pt < 250.) sf = 0.97;
    if(pt > 250) sf = 1.0;
  }
    
  if(fabs(eta) >= 1.5   && fabs(eta) < 2. ) {
    if(pt < 40.0) sf = 0.63;
    if(pt > 40.0 && pt < 50.0) sf = 0.91;
    if(pt > 50.0 && pt < 60.0) sf = 0.94;
    if(pt > 60.0 && pt < 70.0) sf = 0.95;
    if(pt > 70.0 && pt < 80.0) sf = 0.95;
    if(pt > 80.0 && pt < 90.0) sf = 0.95;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.96;
    if(pt > 150. && pt < 200.) sf = 0.99;
    if(pt > 200. && pt < 250.) sf = 0.97;
    if(pt > 250) sf = 1.0;
  }
  if(fabs(eta) >= 2.) {
    if(pt < 40.0) sf = 0.5;
    if(pt > 40.0 && pt < 50.0) sf = 0.83;
    if(pt > 50.0 && pt < 60.0) sf = 0.89;
    if(pt > 60.0 && pt < 70.0) sf = 0.90;
    if(pt > 70.0 && pt < 80.0) sf = 0.92;
    if(pt > 80.0 && pt < 90.0) sf = 0.93;
    if(pt > 90.0 && pt < 100.) sf = 0.94;
    if(pt > 100. && pt < 150.) sf = 0.94;
    if(pt > 150. && pt < 200.) sf = 0.96;
    if(pt > 200. && pt < 250.) sf = 1.0;
    if(pt > 250) sf = 1.0;
  }
  return sf;
}

double ZprimeJetsClass::getSF(int lepindex_leading, int lepindex_subleading) {
  double leadingElePt = elePt->at(lepindex_leading) < 500 ? elePt->at(lepindex_leading) : 499;
  double leadingEleEta = fabs(eleEta->at(lepindex_leading)) < 2.5 ? eleEta->at(lepindex_leading) : 2.49;
  double subleadingElePt = elePt->at(lepindex_subleading) < 500 ? elePt->at(lepindex_subleading) : 499;
  double subleadingEleEta = fabs(eleEta->at(lepindex_subleading)) < 2.5 ? eleEta->at(lepindex_subleading) : 2.49;
  // cout<<"leadingElePt = " << elePt->at(lepindex_leading) <<" leadingEleEta = " << eleEta->at(lepindex_leading) << endl;
  // cout<<"subleadingElePt = " << elePt->at(lepindex_subleading) <<" leadingEleEta = " << eleEta->at(lepindex_subleading) << endl;
  double leadingEleRecoSF_corr=h_eleRecoSF_highpt->GetBinContent(h_eleRecoSF_highpt->GetXaxis()->FindBin(leadingEleEta),h_eleRecoSF_highpt->GetYaxis()->FindBin(leadingElePt));
  double leadingEleEffSF_corr=h_eleIDSF_tight->GetBinContent(h_eleIDSF_tight->GetXaxis()->FindBin(leadingEleEta),h_eleIDSF_tight->GetYaxis()->FindBin(leadingElePt));
  double leadingEleTriggSF = EletriggerSF(elePt->at(lepindex_leading),eleEta->at(lepindex_leading));
  
  double subleadingEleRecoSF_corr=h_eleRecoSF_highpt->GetBinContent(h_eleRecoSF_highpt->GetXaxis()->FindBin(subleadingEleEta),h_eleRecoSF_highpt->GetYaxis()->FindBin(subleadingElePt));
  double subleadingEleEffSF_corr=h_eleIDSF_loose->GetBinContent(h_eleIDSF_loose->GetXaxis()->FindBin(subleadingEleEta),h_eleIDSF_loose->GetYaxis()->FindBin(subleadingElePt));
  double subleadingEleTriggSF = EletriggerSF(elePt->at(lepindex_subleading),eleEta->at(lepindex_subleading));
  // cout<<"leadingEleTriggSF = " << leadingEleTriggSF << endl;
  // cout<<"subleadingEleTriggSF = " << subleadingEleTriggSF << endl;
  
  h_tightEleRecoSF_corr->Fill(leadingEleRecoSF_corr);
  h_tightEleEffSF_corr->Fill(leadingEleEffSF_corr);
  h_tightEleTriggSF->Fill(leadingEleTriggSF);
  h_looseEleRecoSF_corr->Fill(subleadingEleRecoSF_corr);
  h_looseEleEffSF_corr->Fill(subleadingEleEffSF_corr);
  h_looseEleTriggSF->Fill(subleadingEleTriggSF);
  return leadingEleRecoSF_corr*leadingEleEffSF_corr*leadingEleTriggSF*subleadingEleRecoSF_corr*subleadingEleEffSF_corr*subleadingEleTriggSF;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, ndilepton, nNoMuons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection,nTotalEvents_wPU;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = ndilepton = nNoMuons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = nTotalEvents_wPU = 0;
  vector<int> jetveto;
  vector<int> PFCandidates;
  float dphimin = -99;

  if (!sample.isData) {
    //This is the PU histogram obtained from Nick's recipe
    TFile *weights = TFile::Open("PU_Central.root");
    PU = (TH1D*)weights->Get("pileup");
    
    TFile *f_eleReconstrucSF_highpt=new TFile("egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
    TFile *f_eleIDeffSF_loose=new TFile("2017_ElectronLoose.root");
    TFile *f_eleIDeffSF_tight=new TFile("2017_ElectronTight.root");
    h_eleRecoSF_highpt=(TH2F*) f_eleReconstrucSF_highpt->Get("EGamma_SF2D");
    h_eleIDSF_loose=(TH2F*) f_eleIDeffSF_loose->Get("EGamma_SF2D");
    h_eleIDSF_tight=(TH2F*) f_eleIDeffSF_tight->Get("EGamma_SF2D");

    if (sample.isW_or_ZJet()) {
      //This is the root file with EWK Corrections
      TFile *file = new TFile("kfactors.root");
      if (sample.type == WJets) {
	ewkCorrection = (TH1D*)file->Get("EWKcorr/W");
	NNLOCorrection = (TH1D*)file->Get("WJets_LO/inv_pt");
      } else {
	ewkCorrection = (TH1D*)file->Get("EWKcorr/Z");
	NNLOCorrection = (TH1D*)file->Get("ZJets_LO/inv_pt");
      }
    }
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
    jetveto     .clear();
    PFCandidates.clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    double start_weight = 1.;
    double gen_weight = 1;
    double nokfactor = 1;
    noweight = 1;
    int bosonPID;
    double bosonPt;
    bool WorZfound = false;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as start_weight
      if (applyPU){
	int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
	double pileup = PU->GetBinContent(bin);
	h_pileup->Fill(pileup);
	start_weight = pileup;
	nokfactor = pileup;
	gen_weight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;
	start_weight *= gen_weight;
	nokfactor *= gen_weight;
	noweight *= gen_weight;
      }
      if(sample.isW_or_ZJet()) {
	//check which mc particle is W boson
	for(int i=0; i<nMC;i++){
	  if((*mcPID)[i] == sample.PID && mcStatusFlag->at(i)>>2&1 == 1){
	    WorZfound=true;
	    bosonPID = (*mcPID)[i];
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
	  }
	}
      }
    }
    float metcut= 0.0;
    
    nTotalEvents+=gen_weight;

    jetPtNorm   .clear();
    for (double pt : (*jetPt)) jetPtNorm.push_back(pt);
    
    int unclist[3] = {0,1,-1};
    for (int unc : unclist) {
      jetCand     .clear();
      jetveto     .clear();
      PFCandidates.clear();
      j1PFConsEt  .clear();
      j1PFConsPt  .clear();
      j1PFConsEta .clear();
      j1PFConsPhi .clear();
      j1PFConsPID .clear();

      double event_weight = start_weight;

      for (int i = 0; i < nJet; i++)
	jetPt->at(i) = jetPtNorm[i]*(1+unc*jetJECUnc->at(i));
      if (unc == 1) {
	pfMET = pfMET_T1JESUp;
	pfMETPhi = pfMETPhi_T1JESUp;
      }
      if (unc == -1) {
	pfMET = pfMET_T1JESDo;
	pfMETPhi = pfMETPhi_T1JESDo;
      }
      
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand,PFCandidates);
    //CR Variables
    lepindex_leading = -1;
    lepindex_subleading = -1;
    dilepton_pt = dilepton_mass = Recoil=-99;
    if (unc == 0) fillHistos(0,event_weight);
    
    if (metFilters==0 && inclusiveCut()){ 
      if (unc == 0) nFilters+=event_weight;
      if (unc == 0) fillHistos(1,event_weight);
      
      if (HLTEleMuX>>5&1 == 1 || HLTEleMuX>>6&1 == 1 || HLTPho>>11&1 == 1 || !sample.isData) {
	if (unc == 0) nHLT+=event_weight;
	if (unc == 0) fillHistos(2,event_weight);
	
	if(jetCand.size()>0){
	  if (unc == 0) nJetSelection+=event_weight;
	  if (unc == 0) fillHistos(3,event_weight);
	  if (sample.isW_or_ZJet() && applyKF) {
	    double kfactor = getKfactor(bosonPt);
	    event_weight *= kfactor;
	    noweight *= kfactor;
	  }
	  //CR code
	  //At least one of the two electrons passes the tight selection
	  vector<int> elelist = electron_veto_looseID(jetCand[0],0,0,10.0);
	  vector<int> elelist_leading = electron_veto_tightID(jetCand[0],40.0);
	  vector<int> elelist_subleading = electron_veto_looseID(jetCand[0],0,0,10.0);
	  vector<int> mulist;
	  mulist.clear();
	  
	  if(elelist.size() == 2){
	    bool elePairSet = false;
	    TLorentzVector e1, e2;
	    for(int i=0; i<elelist_leading.size(); ++i){
	      for(int j=0; j<elelist_subleading.size(); ++j){
		//Event must have exactly two loose electrons with opposite charge
		if(eleCharge->at(elelist_leading[i])*eleCharge->at(elelist_subleading[j]) == -1){
		  e1.SetPtEtaPhiE(elePt->at(elelist_leading[i]),eleEta->at(elelist_leading[i]),elePhi->at(elelist_leading[i]),eleE->at(elelist_leading[i]));
		  e2.SetPtEtaPhiE(elePt->at(elelist_subleading[j]),eleEta->at(elelist_subleading[j]),elePhi->at(elelist_subleading[j]),eleE->at(elelist_subleading[j]));
		  mulist = muon_veto_looseID(jetCand[0],elelist_leading[i],elelist_subleading[j],10.0);
		  jetveto = JetVetoDecision(elelist_leading[i],elelist_subleading[j]);
		  elePairSet = true;
		  lepindex_leading = elelist_leading[i];
		  lepindex_subleading = elelist_subleading[j];
		  break;
		}
	      }
	      if(elePairSet)
		break;
	    }
                    
	    if(elePairSet){
	      if (unc == 0) nCRSelection+=event_weight;
	      if (unc == 0) fillHistos(4,event_weight);
	      if (!sample.isData && applySF) {
		double sf = getSF(lepindex_leading,lepindex_subleading);
		event_weight *= sf;
		noweight *= sf;
	      }
	      TLorentzVector ll = e1+e2;
	      dilepton_mass = ll.M();
	      dilepton_pt = ll.Pt();
                      
	      TLorentzVector met_4vec;
	      met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	      TLorentzVector leptoMET_4vec = ll+met_4vec;
	      Double_t leptoMET = fabs(leptoMET_4vec.Pt());
	      Double_t leptoMET_phi = leptoMET_4vec.Phi();
	      Recoil = leptoMET;
	      metcut = (fabs(pfMET-caloMET))/Recoil;
	      
	      if (leptoMET>250){
		if (unc == 0) nMET200+=event_weight;
		if (unc == 0) fillHistos(5,event_weight);
		//invariant mass of the two electrons is betwen 60 and 120GeV
		
		if(dilepton_mass > 60 && dilepton_mass < 120){
		  if (unc == 0) ndilepton+=event_weight;
		  if (unc == 0) fillHistos(6,event_weight);
		  
		  if(mulist.size() == 0){
		    if (unc == 0) nNoMuons+=event_weight;
		    if (unc == 0) fillHistos(7,event_weight);
		    if (unc == 0) h_metcut->Fill(metcut);
		    
		    if(metcut < 0.5){
		      if (unc == 0) nMETcut+=event_weight;
		      if (unc == 0) fillHistos(8,event_weight);
		      
		      if(btagVeto()){
			if (unc == 0) nbtagVeto+=event_weight;
			if (unc == 0) fillHistos(9,event_weight);
			double minDPhiJetMET_first4 = TMath::Pi();
			for (int i = 0; i < jetveto.size(); i++) {
			  double dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
			  if (dPhiJetMet < minDPhiJetMET_first4) {
			    if (i < 4)
			      minDPhiJetMET_first4 = dPhiJetMet;
			  }
			}
			if (unc == 0) h_dphimin->Fill(minDPhiJetMET_first4);
			
			if(dPhiJetMETcut(jetveto)){
		      if (unc == 0) nDphiJetMET+=event_weight;
		      if (unc == 0)  fillHistos(10,event_weight); //norm
		      if (unc == 1)  fillHistos(11,event_weight); //up
		      if (unc == -1) fillHistos(12,event_weight);//down
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
    tree->Fill();

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
  h_cutflow->SetBinContent(8,nNoMuons);
  h_cutflow->SetBinContent(9,nMETcut);
  h_cutflow->SetBinContent(10,nbtagVeto);
  h_cutflow->SetBinContent(11,nDphiJetMET);
   
}//Closing the Loop function

void ZprimeJetsClass::BookHistos(const char* outputFilename) {
  
  output = new TFile(outputFilename, "RECREATE");
  tree = new TTree("ZprimeJet","ZprimeJet");
  output->cd();
  
  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float LeadingLeptonPtBins[25] = {20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  float subLeadingLeptonPtBins[26] = {10.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  h_cutflow = new TH1D("h_cutflow","h_cutflow",11,0,11);h_cutflow->Sumw2();
  h_cutflow->GetXaxis()->SetBinLabel(1,"Total Events");
  h_cutflow->GetXaxis()->SetBinLabel(2,"metFilters");
  h_cutflow->GetXaxis()->SetBinLabel(3,"Trigger");
  h_cutflow->GetXaxis()->SetBinLabel(4,"GoodJet");
  h_cutflow->GetXaxis()->SetBinLabel(5,"CRSelection"); 
  h_cutflow->GetXaxis()->SetBinLabel(6,"leptoMetCut");
  h_cutflow->GetXaxis()->SetBinLabel(7,"dileptonMassCut");
  h_cutflow->GetXaxis()->SetBinLabel(8,"NoMuons");
  h_cutflow->GetXaxis()->SetBinLabel(9,"caloMET cut");
  h_cutflow->GetXaxis()->SetBinLabel(10,"B-JetVeto");
  h_cutflow->GetXaxis()->SetBinLabel(11,"DeltaPhiCut");
  
  h_tightEleRecoSF_corr = new TH1F("h_tightEleRecoSF","h_tightEleRecoSF;Leading EleRecoSF",50,0,2); h_tightEleRecoSF_corr->Sumw2(); 
  h_tightEleEffSF_corr = new TH1F("h_tightEleEffSF","h_tightEleEffSF;Leading EleEffSF",50,0,2); h_tightEleEffSF_corr->Sumw2(); 
  h_tightEleTriggSF = new TH1F("h_tightEleTriggSF","h_tightEleTriggSF;Leading EleTriggSF",50,0,2); h_tightEleTriggSF->Sumw2();
  h_looseEleRecoSF_corr = new TH1F("h_looseEleRecoSF","h_looseEleRecoSF;Subleading EleRecoSF",50,0,2); h_looseEleRecoSF_corr->Sumw2(); 
  h_looseEleEffSF_corr = new TH1F("h_looseEleEffSF","h_looseEleEffSF;Subleading EleEffSF",50,0,2); h_looseEleEffSF_corr->Sumw2(); 
  h_looseEleTriggSF = new TH1F("h_looseEleTriggSF","h_looseEleTriggSF;Subleading EleTriggSF",50,0,2); h_looseEleTriggSF->Sumw2(); 
  
  BookCommon(-1,"");
  for(int i = 0; i<nHisto; i++){
    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    //Common Histograms
    BookCommon(i,histname);
    //CR Histograms
    h_leadingLeptonPt[i] = new TH1F(("h_leadingLeptonPt"+histname).c_str(),"h_leadingLeptonPt",24,LeadingLeptonPtBins);h_leadingLeptonPt[i]->Sumw2();
    h_leadingLeptonEta[i] = new TH1F(("h_leadingLeptonEta"+histname).c_str(),"h_leadingLeptonEta",30,-3.0,3.0);h_leadingLeptonEta[i]->Sumw2();
    h_leadingLeptonPhi[i] = new TH1F(("h_leadingLeptonPhi"+histname).c_str(),"h_leadingLeptonPhi",20,-3.1416,3.1416);h_leadingLeptonPhi[i]->Sumw2();
    h_subleadingLeptonPt[i] = new TH1F(("h_subleadingLeptonPt"+histname).c_str(),"h_subleadingLeptonPt",25,subLeadingLeptonPtBins);h_subleadingLeptonPt[i]->Sumw2();
    h_subleadingLeptonEta[i] = new TH1F(("h_subleadingLeptonEta"+histname).c_str(),"h_subleadingLeptonEta",30,-3.0,3.0);h_subleadingLeptonEta[i]->Sumw2();
    h_subleadingLeptonPhi[i] = new TH1F(("h_subleadingLeptonPhi"+histname).c_str(),"h_subleadingLeptonPhi",20,-3.1416,3.1416);h_subleadingLeptonPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
    h_dileptonPt[i] = new TH1F(("h_dileptonPt"+histname).c_str(),"h_dileptonPt",30,0.,1500.);h_dileptonPt[i]->Sumw2();
    h_dileptonM[i] = new TH1F(("h_dileptonM"+histname).c_str(),"h_dileptonM",24,60.,120.);h_dileptonM[i]->Sumw2();
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight){
  fillCommon(histoNumber,event_weight);
  //CR Histograms
  if(lepindex_leading >= 0 && lepindex_subleading >= 0){
    h_leadingLeptonPt[histoNumber]->Fill(elePt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[histoNumber]->Fill(eleEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[histoNumber]->Fill(elePhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[histoNumber]->Fill(elePt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[histoNumber]->Fill(eleEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[histoNumber]->Fill(elePhi->at(lepindex_subleading),event_weight);
  }
  if(dilepton_pt >= 0 && dilepton_mass >= 0){
    h_recoil[histoNumber]->Fill(Recoil,event_weight);
    h_dileptonPt[histoNumber]->Fill(dilepton_pt,event_weight);
    h_dileptonM[histoNumber]->Fill(dilepton_mass,event_weight);
  }
}

vector<int> ZprimeJetsClass::JetVetoDecision(int leading_lep_index, int subleading_lep_index) {

  bool jetVeto=true;
  vector<int> jetindex;

  for(int i = 0; i < nJet; i++){
    double deltar_leading = deltaR(jetEta->at(i),jetPhi->at(i),eleEta->at(leading_lep_index),elePhi->at(leading_lep_index));
    double deltar_subleading = deltaR(jetEta->at(i),jetPhi->at(i),eleEta->at(subleading_lep_index),elePhi->at(subleading_lep_index));
    bool tightJetID = false;
    bool loosePUID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if((*jetPUFullID)[i]&(1<<2)) loosePUID=true;
    if(deltar_leading>0.4 && deltar_subleading>0.4 && jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID && loosePUID)
      jetindex.push_back(i);  }
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
    if(muIDbit->at(i)>>3&1==1 && muIDbit->at(i)>>9&1==1){
      //Muon passes eta cut
      if (fabs(eleEta->at(i)) < 2.4) {
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
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
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
    if(muIDbit->at(i)>>0&1==1){
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut){
	  //Muon does not overlap photon
	  double dR_leadingEle = deltaR(muEta->at(i),muPhi->at(i),eleEta->at(leading_ele_index),elePhi->at(leading_ele_index));
	  double dR_subleadingEle = deltaR(muEta->at(i),muPhi->at(i),eleEta->at(subleading_ele_index),elePhi->at(subleading_ele_index));
	  if(dR_leadingEle > 0.5 && dR_subleadingEle > 0.5 && deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

