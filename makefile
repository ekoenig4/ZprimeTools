ROOT_FLAGS= -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore -Wno-deprecated -Wall

SRC=$(CMSSW_BASE)/src/MonoZprimeJet/src/
BIN=$(CMSSW_BASE)/src/MonoZprimeJet/bin/
SRC_2016=$(CMSSW_BASE)/src/MonoZprimeJet/2016/src/
BIN_2016=$(CMSSW_BASE)/src/MonoZprimeJet/2016/bin/
2016_SR=$(CMSSW_BASE)/src/MonoZprimeJet/2016/SignalRegion/
SRC_2016_SR=$(CMSSW_BASE)/src/MonoZprimeJet/2016/SignalRegion/src/
BIN_2016_SR=$(CMSSW_BASE)/src/MonoZprimeJet/2016/SignalRegion/bin/

all: $(2016_SR)analyze

$(BIN)ZprimeAnalysis.o: $(SRC)ZprimeAnalysis.* $(SRC)Utilities.h $(SRC)Collections.h $(SRC)VariableBins.h $(SRC)ZprimeEnums.h $(SRC)ZprimeMetadata.h $(SRC)ZprimeCutConfig.h
	g++ -I$(SRC) -c $(SRC)ZprimeAnalysis.C -o $(BIN)ZprimeAnalysis.o $(ROOT_FLAGS)

$(BIN)ZprimeDoubleEleCR.o: $(BIN)ZprimeAnalysis.o $(SRC)ZprimeDoubleCR.h $(SRC)ZprimeDoubleEleCR.C
	g++ -I$(SRC) -c $(SRC)ZprimeDoubleEleCR.C -o $(BIN)ZprimeDoubleEleCR.o $(ROOT_FLAGS)

$(BIN)ZprimeDoubleMuCR.o: $(BIN)ZprimeAnalysis.o $(SRC)ZprimeDoubleCR.h $(SRC)ZprimeDoubleMuCR.C
	g++ -I$(SRC) -c $(SRC)ZprimeDoubleMuCR.C -o $(BIN)ZprimeDoubleMuCR.o $(ROOT_FLAGS)


$(BIN)ZprimeSingleEleCR.o: $(BIN)ZprimeAnalysis.o $(SRC)ZprimeSingleCR.h $(SRC)ZprimeSingleEleCR.C
	g++ -I$(SRC) -c $(SRC)ZprimeSingleEleCR.C -o $(BIN)ZprimeSingleEleCR.o $(ROOT_FLAGS)

$(BIN)ZprimeSingleMuCR.o: $(BIN)ZprimeAnalysis.o $(SRC)ZprimeSingleCR.h $(SRC)ZprimeSingleMuCR.C
	g++ -I$(SRC) -c $(SRC)ZprimeSingleMuCR.C -o $(BIN)ZprimeSingleMuCR.o $(ROOT_FLAGS)

$(BIN_2016)ZprimeYear.o: $(BIN)ZprimeAnalysis.o $(SRC_2016)ZprimeYear.* 
	g++ -I$(SRC) -I$(SRC_2016) -c $(SRC_2016)ZprimeYear.C -o $(BIN_2016)ZprimeYear.o $(ROOT_FLAGS)

$(BIN_2016_SR)ZprimeClass.o: $(BIN_2016)ZprimeYear.o $(SRC_2016_SR)ZprimeClass.*
	g++ -I$(SRC) -I$(SRC_2016) -I$(SRC_2016_SR) -c $(SRC_2016_SR)ZprimeClass.C -o $(BIN_2016_SR)ZprimeClass.o $(ROOT_FLAGS)

$(2016_SR)analyze: $(BIN_2016_SR)ZprimeClass.o
	g++ $(BIN)ZprimeAnalysis.o $(BIN_2016)ZprimeYear.o $(BIN_2016_SR)ZprimeClass.o -o $(2016_SR)analyze
