RUN="python ${CMSSW_BASE}/src/ZprimeTools2016/CondorTools/SubmitCondor.py -y 2016 -r SR analyze"

. "${CMSSW_BASE}/src/ZprimeTools2016/plugins/data_cfg.sh"

make || exit -1

echo "Do the CR Data samples"

file="METdata"
label="MET"

MET_F "$RUN" $file $label
