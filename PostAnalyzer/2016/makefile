REGIONS=SignalRegion SingleEleCR SingleMuCR DoubleEleCR DoubleMuCR

all: $(REGIONS)

$(REGIONS):
	@$(MAKE) -C $@

%::
	@for region in $(REGIONS); do \
	$(MAKE) -C $${region} $@; \
	done
