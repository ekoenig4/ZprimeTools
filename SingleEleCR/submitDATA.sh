DATA1=/hdfs/store/user/varuns/Run2018_17Sep2018_May2019
DATA2=/hdfs/store/user/varuns/Run2018D_Prompt
MC=/hdfs/store/user/varuns/MC2018_Autumn18_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo 'Do the data samples'

$RUN $DATA1/EGamma/crab_job_EGamma2018B/190528_233825/0000/ postSingleEle_1_0.root -1 10000 Ele_1_0 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018B/190528_233825/0001/ postSingleEle_1_1.root -1 10000 Ele_1_1 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018B/190528_233825/0002/ postSingleEle_1_2.root -1 10000 Ele_1_2 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018B/190528_233825/0003/ postSingleEle_1_3.root -1 10000 Ele_1_3 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018B/190528_233825/0004/ postSingleEle_1_4.root -1 10000 Ele_1_4 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0000/ postSingleEle_1_5.root -1 10000 Ele_1_5 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0001/ postSingleEle_1_6.root -1 10000 Ele_1_6 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0002/ postSingleEle_1_7.root -1 10000 Ele_1_7 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0003/ postSingleEle_1_8.root -1 10000 Ele_1_8 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0004/ postSingleEle_1_9.root -1 10000 Ele_1_9 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0005/ postSingleEle_1_10.root -1 10000 Ele_1_10 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0006/ postSingleEle_1_11.root -1 10000 Ele_1_11 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0007/ postSingleEle_1_12.root -1 10000 Ele_1_12 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv2/190529_100508/0008/ postSingleEle_1_13.root -1 10000 Ele_1_13 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0000/ postSingleEle_1_14.root -1 10000 Ele_1_14 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0001/ postSingleEle_1_15.root -1 10000 Ele_1_15 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0002/ postSingleEle_1_16.root -1 10000 Ele_1_16 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0003/ postSingleEle_1_17.root -1 10000 Ele_1_17 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0004/ postSingleEle_1_18.root -1 10000 Ele_1_18 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0005/ postSingleEle_1_19.root -1 10000 Ele_1_19 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0006/ postSingleEle_1_20.root -1 10000 Ele_1_20 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0007/ postSingleEle_1_21.root -1 10000 Ele_1_21 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Bv3/190602_052700/0008/ postSingleEle_1_22.root -1 10000 Ele_1_22 split_-1

$RUN $DATA1/EGamma/crab_job_EGamma2018C/190528_233953/0000/ postSingleEle_2_0.root -1 10000 Ele_2_0 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018C/190528_233953/0001/ postSingleEle_2_1.root -1 10000 Ele_2_1 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018C/190528_233953/0002/ postSingleEle_2_2.root -1 10000 Ele_2_2 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018C/190528_233953/0003/ postSingleEle_2_3.root -1 10000 Ele_2_3 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018C/190528_233953/0004/ postSingleEle_2_4.root -1 10000 Ele_2_4 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0000/ postSingleEle_2_5.root -1 10000 Ele_2_5 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0001/ postSingleEle_2_6.root -1 10000 Ele_2_6 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0002/ postSingleEle_2_7.root -1 10000 Ele_2_7 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0003/ postSingleEle_2_8.root -1 10000 Ele_2_8 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0004/ postSingleEle_2_9.root -1 10000 Ele_2_9 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0005/ postSingleEle_2_10.root -1 10000 Ele_2_10 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0006/ postSingleEle_2_11.root -1 10000 Ele_2_11 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv2/190529_100921/0007/ postSingleEle_2_12.root -1 10000 Ele_2_12 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv3/190530_145804/0000/ postSingleEle_2_13.root -1 10000 Ele_2_13 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv3/190530_145804/0001/ postSingleEle_2_14.root -1 10000 Ele_2_14 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv3/190530_145804/0002/ postSingleEle_2_15.root -1 10000 Ele_2_15 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv3/190530_145804/0003/ postSingleEle_2_16.root -1 10000 Ele_2_16 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv3/190530_145804/0004/ postSingleEle_2_17.root -1 10000 Ele_2_17 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv4/190604_144802/0000/ postSingleEle_2_18.root -1 10000 Ele_2_18 split_-1
$RUN $DATA1/EGamma/crab_job_EGamma2018Cv4/190604_144802/0001/ postSingleEle_2_19.root -1 10000 Ele_2_19 split_-1
