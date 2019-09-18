//For use with Ntuples made from JetAnalyzer
////Required arguments: 1 is folder containing input files, 2 is output file path, 3 is maxEvents (-1 to run over all events), 4 is reportEvery
////
////To compile using rootcom to an executable named 'analyze':
////$ ./rootcom ZprimeJetsClass analyze
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
using namespace std;
using std::vector;


int main(int argc, const char* argv[]) { 
  if (argc == 1) {
    printf("Running Test\n");
    argv[1] = "/hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1000/";
    argv[2] = "test.root";
    argv[3] = "-1";
    argv[4] = "100";
    argv[5] = "-1";
  }
  Long64_t maxEvents = atof(argv[3]);
  if (maxEvents < -1LL) {
    cout<<"Please enter a valid value for maxEvents (parameter 3)."<<endl;
    return 1;
  }
  int reportEvery = atof(argv[4]);
  if (reportEvery < 1) {
    cout<<"Please enter a valid value for reportEvery (parameter 4)."<<endl;
    return 1;
  }
  //const char* file2 = argv[2];
  ZprimeJetsClass t(argv[1],argv[2],argv[5]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nMET200, nMETcut,nLeptonIDs,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nMET200 = nMETcut = nLeptonIDs = nDphiJetMET = nbtagVeto = nJetSelection = 0;
  
  if (!sample.isData) {
    //This is the PU histogram obtained from Nick's recipe
    TFile *weights = TFile::Open("RootFiles/PU_Central.root");
    PU = (TH1D*)weights->Get("pileup");
    
    if (sample.isW_or_ZJet()) {
      //This is the root file with EWK Corrections
      TFile *file = new TFile("RootFiles/kfactors.root");
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
  Long64_t nbytes = 0, nb = 0;
  cout<<"Running over "<<nTotal<<" events."<<endl;
  for (Long64_t jentry=0; jentry<nentriesToCheck;) {
    if (sample.isData) jentry+=4;
    else               jentry++;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    jetCand     .clear();
    j1PFConsEt  .clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    double event_weight = 1.;
    double gen_weight = 1;
    noweight = 1;
    bosonPt = -99;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
      double pileup = PU->GetBinContent(bin);
      h_pileup->Fill(pileup);
      gen_weight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;

      event_weight = pileup*gen_weight;
      noweight = gen_weight;

      if (sample.isW_or_ZJet()) {
	for (int i = 0; i < nMC; i++) {
	  if((*mcPID)[i] == sample.PID && mcStatusFlag->at(i)>>2&1 == 1){
	    
	    double bosonPID = (*mcPID)[i];
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
	    break;
	  }
	}
      }
    }

    double weightNorm = event_weight;
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand);
    
    nTotalEvents+=gen_weight;
    fillHistos(0,gen_weight);
    for (int bit = 0; bit < 11; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metFilters->Fill(bit + 1,event_weight);
    
    if ( (metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData) && inclusiveCut() ) {    
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      
      if ((HLTJet>>4&1 == 1) || (HLTJet>>5&1 == 1) || (HLTJet>>6&1 == 1) || (HLTJet>>8&1 == 1) || !sample.isData) {//Mono-jet triggers
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	
	if(jetCand.size()>0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  
	  if (pfMET>250) {
	    nMET200+=event_weight;
	    fillHistos(4,event_weight);
	    double metcut = (fabs(pfMET-caloMET))/pfMET;
	    h_metcut->Fill(metcut);
	    
	    if(metcut<0.5) {
	      nMETcut+=event_weight;
	      fillHistos(5,event_weight);
	      
	      if(electron_veto_looseID(jetCand[0],10) &&  muon_veto_looseID(jetCand[0],10)) {
		nLeptonIDs+=event_weight;
		fillHistos(6,event_weight);
		
		if(btagVeto()) {
		  nbtagVeto+=event_weight;
		  fillHistos(7,event_weight);
		  vector<int> jetveto = JetVetoDecision();
		  double minDPhiJetMET_first4 = TMath::Pi();
		  for (int i = 0; i < jetveto.size(); i++) {
		    double dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
		    if (dPhiJetMet < minDPhiJetMET_first4) {
		      if (i < 4)
			minDPhiJetMET_first4 = dPhiJetMet;
		    }
		  }
		  h_dphimin->Fill(minDPhiJetMET_first4);
		  
		  if(dPhiJetMETcut(jetveto)) {
		    nDphiJetMET+=event_weight;

		    QCDVariations(event_weight);
		    fillHistos(8,event_weight);

		    PFUncertainty(event_weight);
		  }
		}   
	      }	
	    }
	  }
	}	    
      }
    }

    JetEnergyScale(weightNorm); // 2 Histograms
    
    if (jentry%reportEvery == 0)
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
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
   
}//Closing the Loop function

void ZprimeJetsClass::initTree(TTree* tree) {
  tree->Branch("weight",&weight);
  tree->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
  tree->Branch("recoil",&pfMET,"Recoil (GeV)");
}

void ZprimeJetsClass::BookHistos(const char* outputFilename) {
  
  output = new TFile(outputFilename, "RECREATE");
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
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight) {
  fillCommon(histoNumber,event_weight);
  weight = event_weight;
  if (histoNumber == bHisto) tree->Fill();
}



vector<int> ZprimeJetsClass::JetVetoDecision() {

  vector<int> jetindex;
  for(int i = 0; i < nJet; i++) {
    if (jetPt->at(i) < 30. && fabs(jetEta->at(i)) < 2.5 && jetPFLooseId->at(i)==1)
      jetindex.push_back(i);
  }
  return jetindex;
}

bool ZprimeJetsClass::electron_veto_looseID(int jet_index, float elePtCut) {
  bool veto_passed = true; //pass veto if no good electron found

  for(int i = 0; i < nEle; i++) {
    if(eleIDbit->at(i)>>1&1 == 1) {
      //Electron passes eat cut
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
  bool pass_iso = false;
                                                                                                                                                    
  Float_t zero = 0.0;
  Float_t muPhoPU = 999.9;
  Float_t tightIso_combinedRelative = 999.9;
    
  for(int i = 0; i < nMu; i++) {
    muPhoPU = muPFNeuIso->at(i) + muPFPhoIso->at(i) - 0.5*muPFPUIso->at(i);
    tightIso_combinedRelative = (muPFChIso->at(i) + TMath::Max(zero,muPhoPU))/(muPt->at(i));
    pass_iso = tightIso_combinedRelative < 0.25;
    if (fabs(muEta->at(i)) < 2.4) {
      if(muPt->at(i) > muPtCut) {
	if(pass_iso) {
	  //Muon does not overlap jet  
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
