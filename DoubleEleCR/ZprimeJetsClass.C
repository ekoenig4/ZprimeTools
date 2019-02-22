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

double ZprimeJetsClass::getSF(int lepindex_leading, int lepindex_subleading) {
  double leadingElePt = elePt->at(lepindex_leading) < 500 ? elePt->at(lepindex_leading) : 499;
  double leadingEleEta = elePt->at(lepindex_leading) < 500 ? eleEta->at(lepindex_leading) : 2.49;
  double subleadingElePt = elePt->at(lepindex_subleading) < 500 ? elePt->at(lepindex_subleading) : 499;
  double subleadingEleEta = elePt->at(lepindex_subleading) < 500 ? eleEta->at(lepindex_subleading) : 2.49;
  // cout<<"leadingElePt = " << elePt->at(lepindex_leading) <<" leadingEleEta = " << eleEta->at(lepindex_leading) << endl;
  // cout<<"subleadingElePt = " << elePt->at(lepindex_subleading) <<" leadingEleEta = " << eleEta->at(lepindex_subleading) << endl;
  double leadingEleRecoSF_corr=h_eleRecoSF_highpt->GetBinContent(h_eleRecoSF_highpt->GetXaxis()->FindBin(leadingEleEta),h_eleRecoSF_highpt->GetYaxis()->FindBin(leadingElePt));
  double leadingEleEffSF_corr=h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(leadingEleEta),h_eleIDSF->GetYaxis()->FindBin(leadingElePt));
  double leadingEleTriggSF = EletriggerSF(elePt->at(lepindex_leading),eleEta->at(lepindex_leading));
  
  double subleadingEleRecoSF_corr=h_eleRecoSF_highpt->GetBinContent(h_eleRecoSF_highpt->GetXaxis()->FindBin(subleadingEleEta),h_eleRecoSF_highpt->GetYaxis()->FindBin(subleadingElePt));
  double subleadingEleEffSF_corr=h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(subleadingEleEta),h_eleIDSF->GetYaxis()->FindBin(subleadingElePt));
  double subleadingEleTriggSF = EletriggerSF(elePt->at(lepindex_subleading),eleEta->at(lepindex_subleading));
  // cout<<"leadingEleTriggSF = " << leadingEleTriggSF << endl;
  // cout<<"subleadingEleTriggSF = " << subleadingEleTriggSF << endl;
  return leadingEleRecoSF_corr*leadingEleEffSF_corr*leadingEleTriggSF*subleadingEleRecoSF_corr*subleadingEleEffSF_corr*subleadingEleTriggSF;
}

double ZprimeJetsClass::getKfactor(double bosonPt) {
  double kfactor = 1;
  double EWK_corrected_weight = 1.0*(ewkCorrection->GetBinContent(ewkCorrection->GetXaxis()->FindBin(bosonPt)));
  double NNLO_weight = 1.0*(NNLOCorrection->GetBinContent(NNLOCorrection->GetXaxis()->FindBin(bosonPt)));
  if(EWK_corrected_weight!=0 && NNLO_weight!=0)
    kfactor = (EWK_corrected_weight/NNLO_weight);
  else
    kfactor= sample.type == WJets ? 1.21 : 1.23;
  return kfactor;
}

bool ZprimeJetsClass::inclusiveCut() {
  if (sample.isInclusive)
    return genHT < 100;
  else
    return true;
}

void ZprimeJetsClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;
  double nTotalEvents,nFilters, nHLT, nCRSelection, nMET200, ndilepton, nNoMuons, nMETcut,nbtagVeto, nDphiJetMET,nJetSelection;
  nTotalEvents = nFilters = nHLT = nCRSelection = nMET200 = ndilepton = nNoMuons = nMETcut = nDphiJetMET = nbtagVeto = nJetSelection = 0;
  vector<int> jetveto;
  vector<int> PFCandidates;
  float dphimin = -99;

  if (!sample.isData) {
    //This is the PU histogram obtained from Nick's recipe
    TFile *weights = TFile::Open("PU_Central.root");
    PU = (TH1D*)weights->Get("pileup");
    
    TFile *f_eleReconstrucSF_highpt=new TFile("egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
    TFile *f_eleIDeffSF=new TFile("egammaEffi.txt_EGM2D_runBCDEF_passingTight94X.root");
    h_eleRecoSF_highpt=(TH2F*) f_eleReconstrucSF_highpt->Get("EGamma_SF2D");
    h_eleIDSF=(TH2F*) f_eleIDeffSF->Get("EGamma_SF2D");

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
    bool WofZfound = false;
    if (!sample.isData) {
      //For each event we find the bin in the PU histogram that corresponds to puTrue->at(0) and store
      //binContent as event_weight
      int bin = PU->GetXaxis()->FindBin(puTrue->at(0));
      event_weight = PU->GetBinContent(bin);
      //cout<<"event_weight: "<<event_weight<<endl;
      fabs(genWeight) > 0.0 ? event_weight*=genWeight/fabs(genWeight) : event_weight =0.0;

      if(sample.isW_or_ZJet()) {
	//check which mc particle is W boson
	for(int i=0; i<nMC;i++){
	  if((*mcPID)[i] == sample.PID){
	    WofZfound=true;
	    bosonPID = (*mcPID)[i];
	    bosonPt = (*mcPt)[i];
	  }
	}
      }
    }
    float metcut= 0.0;
    
    jetCand = getJetCand(200,2.5,0.8,0.1);
    AllPFCand(jetCand,PFCandidates);
    //CR Variables
    lepindex_leading = -1;
    lepindex_subleading = -1;
    dilepton_pt = dilepton_mass = Recoil=-99;
    nTotalEvents++;
    fillHistos(0,event_weight);
    if (metFilters==0 && inclusiveCut()){ 
        nFilters++;
        fillHistos(1,event_weight);
	if (HLTEleMuX>>5&1 == 1 || HLTEleMuX>>6&1 == 1 || HLTPho>>11&1 == 1 || !sample.isData) {
	    nHLT++;
	    fillHistos(2,event_weight);
	    if(jetCand.size()>0){
		nJetSelection++;
		fillHistos(3,event_weight);
		if (sample.isW_or_ZJet()) event_weight *= getKfactor(bosonPt);
		//CR code
		//At least one of the two electrons passes the tight selection
		vector<int> elelist = electron_veto_looseID(jetCand[0],0,0,10.0);
		vector<int> elelist_leading = electron_veto_tightID(jetCand[0],40.0);
		vector<int> elelist_subleading = electron_veto_looseID(jetCand[0],0,0,10.0);
		vector<int> mulist;
		mulist.clear();   
		if(elelist.size() == 2){
                    bool elePairSet = false;
                    TLorentzVector e1, e2;
                    for(int i=0; i<elelist_leading.size(); ++i){
			for(int j=0; j<elelist_subleading.size(); ++j){
			    //Event must have exactly two loose electrons with opposite charge
			    if(eleCharge->at(elelist_leading[i])*eleCharge->at(elelist_subleading[j]) == -1){
				e1.SetPtEtaPhiE(elePt->at(elelist_leading[i]),eleEta->at(elelist_leading[i]),elePhi->at(elelist_leading[i]),eleEn->at(elelist_leading[i]));
				e2.SetPtEtaPhiE(elePt->at(elelist_subleading[j]),eleEta->at(elelist_subleading[j]),elePhi->at(elelist_subleading[j]),eleEn->at(elelist_subleading[j]));
				mulist = muon_veto_looseID(jetCand[0],elelist_leading[i],elelist_subleading[j],10.0);
				jetveto = JetVetoDecision(elelist_leading[i],elelist_subleading[j]);
				elePairSet = true;
				lepindex_leading = elelist_leading[i];
				lepindex_subleading = elelist_subleading[j];
				break;
			      }
			  }
			if(elePairSet)
			  break;
		      }
                    
                    if(elePairSet){
			nCRSelection++;
			fillHistos(4,event_weight);
			if (!sample.isData) event_weight *= getSF(lepindex_leading,lepindex_subleading);
			TLorentzVector ll = e1+e2;
			dilepton_mass = ll.M();
			dilepton_pt = ll.Pt();
                      
			TLorentzVector met_4vec;
			met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
			TLorentzVector leptoMET_4vec = ll+met_4vec;
			Double_t leptoMET = fabs(leptoMET_4vec.Pt());
			Double_t leptoMET_phi = leptoMET_4vec.Phi();
			Recoil = leptoMET;
			metcut = (fabs(pfMET-caloMET))/Recoil;
			if (leptoMET>250){
			    nMET200++;
			    fillHistos(5,event_weight);
			    //invariant mass of the two electrons is betwen 60 and 120GeV
			    if(dilepton_mass > 60 && dilepton_mass < 120){
                                ndilepton++;
				fillHistos(6,event_weight);
                                if(mulist.size() == 0){
                                    nNoMuons++;
				    fillHistos(7,event_weight);
                                    h_metcut->Fill(metcut);
				    if(metcut < 0.5){
                                        nMETcut++;
					fillHistos(8,event_weight);
                                        if(btagVeto()){
                                            nbtagVeto++;
					    fillHistos(9,event_weight);
					    double minDPhiJetMET_first4 = TMath::Pi();
                                            // cout<<"JetVetoSize: "<<jetveto.size()<<endl;
                                            for(int j = 0; j < jetveto.size(); j++){
						double minDPhiJetMET = DeltaPhi(jetPhi->at(jetveto[j]),pfMETPhi);
						if(DeltaPhi(jetPhi->at(jetveto[j]),pfMETPhi) < minDPhiJetMET)
						    if(j < 4)
						      minDPhiJetMET_first4 = DeltaPhi(jetPhi->at(jetveto[j]),pfMETPhi);
					      }
					    h_dphimin->Fill(minDPhiJetMET_first4);
					    if(dPhiJetMETcut(jetveto)){
						nDphiJetMET++;
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
      }
    tree->Fill();

    if (jentry%reportEvery == 0){
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
    }
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

void ZprimeJetsClass::BookHistos(const char* outputFilename){
  output = new TFile(outputFilename, "RECREATE");
  tree = new TTree("ZprimeJet","ZprimeJet");
  output->cd();
   
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

  float MtBins[51]={180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.,3000.};
  
  float MetBins[45]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		     780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1400.,1800.,2000.,2500.};

  float PtBins[49]={200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,600.,620.,640.,660.,680.,700.,720.,740.,760.,
		    780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};

  float LeadingLeptonPtBins[25] = {20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  float subLeadingLeptonPtBins[26] = {10.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,250.,300.,350.,400.,500.,600.,700.,800.,900.,1000.,1100.,1200.,1300.,1400.,1500.};

  float Pt123Bins[59]={0.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.,220.,240.,260.,280.,300.,320.,340.,360.,380.,400.,420.,440.,460.,480.,500.,520.,540.,560.,580.,
		       600.,620.,640.,660.,680.,700.,720.,740.,760.,780.,800.,820.,840.,860.,880.,900.,920.,940.,960.,980.,1000.,1050.,1100.,1200.,1300.,1400.,1500.,2000.,2500.};
  
  h_metcut  = new TH1F("h_metcut","h_metcut; |pfMET-caloMET|/pfMET", 50,0,1.2);h_metcut->Sumw2();
  h_dphimin = new TH1F("h_dphimin","h_dphimin; Minimum dPhiJetMET",50,0,3.2);h_dphimin->Sumw2();
  for(int i=0; i<nHisto; i++){

    char ptbins[100];
    sprintf(ptbins, "_%d", i);
    string histname(ptbins);
    h_metFilters[i] = new TH1F(("metFilters"+histname).c_str(),"metFilters",50,0,3000); h_metFilters[i]->Sumw2();
    h_nJets[i]   = new TH1F(("nJets"+histname).c_str(), "nJets;Number of Jets", 16, 0, 16);h_nJets[i]->Sumw2();
    h_pfMETall[i] =  new TH1F(("pfMETall"+histname).c_str(), "pfMET",50,0,2000);h_pfMETall[i] ->Sumw2(); 
    h_pfMET200[i] = new TH1F(("pfMET200"+histname).c_str(), "pfMET",50,170,1500);h_pfMET200[i] ->Sumw2(); 
    h_pfMET[i] = new TH1F(("pfMET"+histname).c_str(), "E_{T}^{miss} (GeV)",44,MetBins);h_pfMET[i] ->Sumw2();
    h_pfMETPhi[i] = new TH1F(("pfMETPhi"+histname).c_str(), "pfMETPhi",50,-4,4);h_pfMETPhi[i]->Sumw2();
    h_j1Pt[i]  = new TH1F(("j1pT"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt[i]->Sumw2();
    h_j1Eta[i] = new TH1F(("j1Eta"+histname).c_str(), "j1Eta; #eta of Leading Jet", 50, -3.0, 3.0);h_j1Eta[i]->Sumw2();
    h_j1Phi[i] = new TH1F(("j1Phi"+histname).c_str(), "j1Phi; #phi of Leading Jet", 50, -3.0, 3.0);h_j1Phi[i]->Sumw2();
    h_j1etaWidth[i] = new TH1F(("j1etaWidth"+histname).c_str(),"j1etaWidh; #eta width of Leading Jet", 50,0,0.25);h_j1etaWidth[i] ->Sumw2();
    h_j1phiWidth[i] = new TH1F(("j1phiWidth"+histname).c_str(),"j1phiWidth; #phi width of Leading Jet", 50, 0,0.5);h_j1phiWidth[i]->Sumw2();
    h_j1nCons[i] = new TH1F (("j1nCons"+histname).c_str(),"j1nCons; Number of Constituents of Leading Jet",25, 0, 50);h_j1nCons[i]->Sumw2();
    h_PF123PtFraction[i]= new TH1F(("PF123PtFraction"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction[i]->Sumw2();
    h_Pt123[i] = new TH1F(("Pt123"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",48,Pt123Bins);h_Pt123[i]->Sumw2();
    h_PFConsPt[i] = new TH1F(("PFConsPt"+histname).c_str(),"PFConsPt; P_{T} sum carried by each constituent of the Pencil jet",48,PtBins);h_PFConsPt[i]->Sumw2();
    h_j1TotPFCands[i] = new TH1F(("j1TotPFCands"+histname).c_str(),"j1TotPFCands;# of all PF candidates in Leading Jet",251,-0.5,250.5);h_j1TotPFCands[i]->Sumw2();
    h_j1ChPFCands[i] = new TH1F(("j1ChPFCands"+histname).c_str(),"j1ChPFCands;# of PF charged hadrons in Leading Jet",151,-0.5,150.5);h_j1ChPFCands[i]->Sumw2();
    h_j1NeutPFCands[i] = new TH1F(("j1NeutPFCands"+histname).c_str(),"j1NeutPFCands;# of PF neutral hadrons in Leading Jet",16,-0.5,15.2);h_j1NeutPFCands[i]->Sumw2();
    h_j1GammaPFCands[i] = new TH1F(("j1GammaPFCands"+histname).c_str(),"j1GammaPFCands;# of PF gammas in Leading Jet",101,-0.5,100.5);h_j1GammaPFCands[i]->Sumw2();
    h_j1CHF[i] = new TH1F(("j1CHF"+histname).c_str(),"j1CHF;Charged Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1CHF[i]->Sumw2(); 
    h_j1NHF[i] = new TH1F(("j1NHF"+histname).c_str(),"j1NHF;Neutral Hadron Energy Fraction in Leading Jet",50,0,1.1);h_j1NHF[i]->Sumw2(); 
    h_j1ChMultiplicity[i] = new TH1F(("j1ChMultiplicity"+histname).c_str(),"j1ChMultiplicity;Charged Multiplicity of Leading Jet",25,0,50);h_j1ChMultiplicity[i]->Sumw2();
    h_j1NeutMultiplicity[i] = new TH1F(("j1NeutMultiplicity"+histname).c_str(),"j1NeutMultiplicity;Neutral Multiplicity of Leading Jet",25,0,50);h_j1NeutMultiplicity[i]->Sumw2(); 
    h_j1Mt[i]  = new TH1F(("j1Mt"+histname).c_str(), "j1Mt;M_{T} of Leading Jet (GeV)", 50,MtBins);h_j1Mt[i]->Sumw2(); 
    h_nVtx[i] = new TH1F(("nVtx"+histname).c_str(),"nVtx;nVtx",70,0,70);h_nVtx[i]->Sumw2();
    h_nPFCons_jetPt[i] = new TH2F(("nPFCons_jetPt"+histname).c_str(),"Number Of PFCons vs. jetPt;Leading Jet P_{T};# of PF Constituents in the Pencil Jet",50,0,2000,25,0,50);
    h_PtFrac_PtEta[i] = new TH3F(("PtFrac_PtEta"+histname).c_str(),"PtFraction;Leading Jet P_{T};Leading Jet #eta;PtFraction",50,0,2000,50,-3.0,3.0,50,0,1);
    h_PtFrac_PtPhi[i] = new TH3F(("PtFrac_PtPhi"+histname).c_str(),"PtFraction;Leading Jet P_{T};Leading Jet #phi;PtFraction",50,0,2000,50,-3.0,3.0,50,0,1);
    h_PtFrac_EtaPhi[i] = new TH3F(("PtFrac_EtaPhi"+histname).c_str(),"PtFraction;Leading Jet #eta;Leading Jet #phi;PtFraction",50,-3.0,3.0,50,-3.0,3.0,50,0,1);
    h_PtFrac_Pt123PFConsPt[i] = new TH3F(("PtFrac_Pt123PFConsPt"+histname).c_str(),"PtFraction;Pt123;PFConsPt;PtFraction",50,0,2000,50,0,2000,50,0,1);
    //CR Histograms
    h_leadingLeptonPt[i] = new TH1F(("h_leadingLeptonPt"+histname).c_str(),"h_leadingLeptonPt",24,LeadingLeptonPtBins);h_leadingLeptonPt[i]->Sumw2();
    h_leadingLeptonEta[i] = new TH1F(("h_leadingLeptonEta"+histname).c_str(),"h_leadingLeptonEta",30,-3.0,3.0);h_leadingLeptonEta[i]->Sumw2();
    h_leadingLeptonPhi[i] = new TH1F(("h_leadingLeptonPhi"+histname).c_str(),"h_leadingLeptonPhi",10,0.,3.1416);h_leadingLeptonPhi[i]->Sumw2();
    h_subleadingLeptonPt[i] = new TH1F(("h_subleadingLeptonPt"+histname).c_str(),"h_subleadingLeptonPt",25,subLeadingLeptonPtBins);h_subleadingLeptonPt[i]->Sumw2();
    h_subleadingLeptonEta[i] = new TH1F(("h_subleadingLeptonEta"+histname).c_str(),"h_subleadingLeptonEta",30,-3.0,3.0);h_subleadingLeptonEta[i]->Sumw2();
    h_subleadingLeptonPhi[i] = new TH1F(("h_subleadingLeptonPhi"+histname).c_str(),"h_subleadingLeptonPhi",10,0.,3.1416);h_subleadingLeptonPhi[i]->Sumw2();
    h_recoil[i] = new TH1F(("h_recoil"+histname).c_str(), "Recoil (GeV)",44,MetBins);h_recoil[i] ->Sumw2();
    h_dileptonPt[i] = new TH1F(("h_dileptonPt"+histname).c_str(),"h_dileptonPt",30,0.,1500.);h_dileptonPt[i]->Sumw2();
    h_dileptonM[i] = new TH1F(("h_dileptonM"+histname).c_str(),"h_dileptonM",24,60.,120.);h_dileptonM[i]->Sumw2();

    h_Pt123_Pt400[i] = new TH1F(("Pt123_Pt400"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",48,PtBins);h_Pt123_Pt400[i]->Sumw2();
    h_Pt123_Pt600[i] = new TH1F(("Pt123_Pt600"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",48,PtBins);h_Pt123_Pt600[i]->Sumw2();
    h_Pt123_PtInf[i] = new TH1F(("Pt123_PtInf"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",48,PtBins);h_Pt123_PtInf[i]->Sumw2();
    h_j1Pt_Pt400[i]  = new TH1F(("j1pT_Pt400"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt_Pt400[i]->Sumw2();
    h_j1Pt_Pt600[i]  = new TH1F(("j1pT_Pt600"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt_Pt600[i]->Sumw2();
    h_j1Pt_PtInf[i]  = new TH1F(("j1pT_PtInf"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt_PtInf[i]->Sumw2();
    h_PF123PtFraction_Pt400[i]= new TH1F(("PF123PtFraction_Pt400"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction_Pt400[i]->Sumw2();
    h_PF123PtFraction_Pt600[i]= new TH1F(("PF123PtFraction_Pt600"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction_Pt600[i]->Sumw2();
    h_PF123PtFraction_PtInf[i]= new TH1F(("PF123PtFraction_PtInf"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction_PtInf[i]->Sumw2();
    h_Pt123_jetPt400[i] = new TH1F(("Pt123_jetPt400"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",48,PtBins);h_Pt123_jetPt400[i]->Sumw2();
    h_Pt123_jetPt600[i] = new TH1F(("Pt123_jetPt600"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",48,PtBins);h_Pt123_jetPt600[i]->Sumw2();
    h_Pt123_jetPtInf[i] = new TH1F(("Pt123_jetPtInf"+histname).c_str(),"Pt123;P_{T} sum carried by 3 leading daughters of the Pencil Jet",48,PtBins);h_Pt123_jetPtInf[i]->Sumw2();
    h_j1Pt_jetPt400[i]  = new TH1F(("j1pT_jetPt400"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt_jetPt400[i]->Sumw2();
    h_j1Pt_jetPt600[i]  = new TH1F(("j1pT_jetPt600"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt_jetPt600[i]->Sumw2();
    h_j1Pt_jetPtInf[i]  = new TH1F(("j1pT_jetPtInf"+histname).c_str(), "j1pT;p_{T} of Leading Jet (GeV)", 48,PtBins);h_j1Pt_jetPtInf[i]->Sumw2();
    h_PF123PtFraction_jetPt400[i]= new TH1F(("PF123PtFraction_jetPt400"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction_jetPt400[i]->Sumw2();
    h_PF123PtFraction_jetPt600[i]= new TH1F(("PF123PtFraction_jetPt600"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction_jetPt600[i]->Sumw2();
    h_PF123PtFraction_jetPtInf[i]= new TH1F(("PF123PtFraction_jetPtInf"+histname).c_str(), "PF123PtFraction;P_{T} fraction carried by 3 leading daughters of the Pencil Jet" ,50,0,1);h_PF123PtFraction_jetPtInf[i]->Sumw2();
  }
}

void ZprimeJetsClass::fillHistos(int histoNumber,double event_weight){
  if (sample.isData) event_weight = 1;
  
  h_nVtx[histoNumber]->Fill(nVtx,event_weight);
  h_metFilters[histoNumber]->Fill(metFilters,event_weight);
  h_nJets[histoNumber]->Fill(nJet,event_weight);
  h_pfMETall[histoNumber]->Fill(pfMET,event_weight);
  h_pfMET200[histoNumber]->Fill(pfMET,event_weight);
  h_pfMET[histoNumber]->Fill(pfMET,event_weight);
  h_pfMETPhi[histoNumber]->Fill(pfMETPhi,event_weight);
  if(jetCand.size()>0){
    h_j1Pt[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
    h_j1Eta[histoNumber]->Fill(jetEta->at(jetCand[0]),event_weight);
    h_j1Phi[histoNumber]->Fill(jetPhi->at(jetCand[0]),event_weight);
    h_PF123PtFraction[histoNumber]->Fill(Pt123Fraction,event_weight);
    h_Pt123[histoNumber]->Fill(Pt123,event_weight);
    h_PFConsPt[histoNumber]->Fill(PFConsPt,event_weight);
    h_j1TotPFCands[histoNumber]->Fill(TotalPFCandidates,event_weight);
    h_j1ChPFCands[histoNumber]->Fill(ChargedPFCandidates,event_weight);
    h_j1NeutPFCands[histoNumber]->Fill(NeutralPFCandidates,event_weight);
    h_j1GammaPFCands[histoNumber]->Fill(GammaPFCandidates,event_weight);
    h_j1CHF[histoNumber]->Fill(jetCHF->at(jetCand[0]),event_weight);
    h_j1NHF[histoNumber]->Fill(jetNHF->at(jetCand[0]),event_weight);
    h_j1ChMultiplicity[histoNumber]->Fill(jetNCharged->at(jetCand[0]),event_weight);
    h_j1NeutMultiplicity[histoNumber]->Fill(jetNNeutral->at(jetCand[0]),event_weight);
    h_j1Mt[histoNumber]->Fill(jetMt->at(jetCand[0]),event_weight);
    h_j1etaWidth[histoNumber]->Fill(jetetaWidth->at(jetCand[0]),event_weight);
    h_j1phiWidth[histoNumber]->Fill(jetphiWidth->at(jetCand[0]),event_weight);
    h_j1nCons[histoNumber]->Fill(jetNPhoton->at(jetCand[0])+jetNChargedHad->at(jetCand[0])+jetNNeutralHad->at(jetCand[0]),event_weight);
    h_PtFrac_PtEta[histoNumber]->Fill(jetPt->at(jetCand[0]),jetEta->at(jetCand[0]),Pt123Fraction,event_weight);
    h_PtFrac_PtPhi[histoNumber]->Fill(jetPt->at(jetCand[0]),jetPhi->at(jetCand[0]),Pt123Fraction,event_weight);
    h_PtFrac_EtaPhi[histoNumber]->Fill(jetEta->at(jetCand[0]),jetPhi->at(jetCand[0]),Pt123Fraction,event_weight);
    h_PtFrac_Pt123PFConsPt[histoNumber]->Fill(Pt123,PFConsPt,Pt123Fraction,event_weight);
    h_nPFCons_jetPt[histoNumber]->Fill(jetPt->at(jetCand[0]),TotalPFCandidates,event_weight);

    if (Pt123 <= 400) {
      h_Pt123_Pt400[histoNumber]->Fill(Pt123,event_weight);
      h_j1Pt_Pt400[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
      h_PF123PtFraction_Pt400[histoNumber]->Fill(Pt123Fraction,event_weight);
    } else if (400 < Pt123 && Pt123 <= 600) {
      h_Pt123_Pt600[histoNumber]->Fill(Pt123,event_weight);
      h_j1Pt_Pt600[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
      h_PF123PtFraction_Pt600[histoNumber]->Fill(Pt123Fraction,event_weight);
    } else if (600 < Pt123) {
      h_Pt123_PtInf[histoNumber]->Fill(Pt123,event_weight);
      h_j1Pt_PtInf[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
      h_PF123PtFraction_PtInf[histoNumber]->Fill(Pt123Fraction,event_weight);
    }
    if (jetPt->at(jetCand[0]) <= 400) {
      h_Pt123_jetPt400[histoNumber]->Fill(Pt123,event_weight);
      h_j1Pt_jetPt400[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
      h_PF123PtFraction_jetPt400[histoNumber]->Fill(Pt123Fraction,event_weight);
    } else if (400 < jetPt->at(jetCand[0]) && jetPt->at(jetCand[0]) <= 600) {
      h_Pt123_jetPt600[histoNumber]->Fill(Pt123,event_weight);
      h_j1Pt_jetPt600[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
      h_PF123PtFraction_jetPt600[histoNumber]->Fill(Pt123Fraction,event_weight);
    } else if (600 < jetPt->at(jetCand[0])) {
      h_Pt123_jetPtInf[histoNumber]->Fill(Pt123,event_weight);
      h_j1Pt_jetPtInf[histoNumber]->Fill(jetPt->at(jetCand[0]),event_weight);
      h_PF123PtFraction_jetPtInf[histoNumber]->Fill(Pt123Fraction,event_weight);
    }
  }
  //CR Histograms
  if(lepindex_leading >= 0 && lepindex_subleading >= 0){
    h_leadingLeptonPt[histoNumber]->Fill(elePt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[histoNumber]->Fill(eleEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[histoNumber]->Fill(elePhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[histoNumber]->Fill(elePt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[histoNumber]->Fill(eleEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[histoNumber]->Fill(elePhi->at(lepindex_subleading),event_weight);
  }
  if(dilepton_pt >= 0 && dilepton_mass >= 0){
    h_recoil[histoNumber]->Fill(Recoil,event_weight);
    h_dileptonPt[histoNumber]->Fill(dilepton_pt,event_weight);
    h_dileptonM[histoNumber]->Fill(dilepton_mass,event_weight);
  }
}

void ZprimeJetsClass::getPt123Frac() {
  for (int i = 0; i < j1PFConsPID.size(); i++) {
    PFConsPt += j1PFConsPt.at(i);
    if (i < 3)
      Pt123 += j1PFConsPt.at(i);
  }
  Pt123Fraction = Pt123/jetPt->at(jetCand[0]);
}

void ZprimeJetsClass::AllPFCand(vector<int> jetCand,vector<int> PFCandidates) {
  //getPFCandidatesMethod for the Pencil Jet -> jetCand[0]
  TotalPFCandidates=ChargedPFCandidates=NeutralPFCandidates=GammaPFCandidates=0;
    
  Pt123Fraction=Pt123=0.0;
  //We are using these conditions so we only calculate the following quantities for the signal we are interested in
  //This will also make it faster to process the events
  if(jetCand.size()>0) {
    j1PFConsEt=jetConstEt->at(jetCand[0]);
    j1PFConsPt=jetConstPt->at(jetCand[0]);
    j1PFConsEta=jetConstEta->at(jetCand[0]);
    j1PFConsPhi=jetConstPhi->at(jetCand[0]);
    j1PFConsPID=jetConstPdgId->at(jetCand[0]);
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
    
    getPt123Frac();
  }
}

//Function to calculate regular deltaR separate from jet width variable 'dR'
double ZprimeJetsClass::deltaR(double eta1, double phi1, double eta2, double phi2){
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
float ZprimeJetsClass::DeltaPhi(float phi1, float phi2){
  float pi = TMath::Pi();
  float dphi = fabs(phi1-phi2);
  if(dphi>pi)
    dphi = 2.0*pi - dphi;
  return dphi;
}

float ZprimeJetsClass::dPhiJetMETmin(vector<int> jets){
  float dPhimin=TMath::Pi();
  int njetsMax = jets.size();
  if(njetsMax > 4)
    njetsMax = 4;
  for(int j=0;j< njetsMax; j++)
    {
      float dPhi = DeltaPhi((*jetPhi)[j],pfMETPhi);
      //cout<<"DeltaPhi: "<<dPhi<<endl;
      if(dPhi < dPhimin){
        dPhimin = dPhi;
      }
    }
  return dPhimin;
}

vector<int> ZprimeJetsClass::getJetCand(double jetPtCut, double jetEtaCut, double jetNHFCut, double jetCHFCut){

  //save the Pt of the jetCand as well, whether normal, shiftedUp or shiftedDown 
  vector<int> tmpCand;
  tmpCand.clear();
  //So only check if leading candidate will pass these cuts?
  for(int p=0;p<nJet;p++)
    {
      bool kinematic = (*jetPt)[p] > jetPtCut && (*jetNHF)[p] < jetNHFCut && (*jetCHF)[p] > jetCHFCut && fabs((*jetEta)[p])<jetEtaCut;
      bool tightJetID = false;
      if ((*jetID)[p]>>0&1 == 1) tightJetID = true;
      if(kinematic && tightJetID)
	tmpCand.push_back(p);
      }

  return tmpCand;
}

vector<int> ZprimeJetsClass::JetVetoDecision(int leading_lep_index, int subleading_lep_index) {

  bool jetVeto=true;
  vector<int> jetindex;

  for(int i = 0; i < nJet; i++){
    double deltar_leading = deltaR(jetEta->at(i),jetPhi->at(i),eleEta->at(leading_lep_index),elePhi->at(leading_lep_index));
    double deltar_subleading = deltaR(jetEta->at(i),jetPhi->at(i),eleEta->at(subleading_lep_index),elePhi->at(subleading_lep_index));
    bool tightJetID = false;
    if ((*jetID)[i]>>0&1 == 1) tightJetID = true;
    if(deltar_leading>0.4 && deltar_subleading>0.4 && jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && tightJetID)
      jetindex.push_back(i);  }
  return jetindex;
}

//Return a vector of pairs. "0" = #pfCands, "1"=#chargedPFCands , "3"=#neutralPFCands,"2"=#photonPFCands
//get PF Candidates of the selected Jet ->jetCand[0]
vector<int>ZprimeJetsClass::getPFCandidates() {
  vector<int>PFCands;
  int TotPFCands;
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
  return PFCands;
}

bool ZprimeJetsClass::btagVeto() {

  bool btagVeto = true;
  for(int i = 0; i < nJet; i++)
    if(jetPt->at(i) >30.0 && fabs(jetEta->at(i)) < 2.5 && jetCSV2BJetTags->at(i) > 0.8838)
      btagVeto = false;
  return btagVeto;
}

bool ZprimeJetsClass::dPhiJetMETcut(vector<int> jets){
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

vector<int> ZprimeJetsClass::electron_veto_tightID(int jet_index, float elePtCut){
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++){
    //Electron passes Tight Electron ID cuts
    if(eleIDbit->at(i)>>2&1 == 1){
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut){
	  //Electron does not overlap photon
	  if(deltaR(eleEta->at(i),elePhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    ele_cands.push_back(i);
	}
      }
    }
  }
  return ele_cands;
}

vector<int> ZprimeJetsClass::muon_veto_tightID(int jet_index, float muPtCut){
  // bool veto_passed = true; //pass veto if no good muon found
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++){
    if(muIDbit->at(i)>>3&1==1 && muIDbit->at(i)>>9&1==1){
      //Muon passes eta cut
      if (fabs(eleEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut){
	  //Muon does not overlap photon
	  if(deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

vector<int> ZprimeJetsClass::electron_veto_looseID(int jet_index, int leading_mu_index, int subleading_mu_index, float elePtCut){
  vector<int> ele_cands;
  ele_cands.clear();

  for(int i = 0; i < nEle; i++){
    //Electron passes Loose Electron ID cuts
    if(eleIDbit->at(i)>>0&1 == 1){
      //Electron passes eta cut
      if (fabs(eleEta->at(i)) < 2.5) {
	//Electron passes pt cut
	if(elePt->at(i) > elePtCut){
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
vector<int> ZprimeJetsClass::muon_veto_looseID(int jet_index, int leading_ele_index, int subleading_ele_index, float muPtCut){
  vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++){
    if(muIDbit->at(i)>>0&1==1){
      //Muon passes eta cut
      if (fabs(muEta->at(i)) < 2.4) {
	//Muon passes pt cut
	if(muPt->at(i) > muPtCut){
	  //Muon does not overlap photon
	  double dR_leadingEle = deltaR(muEta->at(i),muPhi->at(i),eleEta->at(leading_ele_index),elePhi->at(leading_ele_index));
	  double dR_subleadingEle = deltaR(muEta->at(i),muPhi->at(i),eleEta->at(subleading_ele_index),elePhi->at(subleading_ele_index));
	  if(dR_leadingEle > 0.5 && dR_subleadingEle > 0.5 && deltaR(muEta->at(i),muPhi->at(i),jetEta->at(jet_index),jetPhi->at(jet_index)) > 0.5)
	    mu_cands.push_back(i);
	}
      }
    }
  }
  return mu_cands;
}

