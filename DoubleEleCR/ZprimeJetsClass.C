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
    argv[1] = "/hdfs/store/user/uhussain/Zprime_Ntuples_May2018/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT400to600/180528_150118/0000/";
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
bool ZprimeJetsCommon::DataMC::isW_or_ZJet() { return type == WJets || type == ZJets || type == DYJets; }
void ZprimeJetsClass::initVars() {
  ZprimeJetsCommon::initVars();

  lepindex_leading = lepindex_subleading = -1;
  dilepton_mass = dilepton_pt = recoil = recoilPhi = -99;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  float nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, ndilepton, nNoMuons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = ndilepton = nNoMuons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = 0;

  if (!sample.isData) SetScalingHistos();
  
  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  Long64_t nbytes = 0, nb = 0;
  cout<<"Running over "<<nTotal<<" events."<<endl;
  //  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry+=4) {    
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
    jetCand   = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
    AllPFCand(jetCand);
    nTotalEvents+=genWeight;
    fillHistos(0,genWeight);
    for (int bit = 0; bit < 11; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metFilters->Fill(bit + 1,event_weight);
    
    if ((metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData) && inclusiveCut()) { 
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      
      if ((HLTEleMuX>>4&1 == 1) || (HLTEleMuX>>38&1 == 1) || (HLTPho >>7&1 ==1) || !sample.isData) {
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	
	if(jetCand.size()>0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  //CR code
	  //At least one of the two electrons passes the tight selection
	  vector<int> elelist_leading = electron_veto_tightID(jetCand[0],eleTightPtCut);
	  vector<int> elelist_subleading = electron_veto_looseID(jetCand[0],eleLoosePtCut);
	  
	  if(elelist_subleading.size() == 2) {
	    bool elePairSet = false;
	    TLorentzVector e1, e2;
                    
	    for(int i=0; i<elelist_leading.size(); ++i) {
	      for(int j=0; j<elelist_subleading.size(); ++j) {
		//Event must have exactly two loose electrons with opposite charge
		if(eleCharge->at(elelist_leading[i])*eleCharge->at(elelist_subleading[j]) == -1)
		  {
		    e1.SetPtEtaPhiE(elePt->at(elelist_leading[i]),eleEta->at(elelist_leading[i]),elePhi->at(elelist_leading[i]),eleEn->at(elelist_leading[i]));
		    e2.SetPtEtaPhiE(elePt->at(elelist_subleading[j]),eleEta->at(elelist_subleading[j]),elePhi->at(elelist_subleading[j]),eleEn->at(elelist_subleading[j]));
		    elePairSet = true;
		    lepindex_leading = elelist_leading[i];
		    lepindex_subleading = elelist_subleading[j];
		    break;
		  }
	      }
	      if(elePairSet)
		break;
	    }
                    
	    if(elePairSet) { 
	      TLorentzVector ll = e1+e2;
	      dilepton_mass = ll.M();
	      dilepton_pt = ll.Pt();
                      
	      TLorentzVector met_4vec;
	      met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	      TLorentzVector leptoMET_4vec = ll+met_4vec;
	      recoil = fabs(leptoMET_4vec.Pt());
	      recoilPhi = leptoMET_4vec.Phi();
	      
	      nCRSelection+=event_weight;
	      fillHistos(4,event_weight);
	      
	      if (recoil > recoilCut) {
		nMET200+=event_weight;
		fillHistos(5,event_weight);
		//invariant mass of the two electrons is betwen 60 and 120GeV
		
		if(dilepton_mass > diLeptonMassCutLow && dilepton_mass < diLeptonMassCutHigh) {
		  ndilepton+=event_weight;
		  fillHistos(6,event_weight);
		  vector<int> mulist = muon_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,muLoosePtCut);
		  vector<int> pholist = photon_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,phoLoosePtCut);
		  // vector<int> taulist = tau_veto_looseID(jetCand[0],lepindex_leading,lepindex_subleading,tauLoosePtCut);
		  
		  if(mulist.size() == 0 && pholist.size() == 0) {
		    nNoMuons+=event_weight;
		    fillHistos(7,event_weight);
		    float metcut = (fabs(pfMET-caloMET))/recoil;
		    h_metcut->Fill(metcut,event_weight);
		    
		    if(metcut < metRatioCut) {
		      nMETcut+=event_weight;
		      fillHistos(8,event_weight);
		      
		      if(btagVeto()) {
			nbtagVeto+=event_weight;
			fillHistos(9,event_weight);
			vector<int> jetveto = JetVetoDecision(lepindex_leading,lepindex_subleading);
			float minDPhiJetMET_first4 = TMath::Pi();
			for (int ijet = 0; ijet < jetveto.size(); ijet++) {
			  float dPhiJetMET = DeltaPhi(jetPhi->at(jetveto[ijet]),recoilPhi);
			  if (dPhiJetMET < minDPhiJetMET_first4 && ijet < 4) minDPhiJetMET_first4 = dPhiJetMET;
			}
			h_dphimin->Fill(minDPhiJetMET_first4,event_weight);
			
			if(dPhiJetMETcut(jetveto,recoilPhi)) {
			  nDphiJetMET+=event_weight;
			  
			  QCDVariations(event_weight);
			  fillHistos(10,event_weight);

			  PFUncertainty(event_weight);
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

    JetEnergyScale(weightNorm);

    if (jentry%reportEvery == 0)
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
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

void ZprimeJetsClass::initTree(TTree* tree) {
  tree->Branch("weight",&weight);
  tree->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
  tree->Branch("recoil",&recoil,"Recoil (GeV)");
  tree->Branch("j1pT",&j1pT,"Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt",&ChNemPt,"Ch + NEM Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt123",&ChNemPt123,"Ch + NEM Leading Jet P^{123}_{T} (GeV)");
}

void ZprimeJetsClass::BookHistos(const char* outputFilename) {
  
  output = new TFile(outputFilename, "RECREATE");
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
    //CR Histograms
    h_leadingLeptonPt[i] = new TH1F(("h_leadingLeptonPt"+histname).c_str(),"h_leadingLeptonPt",24,LeadingLeptonPtBins);h_leadingLeptonPt[i]->Sumw2();
    h_leadingLeptonEta[i] = new TH1F(("h_leadingLeptonEta"+histname).c_str(),"h_leadingLeptonEta",30,-3.0,3.0);h_leadingLeptonEta[i]->Sumw2();
    h_leadingLeptonPhi[i] = new TH1F(("h_leadingLeptonPhi"+histname).c_str(),"h_leadingLeptonPhi",30,-3.1416,3.1416);h_leadingLeptonPhi[i]->Sumw2();
    h_subleadingLeptonPt[i] = new TH1F(("h_subleadingLeptonPt"+histname).c_str(),"h_subleadingLeptonPt",25,subLeadingLeptonPtBins);h_subleadingLeptonPt[i]->Sumw2();
    h_subleadingLeptonEta[i] = new TH1F(("h_subleadingLeptonEta"+histname).c_str(),"h_subleadingLeptonEta",30,-3.0,3.0);h_subleadingLeptonEta[i]->Sumw2();
    h_subleadingLeptonPhi[i] = new TH1F(("h_subleadingLeptonPhi"+histname).c_str(),"h_subleadingLeptonPhi",30,-3.1416,3.1416);h_subleadingLeptonPhi[i]->Sumw2();
    h_dileptonPt[i] = new TH1F(("h_dileptonPt"+histname).c_str(),"h_dileptonPt",30,0.,1500.);h_dileptonPt[i]->Sumw2();
    h_dileptonM[i] = new TH1F(("h_dileptonM"+histname).c_str(),"h_dileptonM",24,60.,120.);h_dileptonM[i]->Sumw2();
  }
}

void ZprimeJetsClass::fillHistos(int nhist,float event_weight) {
  fillCommon(nhist,event_weight);
  //CR Histograms
  if(lepindex_leading >= 0 && lepindex_subleading >= 0){ 
    h_leadingLeptonPt[nhist]->Fill(elePt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[nhist]->Fill(eleEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[nhist]->Fill(elePhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[nhist]->Fill(elePt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[nhist]->Fill(eleEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[nhist]->Fill(elePhi->at(lepindex_subleading),event_weight);}
  if(dilepton_pt >= 0 && dilepton_mass >= 0){  
    h_dileptonPt[nhist]->Fill(dilepton_pt,event_weight);
    h_dileptonM[nhist]->Fill(dilepton_mass,event_weight);}
  weight = event_weight;
  if (nhist == bHisto) tree->Fill();
}

vector<int> ZprimeJetsClass::JetVetoDecision(int leading, int subleading) {
  vector<int> jetindex; jetindex.clear();
			  
  vector<int> tmpcands = ZprimeJetsCommon::JetVetoDecision();
  for (int ijet : tmpcands) {
    float dR_leading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate electrons and jet within dR of 0.5
vector<int> ZprimeJetsClass::muon_veto_looseID(int jet_index, int leading, int subleading, float muPtCut) {
  vector<int> mu_cands;
  mu_cands.clear();
  
  vector<int> tmpcands = ZprimeJetsCommon::muon_veto_looseID(jet_index,muPtCut);
  for(int imu : tmpcands) {
    float dR_leading = deltaR(muEta->at(imu),muPhi->at(imu),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(muEta->at(imu),muPhi->at(imu),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut)
      mu_cands.push_back(imu);
  }
  
  return mu_cands;
}

vector<int> ZprimeJetsClass::photon_veto_looseID(int jet_index,int leading,int subleading,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = ZprimeJetsCommon::photon_veto_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_leading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      pho_cands.push_back(ipho);
  }
  return pho_cands;
}

vector<int> ZprimeJetsClass::tau_veto_looseID(int jet_index,int leading,int subleading,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = ZprimeJetsCommon::tau_veto_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_leading = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(leading),eleSCPhi->at(leading));
    float dR_subleading = deltaR(tauEta->at(itau),tauPhi->at(itau),eleSCEta->at(subleading),eleSCPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands;
}
