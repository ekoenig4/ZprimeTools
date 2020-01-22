YEARS=2016 2017 2018

.PHONY: $(YEARS) all

all: $(YEARS)
	@#

$(YEARS): 
	@$(MAKE) -C $@ $(TARGET)

%:: TARGET:=$(MAKECMDGOALS)
%:: $(YEARS)
	@#
