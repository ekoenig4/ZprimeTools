MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019
DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo "Do the Data samples"

$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0000/ postSingleMu_0_0.root -1 10000 Mu_0_0 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0001/ postSingleMu_0_1.root -1 10000 Mu_0_1 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0002/ postSingleMu_0_2.root -1 10000 Mu_0_2 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0003/ postSingleMu_0_3.root -1 10000 Mu_0_3 split_-1
$RUN $DATA/MET/crab_job_MET2017B/190511_093051/0004/ postSingleMu_0_4.root -1 10000 Mu_0_4 split_-1
$RUN $DATA/MET/crab_job_MET2017Bv2/190515_211629/0000/ postSingleMu_0_5.root -1 10000 Mu_0_5 split_-1

$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0000/ postSingleMu_1_0.root -1 10000 Mu_1_0 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0001/ postSingleMu_1_1.root -1 10000 Mu_1_1 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0002/ postSingleMu_1_2.root -1 10000 Mu_1_2 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0003/ postSingleMu_1_3.root -1 10000 Mu_1_3 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0004/ postSingleMu_1_4.root -1 10000 Mu_1_4 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0005/ postSingleMu_1_5.root -1 10000 Mu_1_5 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0006/ postSingleMu_1_6.root -1 10000 Mu_1_6 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0007/ postSingleMu_1_7.root -1 10000 Mu_1_7 split_-1
$RUN $DATA/MET/crab_job_MET2017C/190515_215954/0008/ postSingleMu_1_8.root -1 10000 Mu_1_8 split_-1
$RUN $DATA/MET/crab_job_MET2017Cv2/190518_230310/0000/ postSingleMu_1_9.root -1 10000 Mu_1_9 split_-1
$RUN $DATA/MET/crab_job_MET2017Cv2/190518_230310/0001/ postSingleMu_1_10.root -1 10000 Mu_1_10 split_-1

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
$RUN $DATA/MET/crab_job_MET2017Ev2/190515_211824/0000/ postSingleMu_3_9.root -1 10000 Mu_3_9 split_-1
$RUN $DATA/MET/crab_job_MET2017Ev2/190515_211824/0001/ postSingleMu_3_10.root -1 10000 Mu_3_10 split_-1
$RUN $DATA/MET/crab_job_MET2017Ev2/190515_211824/0002/ postSingleMu_3_11.root -1 10000 Mu_3_11 split_-1
$RUN $DATA/MET/crab_job_MET2017Ev3/190519_101922/0000/ postSingleMu_3_12.root -1 10000 Mu_3_12 split_-1

$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0000/ postSingleMu_4_0.root -1 10000 Mu_4_0 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0001/ postSingleMu_4_1.root -1 10000 Mu_4_1 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0002/ postSingleMu_4_2.root -1 10000 Mu_4_2 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0003/ postSingleMu_4_3.root -1 10000 Mu_4_3 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0004/ postSingleMu_4_4.root -1 10000 Mu_4_4 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0005/ postSingleMu_4_5.root -1 10000 Mu_4_5 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0006/ postSingleMu_4_6.root -1 10000 Mu_4_6 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0007/ postSingleMu_4_7.root -1 10000 Mu_4_7 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0008/ postSingleMu_4_8.root -1 10000 Mu_4_8 split_-1
$RUN $DATA/MET/crab_job_MET2017F/190516_164713/0009/ postSingleMu_4_9.root -1 10000 Mu_4_9 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0000/ postSingleMu_4_10.root -1 10000 Mu_4_10 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0001/ postSingleMu_4_11.root -1 10000 Mu_4_11 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0002/ postSingleMu_4_12.root -1 10000 Mu_4_12 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0003/ postSingleMu_4_13.root -1 10000 Mu_4_13 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0004/ postSingleMu_4_14.root -1 10000 Mu_4_14 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0005/ postSingleMu_4_15.root -1 10000 Mu_4_15 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0006/ postSingleMu_4_16.root -1 10000 Mu_4_16 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0007/ postSingleMu_4_17.root -1 10000 Mu_4_17 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv2/190518_231241/0008/ postSingleMu_4_18.root -1 10000 Mu_4_18 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv3/190519_231116/0000/ postSingleMu_4_19.root -1 10000 Mu_4_19 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv3/190519_231116/0001/ postSingleMu_4_20.root -1 10000 Mu_4_20 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv3/190519_231116/0002/ postSingleMu_4_21.root -1 10000 Mu_4_21 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv3/190519_231116/0003/ postSingleMu_4_22.root -1 10000 Mu_4_22 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv3/190519_231116/0004/ postSingleMu_4_23.root -1 10000 Mu_4_23 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv4/190522_094103/0000/ postSingleMu_4_24.root -1 10000 Mu_4_24 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv4/190522_094103/0001/ postSingleMu_4_25.root -1 10000 Mu_4_25 split_-1
$RUN $DATA/MET/crab_job_MET2017Fv4/190522_094103/0002/ postSingleMu_4_26.root -1 10000 Mu_4_26 split_-1
