.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools*/plugins/

testDir=/hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJets* $(plugin)/ZprimeJets* RootFiles
	g++ -I $(plugin) -Wno-deprecated ZprimeJets*.C $(plugin)/*.C -o analyze $(rflags)

RootFiles:
	if [ ! -d RootFiles ]; then ln -s ../RootFiles/; fi

test: analyze
	./analyze $(testDir) test.root -1 100 -1
