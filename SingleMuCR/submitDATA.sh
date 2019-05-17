MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019
DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo "Do the Data samples"

$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0000/ postSingleMu_0_0.root -1 10000 Mu_0_0 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0001/ postSingleMu_0_4.root -1 10000 Mu_0_1 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0002/ postSingleMu_0_3.root -1 10000 Mu_0_2 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0003/ postSingleMu_0_2.root -1 10000 Mu_0_3 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0004/ postSingleMu_0_1.root -1 10000 Mu_0_4 split_-1

$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0000/ postSingleMu_1_0.root -1 10000 Mu_1_0 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0001/ postSingleMu_1_1.root -1 10000 Mu_1_1 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0002/ postSingleMu_1_2.root -1 10000 Mu_1_2 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0003/ postSingleMu_1_3.root -1 10000 Mu_1_3 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0004/ postSingleMu_1_4.root -1 10000 Mu_1_4 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0005/ postSingleMu_1_5.root -1 10000 Mu_1_5 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0006/ postSingleMu_1_6.root -1 10000 Mu_1_6 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0007/ postSingleMu_1_7.root -1 10000 Mu_1_7 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190512_005206/0008/ postSingleMu_1_8.root -1 10000 Mu_1_8 split_-1

$RUN $DATA/MET/crab_job_MET2017D/190508_233028/0000/ postSingleMu_2_0.root -1 10000 Mu_2_0 split_-1
$RUN $DATA/MET/crab_job_MET2017D/190508_233028/0001/ postSingleMu_2_1.root -1 10000 Mu_2_1 split_-1
$RUN $DATA/MET/crab_job_MET2017D/190508_233028/0002/ postSingleMu_2_2.root -1 10000 Mu_2_2 split_-1

$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0000/ postSingleMu_3_0.root -1 10000 Mu_3_0 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0001/ postSingleMu_3_1.root -1 10000 Mu_3_1 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0002/ postSingleMu_3_2.root -1 10000 Mu_3_2 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0003/ postSingleMu_3_3.root -1 10000 Mu_3_3 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0004/ postSingleMu_3_4.root -1 10000 Mu_3_4 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0005/ postSingleMu_3_5.root -1 10000 Mu_3_5 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0006/ postSingleMu_3_6.root -1 10000 Mu_3_6 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0007/ postSingleMu_3_7.root -1 10000 Mu_3_7 split_-1
$RUN $DATA/MET/crab_job_MET2017E/190511_093152/0008/ postSingleMu_3_8.root -1 10000 Mu_3_8 split_-1
