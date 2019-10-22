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
    argv[1] = "/hdfs/store/user/uhussain/Zprime_Ntuples_May2018/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/180528_145820/0000/";
    argv[2] = "test.root";
    argv[3] = "5000";
    argv[4] = "100";
    argv[5] = "1-1";
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

void ZprimeJetsClass::initVars() {
  ZprimeJetsCommon::initVars();
  lepindex = -1;
  lepton_pt = recoil = recoilPhi = -99;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  float nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, pfMET50, nNoMuons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = pfMET50 = nNoMuons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = 0;

  if (!sample.isData) SetScalingHistos();

  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  Long64_t nbytes = 0, nb = 0;
  cout<<"Running over "<<nTotal<<" events."<<endl;   
  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    initVars();

    float event_weight = 1.;
    if (!sample.isData) {
      ApplyPileup(event_weight);
      
      if (sample.isW_or_ZJet()) {
	SetBoson(sample.PID);
	ApplyKFactor(event_weight);
      }
    }

    float weightNorm = event_weight;
    jetCand   = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand);
    nTotalEvents+=genWeight;
    fillHistos(0,genWeight);
    for (int bit = 0; bit < 11; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metFilters->Fill(bit + 1,event_weight);
    
    if ((metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData) && inclusiveCut()) { 
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      
      if ((HLTEleMuX>>4&1 == 1) || (HLTEleMuX>>38&1 == 1) || (HLTPho>>7&1 ==1) || !sample.isData) {
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	
	if(jetCand.size()>0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  //CR code
	  //At least one of the one electrons passes the tight selection
	  vector<int> elelist = electron_veto_tightID(jetCand[0],40.0);
	  vector<int> looseEles = electron_veto_looseID(jetCand[0],10.0);
	  
	  if(elelist.size() == 1 && looseEles.size() == 1) {
	    lepindex = elelist[0];
                    
	    TLorentzVector lep_4vec;
	    lep_4vec.SetPtEtaPhiE(elePt->at(elelist[0]),eleSCEta->at(elelist[0]),eleSCPhi->at(elelist[0]),eleEn->at(elelist[0]));

	    lepton_pt = lep_4vec.Pt();
	    TLorentzVector met_4vec;
	    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	    TLorentzVector leptoMET_4vec = lep_4vec+met_4vec;
	    recoil = fabs(leptoMET_4vec.Pt());
	    recoilPhi = leptoMET_4vec.Phi();
	    nCRSelection+=event_weight;
	    fillHistos(4,event_weight);
	    
	    if (recoil>250) {
	      nMET200+=event_weight;
	      fillHistos(5,event_weight);
	      vector<int> mulist = muon_veto_looseID(jetCand[0],lepindex,10.0);
	      vector<int> pholist = photon_veto_looseID(jetCand[0],lepindex,15);
	      vector<int> taulist = tau_veto_looseID(jetCand[0],lepindex,18);
	      
	      if(mulist.size() == 0 && pholist.size() == 0 && taulist.size() == 0) {
		nNoMuons+=event_weight;
		fillHistos(6,event_weight);
		Float_t dPhi_lepMET = DeltaPhi(eleSCPhi->at(lepindex),pfMETPhi);
		Float_t lepMET_MT = sqrt(2*elePt->at(lepindex)*pfMET*(1-TMath::Cos(dPhi_lepMET)));
		h_lepMET_MT->Fill(lepMET_MT);
		
		if(pfMET > 50) {
		  pfMET50+=event_weight;
		  fillHistos(7,event_weight);
		  float metcut = (fabs(pfMET-caloMET))/recoil;
		  h_metcut->Fill(metcut);
		  
		  if(metcut<0.5) {
		    nMETcut+=event_weight;
		    fillHistos(8,event_weight);
		    
		    if(btagVeto()) {
		      nbtagVeto+=event_weight;
		      fillHistos(9,event_weight);
		      vector<int> jetveto = JetVetoDecision(jetCand[0],lepindex);
		      float minDPhiJetMET_first4 = TMath::Pi();
		      for (int i = 0; i < jetveto.size(); i++) {
			float dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),recoilPhi);
			if (dPhiJetMet < minDPhiJetMET_first4) {
			  if (i < 4)
			    minDPhiJetMET_first4 = dPhiJetMet;
			}
		      }
		      h_dphimin->Fill(minDPhiJetMET_first4);
		      
		      if(dPhiJetMETcut(jetveto,recoilPhi)) {
			nDphiJetMET+=event_weight;
			
			QCDVariations(event_weight); // 14 Histograms
			fillHistos(10,event_weight);

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

    JetEnergyScale(weightNorm); // 2 Histograms
    
    if (jentry%reportEvery == 0)
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
  }
  h_cutflow->SetBinContent(1,nTotalEvents); 
  h_cutflow->SetBinContent(2,nFilters);
  h_cutflow->SetBinContent(3,nHLT);
  h_cutflow->SetBinContent(4,nJetSelection);
  h_cutflow->SetBinContent(5,nCRSelection);
  h_cutflow->SetBinContent(6,nMET200);
  h_cutflow->SetBinContent(7,nNoMuons);
  h_cutflow->SetBinContent(8,pfMET50);
  h_cutflow->SetBinContent(9,nMETcut);
  h_cutflow->SetBinContent(10,nbtagVeto);
  h_cutflow->SetBinContent(11,nDphiJetMET);
  
}//Closing the Loop function

void ZprimeJetsClass::initTree(TTree* tree) {
  tree->Branch("weight",&weight);
  tree->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
  tree->Branch("h_recoil",&recoil,"Recoil (GeV)");
  tree->Branch("j1pT",&j1pT,"Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt",&ChNemPt,"Ch + NEM Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt123",&ChNemPt123,"Ch + NEM Leading Jet P^{123}_{T} (GeV)");
}

void ZprimeJetsClass::BookHistos(const char* outputFilename) {

  output = new TFile(outputFilename, "RECREATE");
  output->cd();
  
  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float LeptonPtBins[25] = {20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  h_cutflow = new TH1D("h_cutflow","h_cutflow",11,0,11);h_cutflow->Sumw2();
  h_cutflow->GetXaxis()->SetBinLabel(1,"Total Events");
  h_cutflow->GetXaxis()->SetBinLabel(2,"metFilters");
  h_cutflow->GetXaxis()->SetBinLabel(3,"Trigger");
  h_cutflow->GetXaxis()->SetBinLabel(4,"GoodJet");
  h_cutflow->GetXaxis()->SetBinLabel(5,"CRSelection"); 
  h_cutflow->GetXaxis()->SetBinLabel(6,"leptoMetCut");
  h_cutflow->GetXaxis()->SetBinLabel(7,"NoMuons");
  h_cutflow->GetXaxis()->SetBinLabel(8,"pfMET50");
  h_cutflow->GetXaxis()->SetBinLabel(9,"caloMET cut");
  h_cutflow->GetXaxis()->SetBinLabel(10,"B-JetVeto");
  h_cutflow->GetXaxis()->SetBinLabel(11,"DeltaPhiCut");
  
  h_lepMET_MT = new TH1F("h_lepMET_MT","h_lepMET_MT; transverse mass of the lepton-Emiss system",40,0,400);h_lepMET_MT->Sumw2();

  BookCommon(-1,"");
  for(int i = 0; i<nHisto; i++) {
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
    h_LeptonPt[i] = new TH1F(("h_LeptonPt"+histname).c_str(),"h_LeptonPt",24,LeptonPtBins);h_LeptonPt[i]->Sumw2();
    h_LeptonEta[i] = new TH1F(("h_LeptonEta"+histname).c_str(),"h_LeptonEta",30,-3.0,3.0);h_LeptonEta[i]->Sumw2();
    h_LeptonPhi[i] = new TH1F(("h_LeptonPhi"+histname).c_str(),"h_LeptonPhi",30,0.,3.1416);h_LeptonPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
  }
}

void ZprimeJetsClass::fillHistos(int nhist,float event_weight) {
  fillCommon(nhist,event_weight);
  //CR Histograms
  if(lepindex >= 0){ 
    h_LeptonPt[nhist]->Fill(elePt->at(lepindex),event_weight);
    h_LeptonEta[nhist]->Fill(eleSCEta->at(lepindex),event_weight);
    h_LeptonPhi[nhist]->Fill(eleSCPhi->at(lepindex),event_weight);
  }
  if(lepton_pt > 0){
    h_recoil[nhist]->Fill(recoil,event_weight);}
  weight = event_weight;
  if (nhist == bHisto) tree->Fill();
}

vector<int> ZprimeJetsClass::JetVetoDecision(int jet_index, int lepindex) {
  vector<int> jetindex; jetindex.clear();

  vector<int> tmpcands = ZprimeJetsCommon::JetVetoDecision();
  for(int ijet : tmpcands ) {
    float dR_ele = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if( dR_ele > 0.5 )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate electron and jet within dR of 0.5
vector<int> ZprimeJetsClass::muon_veto_looseID(int jet_index, int lepindex, float muPtCut)
{
  // cout << "Inside Muon Loose Veto" << endl;
  vector<int> mu_cands;
  mu_cands.clear();

  vector<int> tmpcands = ZprimeJetsCommon::muon_veto_looseID(jet_index,muPtCut);
  for(int imu : tmpcands) {
    float dR_ele = deltaR(muEta->at(imu),muPhi->at(imu),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if ( dR_ele > 0.5 )
      mu_cands.push_back(imu);
  }
  
  return mu_cands;
}

vector<int> ZprimeJetsClass::photon_veto_looseID(int jet_index,int lepindex,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = ZprimeJetsCommon::photon_veto_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_ele = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if ( dR_ele > 0.5 )
      pho_cands.push_back(ipho);
  }
  return pho_cands;
}

vector<int> ZprimeJetsClass::tau_veto_looseID(int jet_index,int lepindex,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = ZprimeJetsCommon::tau_veto_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_ele = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(lepindex),eleSCPhi->at(lepindex));
    if ( dR_ele > 0.5 )
      tau_cands.push_back(itau);
  }
  return tau_cands;
}
