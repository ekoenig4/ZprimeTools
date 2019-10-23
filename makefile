regions = SignalRegion SingleEleCR DoubleEleCR SingleMuCR DoubleMuCR

all: sr se sm de dm

sr:
	@$(MAKE) -C SignalRegion
se:
	@$(MAKE) -C SingleEleCR
sm:
	@$(MAKE) -C SingleMuCR
de:
	@$(MAKE) -C DoubleEleCR
dm:
	@$(MAKE) -C DoubleMuCR

test: test_sr test_se test_sm test_de test_dm

test_sr:
	@$(MAKE) -C SignalRegion test
test_se:
	@$(MAKE) -C SingleEleCR test
test_sm:
	@$(MAKE) -C SingleMuCR test
test_de:
	@$(MAKE) -C DoubleEleCR test
test_dm:
	@$(MAKE) -C DoubleMuCR test

clean: clean_sr clean_sr clean_sm clean_de clean_dm

clean_sr:
	@$(MAKE) -C SignalRegion clean
clean_se:
	@$(MAKE) -C SingleEleCR clean
clean_sm:
	@$(MAKE) -C SingleMuCR clean
clean_de:
	@$(MAKE) -C DoubleEleCR clean
clean_dm:
	@$(MAKE) -C DoubleMuCR clean

condor_clean: condor_clean_sr condor_clean_sr condor_clean_sm condor_clean_de condor_clean_dm

condor_clean_sr:
	@$(MAKE) -C SignalRegion condor_clean
condor_clean_se:
	@$(MAKE) -C SingleEleCR condor_clean
condor_clean_sm:
	@$(MAKE) -C SingleMuCR condor_clean
condor_clean_de:
	@$(MAKE) -C DoubleEleCR condor_clean
condor_clean_dm:
	@$(MAKE) -C DoubleMuCR condor_clean

condor_submit: condor_submit_sr condor_submit_sr condor_submit_sm condor_submit_de condor_submit_dm

condor_submit_sr:
	@$(MAKE) -C SignalRegion condor_submit
condor_submit_se:
	@$(MAKE) -C SingleEleCR condor_submit
condor_submit_sm:
	@$(MAKE) -C SingleMuCR condor_submit
condor_submit_de:
	@$(MAKE) -C DoubleEleCR condor_submit
condor_submit_dm:
	@$(MAKE) -C DoubleMuCR condor_submit

hadd: hadd_sr hadd_sr hadd_sm hadd_de hadd_dm

hadd_sr:
	@$(MAKE) -C SignalRegion hadd
hadd_se:
	@$(MAKE) -C SingleEleCR hadd
hadd_sm:
	@$(MAKE) -C SingleMuCR hadd
hadd_de:
	@$(MAKE) -C DoubleEleCR hadd
hadd_dm:
	@$(MAKE) -C DoubleMuCR hadd
