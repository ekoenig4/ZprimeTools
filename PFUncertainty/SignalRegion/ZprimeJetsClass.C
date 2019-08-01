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

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nMET200, nMETcut,nLeptonIDs,nbtagVeto, nDphiJetMET,nJetSelection,eleHEMVeto,nTotalEvents_wPU;
  nTotalEvents = nFilters = nHLT = nMET200 = nMETcut = nLeptonIDs = nDphiJetMET = nbtagVeto = nJetSelection = eleHEMVeto = nTotalEvents_wPU = 0;
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
  cout<<"Running over "<<nTotal<<" events."<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentriesToCheck; sample.isData ? jentry += 4 : jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    jetCand     .clear();
    jetveto     .clear();
    PFCandidates.clear();
    j1PFConsEt  .clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();
    j1PFConsPtUnc.clear();

    TrackerCand.clear();
    EcalCand   .clear();
    HcalCand   .clear();

    double event_weight = 1.;
    double gen_weight = 1;
    noweight = 1;
    int bosonPID;
    double bosonPt;
    bool WorZfound = false;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      if (applyPU) {
	int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
	double pileup = PU->GetBinContent(bin);
	h_pileup->Fill(pileup);
	event_weight = pileup;
	gen_weight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;
	event_weight *= gen_weight;
	noweight *= gen_weight;
      }
      if(sample.isW_or_ZJet()) {
	//check which mc particle is W boson
	for(int i=0; i<nMC;i++){
	  if((*mcPID)[i] == sample.PID && mcStatusFlag->at(i)>>2&1 == 1){
	    WorZfound=true;
	    bosonPID = (*mcPID)[i];
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
	  }
	}
      }
    }
    float metcut = 0.0;

    jetveto = JetVetoDecision();
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand,PFCandidates);
    nTotalEvents+=gen_weight;
    fillHistos(0,event_weight);
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
	  if (sample.isW_or_ZJet()) {
	    double kfactor = getKfactor(bosonPt);
	    event_weight *= kfactor;
	    noweight *= kfactor;
	  }
	  if (pfMET > 250) {
	    nMET200+=event_weight;
	    fillHistos(4,event_weight);
	    metcut = (fabs(pfMET-caloMET)/pfMET);
	    h_metcut->Fill(metcut,event_weight);
	    if (metcut < 0.5) {
	      nMETcut+=event_weight;
	      fillHistos(5,event_weight);
	      if (electron_veto_looseID(jetCand[0],10.) && muon_veto_looseID(jetCand[0],10.)) {
		nLeptonIDs+=event_weight;
		fillHistos(6,event_weight);
		if (btagVeto()) {
		  nbtagVeto+=event_weight;
		  fillHistos(7,event_weight);
		  double minDPhiJetMET_first4 = TMath::Pi();
		  for (int i = 0; i < jetveto.size(); i++) {
		    double dPhiJetMet = DeltaPhi(jetPhi->at(jetveto[i]),pfMETPhi);
		    if (dPhiJetMet < minDPhiJetMET_first4) {
		      if (i < 4)
			minDPhiJetMET_first4 = dPhiJetMet;
		    }
		  }
		  h_dphimin->Fill(minDPhiJetMET_first4,event_weight);
		  if (dPhiJetMETcut(jetveto)) {
		    nDphiJetMET+=event_weight;
		    fillHistos(8,event_weight);
		    if (getEleHEMVeto(40)) {
		      eleHEMVeto+=event_weight;
		      fillHistos(9,event_weight);//norm
		      //   Trk ECAL HCAL
		      //up  12  13   14
		      //dn  15  16   17
		      int UncType[2] = {1,-1};
		      for (int i = 0; i < 2; i++) {
			getPt123Frac(Tracker,UncType[i]);
			fillHistos(12+3*i,event_weight);
			getPt123Frac(ECAL,UncType[i]);
			fillHistos(13+3*i,event_weight);
			getPt123Frac(HCAL,UncType[i]);
			fillHistos(14+3*i,event_weight);
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
  h_cutflow->SetBinContent(5,nMET200);
  h_cutflow->SetBinContent(6,nMETcut);
  h_cutflow->SetBinContent(7,nLeptonIDs);
  h_cutflow->SetBinContent(8,nbtagVeto);
  h_cutflow->SetBinContent(9,nDphiJetMET);
  h_cutflow->SetBinContent(10,eleHEMVeto);
}

void ZprimeJetsClass::BookHistos(const char* outputFilename) {
  
  output = new TFile(outputFilename, "RECREATE");
  tree = new TTree("ZprimeJet","ZprimeJet");
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
    BookCommon(i,histname);
    
    h_EcalPtUnc[i]=new TH2F(("EcalPtUnc"+histname).c_str(),"ECAL P_{T} Uncertainty;Photon P_{T} (GeV);Uncertainty",50,0.,2500.,50,0.,1.);
    h_TrackerPtUnc[i]=new TH2F(("TrackerPtUnc"+histname).c_str(),"Tracker P_{T} Uncertainty;Charged Hadrons P_{T} (GeV);Uncertainty",50,0.,2500.,50,0.,1.);
    h_HcalPtUnc[i]=new TH2F(("HcalPtUnc"+histname).c_str(),"HCAL P_{T} Uncertainty;Neutral Hadron P_{T} (GeV);Uncertainty",50,0.,2500.,50,0.,1.);
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight) {
  fillCommon(histoNumber,event_weight);
  
  for (int ID : TrackerCand)
    if (j1PFConsPt[ID] > 1)
      h_TrackerPtUnc[histoNumber]->Fill(j1PFConsPt[ID],j1PFConsPtUnc[ID]);
  for (int ID : EcalCand)
    if (j1PFConsPt[ID] > 1)
      h_EcalPtUnc[histoNumber]->Fill(j1PFConsPt[ID],j1PFConsPtUnc[ID]);
  for (int ID : HcalCand)
    if (j1PFConsPt[ID] > 1)
      h_HcalPtUnc[histoNumber]->Fill(j1PFConsPt[ID],j1PFConsPtUnc[ID]);
}

void ZprimeJetsClass::getPt123Frac(PFCons cons,int UncType) {
  Pt123Fraction=jetPtAll=Pt123=ChNemPt=ChNemPt123=ChNemPtFrac=0;
  for (int i = 0; i < 3; i++){
    hadronPt[i] = 0.;
  }
  // Neutral, Charged, Photon
  int HadronID[3] = {130,211,22};
  double HadronPtFirst3[3] = {0.,0.,0.};
  for (int i = 0; i < j1PFConsPID.size(); i++) {
    bool applyUnc = ( ( cons == Tracker && ( abs(j1PFConsPID[i]) == 221 || abs(j1PFConsPID[i]) == 13 ) ) ||
		      ( cons == ECAL && ( abs(j1PFConsPID[i]) == 22 || abs(j1PFConsPID[i]) == 11 ) ) ||
		      ( cons == HCAL && ( abs(j1PFConsPID[i]) == 130 ) )
		      ) ;
    double consPt = applyUnc ? j1PFConsPt[i]+UncType*j1PFConsPtUnc[i] : j1PFConsPt[i];
    jetPtAll += consPt;
    if (i < 3) Pt123 += consPt;
    for (int j = 0; j < 3; j++)
      if ( abs(j1PFConsPID[i]) == HadronID[j] ) {
	if (i < 3) HadronPtFirst3[j] += consPt;
	hadronPt[j] += consPt;
      }
  }
  Pt123Fraction = Pt123/jetPtAll;
  PtRawFrac = Pt123/jetRawPt->at(jetCand[0]);
  ChNemPtFrac = (HadronPtFirst3[1]+HadronPtFirst3[2])/(hadronPt[1]+hadronPt[2]);
  ChNemPt123 = HadronPtFirst3[1]+HadronPtFirst3[2];
  ChNemPt = hadronPt[1]+hadronPt[2];
}

void ZprimeJetsClass::AllPFCand(vector<int> jetCand,vector<int> PFCandidates) {
  //getPFCandidatesMethod for the Pencil Jet -> jetCand[0]
  TotalPFCandidates=ChargedPFCandidates=NeutralPFCandidates=GammaPFCandidates=0;
  
  //We are using these conditions so we only calculate the following quantities for the signal we are interested in
  //This will also make it faster to process the events
  if(jetCand.size()>0) {
    j1PFConsEt=jetConstEt->at(jetCand[0]);
    j1PFConsPt=jetConstPt->at(jetCand[0]);
    j1PFConsEta=jetConstEta->at(jetCand[0]);
    j1PFConsPhi=jetConstPhi->at(jetCand[0]);
    j1PFConsPID=jetConstPdgId->at(jetCand[0]);

    for(int i=0;i<j1PFConsPID.size();i++) {
      if (abs(j1PFConsPID.at(i)) == 211 || abs(j1PFConsPID.at(i)) == 13) {
	//Tracker Uncertainty
	//deltaPt=(1/100)*sqrt((0.015*Pt)^2+(0.5)^2)
	j1PFConsPtUnc.push_back((1/100.)*sqrt(pow(0.015*j1PFConsPt.at(i),2)+pow(0.5,2)));
	TrackerCand.push_back(i);
	//cout<<"T"<<TrackerCand[TrackerCand.size()-1]<<":"<<j1PFConsPtUnc[TrackerCand[TrackerCand.size()-1]]<<" ";
      }
      else if (abs(j1PFConsPID.at(i)) == 22 || abs(j1PFConsPID.at(i)) == 11) {
	//ECAL Uncertainty
	//deltaPt=(1/100)*sqrt((2.8)^2/Pt+(12.8/Pt)^2+(0.3)^2)
	j1PFConsPtUnc.push_back((1/100.)*sqrt(pow(2.8,2)/j1PFConsPt.at(i)+pow(12.8/j1PFConsPt.at(i),2)+pow(0.3,2)));
	EcalCand.push_back(i);
	//cout<<"E"<<EcalCand[EcalCand.size()-1]<<":"<<j1PFConsPtUnc[EcalCand[EcalCand.size()-1]]<<" ";
      }
      else if (abs(j1PFConsPID.at(i)) == 130) {
	//HCAL Uncertainty
	//deltaPt=(1/100)*sqrt((115)^2/Pt+(5.5)^2)
	j1PFConsPtUnc.push_back((1/100.)*sqrt(pow(115,2)/j1PFConsPt.at(i)+pow(5.5,2)));
	HcalCand.push_back(i);
	//cout<<"H"<<HcalCand[HcalCand.size()-1]<<":"<<j1PFConsPtUnc[HcalCand[HcalCand.size()-1]]<<" ";
      }
      else {
	j1PFConsPtUnc.push_back(0);
	//cout<<"N"<<i<<":"<<j1PFConsPtUnc[i]<<" ";
      }
    }

    PFCandidates = getPFCandidates();
    
    //cout<<"Vector of Pairs should have size 4: "<<PFCandidates.size()<<endl;
    if(PFCandidates.size()>0) {
      TotalPFCandidates=PFCandidates.at(0);
      // cout<<"TotalPFCandidates: "<<TotalPFCandidates<<endl;
    }
    
    if(PFCandidates.size()>1)
      ChargedPFCandidates=PFCandidates.at(1);
    //cout<<"TotalChargedPFCandidates: "<<ChargedPFCandidates<<endl;}
    
    if(PFCandidates.size()>2)
      GammaPFCandidates=PFCandidates.at(2);
    //cout<<"TotalGammaPFCandidates: "<<GammaPFCandidates<<endl;}
    
    if(PFCandidates.size()>3)
      NeutralPFCandidates=PFCandidates.at(3);
    //cout<<"TotalNeutralPFCandidates: "<<NeutralPFCandidates<<endl;}
    
    getPt123Frac(None,0);
  }
}

vector<int> ZprimeJetsClass::JetVetoDecision() {
  vector<int> jetindex;
  for(int i = 0; i < nJet; i++){
    bool tightJetID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID)
      jetindex.push_back(i);
  }
  return jetindex;
}

bool ZprimeJetsClass::electron_veto_looseID(int jet_index, float elePtCut) {
  bool veto_passed = true; //pass veto if no good electron found
  for(int i = 0; i < nEle; i++) {
    //Electron passes Loose Electron ID cuts
    if(eleIDbit->at(i)>>0&1 == 1) {
      //Electron passes eta cut
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
  for(int i = 0; i < nMu; i++) {
    if(muIDbit->at(i)>>0&1==1) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //cout <<"Passed Pt Cut" << endl;
	  //Muon does not overlap photon
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
