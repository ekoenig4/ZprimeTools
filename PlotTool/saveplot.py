#!/usr/bin/python

from ROOT import *
from sys import argv
from sys import path
import Plot as plot
from os import system,getcwd

gROOT.SetBatch(1)

def GetName(variable,UncType):
  name = variable;
  name = name.split("_")
  n = int(name[1]);
  name = name[0]
  
  if (8<=n and n<=15):
      name="";
  elif (UncType == "pfu"):
      if (n>=18 and n<=23): name="_trackerUp";
      elif (n>=24 and n<=29): name="_ecalUp";
      elif (n>=30 and n<=35): name="_hcalUp";
      elif (n>=38 and n<=43): name="_trackerDown";
      elif (n>=44 and n<=49): name="_ecalDown";
      elif (n>=50 and n<=55): name="_hcalDown";
      
  elif (UncType == "jes"):
      if (19<=n and n<=29):  name="_jesUp";
      elif (30<=n and n<=40): name="_jesDown";
      
  elif (UncType == "nlo"):
      if (16<=n and n<=23): name="_nloUp";
      elif (24<=n and n<=31): name="_nloDown";
      
  label = name
  return label;

argv.insert(1,"-1");
UncType = argv[-1]
argv.pop(len(argv)-1)
samples=plot.datamc(argv);
for variable in argv[1:]:
  
  samples.initiate(variable)
  varname = GetName(variable,UncType)
  
  hs_list = []
  
  for sample in samples.SampleList:
    if sample == 'Data':
      samples.histo['Data'].SetName("data_obs"+varname)
      if not ("Up" in varname or "Down" in varname): hs_list.append(samples.histo['Data'])
      
    elif sample == 'Signal':
      for signal in samples.signal:
        samples.histo[signal].SetName(signal+varname)
        hs_list.append(samples.histo[signal])
    else:
      samples.histo[sample].SetName(sample+varname)
      hs_list.append(samples.histo[sample])

  hs_root = "../../Systematics.root"
  print "Saving to",hs_root
  hs_file = TFile.Open(hs_root,"UPDATE")
  for hs in hs_list:
    if gDirectory.GetListOfKeys().Contains(hs.GetName()): gDirectory.Delete(hs.GetName()+";1")
    hs.Write()
  hs_file.Close()

    
