MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019
DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo "Do the Data samples"

$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0000/ postSingleEle_1_0.root -1 10000 Ele_1_0 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0001/ postSingleEle_1_1.root -1 10000 Ele_1_1 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0002/ postSingleEle_1_2.root -1 10000 Ele_1_2 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0003/ postSingleEle_1_3.root -1 10000 Ele_1_3 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0004/ postSingleEle_1_4.root -1 10000 Ele_1_4 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0005/ postSingleEle_1_5.root -1 10000 Ele_1_5 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0006/ postSingleEle_1_6.root -1 10000 Ele_1_6 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0007/ postSingleEle_1_7.root -1 10000 Ele_1_7 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0000/ postSingleEle_1_8.root -1 10000 Ele_1_8 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0001/ postSingleEle_1_9.root -1 10000 Ele_1_9 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0002/ postSingleEle_1_10.root -1 10000 Ele_1_10 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0003/ postSingleEle_1_11.root -1 10000 Ele_1_11 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0004/ postSingleEle_1_12.root -1 10000 Ele_1_12 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0005/ postSingleEle_1_13.root -1 10000 Ele_1_13 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0006/ postSingleEle_1_14.root -1 10000 Ele_1_14 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0007/ postSingleEle_1_15.root -1 10000 Ele_1_15 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0008/ postSingleEle_1_16.root -1 10000 Ele_1_16 split_-1

$RUN $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0000/ postSingleEle_2_0.root -1 10000 Ele_2_0 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0001/ postSingleEle_2_1.root -1 10000 Ele_2_1 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0002/ postSingleEle_2_2.root -1 10000 Ele_2_2 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0003/ postSingleEle_2_3.root -1 10000 Ele_2_3 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0004/ postSingleEle_2_4.root -1 10000 Ele_2_4 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0005/ postSingleEle_2_5.root -1 10000 Ele_2_5 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0006/ postSingleEle_2_6.root -1 10000 Ele_2_6 split_-1

$RUN $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0000/ postSingleEle_3_0.root -1 10000 Ele_3_0 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0001/ postSingleEle_3_1.root -1 10000 Ele_3_1 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0002/ postSingleEle_3_2.root -1 10000 Ele_3_2 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0003/ postSingleEle_3_3.root -1 10000 Ele_3_3 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0004/ postSingleEle_3_4.root -1 10000 Ele_3_4 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0005/ postSingleEle_3_5.root -1 10000 Ele_3_5 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0006/ postSingleEle_3_6.root -1 10000 Ele_3_6 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0000/ postSingleEle_3_7.root -1 10000 Ele_3_7 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0001/ postSingleEle_3_8.root -1 10000 Ele_3_8 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0002/ postSingleEle_3_9.root -1 10000 Ele_3_9 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0003/ postSingleEle_3_10.root -1 10000 Ele_3_10 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0004/ postSingleEle_3_11.root -1 10000 Ele_3_11 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0005/ postSingleEle_3_12.root -1 10000 Ele_3_12 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0006/ postSingleEle_3_13.root -1 10000 Ele_3_13 split_-1

$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0000/ postSingleEle_4_0.root -1 10000 Ele_4_0 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0001/ postSingleEle_4_1.root -1 10000 Ele_4_1 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0002/ postSingleEle_4_2.root -1 10000 Ele_4_2 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0003/ postSingleEle_4_3.root -1 10000 Ele_4_3 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0004/ postSingleEle_4_4.root -1 10000 Ele_4_4 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0005/ postSingleEle_4_5.root -1 10000 Ele_4_5 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0006/ postSingleEle_4_6.root -1 10000 Ele_4_6 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0007/ postSingleEle_4_7.root -1 10000 Ele_4_7 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0008/ postSingleEle_4_8.root -1 10000 Ele_4_8 split_-1
$RUN $DATA/SingleElectron/crab_job_SingleEle2017F/190605_135235/0009/ postSingleEle_4_9.root -1 10000 Ele_4_9 split_-1
