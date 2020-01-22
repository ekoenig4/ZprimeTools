YEARS=2016 2017 2018

.PHONY: $(YEARS) all

all: $(YEARS)

$(YEARS):
	@$(MAKE) -C $@ ${SUB_TARGET}

%::
	@$(MAKE) SUB_TARGET=$@
