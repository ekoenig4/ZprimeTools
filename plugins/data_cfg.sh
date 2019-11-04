DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019

MET_B () {
    ${1} $DATA/MET/crab_job_MET2017B/190511_093051/0000/ post${2}_0_0.root -1 10000 ${3}_0_0 split_-1
    ${1} $DATA/MET/crab_job_MET2017B/190511_093051/0001/ post${2}_0_1.root -1 10000 ${3}_0_1 split_-1
    ${1} $DATA/MET/crab_job_MET2017B/190511_093051/0002/ post${2}_0_2.root -1 10000 ${3}_0_2 split_-1
    ${1} $DATA/MET/crab_job_MET2017B/190511_093051/0003/ post${2}_0_3.root -1 10000 ${3}_0_3 split_-1
    ${1} $DATA/MET/crab_job_MET2017B/190511_093051/0004/ post${2}_0_4.root -1 10000 ${3}_0_4 split_-1
    ${1} $DATA/MET/crab_job_MET2017Bv2/190515_211629/0000/ post${2}_0_5.root -1 10000 ${3}_0_5 split_-1
}
MET_C () {
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0000/ post${2}_1_0.root -1 10000 ${3}_1_0 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0001/ post${2}_1_1.root -1 10000 ${3}_1_1 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0002/ post${2}_1_2.root -1 10000 ${3}_1_2 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0003/ post${2}_1_3.root -1 10000 ${3}_1_3 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0004/ post${2}_1_4.root -1 10000 ${3}_1_4 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0005/ post${2}_1_5.root -1 10000 ${3}_1_5 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0006/ post${2}_1_6.root -1 10000 ${3}_1_6 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0007/ post${2}_1_7.root -1 10000 ${3}_1_7 split_-1
    ${1} $DATA/MET/crab_job_MET2017C/190515_215954/0008/ post${2}_1_8.root -1 10000 ${3}_1_8 split_-1
    ${1} $DATA/MET/crab_job_MET2017Cv2/190518_230310/0000/ post${2}_1_9.root -1 10000 ${3}_1_9 split_-1
    ${1} $DATA/MET/crab_job_MET2017Cv2/190518_230310/0001/ post${2}_1_10.root -1 10000 ${3}_1_10 split_-1
}
MET_D () {
    ${1} $DATA/MET/crab_job_MET2017D/190508_233028/0000/ post${2}_2_0.root -1 10000 ${3}_2_0 split_-1
    ${1} $DATA/MET/crab_job_MET2017D/190508_233028/0001/ post${2}_2_1.root -1 10000 ${3}_2_1 split_-1
    ${1} $DATA/MET/crab_job_MET2017D/190508_233028/0002/ post${2}_2_2.root -1 10000 ${3}_2_2 split_-1
}
MET_E() {
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0000/ post${2}_3_0.root -1 10000 ${3}_3_0 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0001/ post${2}_3_1.root -1 10000 ${3}_3_1 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0002/ post${2}_3_2.root -1 10000 ${3}_3_2 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0003/ post${2}_3_3.root -1 10000 ${3}_3_3 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0004/ post${2}_3_4.root -1 10000 ${3}_3_4 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0005/ post${2}_3_5.root -1 10000 ${3}_3_5 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0006/ post${2}_3_6.root -1 10000 ${3}_3_6 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0007/ post${2}_3_7.root -1 10000 ${3}_3_7 split_-1
    ${1} $DATA/MET/crab_job_MET2017E/190511_093152/0008/ post${2}_3_8.root -1 10000 ${3}_3_8 split_-1
    ${1} $DATA/MET/crab_job_MET2017Ev2/190515_211824/0000/ post${2}_3_9.root -1 10000 ${3}_3_9 split_-1
    ${1} $DATA/MET/crab_job_MET2017Ev2/190515_211824/0001/ post${2}_3_10.root -1 10000 ${3}_3_10 split_-1
    ${1} $DATA/MET/crab_job_MET2017Ev2/190515_211824/0002/ post${2}_3_11.root -1 10000 ${3}_3_11 split_-1
    ${1} $DATA/MET/crab_job_MET2017Ev3/190519_101922/0000/ post${2}_3_12.root -1 10000 ${3}_3_12 split_-1
}
MET_F() {
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0000/ post${2}_4_0.root -1 10000 ${3}_4_0 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0001/ post${2}_4_1.root -1 10000 ${3}_4_1 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0002/ post${2}_4_2.root -1 10000 ${3}_4_2 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0003/ post${2}_4_3.root -1 10000 ${3}_4_3 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0004/ post${2}_4_4.root -1 10000 ${3}_4_4 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0005/ post${2}_4_5.root -1 10000 ${3}_4_5 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0006/ post${2}_4_6.root -1 10000 ${3}_4_6 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0007/ post${2}_4_7.root -1 10000 ${3}_4_7 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0008/ post${2}_4_8.root -1 10000 ${3}_4_8 split_-1
    ${1} $DATA/MET/crab_job_MET2017F/190516_164713/0009/ post${2}_4_9.root -1 10000 ${3}_4_9 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0000/ post${2}_4_10.root -1 10000 ${3}_4_10 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0001/ post${2}_4_11.root -1 10000 ${3}_4_11 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0002/ post${2}_4_12.root -1 10000 ${3}_4_12 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0003/ post${2}_4_13.root -1 10000 ${3}_4_13 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0004/ post${2}_4_14.root -1 10000 ${3}_4_14 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0005/ post${2}_4_15.root -1 10000 ${3}_4_15 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0006/ post${2}_4_16.root -1 10000 ${3}_4_16 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0007/ post${2}_4_17.root -1 10000 ${3}_4_17 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv2/190518_231241/0008/ post${2}_4_18.root -1 10000 ${3}_4_18 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv3/190519_231116/0000/ post${2}_4_19.root -1 10000 ${3}_4_19 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv3/190519_231116/0001/ post${2}_4_20.root -1 10000 ${3}_4_20 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv3/190519_231116/0002/ post${2}_4_21.root -1 10000 ${3}_4_21 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv3/190519_231116/0003/ post${2}_4_22.root -1 10000 ${3}_4_22 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv3/190519_231116/0004/ post${2}_4_23.root -1 10000 ${3}_4_23 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv4/190522_094103/0000/ post${2}_4_24.root -1 10000 ${3}_4_24 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv4/190522_094103/0001/ post${2}_4_25.root -1 10000 ${3}_4_25 split_-1
    ${1} $DATA/MET/crab_job_MET2017Fv4/190522_094103/0002/ post${2}_4_26.root -1 10000 ${3}_4_26 split_-1
}

ELE_B() {
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017B/190522_153830/0000/   post${2}_0_0.root -1 10000 ${3}_0_0 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017B/190522_153830/0001/   post${2}_0_1.root -1 10000 ${3}_0_1 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017B/190522_153830/0002/   post${2}_0_2.root -1 10000 ${3}_0_2 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017B/190522_153830/0003/   post${2}_0_3.root -1 10000 ${3}_0_3 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017B/190522_153830/0004/   post${2}_0_4.root -1 10000 ${3}_0_4 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017B/190522_153830/0005/   post${2}_0_5.root -1 10000 ${3}_0_5 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017B/190522_153830/0006/   post${2}_0_6.root -1 10000 ${3}_0_6 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Bv2/190524_103450/0000/ post${2}_0_7.root -1 10000 ${3}_0_7 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Bv3/190529_111922/0000/ post${2}_0_8.root -1 10000 ${3}_0_8 split_-1
}

ELE_C() {
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0000/ post${2}_1_0.root -1 10000 ${3}_1_0 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0001/ post${2}_1_1.root -1 10000 ${3}_1_1 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0002/ post${2}_1_2.root -1 10000 ${3}_1_2 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0003/ post${2}_1_3.root -1 10000 ${3}_1_3 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0004/ post${2}_1_4.root -1 10000 ${3}_1_4 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0005/ post${2}_1_5.root -1 10000 ${3}_1_5 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0006/ post${2}_1_6.root -1 10000 ${3}_1_6 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017C/190519_232250/0007/ post${2}_1_7.root -1 10000 ${3}_1_7 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0000/ post${2}_1_8.root -1 10000 ${3}_1_8 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0001/ post${2}_1_9.root -1 10000 ${3}_1_9 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0002/ post${2}_1_10.root -1 10000 ${3}_1_10 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0003/ post${2}_1_11.root -1 10000 ${3}_1_11 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0004/ post${2}_1_12.root -1 10000 ${3}_1_12 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0005/ post${2}_1_13.root -1 10000 ${3}_1_13 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0006/ post${2}_1_14.root -1 10000 ${3}_1_14 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0007/ post${2}_1_15.root -1 10000 ${3}_1_15 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Cv2/190522_094422/0008/ post${2}_1_16.root -1 10000 ${3}_1_16 split_-1
}
ELE_D() {
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0000/ post${2}_2_0.root -1 10000 ${3}_2_0 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0001/ post${2}_2_1.root -1 10000 ${3}_2_1 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0002/ post${2}_2_2.root -1 10000 ${3}_2_2 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0003/ post${2}_2_3.root -1 10000 ${3}_2_3 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0004/ post${2}_2_4.root -1 10000 ${3}_2_4 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0005/ post${2}_2_5.root -1 10000 ${3}_2_5 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017D/190522_153851/0006/ post${2}_2_6.root -1 10000 ${3}_2_6 split_-1
}
ELE_E() {
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0000/ post${2}_3_0.root -1 10000 ${3}_3_0 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0001/ post${2}_3_1.root -1 10000 ${3}_3_1 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0002/ post${2}_3_2.root -1 10000 ${3}_3_2 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0003/ post${2}_3_3.root -1 10000 ${3}_3_3 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0004/ post${2}_3_4.root -1 10000 ${3}_3_4 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0005/ post${2}_3_5.root -1 10000 ${3}_3_5 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017E/190521_134124/0006/ post${2}_3_6.root -1 10000 ${3}_3_6 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0000/ post${2}_3_7.root -1 10000 ${3}_3_7 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0001/ post${2}_3_8.root -1 10000 ${3}_3_8 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0002/ post${2}_3_9.root -1 10000 ${3}_3_9 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0003/ post${2}_3_10.root -1 10000 ${3}_3_10 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0004/ post${2}_3_11.root -1 10000 ${3}_3_11 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0005/ post${2}_3_12.root -1 10000 ${3}_3_12 split_-1
    ${1} $DATA/SingleElectron/crab_job_SingleEle2017Ev2/190524_101121/0006/ post${2}_3_13.root -1 10000 ${3}_3_13 split_-1
}

ELE_F() {
    ${1} /hdfs/store/user/varuns/SingleEle2017F-run_102X_data2017-farmout/ post${3}_4_0.root -1 10000 ${3}_4_0 split_-1
}
