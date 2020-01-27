from ROOT import *

newjec = TFile.Open('PSW_SF.root')
oldjec = TFile.Open('PSW_2018_SF.root')

store = []

def compareFile(f1,f2):
    def compareDir(d1,d2):
        def compareHS(h1,h2):
            c = TCanvas("h_%s" % len(store),"",800,800)
            h1.Divide(h2)
            h1.Draw('hist')
            store.append(c)
        for key in d1.GetListOfKeys(): compareHS(d1.Get(key.GetName()),d2.Get(key.GetName()))
    for key in f1.GetListOfKeys(): compareDir(f1.Get(key.GetName()),f2.Get(key.GetName()))
compareFile(newjec,oldjec)
raw_input()
