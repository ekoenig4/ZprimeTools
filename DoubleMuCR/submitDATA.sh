DATA1=/hdfs/store/user/varuns/Run2018_17Sep2018_May2019
DATA2=/hdfs/store/user/varuns/Run2018D_Prompt
MC=/hdfs/store/user/varuns/MC2018_Autumn18_May2019
RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo 'Do the data samples'

$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0000/ postDoubleMu_0_0.root -1 10000 Mu_0_0 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0001/ postDoubleMu_0_1.root -1 10000 Mu_0_1 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0002/ postDoubleMu_0_2.root -1 10000 Mu_0_2 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0003/ postDoubleMu_0_3.root -1 10000 Mu_0_3 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0004/ postDoubleMu_0_4.root -1 10000 Mu_0_4 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0005/ postDoubleMu_0_5.root -1 10000 Mu_0_5 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0006/ postDoubleMu_0_6.root -1 10000 Mu_0_6 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0007/ postDoubleMu_0_7.root -1 10000 Mu_0_7 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0008/ postDoubleMu_0_8.root -1 10000 Mu_0_8 split_-1
$RUN $DATA1/MET/crab_job_MET2018A/190511_011526/0009/ postDoubleMu_0_9.root -1 10000 Mu_0_9 split_-1

$RUN $DATA1/MET/crab_job_MET2018B/190511_011551/0000/ postDoubleMu_1_0.root -1 10000 Mu_1_0 split_-1
$RUN $DATA1/MET/crab_job_MET2018B/190511_011551/0001/ postDoubleMu_1_1.root -1 10000 Mu_1_1 split_-1
$RUN $DATA1/MET/crab_job_MET2018B/190511_011551/0002/ postDoubleMu_1_2.root -1 10000 Mu_1_2 split_-1
$RUN $DATA1/MET/crab_job_MET2018B/190511_011551/0003/ postDoubleMu_1_3.root -1 10000 Mu_1_3 split_-1
$RUN $DATA1/MET/crab_job_MET2018B/190511_011551/0004/ postDoubleMu_1_4.root -1 10000 Mu_1_4 split_-1

$RUN $DATA1/MET/crab_job_MET2018C/190511_011627/0000/ postDoubleMu_2_0.root -1 10000 Mu_2_0 split_-1
$RUN $DATA1/MET/crab_job_MET2018C/190511_011627/0001/ postDoubleMu_2_1.root -1 10000 Mu_2_1 split_-1
$RUN $DATA1/MET/crab_job_MET2018C/190511_011627/0002/ postDoubleMu_2_2.root -1 10000 Mu_2_2 split_-1
$RUN $DATA1/MET/crab_job_MET2018C/190511_011627/0003/ postDoubleMu_2_3.root -1 10000 Mu_2_3 split_-1
$RUN $DATA1/MET/crab_job_MET2018C/190511_011627/0004/ postDoubleMu_2_4.root -1 10000 Mu_2_4 split_-1

$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0000/ postDoubleMu_3_0.root -1 10000 Mu_3_0 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0001/ postDoubleMu_3_1.root -1 10000 Mu_3_1 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0002/ postDoubleMu_3_2.root -1 10000 Mu_3_2 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0003/ postDoubleMu_3_3.root -1 10000 Mu_3_3 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0004/ postDoubleMu_3_4.root -1 10000 Mu_3_4 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0005/ postDoubleMu_3_5.root -1 10000 Mu_3_5 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0006/ postDoubleMu_3_6.root -1 10000 Mu_3_6 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0007/ postDoubleMu_3_7.root -1 10000 Mu_3_7 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2/190512_164040/0008/ postDoubleMu_3_8.root -1 10000 Mu_3_8 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0000/ postDoubleMu_3_9.root -1 10000 Mu_3_9 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0001/ postDoubleMu_3_10.root -1 10000 Mu_3_10 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0002/ postDoubleMu_3_11.root -1 10000 Mu_3_11 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0003/ postDoubleMu_3_12.root -1 10000 Mu_3_12 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0004/ postDoubleMu_3_13.root -1 10000 Mu_3_13 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0005/ postDoubleMu_3_14.root -1 10000 Mu_3_14 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0006/ postDoubleMu_3_15.root -1 10000 Mu_3_15 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0007/ postDoubleMu_3_16.root -1 10000 Mu_3_16 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0008/ postDoubleMu_3_17.root -1 10000 Mu_3_17 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_2/190516_203151/0009/ postDoubleMu_3_18.root -1 10000 Mu_3_18 split_-1
$RUN $DATA2/MET/crab_job_MET2018Dv2_3/190519_232032/0000/ postDoubleMu_3_19.root -1 10000 Mu_3_19 split_-1
