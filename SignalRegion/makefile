.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools*/plugins/

testDir=/hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJets* $(plugin)/ZprimeJets*
	g++ -I $(plugin) -Wno-deprecated ZprimeJets*.C $(plugin)/*.C -o analyze $(rflags)

test: analyze
	./analyze $(testDir) test.root -1 100 -1
