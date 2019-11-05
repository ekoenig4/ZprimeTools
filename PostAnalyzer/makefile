RFLAGS:=-I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore -Wno-deprecated -Wall -Wparentheses -Wsign-compare

SRC:=src/
BIN:=bin/
INC:=inc/

YEAR:=2016/
LIBRARY:=$(addprefix $(BIN),ScaleUncCollection.o ShapeUncCollection.o Utilities.o)
INCLUDE:=$(addprefix $(INC),ZprimeCutConfig.h ZprimeDataMC.h)
CRFILES:=ZprimeDoubleEleCR.o ZprimeDoubleMuCR.o ZprimeSingleEleCR.o ZprimeSingleMuCR.o

%SignalRegion/analyze: %SignalRegion/$(BIN)ZprimeClass.o %SignalRegion/$(BIN)ZprimeDataMC.o %$(BIN)ZprimeYear.o $(BIN)ZprimeAnalysis.o $(LIBRARY)
	g++ -I$(INC) -I$*$(INC) -I$*SignalRegion/$(INC) $(RFLAGS) $^ -o $@

%SignalRegion/$(BIN)ZprimeClass.o: %SignalRegion/$(SRC)ZprimeClass.C %SignalRegion/$(BIN)ZprimeDataMC.o %$(BIN)ZprimeYear.o $(BIN)ZprimeAnalysis.o $(LIBRARY)
	g++ -I$(INC) -I$*$(INC) -I$*SignalRegion/$(INC) $(RFLAGS) -c $< -o $@

%$(BIN)ZprimeDataMC.o: %$(SRC)ZprimeDataMC.C $(INC)ZprimeDataMC.h
	g++ -I$(INC) $(RFLAGS) -c $< -o $@

%$(BIN)ZprimeYear.o: %$(SRC)ZprimeYear.C %$(INC)ZprimeYear.h $(BIN)ZprimeAnalysis.o
	g++ -I$(INC) -I$*$(INC) $(RFLAGS) -c $< -o $@

$(BIN)ZprimeAnalysis.o: $(SRC)ZprimeAnalysis.C $(INC)ZprimeAnalysis.h $(LIBRARY) $(INCLUDE)
	g++ -I$(INC) $(RFLAGS) -c $< -o $@

$(BIN)ZprimeSingle%CR.o: $(SRC)ZprimeSingle%CR.C $(INC)ZprimeSingleCR.h $(BIN)ZprimeAnalysis.o
	g++ -I$(INC) $(RFLAGS) -c $< -o $@

$(BIN)ZprimeDouble%CR.o: $(SRC)ZprimeDouble%CR.C $(INC)ZprimeDoubleCR.h $(BIN)ZprimeAnalysis.o
	g++ -I$(INC) $(RFLAGS) -c $< -o $@

$(BIN)%.o: $(SRC)%.C $(INC)%.h
	g++ -I$(INC) $(RFLAGS) -c $< -o $@
