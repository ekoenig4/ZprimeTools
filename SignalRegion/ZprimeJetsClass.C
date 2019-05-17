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

bool ZprimeJetsClass::getJetHEMVeto(double jetPtCut){

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

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nMET200, nMETcut,nLeptonIDs,nbtagVeto, nDphiJetMET,nJetSelection,nHEM;
  nTotalEvents = nFilters = nHLT = nMET200 = nMETcut = nLeptonIDs = nDphiJetMET = nbtagVeto = nJetSelection = nHEM = 0;
  vector<int> jetveto;
  vector<int> PFCandidates;
  float dphimin = -99;

  if (!sample.isData) {
    //This is the PU histogram obtained from Nick's recipe
    TFile *weights = TFile::Open("PU_Central.root");
    PU = (TH1D*)weights->Get("pileup");
    
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
  for (Long64_t jentry=0; jentry<nentriesToCheck; sample.isData ? jentry += 4 : jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    jetCand     .clear();
    jetveto     .clear();
    PFCandidates.clear();
    j1PFConsEt  .clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    double event_weight = 1.;
    int bosonPID;
    double bosonPt;
    bool WorZfound = false;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
      event_weight = PU->GetBinContent(bin);
      //cout<<"event_weight: "<<event_weight<<endl;
      fabs(genWeight) > 0.0 ? event_weight*=genWeight/fabs(genWeight) : event_weight =0.0;
      if (sample.isW_or_ZJet()) {
	for (int i = 0; i < nMC; i++)
	  if ((*mcPID)[i] == sample.PID) {
	    WorZfound = true;
	    bosonPID = (*mcPID)[i];
	    bosonPt = (*mcPt)[i];
	  }
      }
    }
    float metcut = 0.0;

    jetveto = JetVetoDecision();
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand,PFCandidates);
    nTotalEvents+=event_weight;
    fillHistos(0,event_weight);
    for (int bit = 0; bit < 8; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metFilters->Fill(bit + 1,event_weight);
    if (metFilters == 0 && inclusiveCut()) {
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      if (HLTMet>>7&1 == 1 || HLTMet>>8&1 == 1 || HLTMet>>10&1 == 1 || !sample.isData) {
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	if (jetCand.size() > 0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  if (sample.isW_or_ZJet()) event_weight *= getKfactor(bosonPt);
	  if (pfMET > 250) {
	    nMET200+=event_weight;
	    fillHistos(4,event_weight);
	    metcut = (fabs(pfMET-caloMET)/pfMET);
	    h_metcut->Fill(metcut);
	    if (metcut < 0.5) {
	      nMETcut+=event_weight;
	      fillHistos(5,event_weight);
	      if (electron_veto_looseID(jetCand[0],10.) && muon_veto_looseID(jetCand[0],10.)) {
		nLeptonIDs+=event_weight;
		fillHistos(6,event_weight);
		if (btagVeto()) {
		  nbtagVeto+=event_weight;
		  fillHistos(7,event_weight);
		  double minDPhiJetMET_first4 = TMath::Pi();
		  for (int i = 0; i < jetveto.size(); i++) {
		    double dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
		    if (dPhiJetMet < minDPhiJetMET_first4) {
		      if (i < 4)
			minDPhiJetMET_first4 = dPhiJetMet;
		    }
		  }
		  h_dphimin->Fill(minDPhiJetMET_first4);
		  if (dPhiJetMETcut(jetveto)) {
		    nDphiJetMET+=event_weight;
		    fillHistos(8,event_weight);
		    if (getJetHEMVeto(200)) {
		      nHEM+=event_weight;
		      fillHistos(9,event_weight);
		    }
		    if (Pt123Fraction > 0.6)
		      fillHistos(10,event_weight);
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    tree->Fill();
    if (jentry%reportEvery == 0)
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck - 1)<<endl;
  }
  h_cutflow->SetBinContent(1,nTotalEvents); 
  h_cutflow->SetBinContent(2,nFilters);
  h_cutflow->SetBinContent(3,nHLT);
  h_cutflow->SetBinContent(4,nJetSelection);
  h_cutflow->SetBinContent(5,nMET200);
  h_cutflow->SetBinContent(6,nMETcut);
  h_cutflow->SetBinContent(7,nLeptonIDs);
  h_cutflow->SetBinContent(8,nbtagVeto);
  h_cutflow->SetBinContent(9,nDphiJetMET);
  h_cutflow->SetBinContent(10,nHEM);
}

void ZprimeJetsClass::BookRegion(int i, string histname) {
  output->cd();

  if (i == -1) {
  h_cutflow = new TH1D("h_cutflow","h_cutflow",10,0,10);h_cutflow->Sumw2();
  h_cutflow->GetXaxis()->SetBinLabel(1,"Total Events");
  h_cutflow->GetXaxis()->SetBinLabel(2,"metFilters");
  h_cutflow->GetXaxis()->SetBinLabel(3,"Trigger");
  h_cutflow->GetXaxis()->SetBinLabel(4,"GoodJet");
  h_cutflow->GetXaxis()->SetBinLabel(5,"MetCut");
  h_cutflow->GetXaxis()->SetBinLabel(6,"caloMET cut");
  h_cutflow->GetXaxis()->SetBinLabel(7,"LeptonIDs");
  h_cutflow->GetXaxis()->SetBinLabel(8,"B-JetVeto");
  h_cutflow->GetXaxis()->SetBinLabel(9,"DeltaPhiCut");
  h_cutflow->GetXaxis()->SetBinLabel(10,"HEM Veto");
  } else {

  }
}

void ZprimeJetsClass::fillRegion(int histoNumber,double event_weight) {
  
}

vector<int> ZprimeJetsClass::JetVetoDecision() {
  vector<int> jetindex;
  for(int i = 0; i < nJet; i++){
    bool tightJetID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID)
      jetindex.push_back(i);
  }
  return jetindex;
}

bool ZprimeJetsClass::electron_veto_looseID(int jet_index, float elePtCut) {
  bool veto_passed = true; //pass veto if no good electron found
  for(int i = 0; i < nEle; i++) {
    //Electron passes Loose Electron ID cuts
    if(eleIDbit->at(i)>>0&1 == 1) {
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5) {
	    veto_passed = false;
	    break;
	  }
	}
      }
    }
  }
  return veto_passed;
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate photon within dR of 0.5
bool ZprimeJetsClass::muon_veto_looseID(int jet_index, float muPtCut) {
  bool veto_passed = true; //pass veto if no good muon found
  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>0&1==1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //cout <<"Passed Pt Cut" << endl;
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5) {
	    veto_passed = false;
	    break;
	  }
	}
      }
    }
  }
  return veto_passed;
}
