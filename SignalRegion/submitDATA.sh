MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019
DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo "Do the Data samples"

$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0000/ postMETdata_0_0.root -1 10000 Mu_0_0 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0001/ postMETdata_0_4.root -1 10000 Mu_0_1 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0002/ postMETdata_0_3.root -1 10000 Mu_0_2 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0003/ postMETdata_0_2.root -1 10000 Mu_0_3 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0004/ postMETdata_0_1.root -1 10000 Mu_0_4 split_-1
$RUN $DATA/MET/crab_job_MET2017Bv2/190515_211629/0000/ postMETdata_0_5.root -1 10000 Mu_0_5 split_-1
