#!/bin/sh
cwd=$(pwd)
for dir in $@; do
    if [[ -d $dir ]]; then
	cd $dir
	filenames=$(ls *.json)
	if [[ -f lumi.txt ]]; then rm lumi.txt; fi
	for fn in $filenames; do
	    echo $fn
	    echo $fn >> lumi.txt
	    brilcalc lumi -b "STABLE BEAMS" --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -i $fn -u /pb >> lumi.txt
	done
    fi
    cd $cwd
done
