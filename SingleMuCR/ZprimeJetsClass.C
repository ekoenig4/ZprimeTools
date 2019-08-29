#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"
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
  ZprimeJetsClass t(argv[1],argv[2],argv[5]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

double ZprimeJetsClass::getSF(int mu_index) {
  double muEta_to_use = fabs(muEta->at(mu_index));
  double muPt_to_use = muPt->at(mu_index);
  if      (muPt_to_use >= 120)  muPt_to_use = 119.9;
  else if (muPt_to_use <= 20 )  muPt_to_use = 20.1;
  if      (muEta_to_use >= 2.4) muEta_to_use = 2.39;
  
  double tightMuISO_SF_corr = h_tightMuSF_ISO->GetBinContent(h_tightMuSF_ISO->GetXaxis()->FindBin(muPt_to_use),h_tightMuSF_ISO->GetYaxis()->FindBin(muEta_to_use));
  double tightMuID_SF_corr = h_tightMuSF_ID->GetBinContent(h_tightMuSF_ID->GetXaxis()->FindBin(muPt_to_use),h_tightMuSF_ID->GetYaxis()->FindBin(muEta_to_use));
  
  h_tightMuISO->Fill(tightMuISO_SF_corr);
  h_tightMuID->Fill(tightMuID_SF_corr);
  return tightMuISO_SF_corr*tightMuID_SF_corr;
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

  if (!sample.isData) {
    //This is the PU histogram obtained from Nick's recipe
    TFile *weights = TFile::Open("RootFiles/PU_Central.root");
    PU = (TH1D*)weights->Get("pileup");
    
    TFile *f_muSF_ISO = new TFile("RootFiles/RunBCDEF_SF_ISO.root");
    TFile *f_muSF_ID = new TFile("RootFiles/RunBCDEF_SF_ID.root");
    h_tightMuSF_ISO = (TH2F*)f_muSF_ISO->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");
    h_tightMuSF_ID = (TH2F*)f_muSF_ID->Get("NUM_TightID_DEN_genTracks_pt_abseta");
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
  cout<<"Running over "<<nTotal<<" events."<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    jetCand     .clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    double event_weight = 1.;
    double gen_weight = 1;
    double nokfactor = 1;
    noweight = 1;

    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      if (applyPU) {
	int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
	double pileup = PU->GetBinContent(bin);
	h_pileup->Fill(pileup);
	event_weight = pileup;
	nokfactor = pileup;
	gen_weight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;
	event_weight *= gen_weight;
	nokfactor *= gen_weight;
	noweight *= gen_weight;
      }
      if (sample.isW_or_ZJet()) {
	for (int i = 0; i < nMC; i++){
	  if((*mcPID)[i] == sample.PID && mcStatusFlag->at(i)>>2&1 == 1){
	    int bosonPID = (*mcPID)[i];
	    double bosonPt = (*mcPt)[i];
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
	  }
	}
      }
    }

    double weightNorm = event_weight;
    
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand);
    lepindex = -1;
    nTotalEvents+=gen_weight;
    fillHistos(0,gen_weight);
    
    if (metFilters == 0 && inclusiveCut()) {
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      
      if (HLTMet>>7&1 == 1 || HLTMet>>8&1 == 1 || HLTMet>>10&1 == 1 || !sample.isData) {
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	
	if (jetCand.size() > 0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  vector<int> mulist = muon_veto_tightID(jetCand[0],20.0);
	  vector<int> looseMu = muon_veto_looseID(jetCand[0],0,10.);
	  
	  if (mulist.size() ==1 && looseMu.size() == 1) {
	    nCRSelection+=event_weight;
	    fillHistos(4,event_weight);
	    lepindex = mulist[0];
	    if (!sample.isData && applySF) {
	      double sf = getSF(lepindex);
	      event_weight *= sf;
	      nokfactor *= sf;
	      noweight *= sf;
	    }
	    TLorentzVector lep_4vec;
	    lep_4vec.SetPtEtaPhiE(muPt->at(mulist[0]),muEta->at(mulist[0]),muPhi->at(mulist[0]),muE->at(mulist[0]));
	    lepton_pt = lep_4vec.Pt();
	    TLorentzVector met_4vec;
	    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	    TLorentzVector leptoMET_4vec = lep_4vec + met_4vec;
	    double leptoMET = fabs(leptoMET_4vec.Pt());
	    double leptoMETphi = leptoMET_4vec.Phi();
	    Recoil = leptoMET;
	    
	    if (leptoMET > 250) {
	      nMET200+=event_weight;
	      fillHistos(5,event_weight);
	      vector<int> elelist = electron_veto_looseID(jetCand[0],lepindex,10.);
	      
	      if (elelist.size() == 0) {
		nNoElectrons+=event_weight;
		fillHistos(6,event_weight);
		float dPhiLepMet = DeltaPhi(muPhi->at(lepindex),pfMETPhi);
		float lepMET_MT = sqrt(2*muPt->at(lepindex)*pfMET*(1-TMath::Cos(dPhiLepMet)));
		h_lepMET_MT->Fill(lepMET_MT);
		
		if (lepMET_MT < 160) {
		  lepMET_MT160+=event_weight;
		  fillHistos(7,event_weight);
		  double metcut = (fabs(pfMET-caloMET))/Recoil;
		  h_metcut->Fill(metcut);
		  
		  if (metcut < 0.5) {
		    nMETcut+=event_weight;
		    fillHistos(8,event_weight);
		    
		    if (btagVeto()) {
		      nbtagVeto+=event_weight;
		      fillHistos(9,event_weight);
		      vector<int> jetveto = JetVetoDecision(jetCand[0],lepindex);
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
			nDphiJetMET+=event_weight;
			fillHistos(10,event_weight);
			fillHistos(11,nokfactor);

			PFUncertainty(12,event_weight); // 6 Histograms
			EWKUncertainty(20,event_weight); // 2 Histograms
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

    JetEnergyScale(18,weightNorm); // 2 Histograms
    
    if (jentry%reportEvery == 0)
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck - 1)<<endl;
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
    h_cutflow->GetXaxis()->SetBinLabel(7,"NoElectrons");
    h_cutflow->GetXaxis()->SetBinLabel(8,"lepMET160");
    h_cutflow->GetXaxis()->SetBinLabel(9,"caloMET cut");
    h_cutflow->GetXaxis()->SetBinLabel(10,"B-JetVeto");
    h_cutflow->GetXaxis()->SetBinLabel(11,"DeltaPhiCut");
    
    h_lepMET_MT = new TH1F("h_lepMET_MT","h_lepMET_MT; transverse mass of the lepton-Emiss system",40,0,400);h_lepMET_MT->Sumw2();
    h_tightMuISO = new TH1F("h_tightMuISO","tightMuISO Scale Factor;tightMuISO Scale Factor",50,0.95,1.05); h_tightMuISO->Sumw2();
    h_tightMuID = new TH1F("h_tightMuID","tightMuID Scale Factor;tightMuID Scale Factor",50,0.95,1.05); h_tightMuID->Sumw2();
  
  BookCommon(-1,"");
  for(int i = 0; i<nHisto; i++){
    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    auto dir = output->mkdir( ("ZprimeJet"+histname).c_str() );
    dir->cd();
    if (i >= bHisto) {
      trees[i] = new TTree("tree","tree");
      trees[i]->Branch("weight",&weight);
      trees[i]->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
    }
    //Common Histograms
    BookCommon(i,histname);
    //CR Histograms
    h_LeptonPt[i] = new TH1F(("h_LeptonPt"+histname).c_str(),"h_LeptonPt",24,LeptonPtBins);h_LeptonPt[i]->Sumw2();
    h_LeptonEta[i] = new TH1F(("h_LeptonEta"+histname).c_str(),"h_LeptonEta",30,-3.0,3.0);h_LeptonEta[i]->Sumw2();
    h_LeptonPhi[i] = new TH1F(("h_LeptonPhi"+histname).c_str(),"h_LeptonPhi",50,-3.1416,3.1416);h_LeptonPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight) {
  fillCommon(histoNumber,event_weight);
  //CR Histograms
  if(lepindex >= 0){ 
    h_LeptonPt[histoNumber]->Fill(muPt->at(lepindex),event_weight);
    h_LeptonEta[histoNumber]->Fill(muEta->at(lepindex),event_weight);
    h_LeptonPhi[histoNumber]->Fill(muPhi->at(lepindex),event_weight);
  }
  if(lepton_pt > 0){
    h_recoil[histoNumber]->Fill(Recoil,event_weight);}
  weight = event_weight;
  if (histoNumber >= bHisto) trees[histoNumber]->Fill();
}

vector<int> ZprimeJetsClass::JetVetoDecision(int jet_index, int mu_index) {
  bool jetVeto=true;
  vector<int> jetindex;
  for(int i = 0; i < nJet; i++){
    double deltar_mu = deltaR(jetEta->at(i),jetPhi->at(i),muEta->at(mu_index),muPhi->at(mu_index));
    bool tightJetID = false;
    bool loosePUID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if((*jetPUFullID)[i]&(1<<2)) loosePUID=true;
    if(deltar_mu>0.4 && jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID && loosePUID)
      jetindex.push_back(i);
  }
  return jetindex;
}

vector<int> ZprimeJetsClass::electron_veto_tightID(int jet_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();
  for(int i = 0; i < nEle; i++) {
    //Electron passes Tight Electron ID cuts
    if(eleIDbit->at(i)>>2&1 == 1) {
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
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

  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>3&1 == 1 && muIDbit->at(i)>>9&1 == 1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
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
    if(eleIDbit->at(i)>>0&1 == 1) {
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
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
vector<int> ZprimeJetsClass::muon_veto_looseID(int jet_index, int ele_index, float muPtCut) {
  vector<int> mu_cands;
  mu_cands.clear();
  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>0&1==1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //cout <<"Passed Pt Cut" << endl;
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}
