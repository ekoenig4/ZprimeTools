RUN="python ${CMSSW_BASE}/src/ZprimeTools2016/CondorTools/SubmitCondor.py -y 2016 -r WE analyze"

. "${CMSSW_BASE}/src/ZprimeTools2016/plugins/data_cfg.sh"

make || exit -1

echo "Do the CR Data samples"

file="SingleEle"
label="Ele"

ELE_B "$RUN" $file $label
ELE_C "$RUN" $file $label
ELE_D "$RUN" $file $label
ELE_E "$RUN" $file $label
ELE_F "$RUN" $file $label
ELE_G "$RUN" $file $label
ELE_H "$RUN" $file $label
