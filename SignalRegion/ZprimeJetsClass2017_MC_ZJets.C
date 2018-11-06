#define ZprimeJetsClass2017_cxx
#include "ZprimeJetsClass2017.h"
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
  ZprimeJetsClass2017 t(argv[1],argv[2],argv[5]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

void ZprimeJetsClass2017::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nMET200, nMETcut,nLeptonIDs,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nMET200 = nMETcut = nLeptonIDs = nDphiJetMET = nbtagVeto = nJetSelection = 0;
  vector<int> jetveto;
  vector<int> PFCandidates;
  float dphimin = -99;

  //This is the PU histogram obtained from Nick's recipe
  TFile *weights = TFile::Open("PU_Central.root");
  TH1D* PU = (TH1D*)weights->Get("pileup");

  //This is the root file with EWK Corrections
  TFile *file = new TFile("kfactors.root");
  TH1D *ewkCorrection = (TH1D*)file->Get("EWKcorr/Z");
  TH1D *NNLOCorrection = (TH1D*)file->Get("ZJets_LO/inv_pt");

  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  cout<<"Running over "<<nTotal<<" events."<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry+=4) {
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

    double event_weight = 1.;
    double EWK_corrected_weight=1.0;
    double NNLO_weight = 1.0;
    double kfactor = 1.0;
    //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
    //binContent as event_weight
    int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
    event_weight = PU->GetBinContent(bin);
    //cout<<"event_weight: "<<event_weight<<endl;
    fabs(genWeight) > 0.0 ? event_weight*=genWeight/fabs(genWeight) : event_weight =0.0;
    int bosonPID;
    double bosonPt;
    bool Zfound = false;
    //check which mc particle is Z boson
    for(int i=0; i<nMC;i++){
      if((*mcPID)[i] == 23){
        Zfound=true;
        bosonPID = (*mcPID)[i];
        bosonPt = (*mcPt)[i];
      }
    }
    float metcut = 0.0;

    jetveto = JetVetoDecision();
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand,PFCandidates);
    nTotalEvents++;
    fillHistos(0,event_weight);
    if (metFilters == 0) {
      nFilters++;
      fillHistos(1,event_weight);
      if (true) {
	nHLT++;
	fillHistos(2,event_weight);
	if (jetCand.size() > 0) {
	  nJetSelection++;
	  fillHistos(3,event_weight);
	  EWK_corrected_weight = 1.0*(ewkCorrection->GetBinContent(ewkCorrection->GetXaxis()->FindBin(bosonPt)));
	  NNLO_weight = 1.0*(NNLOCorrection->GetBinContent(NNLOCorrection->GetXaxis()->FindBin(bosonPt)));
	  if(EWK_corrected_weight!=0 && NNLO_weight!=0)
	    kfactor = (EWK_corrected_weight/NNLO_weight);
	  else
	    kfactor=1.23;
	  event_weight*=kfactor;
	  if (pfMET > 250) {
	    nMET200++;
	    fillHistos(4,event_weight);
	    metcut = (fabs(pfMET)/pfMET);
	    h_metcut->Fill(metcut);
	    if (true) {
	      nMETcut++;
	      fillHistos(5,event_weight);
	      if (electron_veto_looseID(jetCand[0],10.) && muon_veto_looseID(jetCand[0],10.)) {
		nLeptonIDs++;
		fillHistos(6,event_weight);
		if (btagVeto()) {
		  nbtagVeto++;
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
		    nDphiJetMET++;
		    fillHistos(8,event_weight);
		    if (Pt123Fraction > 0.6)
		      fillHistos(9,event_weight);
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
}

void ZprimeJetsClass2017::BookHistos(const char* outputFilename) {
  output = new TFile(outputFilename,"RECREATE");
  tree = new TTree("ZprimeJet","ZprimeJet");
  output->cd();

  h_cutflow = new TH1D("h_cutflow","h_cutflow",9,0,9);h_cutflow->Sumw2();
  h_cutflow->GetXaxis()->SetBinLabel(1,"Total Events");
  h_cutflow->GetXaxis()->SetBinLabel(2,"metFilters");
  h_cutflow->GetXaxis()->SetBinLabel(3,"Trigger");
  h_cutflow->GetXaxis()->SetBinLabel(4,"GoodJet");
  h_cutflow->GetXaxis()->SetBinLabel(5,"MetCut");
  h_cutflow->GetXaxis()->SetBinLabel(6,"caloMET cut");
  h_cutflow->GetXaxis()->SetBinLabel(7,"LeptonIDs");
  h_cutflow->GetXaxis()->SetBinLabel(8,"B-JetVeto");
  h_cutflow->GetXaxis()->SetBinLabel(9,"DeltaPhiCut");

  float MtBins[51]={180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.,3000.};
  
  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float PtBins[49]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};
  
  h_metcut  = new TH1F("h_metcut","h_metcut; |pfMET-caloMET|/pfMET", 50,0,1.2);h_metcut->Sumw2();
  h_dphimin = new TH1F("h_dphimin","h_dphimin; Minimum dPhiJetMET",50,0,3.2);h_dphimin->Sumw2();
  for(int i=0; i<nHisto; i++){

    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    h_metFilters[i] = new TH1F(("metFilters"+histname).c_str(),"metFilters",50,0,3000); h_metFilters[i]->Sumw2();
    h_nJets[i]   = new TH1F(("nJets"+histname).c_str(), "nJets;Number of Jets", 50, 0, 100);h_nJets[i]->Sumw2();
    h_pfMETall[i] =  new TH1F(("pfMETall"+histname).c_str(), "pfMET",50,0,2000);h_pfMETall[i] ->Sumw2(); 
    h_pfMET200[i] = new TH1F(("pfMET200"+histname).c_str(), "pfMET",50,170,1500);h_pfMET200[i] ->Sumw2(); 
    h_pfMET[i] = new TH1F(("pfMET"+histname).c_str(), "E_{T}^{miss} (GeV)",44,MetBins);h_pfMET[i] ->Sumw2();
    h_pfMETPhi[i] = new TH1F(("pfMETPhi"+histname).c_str(), "pfMETPhi",50,-4,4);h_pfMETPhi[i]->Sumw2();
    h_j1Pt[i]  = new TH1F(("j1pT"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt[i]->Sumw2();
    h_j1Eta[i] = new TH1F(("j1Eta"+histname).c_str(), "j1Eta; #eta of Leading Jet", 50, -3.0, 3.0);h_j1Eta[i]->Sumw2();
    h_j1Phi[i] = new TH1F(("j1Phi"+histname).c_str(), "j1Phi; #phi of Leading Jet", 50, -3.0, 3.0);h_j1Phi[i]->Sumw2();
    h_j1etaWidth[i] = new TH1F(("j1etaWidth"+histname).c_str(),"j1etaWidh; #eta width of Leading Jet", 50,0,0.25);h_j1etaWidth[i] ->Sumw2();
    h_j1phiWidth[i] = new TH1F(("j1phiWidth"+histname).c_str(),"j1phiWidth; #phi width of Leading Jet", 50, 0,0.5);h_j1phiWidth[i]->Sumw2();
    h_j1nCons[i] = new TH1F (("j1nCons"+histname).c_str(),"j1nCons; Number of Constituents of Leading Jet",25, 0, 50);h_j1nCons[i]->Sumw2();
    h_PF123PtFraction[i]= new TH1F(("PF123PtFraction"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1.1);h_PF123PtFraction[i]->Sumw2(); 
    h_j1TotPFCands[i] = new TH1F(("j1TotPFCands"+histname).c_str(),"j1TotPFCands;# of all PF candidates in Leading Jet",25,0,50);h_j1TotPFCands[i]->Sumw2();
    h_j1ChPFCands[i] = new TH1F(("j1ChPFCands"+histname).c_str(),"j1ChPFCands;# of PF charged hadrons in Leading Jet",25,0,50);h_j1ChPFCands[i]->Sumw2();
    h_j1NeutPFCands[i] = new TH1F(("j1NeutPFCands"+histname).c_str(),"j1NeutPFCands;# of PF neutral hadrons in Leading Jet",15,0,15);h_j1NeutPFCands[i]->Sumw2();
    h_j1GammaPFCands[i] = new TH1F(("j1GammaPFCands"+histname).c_str(),"j1GammaPFCands;# of PF gammas in Leading Jet",20,0,40);h_j1GammaPFCands[i]->Sumw2();
    h_j1CHF[i] = new TH1F(("j1CHF"+histname).c_str(),"j1CHF;Charged Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1CHF[i]->Sumw2(); 
    h_j1NHF[i] = new TH1F(("j1NHF"+histname).c_str(),"j1NHF;Neutral Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1NHF[i]->Sumw2(); 
    h_j1ChMultiplicity[i] = new TH1F(("j1ChMultiplicity"+histname).c_str(),"j1ChMultiplicity;Charged Multiplicity of Leading Jet",25,0,50);h_j1ChMultiplicity[i]->Sumw2();
    h_j1NeutMultiplicity[i] = new TH1F(("j1NeutMultiplicity"+histname).c_str(),"j1NeutMultiplicity;Neutral Multiplicity of Leading Jet",25,0,50);h_j1NeutMultiplicity[i]->Sumw2(); 
    h_j1Mt[i]  = new TH1F(("j1Mt"+histname).c_str(), "j1Mt;M_{T} of Leading Jet (GeV)", 50,MtBins);h_j1Mt[i]->Sumw2(); 
    h_nVtx[i] = new TH1F(("nVtx"+histname).c_str(),"nVtx;nVtx",70,0,70);h_nVtx[i]->Sumw2();
  }
}

void ZprimeJetsClass2017::fillHistos(int histoNumber,double event_weight) {
  h_nVtx[histoNumber]->Fill(nVtx,event_weight);
  h_nJets[histoNumber]->Fill(nJet,event_weight);
  h_pfMETall[histoNumber]->Fill(pfMET,event_weight);
  h_pfMET200[histoNumber]->Fill(pfMET,event_weight);
  h_pfMET[histoNumber]->Fill(pfMET,event_weight);
  h_pfMETPhi[histoNumber]->Fill(pfMETPhi,event_weight);
  if(jetCand.size()>0){
    h_j1Pt[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
    h_j1Eta[histoNumber]->Fill(jetEta->at(jetCand[0]),event_weight);
    h_j1Phi[histoNumber]->Fill(jetPhi->at(jetCand[0]),event_weight);
    h_PF123PtFraction[histoNumber]->Fill(Pt123Fraction,event_weight);
    h_j1TotPFCands[histoNumber]->Fill(TotalPFCandidates,event_weight);
    h_j1ChPFCands[histoNumber]->Fill(ChargedPFCandidates,event_weight);
    h_j1NeutPFCands[histoNumber]->Fill(NeutralPFCandidates,event_weight);
    h_j1GammaPFCands[histoNumber]->Fill(GammaPFCandidates,event_weight);
    h_j1CHF[histoNumber]->Fill(jetCHF->at(jetCand[0]),event_weight);
    h_j1NHF[histoNumber]->Fill(jetNHF->at(jetCand[0]),event_weight);
    h_j1ChMultiplicity[histoNumber]->Fill(jetNCharged->at(jetCand[0]),event_weight);
    h_j1NeutMultiplicity[histoNumber]->Fill(jetNNeutral->at(jetCand[0]),event_weight);
    h_j1Mt[histoNumber]->Fill(jetMt->at(jetCand[0]),event_weight);
    h_j1etaWidth[histoNumber]->Fill(jetetaWidth->at(jetCand[0]),event_weight);
    h_j1phiWidth[histoNumber]->Fill(jetphiWidth->at(jetCand[0]),event_weight);
    h_j1nCons[histoNumber]->Fill(jetnPhotons->at(jetCand[0])+jetnCHPions->at(jetCand[0])+jetnMisc->at(jetCand[0]),event_weight);
  }
}

void ZprimeJetsClass2017::getPt123Frac() {
  double Pt123 = 0;
  for (int i = 0; i < j1PFConsPID.size(); i++)
    if (i < 3)
      Pt123 += j1PFConsPt.at(i);
  Pt123Fraction = Pt123/jetPt->at(jetCand[0]);
}

void ZprimeJetsClass2017::AllPFCand(vector<int> jetCand,vector<int> PFCandidates) {
  //getPFCandidatesMethod for the Pencil Jet -> jetCand[0]
  TotalPFCandidates=ChargedPFCandidates=NeutralPFCandidates=GammaPFCandidates=0;
  PFCandidates = getPFCandidates();
  //cout<<"Vector of Pairs should have size 4: "<<PFCandidates.size()<<endl;
  if(PFCandidates.size()>0)
    TotalPFCandidates=PFCandidates.at(0);
  //cout<<"TotalPFCandidates: "<<TotalPFCandidates<<endl;}

  if(PFCandidates.size()>1)
    ChargedPFCandidates=PFCandidates.at(1);
  //cout<<"TotalChargedPFCandidates: "<<ChargedPFCandidates<<endl;}
    
  if(PFCandidates.size()>2)
    GammaPFCandidates=PFCandidates.at(2);
  //cout<<"TotalGammaPFCandidates: "<<GammaPFCandidates<<endl;}

  if(PFCandidates.size()>3)
    NeutralPFCandidates=PFCandidates.at(3);
  //cout<<"TotalNeutralPFCandidates: "<<NeutralPFCandidates<<endl;}
    
  Pt123Fraction=0.0;
  //We are using these conditions so we only calculate the following quantities for the signal we are interested in
  //This will also make it faster to process the events
  if(jetCand.size()>0) {
    j1PFConsPt=jetConstPt->at(jetCand[0]);
    j1PFConsEta=jetConstEta->at(jetCand[0]);
    j1PFConsPhi=jetConstPhi->at(jetCand[0]);
    j1PFConsPID=jetConstPdgId->at(jetCand[0]);

    getPt123Frac();
  }
}

//Function to calculate regular deltaR separate from jet width variable 'dR'
double ZprimeJetsClass2017::deltaR(double eta1, double phi1, double eta2, double phi2) {
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
float ZprimeJetsClass2017::DeltaPhi(float phi1, float phi2) {
  float pi = TMath::Pi();
  float dphi = fabs(phi1-phi2);
  if(dphi>pi)
    dphi = 2.0*pi - dphi;
  return dphi;
}

float ZprimeJetsClass2017::dPhiJetMETmin(vector<int> jets) {
  float dPhimin=TMath::Pi();
  int njetsMax = jets.size();
  if(njetsMax > 4)
    njetsMax = 4;
  for(int j=0;j< njetsMax; j++)
    {
      float dPhi = DeltaPhi((*jetPhi)[j],pfMETPhi);
      //cout<<"DeltaPhi: "<<dPhi<<endl;
      if(dPhi < dPhimin){
        dPhimin = dPhi;
      }
    }
  return dPhimin;
}

vector<int> ZprimeJetsClass2017::getJetCand(double jetPtCut, double jetEtaCut, double jetNHFCut, double jetCHFCut) {
  vector<int> tmpCand;
  tmpCand.clear();
  for(int p=0;p<nJet;p++){
      bool kinematic = (*jetPt)[p] > jetPtCut && (*jetNHF)[p] < jetNHFCut && (*jetCHF)[p] > jetCHFCut && fabs((*jetEta)[p])<jetEtaCut;
      bool tightJetID = false;
      if ((*jetID)[p]>>0&1 == 1) tightJetID = true;
      if(kinematic && tightJetID)
        tmpCand.push_back(p);
    }
  return tmpCand;
}

vector<int> ZprimeJetsClass2017::JetVetoDecision() {
  vector<int> jetindex;
  for(int i = 0; i < nJet; i++){
    bool tightJetID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID)
      jetindex.push_back(i);
  }
  return jetindex;
}

//Return a vector of pairs. "0" = #pfCands, "1"=#chargedPFCands , "3"=#neutralPFCands,"2"=#photonPFCands
//get PF Candidates of the selected Jet ->jetCand[0]
vector<int>ZprimeJetsClass2017::getPFCandidates() {
  vector<int>PFCands;
  for(int i = 0;i < nJet; i++) {
    int TotPFCands;
    if(i == 0) {
      TotPFCands = j1PFConsPID.size();
      PFCands.push_back(TotPFCands);
      int ChPFCands,NeuPFCands,GammaPFCands;
      ChPFCands=NeuPFCands=GammaPFCands=0;
      for(int j=0;j<TotPFCands;j++) {
        if(abs(j1PFConsPID.at(j))==211)
          ChPFCands++;
        if(j1PFConsPID.at(j)==22)
          GammaPFCands++;
        if(j1PFConsPID.at(j)==130)
          NeuPFCands++;
      }
      PFCands.push_back(ChPFCands);
      PFCands.push_back(GammaPFCands);
      PFCands.push_back(NeuPFCands);
    }
  }
  return PFCands;
}
bool ZprimeJetsClass2017::btagVeto() {
  bool btagVeto = true;
  for(int i = 0; i < nJet; i++)
    if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && jetCSV2BJetTags->at(i) > 0.8838)
	btagVeto = false;
  return btagVeto;
}

bool ZprimeJetsClass2017::dPhiJetMETcut(vector<int> jets) {
  //reject jet if it is found within DeltaPhi(jet,MET) < 0.5 
  bool passes = false;
  int njetsMax = jets.size();
  //Only look at first four jets (because that's what monojet analysis do)
  if(njetsMax > 4)
    njetsMax = 4;
  int j = 0;
  for(; j < njetsMax; j++)
    if(DeltaPhi((*jetPhi)[j],pfMETPhi) < 0.5)
      break;
  if(j==njetsMax)
    passes = true;
  return passes;
}

bool ZprimeJetsClass2017::electron_veto_looseID(int jet_index, float elePtCut) {
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
bool ZprimeJetsClass2017::muon_veto_looseID(int jet_index, float muPtCut) {
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
