MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019
DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo "Do the Data samples"

$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0000/ postMETdata_0.root -1 10000 MET_0 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0001/ postMETdata_1.root -1 10000 MET_1 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0002/ postMETdata_2.root -1 10000 MET_2 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0003/ postMETdata_3.root -1 10000 MET_3 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0004/ postMETdata_4.root -1 10000 MET_4 split_-1
