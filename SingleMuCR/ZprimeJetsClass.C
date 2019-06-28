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
  //const char* file2 = argv[2];

  ZprimeJetsClass t(argv[1],argv[2],argv[5]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

double ZprimeJetsClass::getKfactor(double bosonPt) {
  double EWK_corrected_weight = 1.0*(ewkCorrection->GetBinContent(ewkCorrection->GetXaxis()->FindBin(bosonPt)));
  double NNLO_weight = 1.0*(NNLOCorrection->GetBinContent(NNLOCorrection->GetXaxis()->FindBin(bosonPt)));
  double kfactor = 1;
  if(EWK_corrected_weight!=0 && NNLO_weight!=0)
    kfactor = (EWK_corrected_weight/NNLO_weight);
  else
    kfactor= sample.type == WJets ? 1.21 : 1.23;
  return kfactor;
}

bool ZprimeJetsClass::inclusiveCut() {
  if (sample.isInclusive)
    return genHT < 100;
  return true;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, lepMET_MT160, nNoElectrons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = lepMET_MT160 = nNoElectrons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = 0;
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
  Long64_t nbytes = 0, nb = 0;
  cout<<"Running over "<<nTotal<<" events."<<endl; 
  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry++) {
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
    int bosonPID;
    double bosonPt;
    bool WorZfound = false;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      if (applyPU) {
	int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
	event_weight = PU->GetBinContent(bin);
	//cout<<"event_weight: "<<event_weight<<endl;
        genWeight > 0.0 ? event_weight*=genWeight : event_weight =0.0;
      }
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
    
    jetCand   = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand,PFCandidates);
    //cout<<"|caloMET-pfMET|/pfMET: "<<metcut<<endl;
    //CR Variables
    lepindex = -1;
    nTotalEvents+=event_weight;
    fillHistos(0,event_weight);
    for (int bit = 0; bit < 11; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metFilters->Fill(bit + 1,event_weight);
    if ((metFilters==1536 && sample.isData) || (metFilters==0 && !sample.isData) && inclusiveCut()) { 
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      if ((HLTJet>>4&1 == 1) || (HLTJet>>5&1 == 1) || (HLTJet>>6&1 == 1) || (HLTJet>>8&1 == 1) || !sample.isData) {
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	if(jetCand.size()>0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  if (sample.isW_or_ZJet() && applyKF) event_weight *= getKfactor(bosonPt);
	  //CR code
	  //At least one of the one electrons passes the tight selection
	  vector<int> elelist;
	  elelist.clear();
	  vector<int> mulist = muon_veto_tightID(jetCand[0],20.0);
	  vector<int> looseMus = muon_veto_looseID(jetCand[0],0,10.0);
	  if(mulist.size() == 1 && looseMus.size() == 1) {
	    lepindex = mulist[0];
	    // cout<<"lepindex: "<<lepindex<<endl;
	    elelist = electron_veto_looseID(jetCand[0],lepindex,10.0);
	    jetveto = JetVetoDecision(jetCand[0],lepindex);
                              
	    TLorentzVector lep_4vec;
	    lep_4vec.SetPtEtaPhiE(muPt->at(lepindex),muEta->at(lepindex),muPhi->at(lepindex),muEn->at(lepindex));

	    lepton_pt = lep_4vec.Pt(); 
	    TLorentzVector met_4vec;
	    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	    TLorentzVector leptoMET_4vec = lep_4vec+met_4vec;
	    Double_t leptoMET = fabs(leptoMET_4vec.Pt());
	    Double_t leptoMET_phi = leptoMET_4vec.Phi();
	    nCRSelection+=event_weight;
	    Recoil = leptoMET;
	    metcut = (fabs(pfMET-caloMET))/Recoil;
	    fillHistos(4,event_weight);
	    if (leptoMET>250) {
	      nMET200+=event_weight;
	      fillHistos(5,event_weight);
	      if(elelist.size() == 0) {
		nNoElectrons+=event_weight;
		fillHistos(6,event_weight);
		Float_t dPhi_lepMET = DeltaPhi(muPhi->at(lepindex),pfMETPhi);
		Float_t lepMET_MT = sqrt(2*muPt->at(lepindex)*pfMET*(1-TMath::Cos(dPhi_lepMET)));
		h_lepMET_MT->Fill(lepMET_MT);
		if(lepMET_MT < 160) {
		  lepMET_MT160+=event_weight;
		  fillHistos(7,event_weight);
		  h_metcut->Fill(metcut);
		  if(metcut<0.5) {
		    nMETcut+=event_weight;
		    fillHistos(8,event_weight);
		    if(btagVeto()) {
		      nbtagVeto+=event_weight;
		      fillHistos(9,event_weight);
		      double minDPhiJetMET_first4 = TMath::Pi();
		      for (int i = 0; i < jetveto.size(); i++) {
			double dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
			if (dPhiJetMet < minDPhiJetMET_first4) {
			  if (i < 4)
			    minDPhiJetMET_first4 = dPhiJetMet;
			}
		      }
		      h_dphimin->Fill(minDPhiJetMET_first4);
		      if(dPhiJetMETcut(jetveto)){
			nDphiJetMET+=event_weight;
			fillHistos(10,event_weight);
			if (Pt123Fraction > 0.6)
			  fillHistos(11,event_weight);
			if (Pt123Fraction > 0.7)
			  fillHistos(12,event_weight);
			if (Pt123Fraction > 0.8)
			  fillHistos(13,event_weight);
			if (Pt123Fraction > 0.85)
			  fillHistos(14,event_weight);
			if (Pt123Fraction > 0.9)
			  fillHistos(15,event_weight);
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
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
  }
  h_cutflow->SetBinContent(1,nTotalEvents); 
  h_cutflow->SetBinContent(2,nFilters);
  h_cutflow->SetBinContent(3,nHLT);
  h_cutflow->SetBinContent(4,nJetSelection);
  h_cutflow->SetBinContent(5,nCRSelection);
  h_cutflow->SetBinContent(6,nMET200);
  h_cutflow->SetBinContent(7,nNoElectrons);
  h_cutflow->SetBinContent(8,lepMET_MT160);
  h_cutflow->SetBinContent(9,nMETcut);
  h_cutflow->SetBinContent(10,nbtagVeto);
  h_cutflow->SetBinContent(11,nDphiJetMET);
  
}//Closing the Loop function

void ZprimeJetsClass::BookRegion(int i,string histname) {
  fileName->cd();

  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float LeptonPtBins[25] = {20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  if (i == -1) {
    h_cutflow = new TH1D("h_cutflow","h_cutflow",11,0,11);h_cutflow->Sumw2();
    h_cutflow->GetXaxis()->SetBinLabel(1,"Total Events");
    h_cutflow->GetXaxis()->SetBinLabel(2,"metFilters");
    h_cutflow->GetXaxis()->SetBinLabel(3,"Trigger");
    h_cutflow->GetXaxis()->SetBinLabel(4,"GoodJet");
    h_cutflow->GetXaxis()->SetBinLabel(5,"CRSelection"); 
    h_cutflow->GetXaxis()->SetBinLabel(6,"leptoMetCut");
    h_cutflow->GetXaxis()->SetBinLabel(7,"NoElectrons");
    h_cutflow->GetXaxis()->SetBinLabel(8,"lepMT160");
    h_cutflow->GetXaxis()->SetBinLabel(9,"caloMET cut");
    h_cutflow->GetXaxis()->SetBinLabel(10,"B-JetVeto");
    h_cutflow->GetXaxis()->SetBinLabel(11,"DeltaPhiCut");
  
    h_lepMET_MT = new TH1F("h_lepMET_MT","h_lepMET_MT; transverse mass of the lepton-Emiss system",40,0,400);h_lepMET_MT->Sumw2();
  } else {
    //CR Histograms
    h_LeptonPt[i] = new TH1F(("h_LeptonPt"+histname).c_str(),"h_LeptonPt",24,LeptonPtBins);h_LeptonPt[i]->Sumw2();
    h_LeptonEta[i] = new TH1F(("h_LeptonEta"+histname).c_str(),"h_LeptonEta",30,-3.0,3.0);h_LeptonEta[i]->Sumw2();
    h_LeptonPhi[i] = new TH1F(("h_LeptonPhi"+histname).c_str(),"h_LeptonPhi",30,0.,3.1416);h_LeptonPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
  }
}

void ZprimeJetsClass::fillRegion(int histoNumber,double event_weight) {
  //CR Histograms
  if(lepindex >= 0){ 
    h_LeptonPt[histoNumber]->Fill(muPt->at(lepindex),event_weight);
    h_LeptonEta[histoNumber]->Fill(muEta->at(lepindex),event_weight);
    h_LeptonPhi[histoNumber]->Fill(muPhi->at(lepindex),event_weight);
  }
  if(lepton_pt > 0){
    h_recoil[histoNumber]->Fill(Recoil,event_weight);}
}

vector<int> ZprimeJetsClass::JetVetoDecision(int jet_index, int mu_index) {

  bool jetVeto=true;
  vector<int> jetindex;

  for(int i = 0; i < nJet; i++) {
    double deltar_mu = 0.0;
    deltar_mu = deltaR(jetEta->at(i),jetPhi->at(i),muEta->at(mu_index),muPhi->at(mu_index));
    if(deltar_mu>0.4 && jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && jetPFLooseId->at(i)==1)
      jetindex.push_back(i);
  }
  return jetindex;
}

vector<int> ZprimeJetsClass::electron_veto_tightID(int jet_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++) {
    //Electron passes Tight Electron ID cuts
    if(eleIDbit->at(i)>>3&1 == 1) {
      //Electron passes eta cut
      if(fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    ele_cands.push_back(i);
	}
      }
    }
  }
  return ele_cands;
}

vector<int> ZprimeJetsClass::muon_veto_tightID(int jet_index, float muPtCut) {
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
  for(int i = 0; i < nMu; i++) {
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
    if(pass_iso && muIDbit->at(i)>>2&1==1) {
      //Muon passes eta cut
      if(fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

vector<int> ZprimeJetsClass::electron_veto_looseID(int jet_index, int mu_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++) {
    //Electron passes Loose Electron ID cuts
    if(eleIDbit->at(i)>>1&1 == 1) {
      //Electrons passes eta cut
      if(fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    ele_cands.push_back(i);
	}
      }
    }
  }
  return ele_cands;
}



//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate photon within dR of 0.5
vector<int> ZprimeJetsClass::muon_veto_looseID(int jet_index, int ele_index, float muPtCut)
{
  // cout << "Inside Muon Loose Veto" << endl;
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>0&1==1) {
      //Muon passes eta cut
      if(fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  // cout <<"Passed Pt Cut" << endl;
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

