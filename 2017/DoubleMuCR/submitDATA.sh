RUN="python ${CMSSW_BASE}/src/ZprimeTools2017/CondorTools/SubmitCondor.py -y 2017 -r ZM analyze"

. "${CMSSW_BASE}/src/ZprimeTools2017/plugins/data_cfg.sh"

make || exit -1

echo "Do the CR Data samples"

file="DoubleMu"
label="Mu"

MET_B "$RUN" $file $label
MET_C "$RUN" $file $label
MET_D "$RUN" $file $label
MET_E "$RUN" $file $label
MET_F "$RUN" $file $label
