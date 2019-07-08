#!/usr/bin/python

import os
from sys import argv
from mcinfo import lumi_by_era
from Plot import datamc

sample = datamc(show=False)
era = lumi_by_era[sample.region]

if __name__ == "__main__":
    region = sample.Data_FileNames[sample.region]
    if not os.path.isdir("DataEra/"): os.mkdir("DataEra/")
    print region
    for i,e in enumerate(sorted(era.keys())):
        filelist = " "
        for f in os.listdir(".output/"):
            if region+"_"+str(i)+"_" in f:
                filelist += ".output/" + f + " "
        os.system("hadd -f " + "DataEra/"+region+"_"+e+".root "+filelist)
