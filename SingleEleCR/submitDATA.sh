DATA1=/hdfs/store/user/varuns/Run2018_17Sep2018_May2019
DATA2=/hdfs/store/user/varuns/Run2018D_Prompt
MC=/hdfs/store/user/varuns/MC2018_Autumn18_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo 'Do the data samples'

$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0000/ postSingleEle_0_0.root -1 10000 Ele_0_0 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0001/ postSingleEle_0_1.root -1 10000 Ele_0_1 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0002/ postSingleEle_0_2.root -1 10000 Ele_0_2 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0003/ postSingleEle_0_3.root -1 10000 Ele_0_3 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0004/ postSingleEle_0_4.root -1 10000 Ele_0_4 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0005/ postSingleEle_0_5.root -1 10000 Ele_0_5 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0006/ postSingleEle_0_6.root -1 10000 Ele_0_6 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0007/ postSingleEle_0_7.root -1 10000 Ele_0_7 split_-1
$rUN $DATA1/EGamma/crab_job_EGamma2018A/190520_092143/0008/ postSingleEle_0_8.root -1 10000 Ele_0_8 split_-1
