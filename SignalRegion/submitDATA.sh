$DATA1=/hdfs/store/user/varuns/Run2018_17Sep2018_May2019
$DATA2=/hdfs/store/user/varuns/Run2018D_Prompt
$MC=/hdfs/store/user/varuns/MC2018_Autumn18_May2019
$RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo 'Do the data samples'

$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0000/ postMETdata_0_0.root -1 10000 MET_0_0 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0001/ postMETdata_0_1.root -1 10000 MET_0_1 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0002/ postMETdata_0_2.root -1 10000 MET_0_2 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0003/ postMETdata_0_3.root -1 10000 MET_0_3 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0004/ postMETdata_0_4.root -1 10000 MET_0_4 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0005/ postMETdata_0_5.root -1 10000 MET_0_5 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0006/ postMETdata_0_6.root -1 10000 MET_0_6 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0007/ postMETdata_0_7.root -1 10000 MET_0_7 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0008/ postMETdata_0_8.root -1 10000 MET_0_8 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0009/ postMETdata_0_9.root -1 10000 MET_0_9 split_-1
