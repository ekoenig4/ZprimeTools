//For use with Ntuples made from JetAnalyzer
////Required arguments: 1 is folder containing input files, 2 is output file path, 3 is maxEvents (-1 to run over all events), 4 is reportEvery
////
////To compile using rootcom to an executable named 'analyze':
////$ ./rootcom ZprimeJetsClass_MC_WJets analyze
////
////To run, assuming this is compiled to an executable named 'analyze':
////$ ./analyze /hdfs/store/user/uhussain/Zprime_Ntuples/ /cms/uhussain/MonoZprimeJet/CMSSW_8_0_8/src/LightZPrimeAnalysis/JetAnalyzer/test/output.root -1 10000
////Runs over every event in the folder Zprime_Ntuples, reporting progress every 10000 events
////and storing the resulting histograms in the file output.root.
////
//
#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"
#include <TH2.h>
#include<TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TH1F.h"
#include <iostream>
#include <bitset>
#include <climits>
#include <cstring>
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TStopwatch.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <set>
#include <stdio.h> 
using namespace std;
using std::vector;

struct inclusive {
  bool isInclusive;
} sample;

int main(int argc, const char* argv[])
{ 
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
  string inclusiveSample = "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8";
  if (string(argv[1]).find(inclusiveSample) != string::npos) sample.isInclusive = true;
  else sample.isInclusive = false;
  ZprimeJetsClass t(argv[1],argv[2],argv[5]);
  
  t.Loop(maxEvents,reportEvery);
  return 0;
}

bool inclusiveCut(Float_t genHT) {
  if (sample.isInclusive)
    return genHT < 100;
  else
    return true;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery)
{
  if (fChain == 0) return;
  int nTotal;
  nTotal = 0;   
  // Book histograms for recording properties of leading jet that passes dR and MET cut
  // TFile* histFile = new TFile(file2, "RECREATE");
  // h_deltar = new TH1F("j1deltaR","j1deltaR; #DeltaR of Leading Jet",50,0,0.51);h_deltar->Sumw2();
  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in: "<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;   
  //jetCandidate that passes the basic pt,eta, NHF, CHF cuts
  jetCand.clear();

  vector<int> jetveto;
  jetveto.clear();

  double nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, ndilepton, nNoElectrons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = ndilepton = nNoElectrons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = 0;
  
  
  //getPFCandidates
  vector<int>PFCandidates;
 
  //This is the PU histogram obtained from Nick's recipe
  TFile *weights = TFile::Open("PU_Central.root");
  TH1D* PU = (TH1D*)weights->Get("pileup");

  //This is the root file with EWK Corrections
  TFile *file = new TFile("kfactors.root");
  TH1D *ewkCorrection = (TH1D*)file->Get("EWKcorr/W");
  TH1D *NNLOCorrection = (TH1D*)file->Get("WJets_LO/inv_pt");
  float dphimin=-99;
  //Event is rejected if it contains a HighPtMuon faking MET

  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  Long64_t nbytes = 0, nb = 0;
  cout<<"Running over "<<nTotal<<" events."<<endl;
  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    double event_weight=1.0;
    double EWK_corrected_weight=1.0;
    double NNLO_weight = 1.0;
    double kfactor = 1.0;
   
    //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
    //binContent as event_weight
    int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
    event_weight = PU->GetBinContent(bin);
    //    cout<<"event_weight: "<<event_weight<<endl;
    int bosonPID;
    double bosonPt;
    bool Wfound = false;
    //check which mc particle is W boson
    for(int i=0; i<nMC;i++){
      if((*mcPID)[i] == 24){
        Wfound=true;
        bosonPID = (*mcPID)[i];
        bosonPt = (*mcPt)[i];
      }
    }
    //if(Wfound){
    ////cout<<"bosonPID: "<<bosonPID<<endl;
    ////cout<<"bosonPt: "<<bosonPt<<endl;
    //}
    jetCand = getJetCand(200,2.5,0.8,0.1);
    float metcut= 0.0;
    //metcut = (fabs(pfMET-caloMET))/pfMET;
    AllPFCand(jetCand,PFCandidates);
    //CR Variables
    lepindex_leading = -1;
    lepindex_subleading = -1;
    dilepton_pt = dilepton_mass = Recoil=-99;
    nTotalEvents+=event_weight;
    if (metFilters==0 && inclusiveCut(genHT))
      {    
        nFilters+=event_weight;
        fillHistos(0,event_weight);
	//if ((HLTEleMuX>>4&1 == 1) || (HLTEleMuX>>38&1 == 1)) //"HLT_Ele27_WPTight_Gsf_v or HLT_Ele115_CaloIdVT_GsfTrkIdT_v"
	if (true) //"HLT_Ele27_WPTight_Gsf_v or HLT_Ele115_CaloIdVT_GsfTrkIdT_v"
	  {
	    nHLT+=event_weight;
	    fillHistos(1,event_weight);
	    if(jetCand.size()>0)
	      {
		nJetSelection+=event_weight;
		EWK_corrected_weight = 1.0*(ewkCorrection->GetBinContent(ewkCorrection->GetXaxis()->FindBin(bosonPt)));
		NNLO_weight = 1.0*(NNLOCorrection->GetBinContent(NNLOCorrection->GetXaxis()->FindBin(bosonPt)));
		if(EWK_corrected_weight!=0 && NNLO_weight!=0){
		  kfactor = (EWK_corrected_weight/NNLO_weight);}
		else{kfactor=1.21;}
		event_weight*=kfactor;
		//CR code
		//At least one of the two electrons passes the tight selection
		vector<int> mulist = muon_veto_looseID(jetCand[0],0,0,10.0);
		vector<int> mulist_leading = muon_veto_tightID(jetCand[0],20.0);
		vector<int> mulist_subleading = muon_veto_looseID(jetCand[0],0,0,10.0);
		vector<int> elelist;
		elelist.clear();
		if(mulist.size() == 2)
		  {
		    bool muPairSet = false;
		    bool subleading_passes_looseIso = false;
		    TLorentzVector m1, m2;                                                                                                                                                                                                               
		    for(int i=0; i<mulist_leading.size(); ++i)
		      {
			for(int j=0; j<mulist_subleading.size(); ++j)
			  {
			    //Event must have exactly two loose muons with opposite charge     
			    if(muCharge->at(mulist_leading[i])*muCharge->at(mulist_subleading[j]) == -1)
                              {
				m1.SetPtEtaPhiE(muPt->at(mulist_leading[i]),muEta->at(mulist_leading[i]),muPhi->at(mulist_leading[i]),muEn->at(mulist_leading[i]));
				m2.SetPtEtaPhiE(muPt->at(mulist_subleading[j]),muEta->at(mulist_subleading[j]),muPhi->at(mulist_subleading[j]),muEn->at(mulist_subleading[j]));
				elelist = electron_veto_looseID(jetCand[0],mulist_leading[i],mulist_subleading[j],10.0);
				jetveto = JetVetoDecision(mulist_leading[i],mulist_subleading[j]);
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
		    if(muPairSet && subleading_passes_looseIso)
                      { 
			TLorentzVector ll = m1+m2;
			dilepton_mass = ll.M();
			dilepton_pt = ll.Pt();
			TLorentzVector met_4vec;
			met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
			TLorentzVector leptoMET_4vec = ll+met_4vec;
			Double_t leptoMET = leptoMET_4vec.Pt();
			Double_t leptoMET_phi = leptoMET_4vec.Phi();
			nCRSelection+=event_weight;
			Recoil = leptoMET;
			metcut = (fabs(pfMET-caloMET))/Recoil;
			fillHistos(2,event_weight);
			if (leptoMET>250)
			  {
			    //leptoMET_phi_to_use = leptoMET_phi;
			    nMET200+=event_weight;
			    fillHistos(3,event_weight);
			    //invariant mass of the two electrons is betwen 60 and 120GeV
			    if(dilepton_mass > 60 && dilepton_mass < 120)
			      {
				ndilepton+=event_weight;
				fillHistos(4,event_weight);
				if(elelist.size() == 0)
				  {
				    nNoElectrons+=event_weight;
				    fillHistos(5,event_weight);
				    h_metcut->Fill(metcut,event_weight);
				    if(metcut<0.5)
				      {
					nMETcut+=event_weight;
					fillHistos(6,event_weight);
					if(btagVeto())
					  {
					    nbtagVeto+=event_weight;
					    fillHistos(7,event_weight);
					    double minDPhiJetMET = TMath::Pi();
					    double minDPhiJetMET_first4 = TMath::Pi();
					    for(int j = 0; j < jetveto.size(); j++)
					      {
						if(DeltaPhi(jetPhi->at(jetveto[j]),pfMETPhi) < minDPhiJetMET)
						  {
						    minDPhiJetMET = DeltaPhi(jetPhi->at(jetveto[j]),pfMETPhi);
						    if(j < 4){
						      minDPhiJetMET_first4 = DeltaPhi(jetPhi->at(jetveto[j]),pfMETPhi);}
						  } 
					      }
					    h_dphimin->Fill(minDPhiJetMET_first4,event_weight);	
					    if(dPhiJetMETcut(jetveto))
					      {
						nDphiJetMET+=event_weight;
						fillHistos(8,event_weight);
						if (Pt123Fraction > 0.6)
						  fillHistos(9,event_weight);
						if (Pt123Fraction > 0.7)
						  fillHistos(10,event_weight);
						if (Pt123Fraction > 0.75)
						  fillHistos(11,event_weight);
						if (Pt123Fraction > 0.8)
						  fillHistos(12,event_weight);
						if (Pt123Fraction > 0.85)
						  fillHistos(13,event_weight);
						if (Pt123Fraction > 0.9)
						  fillHistos(14,event_weight);
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
    
    if (jentry%reportEvery == 0)
      {
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
   
}//Closing the Loop function

void ZprimeJetsClass::BookHistos(const char* file2)
{
  fileName = new TFile(file2, "RECREATE");
  tree = new TTree("ZprimeJet","ZprimeJet");
  fileName->cd();
   
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

  float MtBins[51]={180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.,3000.};
  
  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float PtBins[49]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};
  
  float LeadingLeptonPtBins[25] = {20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  float subLeadingLeptonPtBins[26] = {10.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};
  
  h_metcut  = new TH1F("h_metcut","h_metcut; |pfMET-caloMET|/pfMET", 50,0,1.2);h_metcut->Sumw2();
  h_dphimin = new TH1F("h_dphimin","h_dphimin; Minimum dPhiJetMET",50,0,3.2);h_dphimin->Sumw2();
  for(int i=0; i<nHisto; i++){

    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    h_metFilters[i] = new TH1F(("metFilters"+histname).c_str(),"metFilters",50,0,3000); h_metFilters[i]->Sumw2();
    h_nJets[i]   = new TH1F(("nJets"+histname).c_str(), "nJets;Number of Jets", 16, 0, 16);h_nJets[i]->Sumw2();
    h_pfMETall[i] =  new TH1F(("pfMETall"+histname).c_str(), "pfMET",50,0,2000);h_pfMETall[i] ->Sumw2(); 
    h_pfMET200[i] = new TH1F(("pfMET200"+histname).c_str(), "pfMET",50,170,1500);h_pfMET200[i] ->Sumw2(); 
    h_pfMET[i] = new TH1F(("pfMET"+histname).c_str(), "E_{T}^{miss} (GeV)",44,MetBins);h_pfMET[i] ->Sumw2();
    h_pfMETPhi[i] = new TH1F(("pfMETPhi"+histname).c_str(), "pfMETPhi",50,-4,4);h_pfMETPhi[i]->Sumw2();
    h_j1Pt[i]  = new TH1F(("j1pT"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt[i]->Sumw2();
    h_j1Eta[i] = new TH1F(("j1Eta"+histname).c_str(), "j1Eta; #eta of Leading Jet", 50, -3.0,3.0);h_j1Eta[i]->Sumw2();
    h_j1Phi[i] = new TH1F(("j1Phi"+histname).c_str(), "j1Phi; #phi of Leading Jet", 50, -3.0, 3.0);h_j1Phi[i]->Sumw2();
    h_j1etaWidth[i] = new TH1F(("j1etaWidth"+histname).c_str(),"j1etaWidh; #eta width of Leading Jet", 50,0,0.25);h_j1etaWidth[i] ->Sumw2();
    h_j1phiWidth[i] = new TH1F(("j1phiWidth"+histname).c_str(),"j1phiWidth; #phi width of Leading Jet", 50, 0,0.5);h_j1phiWidth[i]->Sumw2();
    h_j1nCons[i] = new TH1F (("j1nCons"+histname).c_str(),"j1nCons; Number of Constituents of Leading Jet",25, 0, 50);h_j1nCons[i]->Sumw2();
    h_PF123PtFraction[i]= new TH1F(("PF123PtFraction"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction[i]->Sumw2();
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
    //CR Histograms
    h_leadingLeptonPt[i] = new TH1F(("h_leadingLeptonPt"+histname).c_str(),"h_leadingLeptonPt",24,LeadingLeptonPtBins);h_leadingLeptonPt[i]->Sumw2();
    h_leadingLeptonEta[i] = new TH1F(("h_leadingLeptonEta"+histname).c_str(),"h_leadingLeptonEta",30,-3.0,3.0);h_leadingLeptonEta[i]->Sumw2();
    h_leadingLeptonPhi[i] = new TH1F(("h_leadingLeptonPhi"+histname).c_str(),"h_leadingLeptonPhi",10,0.,3.1416);h_leadingLeptonPhi[i]->Sumw2();
    h_subleadingLeptonPt[i] = new TH1F(("h_subleadingLeptonPt"+histname).c_str(),"h_subleadingLeptonPt",25,subLeadingLeptonPtBins);h_subleadingLeptonPt[i]->Sumw2();
    h_subleadingLeptonEta[i] = new TH1F(("h_subleadingLeptonEta"+histname).c_str(),"h_subleadingLeptonEta",30,-3.0,3.0);h_subleadingLeptonEta[i]->Sumw2();
    h_subleadingLeptonPhi[i] = new TH1F(("h_subleadingLeptonPhi"+histname).c_str(),"h_subleadingLeptonPhi",10,0.,3.1416);h_subleadingLeptonPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
    h_dileptonPt[i] = new TH1F(("h_dileptonPt"+histname).c_str(),"h_dileptonPt",30,0.,1500.);h_dileptonPt[i]->Sumw2();
    h_dileptonM[i] = new TH1F(("h_dileptonM"+histname).c_str(),"h_dileptonM",24,60.,120.);h_dileptonM[i]->Sumw2();
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight)
{
  //event_weight not used because data's event_weight should be 1
  h_nVtx[histoNumber]->Fill(nVtx,event_weight);
  h_metFilters[histoNumber]->Fill(metFilters,event_weight);
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
    h_j1ChMultiplicity[histoNumber]->Fill(jetNCH->at(jetCand[0]),event_weight);
    h_j1NeutMultiplicity[histoNumber]->Fill(jetNNP->at(jetCand[0]),event_weight);
    h_j1Mt[histoNumber]->Fill(jetMt->at(jetCand[0]),event_weight);
    h_j1etaWidth[histoNumber]->Fill(jetetaWidth->at(jetCand[0]),event_weight);
    h_j1phiWidth[histoNumber]->Fill(jetphiWidth->at(jetCand[0]),event_weight);
    h_j1nCons[histoNumber]->Fill(jetnPhotons->at(jetCand[0])+jetnCHPions->at(jetCand[0])+jetnMisc->at(jetCand[0]),event_weight);
  }
  //CR Histograms
  if(lepindex_leading >= 0 && lepindex_subleading >= 0){ 
    h_leadingLeptonPt[histoNumber]->Fill(muPt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[histoNumber]->Fill(muEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[histoNumber]->Fill(muPhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[histoNumber]->Fill(muPt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[histoNumber]->Fill(muEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[histoNumber]->Fill(muPhi->at(lepindex_subleading),event_weight);}
  if(dilepton_pt >= 0 && dilepton_mass >= 0){
    h_recoil[histoNumber]->Fill(Recoil,event_weight);
    h_dileptonPt[histoNumber]->Fill(dilepton_pt,event_weight);
    h_dileptonM[histoNumber]->Fill(dilepton_mass,event_weight);}
}

void ZprimeJetsClass::getPt123Frac()
{
  double Pt123=0.;
  double jetPtAll=0.;
  for (int j = 0; j < j1PFConsPID.size(); j++)
    {
      jetPtAll+=j1PFConsPt.at(j);
      if (j < 3) Pt123+=j1PFConsPt.at(j);
    }
  Pt123Fraction=(Pt123/jetPt->at(jetCand[0]));
}

void ZprimeJetsClass::AllPFCand(vector<int> jetCand,vector<int> PFCandidates)
{
  //getPFCandidatesMethod for the Pencil Jet -> jetCand[0]
  TotalPFCandidates=ChargedPFCandidates=NeutralPFCandidates=GammaPFCandidates=0;
  PFCandidates = getPFCandidates();
  //cout<<"Vector of Pairs should have size 4: "<<PFCandidates.size()<<endl;
  if(PFCandidates.size()>0){
    TotalPFCandidates=PFCandidates.at(0);}
  //cout<<"TotalPFCandidates: "<<TotalPFCandidates<<endl;}

  if(PFCandidates.size()>1){
    ChargedPFCandidates=PFCandidates.at(1);}
  //cout<<"TotalChargedPFCandidates: "<<ChargedPFCandidates<<endl;}
    
  if(PFCandidates.size()>2){
    GammaPFCandidates=PFCandidates.at(2);}
  //cout<<"TotalGammaPFCandidates: "<<GammaPFCandidates<<endl;}

  if(PFCandidates.size()>3){
    NeutralPFCandidates=PFCandidates.at(3);}
  //cout<<"TotalNeutralPFCandidates: "<<NeutralPFCandidates<<endl;}
  
  Pt123Fraction=0.0;
  //We are using these conditions so we only calculate the following quantities for the signal we are interested in
  //This will also make it faster to process the events
  if(jetCand.size()>0){
    j1PFConsPt=JetsPFConsPt->at(jetCand[0]);
    j1PFConsEta=JetsPFConsEta->at(jetCand[0]);
    j1PFConsPhi=JetsPFConsPhi->at(jetCand[0]);
    j1PFConsPID=JetsPFConsPID->at(jetCand[0]);

    getPt123Frac();
  }
}

//Function to calculate regular deltaR separate from jet width variable 'dR'
double ZprimeJetsClass::deltaR(double eta1, double phi1, double eta2, double phi2)
{
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
float ZprimeJetsClass::DeltaPhi(float phi1, float phi2)
{
  float pi = TMath::Pi();
  float dphi = fabs(phi1-phi2);
  if(dphi>pi)
    dphi = 2.0*pi - dphi;
  return dphi;
}

float ZprimeJetsClass::dPhiJetMETmin(vector<int> jets)
{
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

vector<int> ZprimeJetsClass::getJetCand(double jetPtCut, double jetEtaCut, double jetNHFCut, double jetCHFCut){

  //save the Pt of the jetCand as well, whether normal, shiftedUp or shiftedDown 
  vector<int> tmpCand;
  tmpCand.clear();
  //So only check if leading candidate will pass these cuts?
  for(int p=0;p<nJet;p++)
    {
      bool kinematic = (*jetPt)[p] > jetPtCut && (*jetNHF)[p] < jetNHFCut && (*jetCHF)[p] > jetCHFCut && fabs((*jetEta)[p])<jetEtaCut;

      if((*jetPFLooseId)[p]==1 && kinematic){
	tmpCand.push_back(p);
      }
    }

  return tmpCand;
}

vector<int> ZprimeJetsClass::JetVetoDecision(int leading_lep_index, int subleading_lep_index) {

  bool jetVeto=true;
  vector<int> jetindex;

  for(int i = 0; i < nJet; i++)
    {
      double deltar_leading = deltaR(jetEta->at(i),jetPhi->at(i),muEta->at(leading_lep_index),muPhi->at(leading_lep_index));
      double deltar_subleading = deltaR(jetEta->at(i),jetPhi->at(i),muEta->at(subleading_lep_index),muPhi->at(subleading_lep_index));
      if(deltar_leading>0.4 && deltar_subleading>0.4 && jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && jetPFLooseId->at(i)==1)
        {
          jetindex.push_back(i);
        }
    }
  return jetindex;
}

//Return a vector of pairs. "0" = #pfCands, "1"=#chargedPFCands , "3"=#neutralPFCands,"2"=#photonPFCands
vector<int>ZprimeJetsClass::getPFCandidates(){
  vector<int>PFCands;
  for(int i=0;i<nJet;i++)
    {
      int TotPFCands;
      if(i==0){
	TotPFCands = j1PFConsPID.size();
	//cout<<TotPFCands<<endl;
	PFCands.push_back(TotPFCands);
	int ChPFCands,NeuPFCands,GammaPFCands;
	ChPFCands=NeuPFCands=GammaPFCands=0;
	for(int j=0;j<TotPFCands;j++){
	  if(abs(j1PFConsPID.at(j))==211){
	    ChPFCands++;
	  }
	  if(j1PFConsPID.at(j)==22){
	    GammaPFCands++;
	  }
	  if(j1PFConsPID.at(j)==130){
	    NeuPFCands++;
	  }
	}
	PFCands.push_back(ChPFCands);
	PFCands.push_back(GammaPFCands);
	PFCands.push_back(NeuPFCands);
      }
    }
  return PFCands;
}

bool ZprimeJetsClass::btagVeto() {

  bool btagVeto = true;
  for(int i = 0; i < nJet; i++)
    {
      if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && jetCSV2BJetTags->at(i) > 0.8484)
	btagVeto = false;
    }
  return btagVeto;
}

bool ZprimeJetsClass::dPhiJetMETcut(vector<int> jets)
{
  //reject jet if it is found within DeltaPhi(jet,MET) < 0.5 
  bool passes = false;
  
  int njetsMax = jets.size();
  //Only look at first four jets (because that's what monojet analysis do)
  if(njetsMax > 4)
    njetsMax = 4;
  int j=0;
  for(;j< njetsMax; j++){

    if(DeltaPhi((*jetPhi)[j],pfMETPhi) < 0.5)
      break;
  }

  if(j==njetsMax)
    passes = true;

  return passes;
  
}

vector<int> ZprimeJetsClass::electron_veto_tightID(int jet_index, float elePtCut)
{
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++)
    {
      //Electron passes Tight Electron ID cuts
      if(eleIDbit->at(i)>>3&1 == 1)
	{
	  //Electron passes eta cut
	  if(fabs(eleEta->at(i)) < 2.5) {
	    //Electron passes pt cut
	    if(elePt->at(i) > elePtCut)
	      {
		//Electron does not overlap photon
		if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
		  {
		    ele_cands.push_back(i);
		  }
	      }
	  }
	}
    }
  return ele_cands;
}

vector<int> ZprimeJetsClass::muon_veto_tightID(int jet_index, float muPtCut)
{
  // bool veto_passed = true; //pass veto if no good muon found
  vector<int> mu_cands;
  mu_cands.clear();

  bool pass_PFMuon = true;
  bool pass_globalMuon = true;
  // bool pass_trackerMuon = true;
  bool pass_chi2ndf = false;
  bool pass_chamberHit = false;
  bool pass_matchedStations = false;
  bool pass_dxy = false;
  bool pass_dz = false;
  bool pass_pixelHits = false;
  bool pass_trackLayers = false;
  bool pass_iso = false;
  //Explicitly stating types to avoid a TMath::Max conversion issue
  Float_t zero = 0.0;
  Float_t muPhoPU = 999.9;
  Float_t tightIso_combinedRelative = 999.9;
  for(int i = 0; i < nMu; i++)
    {
      // pass_globalMuon = muIsGlobalMuon->at(i);
      // pass_PFMuon = muIsPFMuon->at(i);
      // pass_trackerMuon = muIsTrackerMuon->at(i);
      pass_chi2ndf = muChi2NDF->at(i) < 10.0;
      pass_chamberHit = muMuonHits->at(i) > 0;
      pass_matchedStations = muStations->at(i) > 1;
      pass_dxy = fabs(muInnerD0->at(i)) < 0.2;
      pass_dz = fabs(muInnerDz->at(i)) < 0.5;
      pass_pixelHits = muPixelHits->at(i) > 0;
      pass_trackLayers = muTrkLayers->at(i) > 5;

      muPhoPU = muPFNeuIso->at(i) + muPFPhoIso->at(i) - 0.5*muPFPUIso->at(i);
      tightIso_combinedRelative = (muPFChIso->at(i) + TMath::Max(zero,muPhoPU))/(muPt->at(i));
      pass_iso = tightIso_combinedRelative < 0.15;
      //Muon passes Tight Muon ID
      // if(pass_iso && pass_globalMuon && pass_PFMuon && pass_chi2ndf && pass_chamberHit && pass_matchedStations && pass_dxy && pass_dz && pass_pixelHits && pass_trackLayers)
      if(pass_iso && muIDbit->at(i)>>2&1==1)
	{
	  //Muon passes eta cut
	  if (fabs(muEta->at(i)) < 2.4) {
	    //Muon passes pt cut
	    if(muPt->at(i) > muPtCut)
	      {
		//Muon does not overlap photon
		if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
		  {
		    mu_cands.push_back(i);
		  }
	      }
	  }
	}
    }
  return mu_cands;
}

vector<int> ZprimeJetsClass::electron_veto_looseID(int jet_index, int leading_mu_index, int subleading_mu_index, float elePtCut)
{
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++)
    {
      //Electron passes Loose Electron ID cuts
      if(eleIDbit->at(i)>>1&1 == 1)
	{
	  //Electron passes eta cut
	  if (fabs(eleEta->at(i)) < 2.5) {
	    //Electron passes pt cut
	    if(elePt->at(i) > elePtCut)
	      {
		//Electron does not overlap photon
		double dR_leading = deltaR(eleEta->at(i),elePhi->at(i),muEta->at(leading_mu_index),muPhi->at(leading_mu_index));
		double dR_subleading = deltaR(eleEta->at(i),elePhi->at(i),muEta->at(subleading_mu_index),muPhi->at(subleading_mu_index));
		if(dR_leading > 0.5 && dR_subleading > 0.5 && deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
		  {
		    ele_cands.push_back(i);
		  }
	      }
	  }
	}
    }
  return ele_cands;
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate photon within dR of 0.5
vector<int> ZprimeJetsClass::muon_veto_looseID(int jet_index, int leading_ele_index, int subleading_ele_index, float muPtCut)
{
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++)
    {
      if(muIDbit->at(i)>>0&1==1)
	{
	  //Muon passes eta cut
	  if (fabs(muEta->at(i)) < 2.4) {
	    //Muon passes pt cut
	    if(muPt->at(i) > muPtCut)
	      {
		//Muon does not overlap photon
		if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
		  {
		    mu_cands.push_back(i);
		  }
	      }
	  }
	}
    }
  return mu_cands;
}

