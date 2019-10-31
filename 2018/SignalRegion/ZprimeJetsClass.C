#define ZprimeYear_cxx
#include "ZprimeYear.h"
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
    argv[1] = "/hdfs/store/user/varuns/monoZprimeMC2018/MonoZprime_V_Mx10_Mv100/";
    argv[2] = "test.root";
    argv[3] = "5000";
    argv[4] = "1000";
    argv[5] = "-1";
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
  ZprimeYear t(argv[1],argv[2],argv[5]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

void ZprimeYear::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  float nTotalEvents,nFilters, nHLT, nMET200, nMETcut,nLeptonIDs,nbtagVeto, nDphiJetMET,nJetSelection,eleHEMVeto;
  nTotalEvents = nFilters = nHLT = nMET200 = nMETcut = nLeptonIDs = nDphiJetMET = nbtagVeto = nJetSelection = eleHEMVeto = 0;

  if (!sample.isData) SetScalingHistos();

  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  cout<<"Running over "<<nTotal<<" events."<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentriesToCheck; sample.isData ? jentry += 4 : jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    initVars();

    float event_weight = 1.;
    
    if (!sample.isData) {
      ApplyPileup(event_weight);
      if(sample.isW_or_ZJet()) {
	SetBoson(sample.PID);
	ApplyKFactor(event_weight);
      }
    }

    float weightNorm = event_weight;

    jetCand = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
    SetJetPFInfo(jetCand[0]);
    nTotalEvents+=genWeight;
    fillHistos(0,genWeight);
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
	  
	  if (pfMET > recoilCut) {
	    nMET200+=event_weight;
	    fillHistos(4,event_weight);
	    float metcut = (fabs(pfMET-caloMET)/pfMET);
	    h_metcut->Fill(metcut,event_weight);
	    
	    if (metcut < metRatioCut) {
	      nMETcut+=event_weight;
	      fillHistos(5,event_weight);
	      
	      if (electronVeto(jetCand[0],eleLoosePtCut) && muonVeto(jetCand[0],muLoosePtCut) && photonVeto(jetCand[0],phoLoosePtCut) && tauVeto(jetCand[0],tauLoosePtCut)) {
		nLeptonIDs+=event_weight;
		fillHistos(6,event_weight);
		
		if (btagVeto()) {
		  nbtagVeto+=event_weight;
		  fillHistos(7,event_weight);
		  vector<int> jetveto = JetVetoDecision();
		  float minDPhiJetMET_first4 = TMath::Pi();
		  for (int i = 0; i < jetveto.size(); i++) {
		    float dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
		    if (dPhiJetMet < minDPhiJetMET_first4) {
		      if (i < 4)
			minDPhiJetMET_first4 = dPhiJetMet;
		    }
		  }
		  h_dphimin->Fill(minDPhiJetMET_first4,event_weight);
		  
		  if (dPhiJetMETcut(jetveto,pfMETPhi)) {
		    nDphiJetMET+=event_weight;
		    fillHistos(8,event_weight);
		    if (getEleHEMVeto(eleHEMVetoPtCut)) {
		      eleHEMVeto+=event_weight;

		      fillHistos(10,weight_QCDSF);
		      fillHistos(11,weight_16K);

		      // Use weight without genWeight applied
		      PSWeights(weight_nogen); // 44 Histograms
		      QCDVariations(event_weight);
		      fillHistos(9,event_weight);

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

    JetEnergyScale(weightNorm); // 2 Histograms
    
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
  h_cutflow->SetBinContent(10,eleHEMVeto);
}

void ZprimeYear::initTree(TTree* tree) {
  tree->Branch("weight",&weight);
  tree->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
  tree->Branch("h_recoil",&pfMET,"Recoil (GeV)");
  tree->Branch("j1pT",&j1pT,"Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt",&ChNemPt,"Ch + NEM Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt123",&ChNemPt123,"Ch + NEM Leading Jet P^{123}_{T} (GeV)");
}

void ZprimeYear::BookHistos(const char* outputFilename) {
  
  output = new TFile(outputFilename, "RECREATE");
  output->cd();

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
  h_cutflow->GetXaxis()->SetBinLabel(10,"EleHEMVeto");
  
  BookCommon(-1,"");
  for(int i = 0; i<nHisto; i++){
    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    //Common Histograms
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
    BookCommon(i,histname);
  }
}

void ZprimeYear::fillHistos(int histoNumber,float event_weight) {
  fillCommon(histoNumber,event_weight);
  weight = event_weight;
  if (histoNumber == bHisto) tree->Fill();
}
