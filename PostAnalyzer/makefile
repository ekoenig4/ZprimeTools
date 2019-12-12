YEARS=2017 2018

.PHONY: $(YEARS) all

all: $(YEARS)

$(YEARS):
	@$(MAKE) -C $@

%::	
	@for year in $(YEARS); do \
		$(MAKE) -C $${year} $@; \
	done
