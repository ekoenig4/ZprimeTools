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
  for (Long64_t jentry=0; jentry<nentriesToCheck; jentry++) {
    
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
	h_psWeights["norm"]->Fill(ChNemPtFrac,genWeight);
	for (string psw : pswlist) {
	  int iup = pswmap[psw].first; int idn = pswmap[psw].second;
	  h_psWeights[psw+"Up"]->Fill(ChNemPtFrac,psWeight->at(2+iup));
	  h_psWeights[psw+"Down"]->Fill(ChNemPtFrac,psWeight->at(2+idn));
	}
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
  string tmp[22] = { "isrRed","fsrRed","isrDef","fsrDef","isrCon","fsrCon",      
	      "fsr_G2GG_muR","fsr_G2QQ_muR","fsr_Q2QG_muR","fsr_X2XG_muR",
	      "fsr_G2GG_cNS","fsr_G2QQ_cNS","fsr_Q2QG_cNS","fsr_X2XG_cNS",
	      "isr_G2GG_muR","isr_G2QQ_muR","isr_Q2QG_muR","isr_X2XG_muR",
	      "isr_G2GG_cNS","isr_G2QQ_cNS","isr_Q2QG_cNS","isr_X2XG_cNS"  };
  
  int tmpindex[22][2] = {{0,2},{1,3},{4,6},{5,7},{8,10},{9,11},
			 {12,13},{14,15},{16,17},{18,19},
			 {20,21},{22,23},{24,25},{26,27},
			 {28,29},{30,31},{32,33},{34,35},
			 {36,37},{38,39},{40,41},{42,43}};
  h_psWeights["norm"] = new TH1F("norm","",15,0,1.1);
  for (int i = 0 ; i < 22; i++) {
    string psw = tmp[i];
    pswlist[i] = psw;
    pswmap[psw] = make_pair(tmpindex[i][0],tmpindex[i][1]);
    for (string var : {"Up","Down"}) {
      h_psWeights[psw+var] = new TH1F((psw+var).c_str(),"",15,0,1.1);
    }
  }
}

void ZprimeClass::fillHistos(int nhist,float event_weight) {
  
}

void ZprimeClass::Init(TTree *tree) {
  psWeight = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain->SetBranchAddress("psWeight", &psWeight, &b_psWeight);
}
