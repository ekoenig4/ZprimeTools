//For use with Ntuples made from JetAnalyzer
////Required arguments: 1 is folder containing input files, 2 is output file path, 3 is maxEvents (-1 to run over all events), 4 is reportEvery
////
////To compile using rootcom to an executable named 'analyze':
////$ ./rootcom ZprimeClass analyze
////
////To run, assuming this is compiled to an executable named 'analyze':
////$ ./analyze /hdfs/store/user/uhussain/Zprime_Ntuples/ /cms/uhussain/MonoZprimeJet/CMSSW_8_0_8/src/LightZPrimeAnalysis/JetAnalyzer/test/output.root -1 10000
////Runs over every event in the folder Zprime_Ntuples, reporting progress every 10000 events
////and storing the resulting histograms in the file output.root.
////
//
#define ZprimeClass_cxx
#include "ZprimeClass.h"
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

int main(int argc, const char* argv[]) { 
  if (argc == 1) {
    printf("Running Test\n");
    argv[1] = "/hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_102X_JECv32/WJets/WJetsToLNu_HT400-600/0000/";
    argv[2] = "test.root";
    argv[3] = "5000";
    argv[4] = "100";
    argv[5] = "1-1";
    argc = 6;
  }
  const char* inputFilename = argv[1];
  const char* outputFilename = argv[2];
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
  if ( !TFile( (string(inputFilename) + string(argv[5])).c_str() ).IsZombie() ) {
    vector<const char*>filelist;
    for (int i = 5; i < argc; i++) filelist.push_back( argv[i] );
    ZprimeClass t(inputFilename,outputFilename,filelist);
    t.Loop(maxEvents,reportEvery);
  } else {
    const char* fileRange = argv[5];
    ZprimeClass t(inputFilename,outputFilename,fileRange);
    t.Loop(maxEvents,reportEvery);
  }
  return 0;
}

void ZprimeClass::Loop(Long64_t maxEvents, int reportEvery) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  cout<<"Coming in:"<<endl;
  cout<<"nentries:"<<nentries<<endl;
  Long64_t nentriesToCheck = nentries;

  int nTotal = 0;

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
      
      if (isW_or_ZJet()) {
	SetBoson(sample.PID);
	ApplyKFactor(event_weight);
      }
    }

    float weightNorm = event_weight;
    jetCand   = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
    SetJetPFInfo(jetCand);
    cutflow->Fill("Total Events",genWeight);
    fillHistos(0,genWeight);
    for (int bit = 0; bit < 8; bit++)
      if (metFilters >> bit & 1 == 1)
	h_metfilters->Fill(bit + 1,event_weight);
    
    if (metFilters == 0 && inclusiveCut()) { 
      cutflow->Fill("metFilters",event_weight);
      fillHistos(1,event_weight);
      
      if ((HLTEleMuX>>5&1) == 1 || (HLTEleMuX>>6&1) == 1 || (HLTPho>>11&1) == 1 || !sample.isData) {
	cutflow->Fill("Trigger",event_weight);
	fillHistos(2,event_weight);
	
	if(jetCand.size()>0) {
	  cutflow->Fill("GoodJet",event_weight);
	  fillHistos(3,event_weight);
	  //CR code
	  //At least one of the one electrons passes the tight selection
	  vector<int> elelist = electron_tightID(jetCand[0],eleTightPtCut);
	  vector<int> looseEles = electron_looseID(jetCand[0],eleLoosePtCut);
	  
	  if( CRSelection(elelist,looseEles) ) {
	    if (!sample.isData) {
	      SetSF( getSF(lepindex) );
	      ApplySF(event_weight);
	    }
	    cutflow->Fill("CRSelection",event_weight);
	    fillHistos(4,event_weight);
	    
	    if (recoil > recoilCut) {
	      cutflow->Fill("leptoMetCut",event_weight);
	      fillHistos(5,event_weight);
	      bool muVeto = muon_veto(jetCand[0],lepindex,muLoosePtCut);
	      bool phoVeto = photon_veto(jetCand[0],lepindex,phoLoosePtCut);
	      bool tauVeto = tau_veto(jetCand[0],lepindex,tauLoosePtCut);
	      
	      if(muVeto && phoVeto && tauVeto) {
		cutflow->Fill("LeptonVeto",event_weight);
		fillHistos(6,event_weight);
		Float_t lepMET_MT = getMt(elePt->at(lepindex),elePhi->at(lepindex),pfMET,pfMETPhi);
		h_lepMET_MT->Fill(lepMET_MT,event_weight);

		if (lepMET_MT < lepMETMtCut) {
		  cutflow->Fill("lepMETMt160",event_weight);
		  fillHistos(7,event_weight);
		
		  if(pfMET > pfMET50Cut) {
		    cutflow->Fill("pfMET50",event_weight);
		    fillHistos(8,event_weight);
		    float metcut = (fabs(pfMET-caloMET))/recoil;
		    h_metcut->Fill(metcut,event_weight);
		  
		    if(metcut < metRatioCut) {
		      cutflow->Fill("caloMETCut",event_weight);
		      fillHistos(9,event_weight);
		    
		      if(btagVeto()) {
			cutflow->Fill("B-JetVeto",event_weight);
			fillHistos(10,event_weight);
			vector<int> jetveto = JetVetoDecision(lepindex);
			float minDPhiJetMET_first4 = dPhiJetMETmin(jetveto,recoilPhi);
			h_dphimin->Fill(minDPhiJetMET_first4,event_weight);
		      
			if(minDPhiJetMET_first4 > dPhiJetMETCut) {
			  cutflow->Fill("DeltaPhiCut",event_weight);
			  fillHistos(11,event_weight);

			  if( getEleHEMVeto(eleHEMVetoPtCut) ) {
			    cutflow->Fill("eleHEMVeto",event_weight);
			    fillHistos(12,event_weight);
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
    }
    
    if (jentry%reportEvery == 0)
      cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<endl;
  }
  
}//Closing the Loop function

void ZprimeClass::BookHistos(const char* outputFilename) {

  output = new TFile(outputFilename, "RECREATE");
  output->cd();

  cutflow = new Cutflow( {"Total Events","metFilters","Trigger","GoodJet","CRSelection","leptoMetCut","LeptonVeto","lepMETMt160","pfMET50","caloMETCut","B-JetVeto","DeltaPhiCut","eleHEMVeto"});

  BookHistos(-1,"");
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
      scaleUncs.setTree(tree);
      shapeUncs.setDir(treedir);
      dir->cd();
    }
    //Common Histograms
    BookHistos(i,histname);
  }
}

void ZprimeClass::fillHistos(int nhist,float event_weight) {
  // cout << nhist << endl;
  ZprimeYear::fillHistos(nhist,event_weight);
  ZprimeSingleCR::fillHistos(nhist,event_weight);
  weight = event_weight;
  if (nhist == bHisto) tree->Fill();
}


void ZprimeClass::JetEnergyScale(float start_weight) {
  // 2 Histograms
  //     up  dn
  //jes  0   1
  string uncname = "JES";
  if ( !shapeUncs.contains(uncname) ) {
    shapeUncs.addUnc(uncname);

    initTree(shapeUncs.getTreeUp(uncname));
    initTree(shapeUncs.getTreeDn(uncname));
  }
  
  vector<int> jetCandNorm;
  for(int cand : jetCand) jetCandNorm.push_back(cand);
  vector<float> jetPtNorm;
  for (float pt : (*jetPt)) jetPtNorm.push_back(pt);
  float pfMETNorm = pfMET;
  float pfMETPhiNorm = pfMETPhi;

  int lepindexNorm = lepindex;
  float recoilNorm = recoil;
  float recoilPhiNorm = recoilPhi;
  
  
  int unclist[2] = {1,-1};
  for (int unc : unclist) {
    jetCand     .clear();
    j1PFConsEt  .clear();
    j1PFConsPt  .clear();
    j1PFConsEta .clear();
    j1PFConsPhi .clear();
    j1PFConsPID .clear();

    float event_weight = start_weight;

    for (int i = 0; i < nJet; i++)
      jetPt->at(i) = jetPtNorm[i]*(1+unc*jetJECUnc->at(i));
    if (unc == 1) {
      pfMET = pfMET_T1JESUp;
      pfMETPhi = pfMETPhi_T1JESUp;
    }
    if (unc == -1) {
      pfMET = pfMET_T1JESDo;
      pfMETPhi = pfMETPhi_T1JESDo;
    }
    
    jetCand = getJetCand(jetCandPtCut,jetCandEtaCut,jetCandNHFCut,jetCandCHFCut);
    SetJetPFInfo(jetCand);
    //CR Variables
    lepindex = -1;
    recoil = -99;
    
    if (metFilters == 0 && inclusiveCut()) { 
      
      if ((HLTEleMuX>>5&1) == 1 || (HLTEleMuX>>6&1) == 1 || (HLTPho>>11&1) == 1 || !sample.isData) {
	
	if(jetCand.size()>0) {
	  //CR code
	  //At least one of the one electrons passes the tight selection
	  vector<int> elelist = electron_tightID(jetCand[0],eleTightPtCut);
	  vector<int> looseEles = electron_looseID(jetCand[0],eleLoosePtCut);
	  
	  if( CRSelection(elelist,looseEles) ) {
	    if (!sample.isData) event_weight *= getSF(lepindex);
	    
	    if (recoil > recoilCut) {
	      bool muVeto = muon_veto(jetCand[0],lepindex,muLoosePtCut);
	      bool phoVeto = photon_veto(jetCand[0],lepindex,phoLoosePtCut);
	      bool tauVeto = tau_veto(jetCand[0],lepindex,tauLoosePtCut);
	      
	      if(muVeto && phoVeto && tauVeto) {
		Float_t lepMET_MT = getMt(elePt->at(lepindex),elePhi->at(lepindex),pfMET,pfMETPhi);

		if (lepMET_MT < lepMETMtCut) {
		
		  if(pfMET > pfMET50Cut) {
		    float metcut = (fabs(pfMET-caloMET))/recoil;
		  
		    if(metcut < metRatioCut) {
		    
		      if(btagVeto()) {
			vector<int> jetveto = JetVetoDecision(lepindex);
			float minDPhiJetMET_first4 = dPhiJetMETmin(jetveto,pfMETPhi);
		      
			if(minDPhiJetMET_first4 > dPhiJetMETCut) {
			  
			  if( getEleHEMVeto(eleHEMVetoPtCut) ) {
			    weight = event_weight;
			    if (unc == 1)  shapeUncs.fillUp(uncname);// up
			    if (unc == -1) shapeUncs.fillDn(uncname);// down
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
    }
  }
    
  jetCand     .clear();
  for (int cand : jetCandNorm) jetCand.push_back(cand);
  SetJetPFInfo(jetCand);
  for (int i = 0; i < jetPtNorm.size(); i++) jetPt->at(i) = jetPtNorm[i];
  pfMET = pfMETNorm;
  pfMETPhi = pfMETPhiNorm;

  lepindex = lepindexNorm;
  recoil = recoilNorm;
  recoilPhi = recoilPhiNorm;
}//Closing the Loop function



