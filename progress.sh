#!/bin/bash


cd ${1}/.status/

files=$( ls */*.log)
nfiles=$( ls */*.log | wc -l)
finish=1
n=0
for log in ${files[@]}; do
    echo $n of $nfiles
    start=$(grep -n "Job submitted from host" $log | tail -1 | cut -d : -f 1)
    term=$(grep -n "Job terminated." $log | tail -1 | cut -d : -f 1)
    
    if [[ $start -gt $term ]]; then
	echo $log not done
	finish=0
    fi
    n=$(($n + 1))
done
if [[ finish -eq 1 ]]; then
    echo ${1} Finished
fi
