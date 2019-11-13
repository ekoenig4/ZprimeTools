#ifndef ZprimeAnalysis_C
#define ZprimeAnalysis_C

#include <stdexcept>

#include "ZprimeAnalysis.h"
#include "ZprimeCutConfig.h"
#include "ZprimeEnums.h"
#include "VariableBins.h"
#include "Utilities.h"

using namespace std;

void ZprimeAnalysis::SetScalingHistos() {
  //This is the PU histogram obtained from Nick's recipe
  TFile *weights = TFile::Open("RootFiles/PU_Central.root");
  TH1F* PU = (TH1F*)weights->Get("pileup");
  th1fmap["PU"] = PU;
}

void ZprimeAnalysis::initTree(TTree* tree) {
  tree->Branch("weight",&weight);
  tree->Branch("ChNemPtFrac",&ChNemPtFrac,"Ch + NEM P_{T}^{123} Fraction");
  tree->Branch("recoil",&recoil,"Recoil (GeV)");
  tree->Branch("j1pT",&j1pT,"Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt",&ChNemPt,"Ch + NEM Leading Jet P_{T} (GeV)");
  tree->Branch("ChNemPt123",&ChNemPt123,"Ch + NEM Leading Jet P^{123}_{T} (GeV)");
}

void ZprimeAnalysis::BookHistos(int i,string histname) {
  if (i == -1) {
    h_metcut  = new TH1F("h_metcut","h_metcut; |pfMET-caloMET|/pfMET", 50,0,1.2);h_metcut->Sumw2();
    h_dphimin = new TH1F("h_dphimin","h_dphimin; Minimum dPhiJetMET",50,0,3.2);h_dphimin->Sumw2();
    h_kfactor = new TH1F("h_kfactor","h_kfactor;kfactor",50,-2,2); h_kfactor->Sumw2();
    h_pileup = new TH1F("h_pileup","h_pileup;pileup",50,-2,2); h_pileup->Sumw2();
    h_genWeight = new TH1F("h_genWeight","h_genWeight;genWeight",50,-2,2); h_genWeight->Sumw2();
    h_sf = new TH1F("h_sf","h_sf;sf",50,-2,2); h_sf->Sumw2();
    h_bosonPt = new TH1F("h_bosonPt","bosonPt; boson P_{T}",24,BosonPtBins); h_bosonPt->Sumw2();
    h_bosonPtwK = new TH1F("h_bosonPtwK","bosonPtwK; kfactor boson P_{T}",24,BosonPtBins); h_bosonPtwK->Sumw2();
  } else {
    h_nVtx[i] = new TH1F(("nVtx"+histname).c_str(),"nVtx;nVtx",70,0,70);h_nVtx[i]->Sumw2(); 
    h_nVtx2[i] = new TH1F(("nVtx2"+histname).c_str(),"nVtx;nVtx",40,0,80);h_nVtx2[i]->Sumw2();
    h_puTrueNoW[i] = new TH1F( ("puTrueNoW"+histname).c_str(),"puTrue Unweighted;true number of iteractions",100,0,100);h_puTrueNoW[i]->Sumw2();
    h_puTrueReW[i] = new TH1F(("puTrueReW"+histname).c_str(),"puTrue Reweighted;true number of iteractions",100,0,100);h_puTrueReW[i]->Sumw2();
    h_eventWeight[i] = new TH1F(("eventWeight"+histname).c_str(),"eventWeight",50,0,2); h_eventWeight[i]->Sumw2();
    h_genHT[i] = new TH1F(("genHT"+histname).c_str(),"genHT;genHT",100,0,2500);h_genHT[i]->Sumw2();
    h_pfMETall[i] =  new TH1F(("pfMETall"+histname).c_str(), "pfMET",50,0,2000);h_pfMETall[i] ->Sumw2(); 
    h_pfMET200[i] = new TH1F(("pfMET200"+histname).c_str(), "pfMET",50,170,1500);h_pfMET200[i] ->Sumw2(); 
    h_pfMET[i] = new TH1F(("pfMET"+histname).c_str(), "E_{T}^{miss} (GeV)",44,MetBins);h_pfMET[i] ->Sumw2();
    h_pfMETPhi[i] = new TH1F(("pfMETPhi"+histname).c_str(), "pfMETPhi",50,-3.1516,3.1516);h_pfMETPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
    h_recoilPhi[i] = new TH1F(("recoilPhi"+histname).c_str(), "recoilPhi",50,-4,4);h_recoilPhi[i]->Sumw2();
    h_nJets[i]   = new TH1F(("nJets"+histname).c_str(), "nJets;Number of Jets", 50, 0, 100);h_nJets[i]->Sumw2();
    h_j1pT[i]  = new TH1F(("j1pT"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1pT[i]->Sumw2();
    h_j1Eta[i] = new TH1F(("j1Eta"+histname).c_str(), "j1Eta; #eta of Leading Jet", 50, -3.0, 3.0);h_j1Eta[i]->Sumw2();
    h_j1Phi[i] = new TH1F(("j1Phi"+histname).c_str(), "j1Phi; #phi of Leading Jet", 50, -3.0, 3.0);h_j1Phi[i]->Sumw2();
    h_j1etaWidth[i] = new TH1F(("j1etaWidth"+histname).c_str(),"j1etaWidth; #eta width of Leading Jet", 50,0,0.25);h_j1etaWidth[i] ->Sumw2();
    h_j1phiWidth[i] = new TH1F(("j1phiWidth"+histname).c_str(),"j1phiWidth; #phi width of Leading Jet", 50, 0,0.5);h_j1phiWidth[i]->Sumw2();
    h_j1CHF[i] = new TH1F(("j1CHF"+histname).c_str(),"j1CHF;Charged Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1CHF[i]->Sumw2(); 
    h_j1NHF[i] = new TH1F(("j1NHF"+histname).c_str(),"j1NHF;Neutral Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1NHF[i]->Sumw2(); 
    h_j1ChMult[i] = new TH1F(("j1ChMult"+histname).c_str(),"j1ChMult;Charged Mult of Leading Jet",25,0,50);h_j1ChMult[i]->Sumw2();
    h_j1NhMult[i] = new TH1F(("j1NhMult"+histname).c_str(),"j1NhMult;Neutral Mult of Leading Jet",25,0,50);h_j1NhMult[i]->Sumw2(); 
    h_j1Mt[i]  = new TH1F(("j1Mt"+histname).c_str(), "j1Mt;M_{T} of Leading Jet (GeV)", 50,MtBins);h_j1Mt[i]->Sumw2(); 
    h_j1TotPFCands[i] = new TH1F(("j1TotPFCands"+histname).c_str(),"j1TotPFCands;# of all PF candidates in Leading Jet",25,0,50);h_j1TotPFCands[i]->Sumw2();
    h_j1ChPFCands[i] = new TH1F(("j1ChPFCands"+histname).c_str(),"j1ChPFCands;# of PF charged hadrons in Leading Jet",25,0,50);h_j1ChPFCands[i]->Sumw2();
    h_j1NeutPFCands[i] = new TH1F(("j1NeutPFCands"+histname).c_str(),"j1NeutPFCands;# of PF neutral hadrons in Leading Jet",15,0,15);h_j1NeutPFCands[i]->Sumw2();
    h_j1GammaPFCands[i] = new TH1F(("j1GammaPFCands"+histname).c_str(),"j1GammaPFCands;# of PF gammas in Leading Jet",20,0,40);h_j1GammaPFCands[i]->Sumw2();
    h_j1MiscPFCands[i] = new TH1F(("j1MiscPFCands"+histname).c_str(),"j1MiscPFCands;# of PF gammas in Leading Jet",20,0,40);h_j1MiscPFCands[i]->Sumw2();
    h_Pt123[i] = new TH1F(("Pt123"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",58,Pt123Bins);h_Pt123[i]->Sumw2();
    h_Pt123Fraction[i]= new TH1F(("Pt123Fraction"+histname).c_str(), "Pt123Fraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_Pt123Fraction[i]->Sumw2(); 
    h_ChNemPtFrac[i] = new TH1F(("ChNemPtFrac"+histname).c_str(),"ChNemPtFrac;Ch + NEM P_{T}^{123} Fraction",50,0,1.1);h_ChNemPtFrac[i]->Sumw2();
    h_ChNemPt[i]  = new TH1F(("ChNemPt"+histname).c_str(), "ChNemPt;Ch + NEM Leading Jet P_{T} (GeV)", 58,Pt123Bins);h_ChNemPt[i]->Sumw2();
    h_ChNemPt123[i] = new TH1F(("ChNemPt123"+histname).c_str(),"ChNemPt123;Ch + NEM P^{123}_{T} (GeV)",58,Pt123Bins);h_ChNemPt123[i]->Sumw2();
    h_ChPercCons[i] = new TH1F(("ChPercCons"+histname).c_str(),"ChPercCons;Charged Hadron Constituent Percent",50,0,1.1);h_ChPercCons[i]->Sumw2();
    h_NhPercCons[i] = new TH1F(("NhPercCons"+histname).c_str(),"NhPercCons;Neutral Hadron Constituent Percent",50,0,1.1);h_NhPercCons[i]->Sumw2();
    h_GammaPercCons[i] = new TH1F(("GammaPercCons"+histname).c_str(),"GammaPercCons;Photon Constituent Percent",50,0,1.1);h_GammaPercCons[i]->Sumw2();
    h_MiscPercCons[i] = new TH1F(("MiscPercCons"+histname).c_str(),"MiscPercCons;Misc Constituent Percent",50,0,1.1);h_MiscPercCons[i]->Sumw2();
    h_ChargedPt[i] = new TH1F(("ChargedPt"+histname).c_str(),"ChargedPt;Charged Constituent P_{T}",58,Pt123Bins);h_ChargedPt[i]->Sumw2();
    h_NeutralPt[i] = new TH1F(("NeutralPt"+histname).c_str(),"NeutralPt;Neutral Constituent P_{T}",58,Pt123Bins);h_NeutralPt[i]->Sumw2();
    h_PhotonPt[i] = new TH1F(("PhotonPt"+histname).c_str(),"PhotonPt;Photon Constituent P_{T}",58,Pt123Bins);h_PhotonPt[i]->Sumw2();
    h_MiscPt[i] = new TH1F(("MiscPt"+histname).c_str(),"MiscPt;Misc Constituent P_{T}",58,Pt123Bins);h_MiscPt[i]->Sumw2();
    h_ChPercPt[i] = new TH1F(("ChPercPt"+histname).c_str(), "ChPercPt; Charged Constituent P_{T} Percentage" ,50,0,1.1);h_ChPercPt[i]->Sumw2();
    h_NhPercPt[i] = new TH1F(("NhPercPt"+histname).c_str(), "NhPercPt; Nharged Constituent P_{T} Percentage" ,50,0,1.1);h_NhPercPt[i]->Sumw2();
    h_GammaPercPt[i] = new TH1F(("GammaPercPt"+histname).c_str(), "GammaPercPt; Gamma Constituent P_{T} Percentage" ,50,0,1.1);h_GammaPercPt[i]->Sumw2();
    h_MiscPercPt[i] = new TH1F(("MiscPercPt"+histname).c_str(), "MiscPercPt; Misc Constituent P_{T} Percentage" ,50,0,1.1);h_MiscPercPt[i]->Sumw2();
  }
}

void ZprimeAnalysis::fillHistos(int nhist,float event_weight) {
  if (sample.isData) event_weight = 1;
  else {
    h_genHT[nhist]->Fill(genHT,event_weight);
    h_puTrueNoW[nhist]->Fill(puTrue->at(0),genWeight);
    h_puTrueReW[nhist]->Fill(puTrue->at(0),genWeight*pileup);
  }
  h_eventWeight[nhist]->Fill(event_weight,event_weight);
  h_nVtx[nhist]->Fill(nVtx,event_weight);
  h_nVtx2[nhist]->Fill(nVtx,event_weight);
  h_pfMETall[nhist]->Fill(pfMET,event_weight);
  h_pfMET200[nhist]->Fill(pfMET,event_weight);
  h_pfMET[nhist]->Fill(pfMET,event_weight);
  h_pfMETPhi[nhist]->Fill(pfMETPhi,event_weight);
  h_recoil[nhist]->Fill(recoil,event_weight);
  h_recoilPhi[nhist]->Fill(recoilPhi,event_weight);
  h_nJets[nhist]->Fill(nJet,event_weight);
  if (jetCand.size() > 0) {
    h_j1pT[nhist]->Fill(j1pT,event_weight);
    h_j1Eta[nhist]->Fill(jetEta->at(jetCand[0]),event_weight);
    h_j1Phi[nhist]->Fill(jetPhi->at(jetCand[0]),event_weight);
    h_j1etaWidth[nhist]->Fill(jetetaWidth->at(jetCand[0]),event_weight);
    h_j1phiWidth[nhist]->Fill(jetphiWidth->at(jetCand[0]),event_weight);
    h_j1CHF[nhist]->Fill(jetCHF->at(jetCand[0]),event_weight);
    h_j1NHF[nhist]->Fill(jetNHF->at(jetCand[0]),event_weight);
    h_j1ChMult[nhist]->Fill(jetNChargedHad->at(jetCand[0]),event_weight);
    h_j1NhMult[nhist]->Fill(jetNNeutralHad->at(jetCand[0]),event_weight);
    h_j1Mt[nhist]->Fill(jetMt->at(jetCand[0]),event_weight);
    h_j1TotPFCands[nhist]->Fill(TotalPFCands,event_weight);
    h_j1ChPFCands[nhist]->Fill(ChargedPFCands,event_weight);
    h_j1NeutPFCands[nhist]->Fill(NeutralPFCands,event_weight);
    h_j1GammaPFCands[nhist]->Fill(GammaPFCands,event_weight);
    h_j1MiscPFCands[nhist]->Fill(MiscPFCands,event_weight);
    h_Pt123[nhist]->Fill(Pt123,event_weight);
    h_Pt123Fraction[nhist]->Fill(Pt123Fraction,event_weight);
    h_ChNemPtFrac[nhist]->Fill(ChNemPtFrac,event_weight);
    h_ChNemPt[nhist]->Fill(ChNemPt,event_weight);
    h_ChNemPt123[nhist]->Fill(ChNemPt123,event_weight);
    h_ChPercCons[nhist]->Fill(ChargedPFCands/(float)TotalPFCands,event_weight);
    h_NhPercCons[nhist]->Fill(NeutralPFCands/(float)TotalPFCands,event_weight);
    h_GammaPercCons[nhist]->Fill(GammaPFCands/(float)TotalPFCands,event_weight);
    h_MiscPercCons[nhist]->Fill(MiscPFCands/(float)TotalPFCands,event_weight);
    h_ChargedPt[nhist]->Fill(pfHadronPt[0],event_weight);
    h_NeutralPt[nhist]->Fill(pfHadronPt[1],event_weight);
    h_PhotonPt[nhist]->Fill(pfHadronPt[2],event_weight);
    h_MiscPt[nhist]->Fill(pfHadronPt[3],event_weight);
    h_ChPercPt[nhist]->Fill( pfHadronPt[0]/j1pT ,event_weight);
    h_NhPercPt[nhist]->Fill( pfHadronPt[1]/j1pT ,event_weight);
    h_GammaPercPt[nhist]->Fill( pfHadronPt[2]/j1pT ,event_weight);
    h_MiscPercPt[nhist]->Fill( pfHadronPt[3]/j1pT ,event_weight);
  }
}

void ZprimeAnalysis::SetPtFrac() {
  Pt123Fraction=Pt123=ChNemPtFrac=ChNemPt=ChNemPt123=0.0;
  for (int i = 0; i < 4; i++){
    pfHadronPt[i] = 0.;
  }
  float first3_HadronPt[4] = {0,0,0,0};

  for (int i = 0; i < j1PFConsPID.size(); i++) {
    int absPID = abs(j1PFConsPID[i]);
    float consPt = j1PFConsPt[i];
    bool first3 = i < 3;
    if (first3) Pt123 += consPt;
    if ( absPID == Hadron::Charged ) {
      if (first3) first3_HadronPt[0] += consPt;
      pfHadronPt[0] += consPt;
    } else if ( absPID == Hadron::Neutral ) {
      if (first3) first3_HadronPt[1] += consPt;
      pfHadronPt[1] += consPt;
    } else if ( absPID == Hadron::Gamma ) {
      if (first3) first3_HadronPt[2] += consPt;
      pfHadronPt[2] += consPt;
    } else {
      if (first3) first3_HadronPt[3] += consPt;
      pfHadronPt[3] += consPt;
    }
  }
  Pt123Fraction = Pt123/j1pT;
  ChNemPt = pfHadronPt[0] + pfHadronPt[2];
  ChNemPt123 = first3_HadronPt[0] + first3_HadronPt[2];
  ChNemPtFrac = ChNemPt123/ChNemPt;
}

void ZprimeAnalysis::SetJetPFInfo(vector<int> jetCands) {
  if (jetCands.size() == 0) return;
  int jetCand = jetCands[0];
  j1pT = jetPt->at(jetCand);
  SetPFVectors(jetCand);

  TotalPFCands = ChargedPFCands = NeutralPFCands = GammaPFCands = MiscPFCands = 0;
  for (int PID : j1PFConsPID) {
    TotalPFCands++;
    if ( abs(PID) == Hadron::Charged )
      ChargedPFCands++;
    else if ( abs(PID) == Hadron::Neutral )
      NeutralPFCands++;
    else if ( abs(PID) == Hadron::Gamma )
      GammaPFCands++;
    else
      MiscPFCands++;
  }
  SetPtFrac();
}

void ZprimeAnalysis::SetPFVectors(int jetCand) {
  j1PFConsEt = jetConstEt->at(jetCand);
  j1PFConsPt = jetConstPt->at(jetCand);
  j1PFConsEta = jetConstEta->at(jetCand);
  j1PFConsPhi = jetConstPhi->at(jetCand);
  j1PFConsPID = jetConstPID->at(jetCand);
}


vector<int> ZprimeAnalysis::getJetCand(float jetPtCut, float jetEtaCut, float jetNHFCut, float jetCHFCut) {
  vector<int> tmpCand;
  tmpCand.clear();
  for(int p=0;p<nJet;p++){
    bool kinematic = (*jetPt)[p] > jetPtCut && (*jetNHF)[p] < jetNHFCut && (*jetCHF)[p] > jetCHFCut && fabs((*jetEta)[p])<jetEtaCut;
    bool jetID = jetSelectionID(p);
    if(kinematic && jetID) {
	tmpCand.push_back(p);
    }
  }
  return tmpCand;
}

float ZprimeAnalysis::dPhiJetMETmin(vector<int> jets,float metPhi) {
  //Only look at first four jets (because that's what monojet analysis do)
  int njets = jets.size() ? jets.size() < 4 : 4;
  float minDPhiJetMET_first4 = TMath::Pi();
  for (int ijet = 0; ijet < njets; ijet++) {
    float dPhiJetMET = deltaPhi(jetPhi->at(ijet),metPhi);
    if (dPhiJetMET < minDPhiJetMET_first4) minDPhiJetMET_first4 = dPhiJetMET;
  }
  return minDPhiJetMET_first4;
}

void ZprimeAnalysis::SetBoson(int PID) {
  bosonPt = 0;
  for (int i = 0; i < nMC; i++){
    if((*mcPID)[i] == PID && (mcStatusFlag->at(i)>>2&1) == 1){
      bosonPt = (*mcPt)[i];
      SetKFactors(bosonPt);

      h_bosonPt->Fill(bosonPt,genWeight);
      h_bosonPtwK->Fill(bosonPt,genWeight * kfactor);
    }
  }
}

void ZprimeAnalysis::SetKFactors(float bosonPt) {
  kfactor = getKFactor(bosonPt);
}

void ZprimeAnalysis::ApplyKFactor(float &event_weight) {
  h_kfactor->Fill(kfactor);
  event_weight *= kfactor;
  weight_nogen *= kfactor;
}

void ZprimeAnalysis::SetSF(float sf) {
  this->sf = sf;
}

void ZprimeAnalysis::ApplySF(float &event_weight) {
  h_sf->Fill(sf);
  event_weight *= sf;
  weight_nogen *= sf;
}

void ZprimeAnalysis::ApplyPileup(float &event_weight) {
  //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
  //binContent as event_weight
  pileup = th1fmap.getBin("PU",puTrue->at(0));
  genWeight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;
  event_weight *= pileup * genWeight;
  weight_nogen *= pileup;
  h_pileup->Fill(pileup);
  h_genWeight->Fill(genWeight);
}

bool ZprimeAnalysis::isW_or_ZJet() { return sample.type == WJets || sample.type == ZJets; }

bool ZprimeAnalysis::inclusiveCut() {
  if (sample.isInclusive)
    return genHT < 100;
  return true;
}

void ZprimeAnalysis::initVars() {
  jetCand     .clear();
  j1PFConsPt  .clear();
  j1PFConsEta .clear();
  j1PFConsPhi .clear();
  j1PFConsPID .clear();

  if(sample.isData) {
    // genWeight is used for the total events rather than event_weight since it has pileup and kfactors applied at the beginning
    // data doesn't have genWeight so set it to 1
    genWeight = 1;
  }

  weight = weight_nogen = kfactor = pileup = sf = 1;

  bosonPt = Pt123Fraction = Pt123 = j1pT = -99;
  ChNemPtFrac = ChNemPt = ChNemPt123 = -99;
  TotalPFCands = ChargedPFCands = NeutralPFCands = GammaPFCands = MiscPFCands = -99;
  for (int i = 0; i < 4; i++) {
    pfHadronPt[i] = -99;
  }
  recoil = pfMET;
  recoilPhi = pfMETPhi;
}

vector<int> ZprimeAnalysis::electron_tightID(int jet_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++) {
    //Electron passes Tight Electron ID cuts
    if(eleTightID(i)) {
      //Electron passes Eta cut
      if (fabs(eleSCEta->at(i)) < eleTightEtaCut) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleSCEta->at(i),eleSCPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso5Cut) {
	    
	    //Ele DZ and D0 selection
	    if ((fabs(eleSCEta->at(i)) <= eleEtaCutLow) && (fabs(eleD0->at(i)) < eleD0CutLow) && (fabs(eleDz->at(i)) < eleDzCutLow )) {
	      ele_cands.push_back(i);
	    }
	    else if( (fabs(eleSCEta->at(i)) > eleEtaCutHigh) && (fabs(eleD0->at(i)) < eleD0CutHigh) && (fabs(eleDz->at(i)) < eleDzCutHigh )){
	      ele_cands.push_back(i);
	    }
	  }
	}
      }
    }
  }
  return ele_cands;
}

vector<int> ZprimeAnalysis::electron_looseID(int jet_index, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++) {
    //Electron passes Loose Electron ID cuts
    if(eleLooseID(i)) {
      //Electron passes eta cut
      if (fabs(eleSCEta->at(i)) < eleLooseEtaCut) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut) {
	  //Electron does not overlap photon
	  if(deltaR(eleSCEta->at(i),eleSCPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso5Cut) {
	    
	    //Ele DZ and D0 selection
	    if ((fabs(eleSCEta->at(i)) <= eleEtaCutLow) && (fabs(eleD0->at(i)) < eleD0CutLow) && (fabs(eleDz->at(i)) < eleDzCutLow )) {
	      ele_cands.push_back(i);
	    }
	    else if( (fabs(eleSCEta->at(i)) > eleEtaCutHigh) && (fabs(eleD0->at(i)) < eleD0CutHigh) && (fabs(eleDz->at(i)) < eleDzCutHigh )){
	      ele_cands.push_back(i);
	    }
	  }
	}
      }
    }
  }
  return ele_cands;
}

bool ZprimeAnalysis::electron_veto(int jet_index,float elePtCut) {
  return electron_looseID(jet_index,elePtCut).size() == 0;
}


vector<int> ZprimeAnalysis::muon_tightID(int jet_index, float muPtCut) {
  // bool veto_passed = true; //pass veto if no good muon found
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++) {
    //Muon passes Tight Muon ID
    if(muTightID(i)) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < muTightEtaCut) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso4Cut)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

//For MuonCR
//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate jet within dR of 0.5
vector<int> ZprimeAnalysis::muon_looseID(int jet_index, float muPtCut)
{
  // cout << "Inside Muon Loose Veto" << endl;
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++) {
    if(muLooseID(i)) {
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < muLooseEtaCut) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut) {
	  //cout <<"Passed Pt Cut" << endl;
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso4Cut) {
	    mu_cands.push_back(i);
	  }
	}
      }
    }
  }
  return mu_cands;
}

bool ZprimeAnalysis::muon_veto(int jet_index,float muPtCut) {
  return muon_looseID(jet_index,muPtCut).size() == 0;
}

vector<int> ZprimeAnalysis::photon_looseID(int jet_index,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  for (int i = 0; i < nPho; i++) {
    if ( fabs(phoSCEta->at(i)) < phoLooseEtaCut ){
      if ( phoEt->at(i) > phoPtCut ) {
	if ( deltaR(phoSCEta->at(i),phoSCPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso5Cut )
	  pho_cands.push_back(i);
      }
    }
  }
  return pho_cands;
}

bool ZprimeAnalysis::photon_veto(int jet_index,float phoPtCut) {
  return photon_looseID(jet_index,phoPtCut).size() == 0;
}

vector<int> ZprimeAnalysis::tau_looseID(int jet_index,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  for (int i = 0; i < nTau; i++) {
    if ( tauLooseID(i) ) {
      if ( fabs(tauEta->at(i)) < tauLooseEtaCut ){
	if ( tauPt->at(i) > tauPtCut ) {
	  if ( deltaR(tauEta->at(i),tauPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > Iso4Cut )
	    tau_cands.push_back(i);
	}
      }
    }
  }
  return tau_cands;
}

bool ZprimeAnalysis::tau_veto(int jet_index,float tauPtCut) {
  return tau_looseID(jet_index,tauPtCut).size() == 0;
}

vector<int> ZprimeAnalysis::JetVetoDecision() {
  vector<int> jetindex; jetindex.clear();
  for(int i = 0; i < nJet; i++) {
    if (jetPt->at(i) > jetVetoPtCut && fabs(jetEta->at(i)) < jetVetoEtaCut && jetSelectionID(i))
      jetindex.push_back(i);
  }
  return jetindex;
}

bool ZprimeAnalysis::btagVeto() {
  bool btagVeto = true;
  for(int i = 0; i < nJet; i++)
    if(jetPt->at(i) > bjetVetoPtCut && fabs(jetEta->at(i)) < bjetVetoEtaCut && jetCSV2BJetTags->at(i) > getCSV2Cut())
      btagVeto = false;
  return btagVeto;
}

ZprimeAnalysis::~ZprimeAnalysis()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  output->cd();
  output->Write();
  output->Close();
}

Int_t ZprimeAnalysis::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t ZprimeAnalysis::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

void ZprimeAnalysis::PFUncertainty(float event_weight) {
  // 6 Histograms
  //   Trk ECAL HCAL
  //up  0   1    2
  //dn  3   4    5
  string pf_uncs[3] = {"tracker","ecal","hcal"};
  string uncname = "PFU_";
  if ( !shapeUncs.contains(uncname+pf_uncs[0]) ) {
    for (int i = 0; i < 3; i++) {
      string name = uncname + pf_uncs[i];
      shapeUncs.addUnc(name);
      
      initTree(shapeUncs.getTreeUp(name));
      initTree(shapeUncs.getTreeDn(name));
    }
  }
  
  vector<float> j1PFConsPtNorm;
  vector<float> j1PFConsPtUnc;

  float jetPtNorm = j1pT;
  for(int i=0;i<j1PFConsPID.size();i++) {
    j1PFConsPtNorm.push_back(j1PFConsPt[i]);
    if ( abs(j1PFConsPID[i]) == 211 || abs(j1PFConsPID[i]) == 13 ) {
      //Tracker Uncertainty
      //deltaPt=(1/100)*sqrt((0.015*Pt)^2+(0.5)^2)
      float deltaPt = (1/100.)*sqrt(pow(0.015*j1PFConsPt[i],2)+pow(0.5,2));
      j1PFConsPtUnc.push_back(deltaPt);
      // h_TrackerPtUnc->Fill(j1PFConsPtNorm[i],j1PFConsPtUnc[i]);
      // cout << "Tracker Unc: " << deltaPt << endl;
    }
    else if ( abs(j1PFConsPID[i]) == 22 || abs(j1PFConsPID[i]) == 11 ) {
      //ECAL Uncertainty
      //deltaPt=(1/100)*sqrt((2.8)^2/Pt+(12.8/Pt)^2+(0.3)^2)
      float deltaPt = (1/100.)*sqrt(pow(2.8,2)/j1PFConsPt[i]+pow(12.8/j1PFConsPt[i],2)+pow(0.3,2));
      j1PFConsPtUnc.push_back(deltaPt);
      // h_EcalPtUnc->Fill(j1PFConsPtNorm[i],j1PFConsPtUnc[i]);
      // cout << "ECAL Unc: " << deltaPt << endl;
    }
    else if ( abs(j1PFConsPID[i]) == 130 ) {
      //HCAL Uncertainty
      //deltaPt=(1/100)*sqrt((115)^2/Pt+(5.5)^2)
      float deltaPt = (1/100.)*sqrt(pow(115,2)/j1PFConsPt[i]+pow(5.5,2));
      j1PFConsPtUnc.push_back(deltaPt);
      // h_HcalPtUnc->Fill(j1PFConsPtNorm[i],j1PFConsPtUnc[i]);
      // cout << "HCAL Unc: " << deltaPt << endl;
    }
    else {
      j1PFConsPtUnc.push_back(0);
    }
  }
  
  // cout << "ChNemPtFrac:" << endl;
  // cout << "\tNorm: " << ChNemPtFrac << endl;
  weight = event_weight;
  int UncType[2] = {1,-1};
  for (int i = 0; i < 2; i++) {
    int variation = UncType[i];
    // Tracker
    j1pT = 0;
    j1PFConsPt.clear();
    for (int j = 0; j < j1PFConsPID.size(); j++) {
      if ( ( abs(j1PFConsPID[j]) == 221 || abs(j1PFConsPID[j]) == 13 ) )
	j1PFConsPt.push_back( j1PFConsPtNorm[j]*(1 + variation*j1PFConsPtUnc[j]) );
      else j1PFConsPt.push_back(j1PFConsPtNorm[j]);
      j1pT += j1PFConsPt[j];
    }
    SetPtFrac();
    if (variation == 1)  shapeUncs.fillUp(uncname+"tracker");
    if (variation == -1) shapeUncs.fillDn(uncname+"tracker");
    // cout << "\tTracker " << (variation == 1 ? "Up " : "Down ") << ChNemPtFrac << endl;
    
    // ECAL
    j1pT = 0;
    j1PFConsPt.clear();
    for (int j = 0; j < j1PFConsPID.size(); j++) {
      if ( ( abs(j1PFConsPID[j]) == 22 || abs(j1PFConsPID[j]) == 11 ) ) 
	j1PFConsPt.push_back( j1PFConsPtNorm[j]*(1 + variation*j1PFConsPtUnc[j]) );
      else j1PFConsPt.push_back(j1PFConsPtNorm[j]);
      j1pT += j1PFConsPt[j];
    }
    SetPtFrac();
    if (variation == 1)  shapeUncs.fillUp(uncname+"ecal");
    if (variation == -1) shapeUncs.fillDn(uncname+"ecal");
    // cout << "\tECAL " << (variation == 1 ? "Up " : "Down ") << ChNemPtFrac << endl;
    
    // HCAL
    j1pT = 0;
    j1PFConsPt.clear();
    for (int j = 0; j < j1PFConsPID.size(); j++) {
      if ( ( abs(j1PFConsPID[j]) == 130 ) )
	j1PFConsPt.push_back( j1PFConsPtNorm[j]*(1 + variation*j1PFConsPtUnc[j]) );
      else j1PFConsPt.push_back(j1PFConsPtNorm[j]);
      j1pT += j1PFConsPt[j];
    }
    SetPtFrac();
    if (variation == 1)  shapeUncs.fillUp(uncname+"hcal");
    if (variation == -1) shapeUncs.fillDn(uncname+"hcal");
    // cout << "\tHCAL " << (variation == 1 ? "Up " : "Down ") << ChNemPtFrac << endl;
  }
  
  j1pT = jetPtNorm;
  j1PFConsPt.clear();
  for (float consPt : j1PFConsPtNorm) j1PFConsPt.push_back(consPt);
  SetPtFrac();
  // cout << "\tReset: " << ChNemPtFrac << endl;
}//Closing the Loop function

void ZprimeAnalysis::QCDVariations(float event_weight) {
  /* 14 Histograms
     up  dn
     d1K_NLO     11  12
     d2K_NLO     13  14
     d3K_NLO     15  16
     d1K_EW      23  24
     d2K_EW      25  26
     d3K_EW      27  28
     dK_NLO_mix  29  30 
  */
  string uncnames[7] = {"QCD_Scale","QCD_Shape","QCD_Proc","NNLO_EWK","NNLO_Miss","NNLO_Sud","QCD_EWK_Mix"};
  // Initializing
  if ( !scaleUncs.contains(uncnames[0]) ) {
    string hnames[7] = {"d1K_NLO","d2K_NLO","d3K_NLO","d1kappa_EW","d2kappa_EW","d3kappa_EW","dK_NLO_mix"};
    TFile* file = NULL;
    string prefix = "";
    if (isW_or_ZJet()) {
      if (sample.type == WJets) {
	file = TFile::Open("RootFiles/WJets_NLO_EWK.root");
	prefix = "evj_pTV_";
      } else if (sample.type == ZJets) {
	file = TFile::Open("RootFiles/ZJets_NLO_EWK.root");
	prefix = "vvj_pTV_";
      } else if (sample.type == DYJets) {
	file = TFile::Open("RootFiles/DYJets_NLO_EWK.root");
	prefix = "eej_pTV_";
      }
      th1fmap["K_NLO_QCD"] = (TH1F*)file->Get( (prefix+"K_NLO").c_str() );
      th1fmap["K_EW"]      = (TH1F*)file->Get( (prefix+"kappa_EW").c_str() );
    }
    
    for (int i = 0; i < 7; i++) {
      string name = uncnames[i];
      TH1F* histo = NULL;
      if (isW_or_ZJet()) histo = (TH1F*)file->Get( (prefix+hnames[i]).c_str() );
      scaleUncs.addUnc(name,histo);
    }
  }
  
  for (int i = 0; i < 7; i++) {
    string name = uncnames[i];
    float weightUp = event_weight;
    float weightDn = event_weight;
    
    if (isW_or_ZJet()) {
      float unc = scaleUncs.getBin(name,bosonPt);
      float k_qcd = th1fmap.getBin("K_NLO_QCD",bosonPt);
      float k_ewk = th1fmap.getBin("K_EW",bosonPt);
      if ( name.find("NNLO") != string::npos || name.find("EWK") != string::npos ) unc *= k_ewk;
      else if ( name.find("QCD") != string::npos ) unc *= k_qcd;
      weightUp += unc;
      weightDn -= unc;
    }
    scaleUncs.setUnc(name,weightUp,weightDn);
  }
}

#endif
