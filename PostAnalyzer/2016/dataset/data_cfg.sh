DATA_MET=/hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR
DATA_ELE=/hdfs/store/user/gomber/MonoZprime_Ntuples_19May_CR

MET_B () {
    ${1} $DATA_MET/MET/crab_dataset1/180529_*/0000/ post${2}_0_0.root -1 10000 ${3}_0_0 split_-1
    ${1} $DATA_MET/MET/crab_dataset1/180529_*/0001/ post${2}_0_1.root -1 10000 ${3}_0_1 split_-1
    ${1} $DATA_MET/MET/crab_dataset1/180529_*/0002/ post${2}_0_2.root -1 10000 ${3}_0_2 split_-1
    ${1} $DATA_MET/MET/crab_dataset1/180529_*/0003/ post${2}_0_3.root -1 10000 ${3}_0_3 split_-1
    ${1} $DATA_MET/MET/crab_dataset2/180529_*/0000/ post${2}_0_4.root -1 10000 ${3}_0_4 split_-1
    ${1} $DATA_MET/MET/crab_dataset2/180529_*/0001/ post${2}_0_5.root -1 10000 ${3}_0_5 split_-1
}
MET_C () {
    ${1} $DATA_MET/MET/crab_dataset3/180529_*/0000/ post${2}_1_0.root -1 10000 ${3}_1_0 split_-1
    ${1} $DATA_MET/MET/crab_dataset3/180529_*/0001/ post${2}_1_1.root -1 10000 ${3}_1_1 split_-1
}
MET_D () {
    ${1} $DATA_MET/MET/crab_dataset4/180529_*/0000/ post${2}_2_0.root -1 10000 ${3}_2_0 split_-1
    ${1} $DATA_MET/MET/crab_dataset4/180529_*/0001/ post${2}_2_1.root -1 10000 ${3}_2_1 split_-1
}
MET_E () {
    ${1} $DATA_MET/MET/crab_dataset5/180529_*/0000/ post${2}_3_0.root -1 10000 ${3}_3_0 split_-1
    ${1} $DATA_MET/MET/crab_dataset5/180529_*/0001/ post${2}_3_1.root -1 10000 ${3}_3_1 split_-1
}
MET_F () {
    ${1} $DATA_MET/MET/crab_dataset6/180529_*/0000/ post${2}_4_0.root -1 10000 ${3}_4_0 split_-1
    ${1} $DATA_MET/MET/crab_dataset6/180529_*/0001/ post${2}_4_1.root -1 10000 ${3}_4_1 split_-1
    ${1} $DATA_MET/MET/crab_dataset6/180529_*/0002/ post${2}_4_2.root -1 10000 ${3}_4_2 split_-1
}
MET_G () {
    ${1} $DATA_MET/MET/crab_dataset7/180529_*/0000/ post${2}_5_0.root -1 10000 ${3}_5_0  split_-1
    ${1} $DATA_MET/MET/crab_dataset7/180529_*/0001/ post${2}_5_1.root -1 10000 ${3}_5_1  split_-1
    ${1} $DATA_MET/MET/crab_dataset7/180529_*/0002/ post${2}_5_2.root -1 10000 ${3}_5_2  split_-1
    ${1} $DATA_MET/MET/crab_dataset7/180529_*/0003/ post${2}_5_3.root -1 10000 ${3}_5_3  split_-1
}
MET_H () {
    ${1} $DATA_MET/MET/crab_dataset8/180529_*/0000/ post${2}_6_0.root -1 10000 ${3}_6_0 split_-1
}

ELE_B () {
    ${1} $DATA_ELE/SingleElectron/crab_dataset1/180529_*/0000/ post${2}_0_0.root -1 10000 ${3}_0_0 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset1/180529_*/0001/ post${2}_0_1.root -1 10000 ${3}_0_1 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset1/180529_*/0002/ post${2}_0_2.root -1 10000 ${3}_0_2 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset1/180529_*/0003/ post${2}_0_3.root -1 10000 ${3}_0_3 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset2/180529_*/0000/ post${2}_0_4.root -1 10000 ${3}_0_4 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset2/180529_*/0001/ post${2}_0_5.root -1 10000 ${3}_0_5 split_-1
}
ELE_C () {
    ${1} $DATA_ELE/SingleElectron/crab_dataset3/180529_*/0000/ post${2}_1_0.root -1 10000 ${3}_1_0 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset3/180529_*/0001/ post${2}_1_1.root -1 10000 ${3}_1_1 split_-1
}
ELE_D () {
    ${1} $DATA_ELE/SingleElectron/crab_dataset4/180529_*/0000/ post${2}_2_0.root -1 10000 ${3}_2_0 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset4/180529_*/0001/ post${2}_2_1.root -1 10000 ${3}_2_1 split_-1
}
ELE_E () {
    ${1} $DATA_ELE/SingleElectron/crab_dataset5/180529_*/0000/ post${2}_3_0.root -1 10000 ${3}_3_0 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset5/180529_*/0001/ post${2}_3_1.root -1 10000 ${3}_3_1 split_-1
}
ELE_F () {
    ${1} $DATA_ELE/SingleElectron/crab_dataset6/180529_*/0000/ post${2}_4_0.root -1 10000 ${3}_4_0 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset6/180529_*/0001/ post${2}_4_1.root -1 10000 ${3}_4_1 split_-1
    ${1} $DATA_ELE/SingleElectron/crab_dataset6/180529_*/0002/ post${2}_4_2.root -1 10000 ${3}_4_2 split_-1
}
ELE_G() {
    ${1} $DATA_ELE/SingleElectron/crab_dataset7/180529_*/0000/ post${2}_5_0.root -1 10000 ${3}_5_0 split_-1 
    ${1} $DATA_ELE/SingleElectron/crab_dataset7/180529_*/0001/ post${2}_5_1.root -1 10000 ${3}_5_1 split_-1 
    ${1} $DATA_ELE/SingleElectron/crab_dataset7/180529_*/0002/ post${2}_5_2.root -1 10000 ${3}_5_2 split_-1 
    ${1} $DATA_ELE/SingleElectron/crab_dataset7/180529_*/0003/ post${2}_5_3.root -1 10000 ${3}_5_3 split_-1  
}
ELE_H() {
    ${1} $DATA_ELE/SingleElectron/crab_dataset8/180529_*/0000/ post${2}_6_0.root -1 10000 ${3}_6_0 split_-1 
}
