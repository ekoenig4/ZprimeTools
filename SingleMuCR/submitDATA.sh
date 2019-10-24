RUN="python ${CMSSW_BASE}/src/ZprimeTools2016/CondorTools/SubmitCondor.py -y 2016 -r WM analyze"

. "${CMSSW_BASE}/src/ZprimeTools2016/plugins/data_cfg.sh"

make || exit -1

echo "Do the CR Data samples"

file="SingleMu"
label="Mu"

MET_B "$RUN" $file $label
MET_C "$RUN" $file $label
MET_D "$RUN" $file $label
MET_E "$RUN" $file $label
MET_F "$RUN" $file $label
MET_G "$RUN" $file $label
MET_H "$RUN" $file $label
