RFLAGS:=-I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore -Wno-deprecated -Wall -Wparentheses -Wsign-compare

ROOT:=../../
YEAR:=../
SRC:=src/
INC:=inc/
BIN:=bin/

LIBRARY:=$(addprefix $(ROOT)$(BIN),ScaleUncCollection.o ShapeUncCollection.o Utilities.o)
INCLUDE:=$(addprefix $(ROOT)$(INC),ZprimeCutConfig.h ZprimeDataMC.h VariableBins.h ScaleUncCollection.h ShapeUncCollection.h Utilities.h)

analyze: $(BIN)ZprimeClass.o $(BIN)ZprimeDataMC.o $(YEAR)$(BIN)ZprimeYear.o $(ROOT)$(BIN)ZprimeAnalysis.o $(LIBRARY)
	@if [ ! -d RootFiles ]; then ln -s ../RootFiles/; fi
	@if [ ! -d PlotTool ]; then ln -s ../PlotTool/; fi
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) -I$(INC) $(RFLAGS) $^ -o $@

test: analyze
	./analyze

$(BIN)ZprimeClass.o: $(SRC)ZprimeClass.C $(INC)ZprimeClass.h $(BIN)ZprimeDataMC.o $(YEAR)$(INC)ZprimeYear.h $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) -I$(INC) $(RFLAGS) -c $< -o $@

$(BIN)ZprimeDataMC.o: $(SRC)ZprimeDataMC.C $(ROOT)$(INC)ZprimeDataMC.h
	g++ -I$(ROOT)$(INC) -c $< -o $@

$(YEAR)$(BIN)ZprimeYear.o: $(YEAR)$(SRC)ZprimeYear.C $(YEAR)$(INC)ZprimeYear.h $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) $(RFLAGS) -c $< -o $@

$(ROOT)$(BIN)ZprimeAnalysis.o: $(ROOT)$(SRC)ZprimeAnalysis.C $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) $(RFLAGS) -c $< -o $@

%$(BIN)%.o: %$(SRC)%.C %$(INC)%.h
	g++ -I$(INC) $(RFLAGS) -c $< -o $@
