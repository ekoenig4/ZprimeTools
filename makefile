regions = SignalRegion SingleEleCR DoubleEleCR SingleMuCR DoubleMuCR

all:
	@$(MAKE) -C SignalRegion
	@$(MAKE) -C SingleEleCR
	@$(MAKE) -C DoubleEleCR
	@$(MAKE) -C SingleMuCR
	@$(MAKE) -C DoubleMuCR

clean:
	@$(MAKE) -C SignalRegion clean
	@$(MAKE) -C SingleEleCR clean
	@$(MAKE) -C DoubleEleCR clean
	@$(MAKE) -C SingleMuCR clean
	@$(MAKE) -C DoubleMuCR clean

condor_clean:
	@$(MAKE) -C SignalRegion condor_clean
	@$(MAKE) -C SingleEleCR condor_clean
	@$(MAKE) -C DoubleEleCR condor_clean
	@$(MAKE) -C SingleMuCR condor_clean
	@$(MAKE) -C DoubleMuCR condor_clean

condor_submit:
	@$(MAKE) -C SignalRegion condor_submit
	@$(MAKE) -C SingleEleCR condor_submit
	@$(MAKE) -C DoubleEleCR condor_submit
	@$(MAKE) -C SingleMuCR condor_submit
	@$(MAKE) -C DoubleMuCR condor_submit

hadd:
	@$(MAKE) -C SignalRegion hadd
	@$(MAKE) -C SingleEleCR hadd
	@$(MAKE) -C DoubleEleCR hadd
	@$(MAKE) -C SingleMuCR hadd
	@$(MAKE) -C DoubleMuCR hadd

plot:
	@$(MAKE) -C SignalRegion plot variable="h_cutflow ChNemPtFrac_8 ChNemPt123_8 ChNemPt_8 PF123PtFraction_8 Pt123_8 j1pT_8 j1Eta_8 j1Phi_8 j1TotPFCands_8 nVtx_8 pfMET_8"
	@$(MAKE) -C SingleEleCR plot variable="h_cutflow ChNemPtFrac_10 ChNemPt123_10 ChNemPt_10 PF123PtFraction_10 Pt123_10 j1pT_10 j1Eta_10 j1Phi_10 j1TotPFCands_10 nVtx_10 h_recoil_10 h_LeptonPt_10 h_LeptonEta_10 h_LeptonPhi_10"
	@$(MAKE) -C DoubleEleCR plot variable="h_cutflow ChNemPtFrac_10 ChNemPt123_10 ChNemPt_10 PF123PtFraction_10 Pt123_10 j1pT_10 j1Eta_10 j1Phi_10 j1TotPFCands_10 nVtx_10 h_recoil_10 h_dileptonPt_10 h_dileptonM_10"
	@$(MAKE) -C SingleMuCR plot variable="h_cutflow ChNemPtFrac_10 ChNemPt123_10 ChNemPt_10 PF123PtFraction_10 Pt123_10 j1pT_10 j1Eta_10 j1Phi_10 j1TotPFCands_10 nVtx_10 h_recoil_10 h_LeptonPt_10 h_LeptonEta_10 h_LeptonPhi_10"
	@$(MAKE) -C DoubleMuCR plot variable="h_cutflow ChNemPtFrac_10 ChNemPt123_10 ChNemPt_10 PF123PtFraction_10 Pt123_10 j1pT_10 j1Eta_10 j1Phi_10 j1TotPFCands_10 nVtx_10 h_recoil_10 h_dileptonPt_10 h_dileptonM_10"
