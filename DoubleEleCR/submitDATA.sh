$DATA1=/hdfs/store/user/varuns/Run2018_17Sep2018_May2019
$DATA2=/hdfs/store/user/varuns/Run2018D_Prompt
$MC=/hdfs/store/user/varuns/MC2018_Autumn18_May2019
$RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo 'Do the data samples'

