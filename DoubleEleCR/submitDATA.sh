DATE=May2018
DATE_2=29May
DATE_DATA=19May
DATA=/hdfs/store/user/gomber/MonoZprime_Ntuples_${DATE_DATA}_CR
RUN="python ../SubmitCondor.py analyze"

make || exit -1

echo "Do the CR data samples"

$RUN $DATA/SingleElectron/crab_dataset1/180529_*/0000/ postDoubleEle_0_0.root -1 10000 Ele_0_0 split_-1
$RUN $DATA/SingleElectron/crab_dataset1/180529_*/0001/ postDoubleEle_0_1.root -1 10000 Ele_0_1 split_-1
$RUN $DATA/SingleElectron/crab_dataset1/180529_*/0002/ postDoubleEle_0_2.root -1 10000 Ele_0_2 split_-1
$RUN $DATA/SingleElectron/crab_dataset1/180529_*/0003/ postDoubleEle_0_3.root -1 10000 Ele_0_3 split_-1
$RUN $DATA/SingleElectron/crab_dataset2/180529_*/0000/ postDoubleEle_0_4.root -1 10000 Ele_0_4 split_-1
$RUN $DATA/SingleElectron/crab_dataset2/180529_*/0001/ postDoubleEle_0_5.root -1 10000 Ele_0_5 split_-1

$RUN $DATA/SingleElectron/crab_dataset3/180529_*/0000/ postDoubleEle_1_0.root -1 10000 Ele_1_0 split_-1
$RUN $DATA/SingleElectron/crab_dataset3/180529_*/0001/ postDoubleEle_1_1.root -1 10000 Ele_1_1 split_-1

$RUN $DATA/SingleElectron/crab_dataset4/180529_*/0000/ postDoubleEle_2_0.root -1 10000 Ele_2_0 split_-1
$RUN $DATA/SingleElectron/crab_dataset4/180529_*/0001/ postDoubleEle_2_1.root -1 10000 Ele_2_1 split_-1

$RUN $DATA/SingleElectron/crab_dataset5/180529_*/0000/ postDoubleEle_3_0.root -1 10000 Ele_3_0 split_-1
$RUN $DATA/SingleElectron/crab_dataset5/180529_*/0001/ postDoubleEle_3_1.root -1 10000 Ele_3_1 split_-1

$RUN $DATA/SingleElectron/crab_dataset6/180529_*/0000/ postDoubleEle_4_0.root -1 10000 Ele_4_0 split_-1
$RUN $DATA/SingleElectron/crab_dataset6/180529_*/0001/ postDoubleEle_4_1.root -1 10000 Ele_4_1 split_-1
$RUN $DATA/SingleElectron/crab_dataset6/180529_*/0002/ postDoubleEle_4_2.root -1 10000 Ele_4_2 split_-1

$RUN $DATA/SingleElectron/crab_dataset7/180529_*/0000/ postDoubleEle_5_0.root -1 10000 Ele_5_0 split_-1 
$RUN $DATA/SingleElectron/crab_dataset7/180529_*/0001/ postDoubleEle_5_1.root -1 10000 Ele_5_1 split_-1 
$RUN $DATA/SingleElectron/crab_dataset7/180529_*/0002/ postDoubleEle_5_2.root -1 10000 Ele_5_2 split_-1 
$RUN $DATA/SingleElectron/crab_dataset7/180529_*/0003/ postDoubleEle_5_3.root -1 10000 Ele_5_3 split_-1  

$RUN $DATA/SingleElectron/crab_dataset8/180529_*/0000/ postDoubleEle_6_0.root -1 10000 Ele_6_0 split_-1 
