#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"
#include "fstream"

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

double EletriggerSF(float pt, float eta){
  double sf = 1.0;
  if(fabs(eta) >= 0.0   && fabs(eta) < 0.8){
    if(pt < 40.0) sf = 0.75;
    if(pt > 40.0 && pt < 50.0) sf = 0.92;
    if(pt > 50.0 && pt < 60.0) sf = 0.95;
    if(pt > 60.0 && pt < 70.0) sf = 0.96;
    if(pt > 70.0 && pt < 80.0) sf = 0.96;
    if(pt > 80.0 && pt < 90.0) sf = 0.97;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.97;
    if(pt > 150. && pt < 200.) sf = 0.97;
    if(pt > 200. && pt < 250.) sf = 0.98;
    if(pt > 250) sf = 0.93;
  }
  if(fabs(eta) >= 0.8   && fabs(eta) < 1.5){
    if(pt < 40.0) sf = 0.64;
    if(pt > 40.0 && pt < 50.0) sf = 0.91;
    if(pt > 50.0 && pt < 60.0) sf = 0.94;
    if(pt > 60.0 && pt < 70.0) sf = 0.95;
    if(pt > 70.0 && pt < 80.0) sf = 0.95;
    if(pt > 80.0 && pt < 90.0) sf = 0.96;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.96;
    if(pt > 150. && pt < 200.) sf = 0.96;
    if(pt > 200. && pt < 250.) sf = 0.97;
    if(pt > 250) sf = 1.0;
  }
    
  if(fabs(eta) >= 1.5   && fabs(eta) < 2. ) {
    if(pt < 40.0) sf = 0.63;
    if(pt > 40.0 && pt < 50.0) sf = 0.91;
    if(pt > 50.0 && pt < 60.0) sf = 0.94;
    if(pt > 60.0 && pt < 70.0) sf = 0.95;
    if(pt > 70.0 && pt < 80.0) sf = 0.95;
    if(pt > 80.0 && pt < 90.0) sf = 0.95;
    if(pt > 90.0 && pt < 100.) sf = 0.96;
    if(pt > 100. && pt < 150.) sf = 0.96;
    if(pt > 150. && pt < 200.) sf = 0.99;
    if(pt > 200. && pt < 250.) sf = 0.97;
    if(pt > 250) sf = 1.0;
  }
  if(fabs(eta) >= 2.) {
    if(pt < 40.0) sf = 0.5;
    if(pt > 40.0 && pt < 50.0) sf = 0.83;
    if(pt > 50.0 && pt < 60.0) sf = 0.89;
    if(pt > 60.0 && pt < 70.0) sf = 0.90;
    if(pt > 70.0 && pt < 80.0) sf = 0.92;
    if(pt > 80.0 && pt < 90.0) sf = 0.93;
    if(pt > 90.0 && pt < 100.) sf = 0.94;
    if(pt > 100. && pt < 150.) sf = 0.94;
    if(pt > 150. && pt < 200.) sf = 0.96;
    if(pt > 200. && pt < 250.) sf = 1.0;
    if(pt > 250) sf = 1.0;
  }
  return sf;
}

double ZprimeJetsClass::getSF(int ele_index) {
  double eleEta_to_use = fabs(eleEta->at(ele_index)) < 2.5 ? eleEta->at(ele_index) : 2.49;
  double elePt_to_use = elePt->at(ele_index) < 500 ? elePt->at(ele_index) : 499;
  double eleRecoSF_corr=h_eleRecoSF_highpt->GetBinContent(h_eleRecoSF_highpt->GetXaxis()->FindBin(eleEta_to_use),h_eleRecoSF_highpt->GetYaxis()->FindBin(elePt_to_use));
  // std::cout<<"eleRecoSF_corr =  "<< eleRecoSF_corr<<std::endl;
  double eleEffSF_corr=h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(eleEta_to_use),h_eleIDSF->GetYaxis()->FindBin(elePt_to_use));
  // std::cout<<"eleEffSF_corr =  "<< eleEffSF_corr<<std::endl;
  double eleTriggSF = EletriggerSF(elePt_to_use,eleEta_to_use);
  // cout<<"eleTriggSF = " << eleTriggSF << endl;
  return eleRecoSF_corr*eleEffSF_corr*eleTriggSF;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;
  
  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, pfMET50, nNoMuons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = pfMET50 = nNoMuons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = 0;
  vector<int> jetveto;
  vector<int> PFCandidates;
  float dphimin = -99;
  
  if (!sample.isData) {
    //This is the PU histogram obtained from Nick's recipe
    TFile *weights = TFile::Open("PU_Central.root");
    PU = (TH1D*)weights->Get("pileup");
    //This is the root file with EWK Corrections
    TFile *file = new TFile("kfactors.root");
    if (sample.type == ZJets || sample.type == DYJets) {
      ewkCorrection = (TH1D*)file->Get("EWKcorr/Z");
      NNLOCorrection = (TH1D*)file->Get("ZJets_LO/inv_pt");
    }
    if (sample.type == WJets) {
      ewkCorrection = (TH1D*)file->Get("EWKcorr/W");
      NNLOCorrection = (TH1D*)file->Get("WJets_LO/inv_pt");
    }

    TFile *f_eleReconstrucSF_highpt=new TFile("egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
    TFile *f_eleIDeffSF=new TFile("2017_ElectronTight.root");
    h_eleRecoSF_highpt=(TH2F*) f_eleReconstrucSF_highpt->Get("EGamma_SF2D");
    h_eleIDSF=(TH2F*) f_eleIDeffSF->Get("EGamma_SF2D");
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
    noweight = 1;
    int bosonPID;
    double bosonPt;
    bool found = false;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      if (applyPU) {
	int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
	event_weight = PU->GetBinContent(bin);
	double gen_weight = genWeight > 0. ? genWeight : 0;
	event_weight *= gen_weight;
	noweight *= gen_weight;
      }
      //cout<<"event_weight: "<<event_weight<<endl;
      if (sample.isW_or_ZJet())
	for (int i = 0; i < nMC; i++)
	  if ((*mcPID)[i] == sample.PID) {
	    found = true;
	    bosonPID = (*mcPID)[i];
	    bosonPt = (*mcPt)[i];
	  } 
    }
    float metcut = 0.0;

    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand,PFCandidates);
    lepindex = -1;
    nTotalEvents+=event_weight;
    fillHistos(0,event_weight);
    for (int bit = 0; bit < 8; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metFilters->Fill(bit + 1,event_weight);
    if (metFilters == 0 && inclusiveCut()) {
      nFilters+=event_weight;
      fillHistos(1,event_weight);
      if (HLTEleMuX>>5&1 == 1 || HLTEleMuX>>6&1 == 1 || HLTPho>>11&1 == 1 || !sample.isData) {
	nHLT+=event_weight;
	fillHistos(2,event_weight);
	if (jetCand.size() > 0) {
	  nJetSelection+=event_weight;
	  fillHistos(3,event_weight);
	  if (sample.isW_or_ZJet() && applyKF) {
	    double kfactor = getKfactor(bosonPt);
	    event_weight *= kfactor;
	    noweight *= kfactor;
	  }
	  vector<int> elelist = electron_veto_tightID(jetCand[0],40.);
	  vector<int> looseEle = electron_veto_looseID(jetCand[0],0,10.);
	  if (elelist.size() ==1 && looseEle.size() == 1) {
	    nCRSelection+=event_weight;
	    fillHistos(4,event_weight);
	    lepindex = elelist[0];
	    if (!sample.isData && applySF) {
	      double sf = getSF(elelist[0]);
	      event_weight *= sf;
	      noweight *= sf;
	    }
	    vector<int> mulist = muon_veto_looseID(jetCand[0],lepindex,10.);
	    jetveto = JetVetoDecision(jetCand[0],lepindex);
	    TLorentzVector lep_4vec;
	    lep_4vec.SetPtEtaPhiE(elePt->at(lepindex),eleEta->at(lepindex),elePhi->at(lepindex),eleE->at(lepindex));
	    lepton_pt = lep_4vec.Pt();
	    TLorentzVector met_4vec;
	    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	    TLorentzVector leptoMET_4vec = lep_4vec + met_4vec;
	    double leptoMET = fabs(leptoMET_4vec.Pt());
	    double leptoMETphi = leptoMET_4vec.Phi();
	    Recoil = leptoMET;
	    metcut = (fabs(pfMET-caloMET))/Recoil; //should be subtracted by caloMET
	    if (leptoMET > 250) {
	      nMET200+=event_weight;
	      fillHistos(5,event_weight);
	      if (mulist.size() == 0) {
		nNoMuons+=event_weight;
		fillHistos(6,event_weight);
		float dPhiLepMet = DeltaPhi(elePhi->at(lepindex),pfMETPhi);
		float lepMET_MT = sqrt(2*elePt->at(lepindex)*pfMET*(1-TMath::Cos(dPhiLepMet)));
		h_lepMET_MT->Fill(lepMET_MT);
		if (pfMET > 50) {
		  pfMET50+=event_weight;
		  fillHistos(7,event_weight);
		  h_metcut->Fill(metcut);
		  if (metcut < 0.5) {
		    nMETcut+=event_weight;
		    fillHistos(8,event_weight);
		    if (btagVeto()) {
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
		      if (dPhiJetMETcut(jetveto)) {
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
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck - 1)<<endl;
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
}

void ZprimeJetsClass::BookRegion(int i,string histname) {
  output->cd();
  
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
    h_cutflow->GetXaxis()->SetBinLabel(7,"NoMuons");
    h_cutflow->GetXaxis()->SetBinLabel(8,"pfMET50");
    h_cutflow->GetXaxis()->SetBinLabel(9,"caloMET cut");
    h_cutflow->GetXaxis()->SetBinLabel(10,"B-JetVeto");
    h_cutflow->GetXaxis()->SetBinLabel(11,"DeltaPhiCut");
  
    h_lepMET_MT = new TH1F("h_lepMET_MT","h_lepMET_MT; transverse mass of the lepton-Emiss system",40,0,400);h_lepMET_MT->Sumw2();
  } else {
    //CR Histograms
    h_LeptonPt[i] = new TH1F(("h_LeptonPt"+histname).c_str(),"h_LeptonPt",24,LeptonPtBins);h_LeptonPt[i]->Sumw2();
    h_LeptonEta[i] = new TH1F(("h_LeptonEta"+histname).c_str(),"h_LeptonEta",30,-3.0,3.0);h_LeptonEta[i]->Sumw2();
    h_LeptonPhi[i] = new TH1F(("h_LeptonPhi"+histname).c_str(),"h_LeptonPhi",50,-3.1416,3.1416);h_LeptonPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
  }
}

void ZprimeJetsClass::fillRegion(int histoNumber,double event_weight) {
  //CR Histograms
  if(lepindex >= 0){ 
    h_LeptonPt[histoNumber]->Fill(elePt->at(lepindex),event_weight);
    h_LeptonEta[histoNumber]->Fill(eleEta->at(lepindex),event_weight);
    h_LeptonPhi[histoNumber]->Fill(elePhi->at(lepindex),event_weight);
  }
  if(lepton_pt > 0){
    h_recoil[histoNumber]->Fill(Recoil,event_weight);}
}

vector<int> ZprimeJetsClass::JetVetoDecision(int jet_index, int ele_index) {
  bool jetVeto=true;
  vector<int> jetindex;
  for(int i = 0; i < nJet; i++){
    double deltar_ele = deltaR(jetEta->at(i),jetPhi->at(i),eleEta->at(ele_index),elePhi->at(ele_index));
    bool tightJetID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if(deltar_ele>0.4 && jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID)
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
      //Electron passes Eta cut
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
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5 && deltaR(muEta->at(i),muPhi->at(i),eleEta->at(ele_index),elePhi->at(ele_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}
