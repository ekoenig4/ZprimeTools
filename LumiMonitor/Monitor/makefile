.PHONY = test

testDir=/hdfs/store/user/varuns/Egamma2018D-run_102X_data2018_farmout/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsClass.h
	g++ -Wno-deprecated ZprimeJetsClass.C ZprimeJetsInit.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 -1
