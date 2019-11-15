
RFLAGS:=-I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore -Wno-deprecated

ROOT:=../../
YEAR:=../
SRC:=src/
INC:=inc/
BIN:=bin/
SCRIPTS:=scripts/

CR:=ZprimeDoubleCR
LEP:=$(CR:CR=MuCR)

LIBRARY:=$(addprefix $(ROOT)$(BIN),ScaleUncCollection.o ShapeUncCollection.o Utilities.o Dataset.o)
INCLUDE:=$(addprefix $(ROOT)$(INC),ZprimeCutConfig.h Dataset.h VariableBins.h ScaleUncCollection.h ShapeUncCollection.h Utilities.h)
OBJECTS:=$(BIN)ZprimeClass.o $(YEAR)$(BIN)ZprimeYear.o $(ROOT)$(BIN)$(LEP).o $(ROOT)$(BIN)ZprimeAnalysis.o $(LIBRARY)

.PHONY:test clean condor_clean hadd bin

analyze: $(ROOT)$(SCRIPTS)analyze.C $(OBJECTS)
	@if [ ! -d RootFiles ]; then ln -s $(YEAR)RootFiles/; fi
	@if [ ! -d PlotTool ]; then ln -s $(ROOT)PlotTool/; fi
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) -I$(INC) $(RFLAGS) $(WARNINGS) $< $(OBJECTS) -o $@

$(BIN)ZprimeClass.o: $(SRC)ZprimeClass.C $(INC)ZprimeClass.h $(YEAR)$(INC)ZprimeYear.h $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) -I$(INC) $(RFLAGS) -c $< -o $@

$(YEAR)$(BIN)ZprimeYear.o: $(YEAR)$(SRC)ZprimeYear.C $(YEAR)$(INC)ZprimeYear.h $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) $(RFLAGS) -c $< -o $@

$(ROOT)$(BIN)$(LEP).o: $(ROOT)$(SRC)$(LEP).C $(ROOT)$(INC)$(CR).h $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) $(RFLAGS) -c $< -o $@

$(ROOT)$(BIN)ZprimeAnalysis.o: $(ROOT)$(SRC)ZprimeAnalysis.C $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) $(RFLAGS) -c $< -o $@

$(ROOT)$(BIN)%.o: $(ROOT)$(SRC)%.C $(ROOT)$(INC)%.h
	g++ -I$(ROOT)$(INC) $(RFLAGS) -c $< -o $@

bin:
	mkdir -p $(BIN)
	mkdir -p $(YEAR)$(BIN)
	mkdir -p $(ROOT)$(BIN)

test: analyze
	./analyze

clean:
	rm post*.root

condor_clean:
	rm -r .output/
	rm -r .status/

condor_submit:
	./submit.py

hadd:
	./PlotTool/plotter.py
