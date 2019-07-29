DATE=May2018
DATE_2=29May
DATA=/hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR
RUN="python ../SubmitCondor.py analyze"

make || exit -1

echo "Do the CR data samples"

$RUN $DATA/MET/crab_dataset1/180529_*/0000/ postSingleMu_0_0.root -1 10000 Mu_0_0 split_-1
$RUN $DATA/MET/crab_dataset1/180529_*/0001/ postSingleMu_0_1.root -1 10000 Mu_0_1 split_-1
$RUN $DATA/MET/crab_dataset1/180529_*/0002/ postSingleMu_0_2.root -1 10000 Mu_0_2 split_-1
$RUN $DATA/MET/crab_dataset1/180529_*/0003/ postSingleMu_0_3.root -1 10000 Mu_0_3 split_-1
$RUN $DATA/MET/crab_dataset2/180529_*/0000/ postSingleMu_0_4.root -1 10000 Mu_0_4 split_-1
$RUN $DATA/MET/crab_dataset2/180529_*/0001/ postSingleMu_0_5.root -1 10000 Mu_0_5 split_-1

$RUN $DATA/MET/crab_dataset3/180529_*/0000/ postSingleMu_1_0.root -1 10000 Mu_1_0 split_-1
$RUN $DATA/MET/crab_dataset3/180529_*/0001/ postSingleMu_1_1.root -1 10000 Mu_1_1 split_-1

$RUN $DATA/MET/crab_dataset4/180529_*/0000/ postSingleMu_2_0.root -1 10000 Mu_2_0 split_-1
$RUN $DATA/MET/crab_dataset4/180529_*/0001/ postSingleMu_2_1.root -1 10000 Mu_2_1 split_-1

$RUN $DATA/MET/crab_dataset5/180529_*/0000/ postSingleMu_3_0.root -1 10000 Mu_3_0 split_-1
$RUN $DATA/MET/crab_dataset5/180529_*/0001/ postSingleMu_3_1.root -1 10000 Mu_3_1 split_-1

$RUN $DATA/MET/crab_dataset6/180529_*/0000/ postSingleMu_4_0.root -1 10000 Mu_4_0 split_-1
$RUN $DATA/MET/crab_dataset6/180529_*/0001/ postSingleMu_4_1.root -1 10000 Mu_4_1 split_-1
$RUN $DATA/MET/crab_dataset6/180529_*/0002/ postSingleMu_4_2.root -1 10000 Mu_4_2 split_-1

$RUN $DATA/MET/crab_dataset7/180529_*/0000/ postSingleMu_5_0.root -1 10000 Mu_5_0  split_-1
$RUN $DATA/MET/crab_dataset7/180529_*/0001/ postSingleMu_5_1.root -1 10000 Mu_5_1  split_-1
$RUN $DATA/MET/crab_dataset7/180529_*/0002/ postSingleMu_5_2.root -1 10000 Mu_5_2  split_-1
$RUN $DATA/MET/crab_dataset7/180529_*/0003/ postSingleMu_5_3.root -1 10000 Mu_5_3  split_-1

$RUN $DATA/MET/crab_dataset8/180529_*/0000/ postSingleMu_6_0.root -1 10000 Mu_6_0 split_-1
