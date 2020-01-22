REGIONS=SignalRegion SingleEleCR SingleMuCR DoubleEleCR DoubleMuCR

.PHONY: $(REGIONS) all

all: $(REGIONS)

$(REGIONS):
	@$(MAKE) -C $@ ${SUB_TARGET}

%::
	@$(MAKE) SUB_TARGET=$@
