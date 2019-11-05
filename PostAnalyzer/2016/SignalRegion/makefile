RFLAGS:=-I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore -Wno-deprecated

ROOT:=../../
YEAR:=../
SRC:=src/
INC:=inc/
BIN:=bin/

LIBRARY:=$(addprefix $(ROOT)$(BIN),ScaleUncCollection.o ShapeUncCollection.o Utilities.o)
INCLUDE:=$(addprefix $(ROOT)$(INC),ZprimeCutConfig.h ZprimeDataMC.h VariableBins.h ScaleUncCollection.h ShapeUncCollection.h Utilities.h)
OBJECTS:=$(BIN)ZprimeDataMC.o $(YEAR)$(BIN)ZprimeYear.o $(ROOT)$(BIN)ZprimeAnalysis.o $(LIBRARY)

analyze: $(SRC)ZprimeClass.C $(INC)ZprimeClass.h $(OBJECTS)
	@if [ ! -d RootFiles ]; then ln -s ../RootFiles/; fi
	@if [ ! -d PlotTool ]; then ln -s ../PlotTool/; fi
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) -I$(INC) $(RFLAGS) $< $(OBJECTS) -o $@

test: analyze
	./analyze

$(BIN)ZprimeDataMC.o: $(SRC)ZprimeDataMC.C $(ROOT)$(INC)ZprimeDataMC.h
	g++ -I$(ROOT)$(INC) -c $< -o $@

$(YEAR)$(BIN)ZprimeYear.o: $(YEAR)$(SRC)ZprimeYear.C $(YEAR)$(INC)ZprimeYear.h $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) -I$(YEAR)$(INC) $(RFLAGS) -c $< -o $@

$(ROOT)$(BIN)ZprimeAnalysis.o: $(ROOT)$(SRC)ZprimeAnalysis.C $(ROOT)$(INC)ZprimeAnalysis.h $(INCLUDE)
	g++ -I$(ROOT)$(INC) $(RFLAGS) -c $< -o $@

$(ROOT)$(BIN)%.o: $(ROOT)$(SRC)%.C $(ROOT)$(INC)%.h
	g++ -I$(ROOT)$(INC) $(RFLAGS) -c $< -o $@
