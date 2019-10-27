#define ZprimeJetsCommon_cxx
#include "ZprimeJetsCommon.h"

void ZprimeJetsCommon::SetScalingHistos() {
  //This is the PU histogram obtained from Nick's recipe
  TFile *weights = TFile::Open("RootFiles/PU_Central.root");
  TH1F* PU = (TH1F*)weights->Get("pileup");
  th1fmap["PU"] = PU;

  if (sample.isW_or_ZJet()) {
    //This is the root file with EWK Corrections
    TFile* f_kfactor = TFile::Open("RootFiles/kfactors.root");

    TH1F *LO_QCD,*NLO_QCD_EWK;
    if ( sample.type == WJets ) {
      LO_QCD = (TH1F*)f_kfactor->Get("WJets_LO/inv_pt");
      NLO_QCD_EWK = (TH1F*)f_kfactor->Get("EWKcorr/W");
    } else {
      LO_QCD = (TH1F*)f_kfactor->Get("ZJets_LO/inv_pt");
      NLO_QCD_EWK = (TH1F*)f_kfactor->Get("EWKcorr/Z");
    }
    th1fmap["LO_QCD"] = LO_QCD;
    th1fmap["NLO_QCD_EWK"] = NLO_QCD_EWK;
  }
}

void ZprimeJetsCommon::BookCommon(int i,string histname) {

  float MtBins[51]={180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.,3000.};
  
  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float PtBins[49]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};

  float Pt123Bins[59]={0.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,
		       600.,620.,640.,660.,680.,700.,720.,740.,760.,780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};
  
  float BosonPtBins[25] = {150,170,200,230,260,290,320,350,390,430,470,510,550,590,640,690,740,790,840,900,960,1020,1090,1160,1250};

  if (i == -1) {
    
    h_metcut  = new TH1F("h_metcut","h_metcut; |pfMET-caloMET|/pfMET", 50,0,1.2);h_metcut->Sumw2();
    h_dphimin = new TH1F("h_dphimin","h_dphimin; Minimum dPhiJetMET",50,0,3.2);h_dphimin->Sumw2();
    h_metFilters = new TH1F("h_metFilters","metFilters",11,0.5,11.5); h_metFilters->Sumw2();
    h_kfactor = new TH1F("h_kfactor","h_kfactor;kfactor",50,0,2); h_kfactor->Sumw2();
    h_puTrueUnWeight = new TH1F("puTrueUnWeight","puTrue;true number of iteractions",100,0,100);h_puTrueUnWeight->Sumw2();
    h_puTrueReWeight = new TH1F("puTrueReWeight","puTrue;true number of iteractions",100,0,100);h_puTrueReWeight->Sumw2();
    h_genBosonPt = new TH1F("h_genBosonPt","genBosonPt;Gen Boson P_{T}",24,BosonPtBins); h_genBosonPt->Sumw2();
    h_genBosonPtwK = new TH1F("h_genBosonPtwK","genBosonPtwK;Gen Boson P_{T}",24,BosonPtBins); h_genBosonPtwK->Sumw2();
    
    // Uncertainty Plots
    h_EcalPtUnc=new TH2F("EcalPtUnc","ECAL P_{T} Uncertainty;Photon P_{T} (GeV);Uncertainty",50,0.,2500.,50,0.,1.);
    h_TrackerPtUnc=new TH2F("TrackerPtUnc","Tracker P_{T} Uncertainty;Charged Hadrons P_{T} (GeV);Uncertainty",50,0.,2500.,50,0.,1.);
    h_HcalPtUnc=new TH2F("HcalPtUnc","HCAL P_{T} Uncertainty;Neutral Hadron P_{T} (GeV);Uncertainty",50,0.,2500.,50,0.,1.);

    h_nlo_ewk=new TH1F(("nloEWK"+histname).c_str(),"nloEWK",100,-0.6,0.1); h_nlo_ewk->Sumw2();
    
  } else {
    
    h_eventWeight[i] = new TH1F(("eventWeight"+histname).c_str(),"eventWeight",50,0,2); h_eventWeight[i]->Sumw2();
    h_genHT[i] = new TH1F(("genHT"+histname).c_str(),"genHT;genHT",100,0,2500);h_genHT[i]->Sumw2();
    h_nJets[i]   = new TH1F(("nJets"+histname).c_str(), "nJets;Number of Jets", 20,0,20);h_nJets[i]->Sumw2();
    h_pfMETall[i] =  new TH1F(("pfMETall"+histname).c_str(), "pfMET",50,0,2000);h_pfMETall[i] ->Sumw2(); 
    h_pfMET200[i] = new TH1F(("pfMET200"+histname).c_str(), "pfMET",50,170,1500);h_pfMET200[i] ->Sumw2(); 
    h_pfMET[i] = new TH1F(("pfMET"+histname).c_str(), "E_{T}^{miss} (GeV)",44,MetBins);h_pfMET[i] ->Sumw2();
    h_pfMETPhi[i] = new TH1F(("pfMETPhi"+histname).c_str(), "pfMETPhi",30,-3.1416,3.1416);h_pfMETPhi[i]->Sumw2();
    h_j1Pt[i]  = new TH1F(("j1pT"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt[i]->Sumw2();
    h_j1TotConsPt[i]  = new TH1F(("j1TotConsPt"+histname).c_str(), "j1pT;Leading Jet Total Constituent P_{T}", 48,PtBins);h_j1TotConsPt[i]->Sumw2();
    h_j1Eta[i] = new TH1F(("j1Eta"+histname).c_str(), "j1Eta; #eta of Leading Jet", 50, -3.0, 3.0);h_j1Eta[i]->Sumw2();
    h_j1Phi[i] = new TH1F(("j1Phi"+histname).c_str(), "j1Phi; #phi of Leading Jet", 30, -3.1416, 3.1416);h_j1Phi[i]->Sumw2();
    h_j1etaWidth[i] = new TH1F(("j1etaWidth"+histname).c_str(),"j1etaWidth; #eta width of Leading Jet", 50,0,0.25);h_j1etaWidth[i] ->Sumw2();
    h_j1phiWidth[i] = new TH1F(("j1phiWidth"+histname).c_str(),"j1phiWidth; #phi width of Leading Jet", 50, 0,0.5);h_j1phiWidth[i]->Sumw2();
    h_j1nCons[i] = new TH1F (("j1nCons"+histname).c_str(),"j1nCons; Number of Constituents of Leading Jet",25, 0, 50);h_j1nCons[i]->Sumw2();
    h_Pt123[i] = new TH1F(("Pt123"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",58,Pt123Bins);h_Pt123[i]->Sumw2();
    h_PF123PtFraction[i]= new TH1F(("PF123PtFraction"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1.1);h_PF123PtFraction[i]->Sumw2();
    h_PtRawFrac[i]= new TH1F(("PtRawFrac"+histname).c_str(), "PtRawFrac;Raw P_{T}^{123} Fraction" ,50,0,1.1);h_PtRawFrac[i]->Sumw2(); 
    h_j1TotPFCands[i] = new TH1F(("j1TotPFCands"+histname).c_str(),"j1TotPFCands;# of all PF candidates in Leading Jet",25,0,50);h_j1TotPFCands[i]->Sumw2();
    h_j1ChPFCands[i] = new TH1F(("j1ChPFCands"+histname).c_str(),"j1ChPFCands;# of PF charged hadrons in Leading Jet",25,0,50);h_j1ChPFCands[i]->Sumw2();
    h_j1NeutPFCands[i] = new TH1F(("j1NeutPFCands"+histname).c_str(),"j1NeutPFCands;# of PF neutral hadrons in Leading Jet",15,0,15);h_j1NeutPFCands[i]->Sumw2();
    h_j1GammaPFCands[i] = new TH1F(("j1GammaPFCands"+histname).c_str(),"j1GammaPFCands;# of PF gammas in Leading Jet",20,0,40);h_j1GammaPFCands[i]->Sumw2();
    h_j1CHF[i] = new TH1F(("j1CHF"+histname).c_str(),"j1CHF;Charged Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1CHF[i]->Sumw2(); 
    h_j1NHF[i] = new TH1F(("j1NHF"+histname).c_str(),"j1NHF;Neutral Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1NHF[i]->Sumw2(); 
    h_j1ChMultiplicity[i] = new TH1F(("j1ChMultiplicity"+histname).c_str(),"j1ChMultiplicity;Charged Multiplicity of Leading Jet",25,0,50);h_j1ChMultiplicity[i]->Sumw2();
    h_j1NeutMultiplicity[i] = new TH1F(("j1NeutMultiplicity"+histname).c_str(),"j1NeutMultiplicity;Neutral Multiplicity of Leading Jet",25,0,50);h_j1NeutMultiplicity[i]->Sumw2(); 
    h_j1Mt[i]  = new TH1F(("j1Mt"+histname).c_str(), "j1Mt;M_{T} of Leading Jet (GeV)", 50,MtBins);h_j1Mt[i]->Sumw2(); 
    h_nVtx[i] = new TH1F(("nVtx"+histname).c_str(),"nVtx;nVtx",70,0,70);h_nVtx[i]->Sumw2();
    h_nVtx2[i] = new TH1F(("nVtx2"+histname).c_str(),"nVtx;nVtx",40,0,80);h_nVtx2[i]->Sumw2();
    h_j1Mass[i] = new TH1F(("j1Mass"+histname).c_str(),"j1Mass;Leading Jet Mass (GeV)",50,0,3000);h_j1Mass[i]->Sumw2();
    h_j1JEC[i] = new TH1F(("j1JEC"+histname).c_str(),"j1JEC;Leading Jet JEC Uncertainty",50,0,0.1); h_j1JEC[i]->Sumw2();
    h_ChNemPtFrac[i] = new TH1F(("ChNemPtFrac"+histname).c_str(),"ChNemPtFrac;Ch + NEM P_{T}^{123} Fraction",50,0,1.1);h_ChNemPtFrac[i]->Sumw2();
    h_ChNemPt[i]  = new TH1F(("ChNemPt"+histname).c_str(), "ChNemPt;Ch + NEM Leading Jet P_{T} (GeV)", 58,Pt123Bins);h_ChNemPt[i]->Sumw2();
    h_ChNemPt123[i] = new TH1F(("ChNemPt123"+histname).c_str(),"ChNemPt123;Ch + NEM P^{123}_{T} (GeV)",58,Pt123Bins);h_ChNemPt123[i]->Sumw2();
    h_ChPercCons[i] = new TH1F(("ChPercCons"+histname).c_str(),"ChPercCons;Charged Hadron Constituent Percent",50,0,1.1);h_ChPercCons[i]->Sumw2();
    h_NhPercCons[i] = new TH1F(("NhPercCons"+histname).c_str(),"NhPercCons;Neutral Hadron Constituent Percent",50,0,1.1);h_NhPercCons[i]->Sumw2();
    h_GammaPercCons[i] = new TH1F(("GammaPercCons"+histname).c_str(),"GammaPercCons;Photon Constituent Percent",50,0,1.1);h_GammaPercCons[i]->Sumw2();

    h_ChargedPt[i] = new TH1F(("ChargedPt"+histname).c_str(),"ChargedPt;Charged Constituent P_{T}",58,Pt123Bins);h_ChargedPt[i]->Sumw2();
    h_NeutralPt[i] = new TH1F(("NeutralPt"+histname).c_str(),"NeutralPt;Neutral Constituent P_{T}",58,Pt123Bins);h_NeutralPt[i]->Sumw2();
    h_PhotonPt[i] = new TH1F(("PhotonPt"+histname).c_str(),"PhotonPt;Photon Constituent P_{T}",58,Pt123Bins);h_PhotonPt[i]->Sumw2();

    h_ChPercPt[i] = new TH1F(("ChPercPt"+histname).c_str(), "ChPercPt; Charged Constituent P_{T} Percentage" ,50,0,1.1);h_ChPercPt[i]->Sumw2();
    h_NhPercPt[i] = new TH1F(("NhPercPt"+histname).c_str(), "NhPercPt; Nharged Constituent P_{T} Percentage" ,50,0,1.1);h_NhPercPt[i]->Sumw2();
    h_GammaPercPt[i] = new TH1F(("GammaPercPt"+histname).c_str(), "GammaPercPt; Gammaarged Constituent P_{T} Percentage" ,50,0,1.1);h_GammaPercPt[i]->Sumw2();
  }
}

void ZprimeJetsCommon::fillCommon(int nhist,float event_weight) {
  if (sample.isData) event_weight = 1;
  else {
    h_genHT[nhist]->Fill(genHT,event_weight);
  }

  h_eventWeight[nhist]->Fill(event_weight,event_weight);
  h_nVtx[nhist]->Fill(nVtx,event_weight);
  h_nVtx2[nhist]->Fill(nVtx,event_weight);
  h_nJets[nhist]->Fill(nJet,event_weight);
  h_pfMETall[nhist]->Fill(pfMET,event_weight);
  h_pfMET200[nhist]->Fill(pfMET,event_weight);
  h_pfMET[nhist]->Fill(pfMET,event_weight);
  h_pfMETPhi[nhist]->Fill(pfMETPhi,event_weight);
  if(jetCand.size()>0){
    h_j1TotConsPt[nhist]->Fill(j1TotConsPt,event_weight);
    h_j1Pt[nhist]->Fill(jetPt->at(jetCand[0]),event_weight);
    h_j1Eta[nhist]->Fill(jetEta->at(jetCand[0]),event_weight);
    h_j1Phi[nhist]->Fill(jetPhi->at(jetCand[0]),event_weight);
    h_Pt123[nhist]->Fill(Pt123,event_weight);
    h_PF123PtFraction[nhist]->Fill(Pt123Fraction,event_weight);
    h_PtRawFrac[nhist]->Fill(PtRawFrac,event_weight);
    h_j1TotPFCands[nhist]->Fill(TotalPFCandidates,event_weight);
    h_j1ChPFCands[nhist]->Fill(ChargedPFCandidates,event_weight);
    h_j1NeutPFCands[nhist]->Fill(NeutralPFCandidates,event_weight);
    h_j1GammaPFCands[nhist]->Fill(GammaPFCandidates,event_weight);
    h_j1CHF[nhist]->Fill(jetCHF->at(jetCand[0]),event_weight);
    h_j1NHF[nhist]->Fill(jetNHF->at(jetCand[0]),event_weight);
    h_j1ChMultiplicity[nhist]->Fill(jetNCH->at(jetCand[0]),event_weight);
    h_j1NeutMultiplicity[nhist]->Fill(jetNNP->at(jetCand[0]),event_weight);
    h_j1Mt[nhist]->Fill(jetMt->at(jetCand[0]),event_weight);
    h_j1etaWidth[nhist]->Fill(jetetaWidth->at(jetCand[0]),event_weight);
    h_j1phiWidth[nhist]->Fill(jetphiWidth->at(jetCand[0]),event_weight);
    h_j1nCons[nhist]->Fill(jetnPhotons->at(jetCand[0])+jetnCHPions->at(jetCand[0])+jetnMisc->at(jetCand[0]),event_weight);
    h_j1Mass[nhist]->Fill(j1Mass,event_weight);
    h_j1JEC[nhist]->Fill(jetJECUnc->at(jetCand[0]),event_weight);
    h_ChNemPtFrac[nhist]->Fill(ChNemPtFrac,event_weight);
    h_ChNemPt[nhist]->Fill(ChNemPt,event_weight);
    h_ChNemPt123[nhist]->Fill(ChNemPt123,event_weight);
    h_ChPercCons[nhist]->Fill(ChargedPFCandidates/(float)TotalPFCandidates,event_weight);
    h_NhPercCons[nhist]->Fill(NeutralPFCandidates/(float)TotalPFCandidates,event_weight);
    h_GammaPercCons[nhist]->Fill(GammaPFCandidates/(float)TotalPFCandidates,event_weight);

    
    h_NeutralPt[nhist]->Fill(hadronPt[0],event_weight);
    h_ChargedPt[nhist]->Fill(hadronPt[1],event_weight);
    h_PhotonPt[nhist]->Fill(hadronPt[2],event_weight);
      
    h_NhPercPt[nhist]->Fill( hadronPt[0]/jetPt->at(jetCand[0]) ,event_weight);
    h_ChPercPt[nhist]->Fill( hadronPt[1]/jetPt->at(jetCand[0]) ,event_weight);
    h_GammaPercPt[nhist]->Fill( hadronPt[2]/jetPt->at(jetCand[0]) ,event_weight);
  }
}

void ZprimeJetsCommon::getPt123Frac() {
  Pt123Fraction=Pt123=ChNemPtFrac=ChNemPt=ChNemPt123=j1TotConsPt=0.0;
  for (int i = 0; i < 3; i++){
    hadronPt[i] = 0.;
  }
  
  // Neutral, Charged, Photon
  int HadronID[3] = {130,211,22};
  float HadronPtFirst3[3] = {0,0,0};
  
  for (int i = 0; i < j1PFConsPID.size(); i++) {
    if (i < 3)
      Pt123 += j1PFConsPt.at(i);
    j1TotConsPt += j1PFConsPt.at(i);
    for (int j = 0; j < 3; j++)
      if (abs(j1PFConsPID.at(i)) == HadronID[j]) {
	if (i < 3)
	  HadronPtFirst3[j] += j1PFConsPt.at(i);
	hadronPt[j] += j1PFConsPt.at(i);
      }
  }
  j1pT = jetPt->at(jetCand[0]);
  Pt123Fraction = Pt123/jetPt->at(jetCand[0]);
  PtRawFrac = Pt123/jetRawPt->at(jetCand[0]);
  ChNemPtFrac = (HadronPtFirst3[1]+HadronPtFirst3[2])/(hadronPt[1]+hadronPt[2]);
  ChNemPt123 = HadronPtFirst3[1]+HadronPtFirst3[2];
  ChNemPt = hadronPt[1]+hadronPt[2];
}

void ZprimeJetsCommon::AllPFCand(vector<int> jetCand) {
  //getPFCandidatesMethod for the Pencil Jet -> jetCand[0]
  TotalPFCandidates=ChargedPFCandidates=NeutralPFCandidates=GammaPFCandidates=0;
    
  Pt123Fraction=Pt123=ChNemPtFrac=ChNemPt=ChNemPt123=j1TotConsPt=0.0;
  for (int i = 0; i < 3; i++){
    hadronPt[i] = 0.;
  }
  //We are using these conditions so we only calculate the following quantities for the signal we are interested in
  //This will also make it faster to process the events
  if(jetCand.size()>0) {
    j1PFConsEt=JetsPFConsEt->at(jetCand[0]);
    j1PFConsPt=JetsPFConsPt->at(jetCand[0]);
    j1PFConsEta=JetsPFConsEta->at(jetCand[0]);
    j1PFConsPhi=JetsPFConsPhi->at(jetCand[0]);
    j1PFConsPID=JetsPFConsPID->at(jetCand[0]);
    vector<int> PFCandidates = getPFCandidates();

    TLorentzVector pfCons;
    for (int i = 0; i < j1PFConsPID.size(); i++) {
      TLorentzVector cons; cons.SetPtEtaPhiE(j1PFConsPt[i],j1PFConsEta[i],j1PFConsPhi[i],j1PFConsEt[i]);
      pfCons += cons;
    }
    j1Mass = pow(pfCons.M2(),0.5);
    
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
    
    getPt123Frac();
  }
}

//Function to calculate regular deltaR separate from jet width variable 'dR'
float ZprimeJetsCommon::deltaR(float eta1, float phi1, float eta2, float phi2) {
  float deltaeta = abs(eta1 - eta2);
  float deltaphi = DeltaPhi(phi1, phi2);
  float deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
float ZprimeJetsCommon::DeltaPhi(float phi1, float phi2) {
  float pi = TMath::Pi();
  float dphi = fabs(phi1-phi2);
  if(dphi>pi)
    dphi = 2.0*pi - dphi;
  return dphi;
}
float ZprimeJetsCommon::dPhiJetMETmin(vector<int> jets,float metPhi) {
  float dPhimin=TMath::Pi();
  int njetsMax = jets.size();
  if(njetsMax > 4)
    njetsMax = 4;
  for(int j=0;j< njetsMax; j++) {
    float dPhi = DeltaPhi((*jetPhi)[j],metPhi);
    //cout<<"DeltaPhi: "<<dPhi<<endl;
    if(dPhi < dPhimin)
      dPhimin = dPhi;
  }
  return dPhimin;
}

vector<int> ZprimeJetsCommon::getJetCand(float jetPtCut, float jetEtaCut, float jetNHFCut, float jetCHFCut){

  vector<int> tmpCand;
  tmpCand.clear();

  for(int p=0;p<nJet;p++) {

    bool kinematic = (*jetPt)[p] > jetPtCut && (*jetNHF)[p] < jetNHFCut && (*jetCHF)[p] > jetCHFCut && fabs((*jetEta)[p])<jetEtaCut;

    if((*jetPFLooseId)[p]==1 && kinematic)
      tmpCand.push_back(p);
  }
  return tmpCand;
}

//Return a vector of pairs. "0" = #pfCands, "1"=#chargedPFCands , "3"=#neutralPFCands,"2"=#photonPFCands
//get PF Candidates of the selected Jet ->jetCand[0]
vector<int>ZprimeJetsCommon::getPFCandidates() {
  vector<int>PFCands;
  for(int i = 0;i < nJet; i++) {
    int TotPFCands;
    if(i == 0) {
      TotPFCands = j1PFConsPID.size();
      PFCands.push_back(TotPFCands);
      int ChPFCands,NeuPFCands,GammaPFCands;
      ChPFCands=NeuPFCands=GammaPFCands=0;
      for(int j=0;j<TotPFCands;j++) {
        if(abs(j1PFConsPID.at(j))==211)
          ChPFCands++;
        if(j1PFConsPID.at(j)==22)
          GammaPFCands++;
        if(j1PFConsPID.at(j)==130)
          NeuPFCands++;
      }
      PFCands.push_back(ChPFCands);
      PFCands.push_back(GammaPFCands);
      PFCands.push_back(NeuPFCands);
    }
  }
  return PFCands;
}

bool ZprimeJetsCommon::dPhiJetMETcut(vector<int> jets,float metPhi) {
  //Only look at first four jets (because that's what monojet analysis do)
  int njets = jets.size() ? jets.size() <= 4 : 4;
  float minDPhiJetMET_first4 = TMath::Pi();
  for (int ijet = 0; ijet < njets; ijet++) {
    float dPhiJetMET = DeltaPhi(jetPhi->at(ijet),metPhi);
    if (dPhiJetMET < minDPhiJetMET_first4) minDPhiJetMET_first4 = dPhiJetMET;
  }

  //reject jet if it is found within DeltaPhi(jet,MET) < 0.5 
  if (minDPhiJetMET_first4 > dPhiJetMETCut) return true;
  return false;
}

void ZprimeJetsCommon::SetBoson(int PID) {
  bosonPt = 0;
  for (int i = 0; i < nMC; i++){
    if((*mcPID)[i] == PID && mcStatusFlag->at(i)>>2&1 == 1){
      bosonPt = (*mcPt)[i];
      SetKFactors(bosonPt);

      h_genBosonPt->Fill(bosonPt,genWeight);
      h_genBosonPtwK->Fill(bosonPt,genWeight*kfactor);
    }
  }
}

void ZprimeJetsCommon::ApplyPileup(float &event_weight) {
  //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
  //binContent as event_weight
  float pileup = th1fmap.getBin("PU",puTrue->at(0));
  genWeight = fabs(genWeight) > 0 ? genWeight/fabs(genWeight) : 0;
  event_weight *= pileup * genWeight;

  h_puTrueUnWeight->Fill(puTrue->at(0),genWeight);
  h_puTrueReWeight->Fill(puTrue->at(0),event_weight);
}

void ZprimeJetsCommon::ApplySF(float &event_weight,float sf) {
  event_weight *= sf;
}

void ZprimeJetsCommon::ApplyKFactor(float &event_weight) {
  event_weight *= kfactor;
}

void ZprimeJetsCommon::SetKFactors(float bosonPt) {
  kfactor = getKFactor(bosonPt);
}

float ZprimeJetsCommon::getKFactor(float bosonPt) {
  float nlo_qcd_ewk = th1fmap.getBin("NLO_QCD_EWK",bosonPt);
  float lo_qcd = th1fmap.getBin("LO_QCD",bosonPt);
  float kfactor = 1;
  if(nlo_qcd_ewk!=0 && lo_qcd!=0)
    kfactor = (nlo_qcd_ewk/lo_qcd);
  else
    kfactor= sample.type == WJets ? 1.21 : 1.23;
  h_kfactor->Fill(kfactor);
  return kfactor;
}

bool ZprimeJetsCommon::inclusiveCut() {
  if (sample.isInclusive)
    return genHT < 100;
  return true;
}

void ZprimeJetsCommon::initVars() {
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
    
    weight = 1;
    kfactor = 1;

    bosonPt = Pt123Fraction = Pt123 = PtRawFrac = j1pT = 0;
    ChNemPtFrac = ChNemPt = ChNemPt123 = 0;
    TotalPFCandidates = ChargedPFCandidates = NeutralPFCandidates = GammaPFCandidates = 0;
}
