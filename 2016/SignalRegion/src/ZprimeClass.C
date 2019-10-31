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
#define ZprimeClass_cxx
#include "ZprimeClass.h"

using namespace std;
using std::vector;


int main(int argc, const char* argv[]) { 
  if (argc == 1) {
    printf("Running Test\n");
    argv[1] = "/hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1000/";
    argv[2] = "test.root";
    argv[3] = "5";
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
  ZprimeClass t(argv[1],argv[2],argv[5]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

void ZprimeClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  float nTotalEvents,nFilters, nHLT, nMET200, nMETcut,nLeptonIDs,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nMET200 = nMETcut = nLeptonIDs = nDphiJetMET = nbtagVeto = nJetSelection = 0;
  
  if (!sample.isData) SetScalingHistos();
  
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

    initVars();

    float event_weight = 1.;
    if (!sample.isData) {
      ApplyPileup(event_weight);

      if (sample.isW_or_ZJet()) {
	SetBoson(event_weight);
	ApplyKFactor(event_weight);
      }
    }

    // float weightNorm = event_weight;
    jetCand = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
    SetJetPFInfo(jetCand);
    nTotalEvents+=genWeight;
    fillHistos(0,genWeight);
    for (int bit = 0; bit < 11; bit++)
      if ((metFilters >> bit & 1) == 1)
	h_metfilters->Fill(bit + 1,event_weight);
    
    if ( (metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData && inclusiveCut()) ) {    
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      
      if ( (HLTJet>>4&1) == 1 || (HLTJet>>5&1) == 1 || (HLTJet>>6&1) == 1 || (HLTJet>>8&1) == 1 || !sample.isData) {//Mono-jet triggers
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	
	if(jetCand.size()>0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  
	  if (pfMET > recoilCut) {
	    nMET200+=event_weight;
	    fillHistos(4,event_weight);
	    float metcut = (fabs(pfMET-caloMET))/pfMET;
	    h_metcut->Fill(metcut,event_weight);
	    
	    if(metcut < metRatioCut) {
	      nMETcut+=event_weight;
	      fillHistos(5,event_weight);

	      bool noLeptonID = electronVeto(jetCand[0],eleLoosePtCut) && muonVeto(jetCand[0],muLoosePtCut) && photonVeto(jetCand[0],phoLoosePtCut);
	      if( noLeptonID )  {
		nLeptonIDs+=event_weight;
		fillHistos(6,event_weight);
		
		if(btagVeto()) {
		  nbtagVeto+=event_weight;
		  fillHistos(7,event_weight);
		  vector<int> jetveto = JetVetoDecision();
		  float minDPhiJetMET_first4 = TMath::Pi();
		  for (unsigned int ijet = 0; ijet < jetveto.size(); ijet++) {
		    float dPhiJetMET = deltaPhi(jetPhi->at(jetveto[ijet]),recoilPhi);
		    if (dPhiJetMET < minDPhiJetMET_first4 && ijet < 4) minDPhiJetMET_first4 = dPhiJetMET;
		  }
		  h_dphimin->Fill(minDPhiJetMET_first4,event_weight);
		  
		  if(dPhiJetMET(jetveto,pfMETPhi)) {
		    nDphiJetMET+=event_weight;

		    // QCDVariations(event_weight);
		    fillHistos(8,event_weight);

		    // PFUncertainty(event_weight);
		  }
		}   
	      }	
	    }
	  }
	}	    
      }
    }

    // JetEnergyScale(weightNorm); // 2 Histograms
    
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

void ZprimeClass::BookHistos(const char* outputFilename) {
  
  output = new TFile(outputFilename, "RECREATE");
  output->cd();

  h_cutflow = new TH1F("h_cutflow","h_cutflow",9,0,9);h_cutflow->Sumw2();
  h_cutflow->GetXaxis()->SetBinLabel(1,"Total Events");
  h_cutflow->GetXaxis()->SetBinLabel(2,"metFilters");
  h_cutflow->GetXaxis()->SetBinLabel(3,"Trigger");
  h_cutflow->GetXaxis()->SetBinLabel(4,"GoodJet");
  h_cutflow->GetXaxis()->SetBinLabel(5,"MetCut");
  h_cutflow->GetXaxis()->SetBinLabel(6,"caloMET cut");
  h_cutflow->GetXaxis()->SetBinLabel(7,"LeptonIDs");
  h_cutflow->GetXaxis()->SetBinLabel(8,"B-JetVeto");
  h_cutflow->GetXaxis()->SetBinLabel(9,"DeltaPhiCut");
  
  ZprimeAnalysis::BookHistos(-1,"");
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
      scaleUncs.setTree(tree);
      shapeUncs.setDir(treedir);
      dir->cd();
    }
    //Common Histograms
    ZprimeYear::BookHistos(i,histname);
  }
}

void ZprimeClass::fillHistos(int nhist,float event_weight) {
  ZprimeYear::fillHistos(nhist,event_weight);
  weight = event_weight;
  if (nhist == bHisto) tree->Fill();
}



