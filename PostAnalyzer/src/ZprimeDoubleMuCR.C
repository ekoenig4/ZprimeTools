#ifndef ZprimeDoubleCR_C
#define ZprimeDoubleCR_C

#include "ZprimeDoubleCR.h"
#include "VariableBins.h"
#include "ZprimeCutConfig.h"
#include "Utilities.h"

using namespace std;

const string ZprimeDoubleCR::REGION = "DoubleMuCR";

void ZprimeDoubleCR::initVars() {
  lepindex_leading = lepindex_subleading = -1;
  dilepton_mass = dilepton_pt = -1;
}

void ZprimeDoubleCR::BookHistos(int i,string histname) {
  if (i == -1) {
    
  } else {
    auto Name = [histname](string name) { return (name + histname); };
    
    h_leadingLeptonPt[i]     = MakeTH1F(new TH1F(Name("leadingLeptonPt").c_str()    ,"leadingLeptonPt;Leading Lepton P_{T} (GeV)"       ,nLeadingLeptonPtBins,LeadingLeptonPtBins));   
    h_leadingLeptonEta[i]    = MakeTH1F(new TH1F(Name("leadingLeptonEta").c_str()   ,"leadingLeptonEta;Leading Lepton #eta"             ,nEtaBins,lEta,uEta));              
    h_leadingLeptonPhi[i]    = MakeTH1F(new TH1F(Name("leadingLeptonPhi").c_str()   ,"leadingLeptonPhi;Leading Lepton #phi"             ,nPhiBins,lPhi,uPhi));        
    h_subleadingLeptonPt[i]  = MakeTH1F(new TH1F(Name("subleadingLeptonPt").c_str() ,"subleadingLeptonPt;Subleading Lepton P_{T} (GeV)" ,nSubLeadingLeptonPtBins,subLeadingLeptonPtBins));
    h_subleadingLeptonEta[i] = MakeTH1F(new TH1F(Name("subleadingLeptonEta").c_str(),"subleadingLeptonEta;Subleading Lepton #eta"       ,nEtaBins,lEta,uEta));              
    h_subleadingLeptonPhi[i] = MakeTH1F(new TH1F(Name("subleadingLeptonPhi").c_str(),"subleadingLeptonPhi;Subleading Lepton #phi"       ,nPhiBins,lPhi,uPhi));        
    h_dileptonPt[i]          = MakeTH1F(new TH1F(Name("dileptonPt").c_str()         ,"dileptonPt;Z P_{T} (GeV)"                         ,30,0.,1500.));              
    h_dileptonM[i]           = MakeTH1F(new TH1F(Name("dileptonM").c_str()          ,"dileptonM;Z Mass (GeV)"                           ,24,60.,120.));
    h_dileptonMall[i]        = MakeTH1F(new TH1F(Name("dileptonMall").c_str()       ,"dileptonM;Z Mass (GeV)"                           ,50,30.,200.));      
  }
}

void ZprimeDoubleCR::fillHistos(int nhist,float event_weight) {
  if(lepindex_leading >= 0 && lepindex_subleading >= 0){ 
    h_leadingLeptonPt[nhist]    ->Fill(muPt->at(lepindex_leading),event_weight);
    h_leadingLeptonEta[nhist]   ->Fill(muEta->at(lepindex_leading),event_weight);
    h_leadingLeptonPhi[nhist]   ->Fill(muPhi->at(lepindex_leading),event_weight);
    h_subleadingLeptonPt[nhist] ->Fill(muPt->at(lepindex_subleading),event_weight);
    h_subleadingLeptonEta[nhist]->Fill(muEta->at(lepindex_subleading),event_weight);
    h_subleadingLeptonPhi[nhist]->Fill(muPhi->at(lepindex_subleading),event_weight);
    
    h_dileptonPt[nhist]         ->Fill(dilepton_pt,event_weight);
    h_dileptonM[nhist]          ->Fill(dilepton_mass,event_weight);
    h_dileptonMall[nhist]       ->Fill(dilepton_mass,event_weight);
  }
}


bool ZprimeDoubleCR::CRSelection(vector<int> tightlist,vector<int> looselist) {
  float zero = 0.;
  for (int leading : tightlist) {
    for (int subleading : looselist) {
      //Event must have exactly two loose muons with opposite charge
      if (muCharge->at(leading)*muCharge->at(subleading) == -1) {
	float muPhoPU = muPFNeuIso->at(subleading) + muPFPhoIso->at(subleading) - 0.5*muPFPUIso->at(subleading);
	float muIso_combinedRelative = ( muPFChIso->at(subleading) + TMath::Max(zero,muPhoPU) )/muPt->at(subleading);
	  
	lep1.SetPtEtaPhiE(muPt->at(leading),muEta->at(leading),muPhi->at(leading),muE->at(leading));
	lep2.SetPtEtaPhiE(muPt->at(subleading),muEta->at(subleading),muPhi->at(subleading),muE->at(subleading));
	lepindex_leading = leading;
	lepindex_subleading = subleading;
	TLorentzVector ll = lep1 + lep2;
	dilepton_mass = ll.M();
	dilepton_pt = ll.Pt();
	
	TLorentzVector met_4vec;
	met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
	TLorentzVector leptoMET_4vec = ll+met_4vec;
	recoil = fabs(leptoMET_4vec.Pt());
	recoilPhi = leptoMET_4vec.Phi();
	
	if ( muIso_combinedRelative < 0.25) 
	  return true;
	return false;
      }
    }
  }
  return false;
}

float ZprimeDoubleCR::getSF(int leading,int subleading) {
  float leading_pt = muPt->at(leading); float leading_eta = muEta->at(leading); 
  float subleading_pt = muPt->at(subleading); float subleading_eta = muEta->at(subleading);
  
  float tightMuISO_SF_corr;
  float tightMuID_SF_corr; 
  float looseMuISO_SF_corr;
  float looseMuID_SF_corr;
  
  if ( th2fmap.contains("tightMuSF_ISO_abseta") ) {
    tightMuISO_SF_corr = th2fmap.getBin("tightMuSF_ISO_abseta",leading_pt,fabs(leading_eta));
    tightMuID_SF_corr = th2fmap.getBin("tightMuSF_ID_abseta",leading_pt,fabs(leading_eta));
    looseMuISO_SF_corr = th2fmap.getBin("looseMuSF_ISO_abseta",subleading_pt,fabs(subleading_eta));
    looseMuID_SF_corr = th2fmap.getBin("looseMuSF_ID_abseta",subleading_pt,fabs(subleading_eta));
  } else {
    tightMuISO_SF_corr = th2fmap.getBin("tightMuSF_ISO",leading_pt,leading_eta);
    tightMuID_SF_corr = th2fmap.getBin("tightMuSF_ID",leading_pt,leading_eta);
    looseMuISO_SF_corr = th2fmap.getBin("looseMuSF_ISO",subleading_pt,subleading_eta);
    looseMuID_SF_corr = th2fmap.getBin("looseMuSF_ID",subleading_pt,subleading_eta);
  }
  
  return tightMuISO_SF_corr*tightMuID_SF_corr*looseMuISO_SF_corr*looseMuID_SF_corr;
}

vector<int> ZprimeDoubleCR::jet_veto(int leading, int subleading) {
  vector<int> jetindex; jetindex.clear();
			  
  vector<int> tmpcands = jet_looseID();
  for (int ijet : tmpcands) {
    float dR_leading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      jetindex.push_back(ijet);
  }
  return jetindex;
}

bool ZprimeDoubleCR::electron_veto(int jet_index, int leading, int subleading, float elePtCut) {
  vector<int> ele_cands;
  ele_cands.clear();

  vector<int> tmpcands = electron_looseID(jet_index,elePtCut);
  for(int iele : tmpcands) {
    float dR_leading = deltaR(eleSCEta->at(iele),eleSCPhi->at(iele),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(eleSCEta->at(iele),eleSCPhi->at(iele),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso5Cut && dR_subleading > Iso5Cut )
      ele_cands.push_back(iele);
  }
  
  return ele_cands.size() == 0;
}

bool ZprimeDoubleCR::muon_veto(int jet_index,int leading,int subleading,float muPtCut) {
  return ZprimeAnalysis::muon_veto(jet_index,muPtCut);
}

bool ZprimeDoubleCR::photon_veto(int jet_index,int leading,int subleading,float phoPtCut) {
  vector<int> pho_cands; pho_cands.clear();

  vector<int> tmpcands = photon_looseID(jet_index,phoPtCut);
  for (int ipho : tmpcands ) {
    float dR_leading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(phoSCEta->at(ipho),phoSCPhi->at(ipho),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso5Cut && dR_subleading > Iso5Cut )
      pho_cands.push_back(ipho);
  }
  return pho_cands.size() == 0;
}

bool ZprimeDoubleCR::tau_veto(int jet_index,int leading,int subleading,float tauPtCut) {
  vector<int> tau_cands; tau_cands.clear();

  vector<int> tmpcands = tau_looseID(jet_index,tauPtCut);
  for (int itau : tmpcands ) {
    float dR_leading = deltaR(tauEta->at(itau),tauPhi->at(itau),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(tauEta->at(itau),tauPhi->at(itau),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      tau_cands.push_back(itau);
  }
  return tau_cands.size() == 0;
}

bool ZprimeDoubleCR::bjet_veto(int leading,int subleading) {
  vector<int> bjet_cands; bjet_cands.clear();

  vector<int> tmpcands = bjet_looseID();
  for (int ijet : tmpcands) {
    float dR_leading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(leading),muPhi->at(leading));
    float dR_subleading = deltaR(jetEta->at(ijet),jetPhi->at(ijet),muEta->at(subleading),muPhi->at(subleading));
    if ( dR_leading > Iso4Cut && dR_subleading > Iso4Cut )
      bjet_cands.push_back(ijet);
  }
  return bjet_cands.size() == 0;
}

#endif
