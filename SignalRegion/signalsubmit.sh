RUN="python $CMSSW_BASE/src/ZprimeTools2016/CondorTools/SubmitCondor.py -y 2016 -r SR analyze"

make || exit -1

echo Dark Matter Mass 1 GeV

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv10/ postMx1_Mv10.root -1 1000 Mx1_Mv10 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv20/ postMx1_Mv20.root -1 1000 Mx1_Mv20 split_1 

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv50/ postMx1_Mv50.root -1 1000 Mx1_Mv50 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv100/ postMx1_Mv100.root -1 1000 Mx1_Mv100 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv200/ postMx1_Mv200.root -1 1000 Mx1_Mv200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv300/ postMx1_Mv300.root -1 1000 Mx1_Mv300 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv500/ postMx1_Mv500.root -1 1000 Mx1_Mv500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv1000/ postMx1_Mv1000.root -1 1000 Mx1_Mv1000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1_Mv10000/ postMx1_Mv10000.root -1 1000 Mx1_Mv10000 split_1

echo Dark Matter Mass 10 GeV

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv10/ postMx10_Mv10.root -1 1000 Mx10_Mv10 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv15/ postMx10_Mv15.root -1 1000 Mx10_Mv15 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv50/ postMx10_Mv50.root -1 1000 Mx10_Mv50 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv95/ postMx10_Mv95.root -1 1000 Mx10_Mv95 split_1 

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv100/ postMx10_Mv100.root -1 1000 Mx10_Mv100 split_1 

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv200/ postMx10_Mv200.root -1 1000 Mx10_Mv200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv300/ postMx10_Mv300.root -1 1000 Mx10_Mv300 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv400/ postMx10_Mv400.root -1 1000 Mx10_Mv400 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv500/ postMx10_Mv500.root -1 1000 Mx10_Mv500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv600/ postMx10_Mv600.root -1 1000 Mx10_Mv600 split_1 

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv800/ postMx10_Mv800.root -1 1000 Mx10_Mv800 split_1 

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1000/ postMx10_Mv1000.root -1 1000 Mx10_Mv1000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1200/ postMx10_Mv1200.root -1 1000 Mx10_Mv1200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1500/ postMx10_Mv1500.root -1 1000 Mx10_Mv1500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv1800/ postMx10_Mv1800.root -1 1000 Mx10_Mv1800 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv2000/ postMx10_Mv2000.root -1 1000 Mx10_Mv2000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv2200/ postMx10_Mv2200.root -1 1000 Mx10_Mv2200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv2500/ postMx10_Mv2500.root -1 1000 Mx10_Mv2500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv3000/ postMx10_Mv3000.root -1 1000 Mx10_Mv3000 split_1 

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx10_Mv10000/ postMx10_Mv10000.root -1 1000 Mx10_Mv10000 split_1

echo Dark Matter Mass 50 GeV

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv10/ postMx50_Mv10.root -1 1000 Mx50_Mv10 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv50/ postMx50_Mv50.root -1 1000 Mx50_Mv50 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv95/ postMx50_Mv95.root -1 1000 Mx50_Mv95 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv100/ postMx50_Mv100.root -1 1000 Mx50_Mv100 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv200/ postMx50_Mv200.root -1 1000 Mx50_Mv200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv300/ postMx50_Mv300.root -1 1000 Mx50_Mv300 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv400/ postMx50_Mv400.root -1 1000 Mx50_Mv400 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv500/ postMx50_Mv500.root -1 1000 Mx50_Mv500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv600/ postMx50_Mv600.root -1 1000 Mx50_Mv600 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv800/ postMx50_Mv800.root -1 1000 Mx50_Mv800 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv1000/ postMx50_Mv1000.root -1 1000 Mx50_Mv1000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv1200/ postMx50_Mv1200.root -1 1000 Mx50_Mv1200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv1500/ postMx50_Mv1500.root -1 1000 Mx50_Mv1500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv1800/ postMx50_Mv1800.root -1 1000 Mx50_Mv1800 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv2000/ postMx50_Mv2000.root -1 1000 Mx50_Mv2000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv2200/ postMx50_Mv2200.root -1 1000 Mx50_Mv2200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv2500/ postMx50_Mv2500.root -1 1000 Mx50_Mv2500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv3000/ postMx50_Mv3000.root -1 1000 Mx50_Mv3000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx50_Mv10000/ postMx50_Mv10000.root -1 1000 Mx50_Mv10000 split_1

echo Dark Matter Mass 100 GeV

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv10/ postMx100_Mv10.root -1 1000 Mx100_Mv10 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv50/ postMx100_Mv50.root -1 1000 Mx100_Mv50 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv95/ postMx100_Mv95.root -1 1000 Mx100_Mv95 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv100/ postMx100_Mv100.root -1 1000 Mx100_Mv100 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv200/ postMx100_Mv200.root -1 1000 Mx100_Mv200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv300/ postMx100_Mv300.root -1 1000 Mx100_Mv300 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv400/ postMx100_Mv400.root -1 1000 Mx100_Mv400 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv500/ postMx100_Mv500.root -1 1000 Mx100_Mv500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv600/ postMx100_Mv600.root -1 1000 Mx100_Mv600 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv800/ postMx100_Mv800.root -1 1000 Mx100_Mv800 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv1000/ postMx100_Mv1000.root -1 1000 Mx100_Mv1000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv1200/ postMx100_Mv1200.root -1 1000 Mx100_Mv1200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv1500/ postMx100_Mv1500.root -1 1000 Mx100_Mv1500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv1800/ postMx100_Mv1800.root -1 1000 Mx100_Mv1800 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv2000/ postMx100_Mv2000.root -1 1000 Mx100_Mv2000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv2200/ postMx100_Mv2200.root -1 1000 Mx100_Mv2200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv2500/ postMx100_Mv2500.root -1 1000 Mx100_Mv2500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv3000/ postMx100_Mv3000.root -1 1000 Mx100_Mv3000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx100_Mv10000/ postMx100_Mv10000.root -1 1000 Mx100_Mv10000 split_1

echo Dark Matter Mass 150 GeV

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx150_Mv10/ postMx150_Mv10.root -1 1000 Mx150_Mv10 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx150_Mv200/ postMx150_Mv200.root -1 1000 Mx150_Mv200 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx150_Mv295/ postMx150_Mv295.root -1 1000 Mx150_Mv295 split_1 

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx150_Mv500/ postMx150_Mv500.root -1 1000 Mx150_Mv500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx150_Mv1000/ postMx150_Mv1000.root -1 1000 Mx150_Mv1000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx150_Mv10000/ postMx150_Mv10000.root -1 1000 Mx150_Mv10000 split_1

echo Dark Matter Mass 500 GeV

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx500_Mv10/ postMx500_Mv10.root -1 1000 Mx500_Mv10 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx500_Mv500/ postMx500_Mv500.root -1 1000 Mx500_Mv500 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx500_Mv995/ postMx500_Mv995.root -1 1000 Mx500_Mv995 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx500_Mv10000/ postMx500_Mv10000.root -1 1000 Mx500_Mv10000 split_1

echo Dark Matter Mass 1000 GeV

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1000_Mv10/ postMx1000_Mv10.root -1 1000 Mx1000_Mv10 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1000_Mv1000/ postMx1000_Mv1000.root -1 1000 Mx1000_Mv1000 split_1

$RUN /hdfs/store/user/varuns/NTuples/monoZprime_2016_80X/MonoZprime_Mx1000_Mv10000/ postMx1000_Mv10000.root -1 1000 Mx1000_Mv10000 split_1
