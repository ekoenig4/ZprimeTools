
#define ZprimeJetsClass_cxx
#include "ZprimeJetsClass.h"

void ZprimeJetsClass::BookHistos(const char* outputFilename) {
  fileName = new TFile(outputFilename, "RECREATE");
  tree = new TTree("ZprimeJet","ZprimeJet");
  fileName->cd();

  BookRegion(-1,"");

  float MtBins[51]={180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.,3000.};
  
  float MetBins[49]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};

  float PtBins[49]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};

  float Pt123Bins[59]={0.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,
		       600.,620.,640.,660.,680.,700.,720.,740.,760.,780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};
  
  h_metcut  = new TH1F("h_metcut","h_metcut; |pfMET-caloMET|/pfMET", 50,0,1.2);h_metcut->Sumw2();
  h_dphimin = new TH1F("h_dphimin","h_dphimin; Minimum dPhiJetMET",50,0,3.2);h_dphimin->Sumw2();
  h_metFilters = new TH1F("h_metFilters","metFilters",11,0.5,11.5); h_metFilters->Sumw2();
  for(int i=0; i<nHisto; i++){

    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    h_eventWeight[i] = new TH1F(("eventWeight"+histname).c_str(),"eventWeight",50,0,2); h_eventWeight[i]->Sumw2();
    h_puTrue[i] = new TH1F(("puTrue"+histname).c_str(),"puTrue;puTrue",100,0,100);h_puTrue[i]->Sumw2();
    h_genHT[i] = new TH1F(("genHT"+histname).c_str(),"genHT;genHT",100,0,2500);h_genHT[i]->Sumw2();
    h_nJets[i]   = new TH1F(("nJets"+histname).c_str(), "nJets;Number of Jets", 50, 0, 100);h_nJets[i]->Sumw2();
    h_pfMETall[i] =  new TH1F(("pfMETall"+histname).c_str(), "pfMET",50,0,2000);h_pfMETall[i] ->Sumw2(); 
    h_pfMET200[i] = new TH1F(("pfMET200"+histname).c_str(), "pfMET",50,170,1500);h_pfMET200[i] ->Sumw2(); 
    h_pfMET[i] = new TH1F(("pfMET"+histname).c_str(), "E_{T}^{miss} (GeV)",48,MetBins);h_pfMET[i] ->Sumw2();
    h_pfMETPhi[i] = new TH1F(("pfMETPhi"+histname).c_str(), "pfMETPhi",50,-4,4);h_pfMETPhi[i]->Sumw2();
    h_j1Pt[i]  = new TH1F(("j1pT"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt[i]->Sumw2();
    h_j1Eta[i] = new TH1F(("j1Eta"+histname).c_str(), "j1Eta; #eta of Leading Jet", 50, -3.0, 3.0);h_j1Eta[i]->Sumw2();
    h_j1Phi[i] = new TH1F(("j1Phi"+histname).c_str(), "j1Phi; #phi of Leading Jet", 50, -3.0, 3.0);h_j1Phi[i]->Sumw2();
    h_j1etaWidth[i] = new TH1F(("j1etaWidth"+histname).c_str(),"j1etaWidth; #eta width of Leading Jet", 50,0,0.25);h_j1etaWidth[i] ->Sumw2();
    h_j1phiWidth[i] = new TH1F(("j1phiWidth"+histname).c_str(),"j1phiWidth; #phi width of Leading Jet", 50, 0,0.5);h_j1phiWidth[i]->Sumw2();
    h_j1ChNemEtaWidth[i] = new TH1F(("j1ChNemEtaWidth"+histname).c_str(),"j1ChNemEtaWidth;Ch+NEM #eta width of Leading Jet", 50,0,0.25);h_j1ChNemEtaWidth[i] ->Sumw2();
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
    h_j1Mass[i] = new TH1F(("j1Mass"+histname).c_str(),"j1Mass;Leading Jet Mass (GeV)",50,0,3000);h_j1Mass[i]->Sumw2();
    h_j1JEC[i] = new TH1F(("j1JEC"+histname).c_str(),"j1JEC;Leading Jet JEC Uncertainty",50,0,0.1); h_j1JEC[i]->Sumw2();
    h_j1PID[i] = new TH1F(("j1PID"+histname).c_str(),"j1PID;Leading Jet Particle ID",50,0,400); h_j1PID[i]->Sumw2();
    h_j1Lepton[i] = new TH1F(("j1Lepton"+histname).c_str(),"j1Lepton;Leading Jet Lepton",11,0,10); h_j1Lepton[i]->Sumw2();
    h_ChPtFrac[i] = new TH1F(("ChPtFrac"+histname).c_str(),"ChPtFrac;Charged P_{T}^{123} Fraction",50,0,1.1);h_ChPtFrac[i]->Sumw2();
    h_ChTotPtFrac[i] = new TH1F(("ChTotPtFrac"+histname).c_str(),"ChTotPtFrac;Charged P_{T}^{123} Total Fraction",50,0,1.1);h_ChTotPtFrac[i]->Sumw2();
    h_ChNemPtFrac[i] = new TH1F(("ChNemPtFrac"+histname).c_str(),"ChNemPtFrac;Ch + NEM P_{T}^{123} Fraction",50,0,1.1);h_ChNemPtFrac[i]->Sumw2();
    h_ChNemTotPtFrac[i] = new TH1F(("ChNemTotPtFrac"+histname).c_str(),"ChNemTotPtFrac;Ch + NEM P_{T}^{123} Total Fraction",50,0,1.1);h_ChNemTotPtFrac[i]->Sumw2();
    h_PtFracCH[i] = new TH1F(("PtFracCH"+histname).c_str(),"PtFracCH; Charged Hadron P_{T}^{123} Total Fraction",50,0,1.1);h_PtFracCH[i]->Sumw2();
    h_PtFracNH[i] = new TH1F(("PtFracNH"+histname).c_str(),"PtFracNH; Neutral Hadron P_{T}^{123} Total Fraction",50,0,1.1);h_PtFracNH[i]->Sumw2();
    h_PtFracG[i] = new TH1F(("PtFracG"+histname).c_str(),"PtFracG; Photon P_{T}^{123} Total Fraction",50,0,1.1);h_PtFracG[i]->Sumw2();
    h_PtFracChFirst3[i] = new TH1F(("PtFracChFirst3"+histname).c_str(),"PtFracChFirst3; First 3 Charged Hadron P_{T} Fraction",50,0,1.1);h_PtFracChFirst3[i]->Sumw2();
    h_PtFracNhFirst3[i] = new TH1F(("PtFracNhFirst3"+histname).c_str(),"PtFracNhFirst3; First 3 Neutral Hadron P_{T} Fraction",50,0,1.1);h_PtFracNhFirst3[i]->Sumw2();
    h_PtFracGammaFirst3[i] = new TH1F(("PtFracGammaFirst3"+histname).c_str(),"PtFracGammaFirst3; First 3 Photon P_{T} Fraction",50,0,1.1);h_PtFracGammaFirst3[i]->Sumw2();
    h_ChPercCons[i] = new TH1F(("ChPercCons"+histname).c_str(),"ChPercCons;Charged Hadron Constituent Percent",50,0,1.1);h_ChPercCons[i]->Sumw2();
    h_NhPercCons[i] = new TH1F(("NhPercCons"+histname).c_str(),"NhPercCons;Neutral Hadron Constituent Percent",50,0,1.1);h_NhPercCons[i]->Sumw2();
    h_GammaPercCons[i] = new TH1F(("GammaPercCons"+histname).c_str(),"GammaPercCons;Photon Constituent Percent",50,0,1.1);h_GammaPercCons[i]->Sumw2();

    h_LepPtFrac[i] = new TH1F(("LepPtFrac"+histname).c_str(),"LepPtFrac; Lepton P_{T}^{123} Total Fraction",50,0,1.1);h_LepPtFrac[i]->Sumw2();

    //Region Specific Histograms
    BookRegion(i,histname);
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight) {
  if (sample.isData) event_weight = 1;
  else {
    h_genHT[histoNumber]->Fill(genHT,event_weight);
    h_puTrue[histoNumber]->Fill(puTrue->at(0),event_weight);
  }

  h_eventWeight[histoNumber]->Fill(event_weight,event_weight);
  h_nVtx[histoNumber]->Fill(nVtx,event_weight);
  h_nJets[histoNumber]->Fill(nJet,event_weight);
  h_pfMETall[histoNumber]->Fill(pfMET,event_weight);
  h_pfMET200[histoNumber]->Fill(pfMET,event_weight);
  h_pfMET[histoNumber]->Fill(pfMET,event_weight);
  h_pfMETPhi[histoNumber]->Fill(pfMETPhi,event_weight);
  if(jetCand.size()>0){
    h_j1Pt[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
    h_j1Eta[histoNumber]->Fill(jetEta->at(jetCand[0]),event_weight);
    h_j1Phi[histoNumber]->Fill(jetPhi->at(jetCand[0]),event_weight);
    h_Pt123[histoNumber]->Fill(Pt123,event_weight);
    h_PF123PtFraction[histoNumber]->Fill(Pt123Fraction,event_weight);
    h_PtRawFrac[histoNumber]->Fill(PtRawFrac,event_weight);
    h_j1TotPFCands[histoNumber]->Fill(TotalPFCandidates,event_weight);
    h_j1ChPFCands[histoNumber]->Fill(ChargedPFCandidates,event_weight);
    h_j1NeutPFCands[histoNumber]->Fill(NeutralPFCandidates,event_weight);
    h_j1GammaPFCands[histoNumber]->Fill(GammaPFCandidates,event_weight);
    h_j1CHF[histoNumber]->Fill(jetCHF->at(jetCand[0]),event_weight);
    h_j1NHF[histoNumber]->Fill(jetNHF->at(jetCand[0]),event_weight);
    h_j1ChMultiplicity[histoNumber]->Fill(jetNCH->at(jetCand[0]),event_weight);
    h_j1NeutMultiplicity[histoNumber]->Fill(jetNNP->at(jetCand[0]),event_weight);
    h_j1Mt[histoNumber]->Fill(jetMt->at(jetCand[0]),event_weight);
    h_j1etaWidth[histoNumber]->Fill(jetetaWidth->at(jetCand[0]),event_weight);
    h_j1phiWidth[histoNumber]->Fill(jetphiWidth->at(jetCand[0]),event_weight);
    h_j1nCons[histoNumber]->Fill(jetnPhotons->at(jetCand[0])+jetnCHPions->at(jetCand[0])+jetnMisc->at(jetCand[0]),event_weight);
    h_j1Mass[histoNumber]->Fill(j1Mass,event_weight);
    h_j1JEC[histoNumber]->Fill(jetJECUnc->at(jetCand[0]),event_weight);
    h_j1ChNemEtaWidth[histoNumber]->Fill(j1ChNemEtaWidth,event_weight);
    for (int ID : j1PFConsPID) h_j1PID[histoNumber]->Fill(abs(ID),event_weight);
    h_j1Lepton[histoNumber]->Fill(LeptonPFCandidates,event_weight);
    h_ChNemPtFrac[histoNumber]->Fill(ChNemPtFrac,event_weight);
    h_ChNemTotPtFrac[histoNumber]->Fill(ChNemTotPtFrac,event_weight);
    h_ChPtFrac[histoNumber]->Fill(ChPtFrac,event_weight);
    h_ChTotPtFrac[histoNumber]->Fill(ChTotPtFrac,event_weight);
    h_PtFracNH[histoNumber]->Fill(hadronTotPtFrac[0],event_weight);
    h_PtFracCH[histoNumber]->Fill(hadronTotPtFrac[1],event_weight);
    h_PtFracG[histoNumber]->Fill(hadronTotPtFrac[2],event_weight);
    h_PtFracNhFirst3[histoNumber]->Fill(hadronFirst3Frac[0],event_weight);
    h_PtFracChFirst3[histoNumber]->Fill(hadronFirst3Frac[1],event_weight);
    h_PtFracGammaFirst3[histoNumber]->Fill(hadronFirst3Frac[2],event_weight);
    h_ChPercCons[histoNumber]->Fill(ChargedPFCandidates/(float)TotalPFCandidates,event_weight);
    h_NhPercCons[histoNumber]->Fill(NeutralPFCandidates/(float)TotalPFCandidates,event_weight);
    h_GammaPercCons[histoNumber]->Fill(GammaPFCandidates/(float)TotalPFCandidates,event_weight);

    h_LepPtFrac[histoNumber]->Fill(LepPtFrac,event_weight);
  }

  fillRegion(histoNumber,event_weight);
}

void ZprimeJetsClass::getPt123Frac() {
  // Neutral, Charged, Photon
  int HadronID[3] = {130,211,22};
  double HadronPtFirst3[3] = {0,0,0};
  double HadronPt[3] = {0,0,0};
  double HadronEt[3] = {0,0,0};
  double HadronEta[3] = {0,0,0};
  double HadronEtaSq[3] = {0,0,0};
  int HadronIndex[3] = {0,0,0};
  
  for (int i = 0; i < j1PFConsPID.size(); i++) {
    int ID = abs(j1PFConsPID[i]);
    if (ID == 11 || ID == 13) {
      LeptonPFCandidates++;
      LepPtFrac += j1PFConsPt[i];
    }
    if (i < 3)
      Pt123 += j1PFConsPt.at(i);
    for (int j = 0; j < 3; j++)
      if (abs(j1PFConsPID.at(i)) == HadronID[j]) {
	if (i < 3)
	  HadronPtFirst3[j] += j1PFConsPt.at(i);
	HadronPt[j] += j1PFConsPt.at(i);
	HadronEt[j] += j1PFConsEt.at(i);
	HadronEta[j] += j1PFConsEta.at(i)*j1PFConsEt.at(i);
	HadronEtaSq[j] += j1PFConsEta.at(i)*j1PFConsEta.at(i)*j1PFConsEt.at(i);

	if (HadronIndex[j] < 3) {
	  hadronFirst3Frac[j] += j1PFConsPt.at(i);
	  HadronIndex[j]++;
	}
      }
    
  }
  Pt123Fraction = Pt123/jetPt->at(jetCand[0]);
  PtRawFrac = Pt123/jetRawPt->at(jetCand[0]);
  ChPtFrac = HadronPtFirst3[1]/HadronPt[1];
  ChTotPtFrac = HadronPtFirst3[1]/jetPt->at(jetCand[0]);
  ChNemPtFrac = (HadronPtFirst3[1]+HadronPtFirst3[2])/(HadronPt[1]+HadronPt[2]);
  ChNemTotPtFrac = (HadronPtFirst3[1]+HadronPtFirst3[2])/jetPt->at(jetCand[0]);
  LepPtFrac /= jetPt->at(jetCand[0]);
  
  for (int i = 0; i < 3; i++){
    hadronTotPtFrac[i] = HadronPtFirst3[i]/jetPt->at(jetCand[0]);
    hadronFirst3Frac[i] /= jetPt->at(jetCand[0]);
  }

  double etaAvg = (HadronEta[1]+HadronEta[2])/(HadronEt[1]+HadronEt[2]);
  double etaSqAvg = (HadronEtaSq[1]+HadronEtaSq[2])/(HadronEt[1]+HadronEt[2]);
  j1ChNemEtaWidth = sqrt(etaSqAvg - (etaAvg*etaAvg));
}

void ZprimeJetsClass::AllPFCand(vector<int> jetCand,vector<int> PFCandidates) {
  //getPFCandidatesMethod for the Pencil Jet -> jetCand[0]
  TotalPFCandidates=ChargedPFCandidates=NeutralPFCandidates=GammaPFCandidates=0;
  LeptonPFCandidates=0;
    
  Pt123Fraction=Pt123=0.0;
  ChPtFrac=ChTotPtFrac=ChNemPtFrac=ChNemTotPtFrac=j1ChNemEtaWidth=0.0;
  for (int i = 0; i < 3; i++){
    hadronTotPtFrac[i] = 0.;
    hadronFirst3Frac[i] = 0.;
  }
  //We are using these conditions so we only calculate the following quantities for the signal we are interested in
  //This will also make it faster to process the events
  if(jetCand.size()>0) {
    j1PFConsEt=JetsPFConsEt->at(jetCand[0]);
    j1PFConsPt=JetsPFConsPt->at(jetCand[0]);
    j1PFConsEta=JetsPFConsEta->at(jetCand[0]);
    j1PFConsPhi=JetsPFConsPhi->at(jetCand[0]);
    j1PFConsPID=JetsPFConsPID->at(jetCand[0]);
    PFCandidates = getPFCandidates();

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
double ZprimeJetsClass::deltaR(double eta1, double phi1, double eta2, double phi2) {
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
float ZprimeJetsClass::DeltaPhi(float phi1, float phi2) {
  float pi = TMath::Pi();
  float dphi = fabs(phi1-phi2);
  if(dphi>pi)
    dphi = 2.0*pi - dphi;
  return dphi;
}
float ZprimeJetsClass::dPhiJetMETmin(vector<int> jets) {
  float dPhimin=TMath::Pi();
  int njetsMax = jets.size();
  if(njetsMax > 4)
    njetsMax = 4;
  for(int j=0;j< njetsMax; j++) {
    float dPhi = DeltaPhi((*jetPhi)[j],pfMETPhi);
    //cout<<"DeltaPhi: "<<dPhi<<endl;
    if(dPhi < dPhimin)
      dPhimin = dPhi;
  }
  return dPhimin;
}

vector<int> ZprimeJetsClass::getJetCand(double jetPtCut, double jetEtaCut, double jetNHFCut, double jetCHFCut){

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
vector<int>ZprimeJetsClass::getPFCandidates() {
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

bool ZprimeJetsClass::btagVeto() {

  bool btagVeto = true;
  for(int i = 0; i < nJet; i++)
    if(jetPt->at(i) > 30.0 && fabs(jetEta->at(i)) < 2.5 && jetCSV2BJetTags->at(i) > 0.8484)
      btagVeto = false;
  return btagVeto;
}

bool ZprimeJetsClass::dPhiJetMETcut(vector<int> jets) {
  //reject jet if it is found within DeltaPhi(jet,MET) < 0.5 
  bool passes = false;
  
  int njetsMax = jets.size();
  //Only look at first four jets (because that's what monojet analysis do)
  if(njetsMax > 4)
    njetsMax = 4;
  int j=0;
  for(;j< njetsMax; j++)
    if(DeltaPhi((*jetPhi)[j],pfMETPhi) < 0.5)
      break;

  if(j==njetsMax)
    passes = true;

  return passes;
  
}
