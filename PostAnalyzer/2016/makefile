REGIONS=SingleEleCR SingleMuCR DoubleEleCR DoubleMuCR

.PHONY: $(REGIONS) all

all: $(REGIONS)

$(REGIONS):
	@$(MAKE) -C $@

%::	
	@for region in $(REGIONS); do \
		$(MAKE) -C $${region} $@; \
	done
