REGIONS=SignalRegion SingleEleCR SingleMuCR DoubleEleCR DoubleMuCR

.PHONY: $(REGIONS) test

all: $(REGIONS)

$(REGIONS):
	@$(MAKE) -C $@
