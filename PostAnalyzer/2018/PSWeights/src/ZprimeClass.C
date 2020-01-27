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
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

void ZprimeClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  
  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  Long64_t nbytes = 0, nb = 0;
  cout<<"Running over "<<nTotal<<" events."<<endl;
  for (Long64_t jentry=0; jentry<nentriesToCheck; sample.isData ? jentry += 4 : jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    initVars();
    genWeight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;
 
    cutflow->Fill(0,genWeight);
    if ( MET_Filters() && inclusiveCut() ) {
      jetCand = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
      SetJetPFInfo(jetCand);
      if ( jetCand.size() > 0 ) {
	PSWeights(1);
	fillHistos(0,1);
      }
    }
    
    if (jentry%reportEvery == 0)
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
  }
   
}//Closing the Loop function

void ZprimeClass::BookHistos(const char* outputFilename) {
  output = new TFile(outputFilename, "RECREATE");
  output->cd();

  cutflow = new Cutflow({"Total Events"});
  
  for(int i = 0; i<nHisto; i++){
    if (i == bHisto) {
      auto treedir = gDirectory->mkdir("trees");
      treedir->cd();
      tree = new TTree("norm","norm");
      tree->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
      tree->Branch("genWeight",&genWeight);
      scaleUncs.setTree(tree);
      shapeUncs.setDir(treedir);
    }
  }
}

void ZprimeClass::fillHistos(int nhist,float event_weight) {
  weight = event_weight;
  if (nhist == bHisto) tree->Fill();
}

void ZprimeClass::PSWeights(float event_weight) {
  /* 44 Histograms
     up  dn
     isrRed        0   2
     fsrRed        1   3
     isrDef        4   6
     fsrDef        5   7
     isrCon        8  10 
     fsrCon        9  11
     fsr_G2GG_muR  12 13
     fsr_G2QQ_muR  14 15
     fsr_Q2QG_muR  16 17
     fsr_X2XG_muR  18 19
     fsr_G2GG_cNS  20 21
     fsr_G2QQ_cNS  22 23
     fsr_Q2QG_cNS  24 25
     fsr_X2XG_cNS  26 27 
     isr_G2GG_muR  28 29
     isr_G2QQ_muR  30 31
     isr_Q2QG_muR  32 33
     isr_X2XG_muR  34 35
     isr_G2GG_cNS  36 37
     isr_G2QQ_cNS  38 39
     isr_Q2QG_cNS  40 41
     isr_X2XG_cNS  42 43
  */
  
  string psw_uncs[22] = { "isrRed",   
			  "fsrRed",      
			  "isrDef",    
			  "fsrDef",  
			  "isrCon",
			  "fsrCon",      
			  "fsr_G2GG_muR",
			  "fsr_G2QQ_muR",
			  "fsr_Q2QG_muR",
			  "fsr_X2XG_muR",
			  "fsr_G2GG_cNS",
			  "fsr_G2QQ_cNS",
			  "fsr_Q2QG_cNS",
			  "fsr_X2XG_cNS",
			  "isr_G2GG_muR",
			  "isr_G2QQ_muR",
			  "isr_Q2QG_muR",
			  "isr_X2XG_muR",
			  "isr_G2GG_cNS",
			  "isr_G2QQ_cNS",
			  "isr_Q2QG_cNS",
			  "isr_X2XG_cNS"  };
  
  string uncname = "PSW_";
  // Initializing
  if ( !scaleUncs.contains(uncname+psw_uncs[0]) ) {
    for (int i = 0; i < 22; i++) {
      string name = uncname + psw_uncs[i];
      scaleUncs.addUnc(name,NULL);
    }
  }
  
  int nPS = 22;
  for (int i = 0; i < nPS; i++) {
    string name = uncname + psw_uncs[i];
    float weightUp = event_weight;
    float weightDn = event_weight;
    if ( !sample.isData && !sample.isSignal ) {
      if ( i < 2 ) {
	weightUp *= psWeight->at(2 + i);
	weightDn *= psWeight->at(2 + i + 2);
      } else if ( i < 4 ) {
	weightUp *= psWeight->at(2 + i + 2);
	weightDn *= psWeight->at(2 + i + 4);
      } else if ( i < 6 ) {
	weightUp *= psWeight->at(2 + i + 4);
	weightDn *= psWeight->at(2 + i + 6);
      } else {
	weightUp *= psWeight->at(2 + 2*i);
	weightDn *= psWeight->at(2 + 2*i + 1);
      }
    }
    scaleUncs.setUnc(name,weightUp,weightDn);
  }
}

void ZprimeClass::Init(TTree *tree) {
  psWeight = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain->SetBranchAddress("psWeight", &psWeight, &b_psWeight);
}
