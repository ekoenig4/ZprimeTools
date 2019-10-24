RUN="python ${CMSSW_BASE}/src/ZprimeTools2018/CondorTools/SubmitCondor.py -y 2018 -r WM analyze"

. "${CMSSW_BASE}/src/ZprimeTools2018/plugins/data_cfg.sh"

make || exit -1

echo "Do the CR Data samples"

file="SingleMu"
label="Mu"

MET_A "$RUN" $file $label
MET_B "$RUN" $file $label
MET_C "$RUN" $file $label
MET_D "$RUN" $file $label
