rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsClass.h
	g++ -Wno-deprecated ZprimeJetsClass.C ZprimeJetsInit.C -o analyze $(rflags)
