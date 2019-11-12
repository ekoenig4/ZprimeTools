version="2016"

lumi = {"SingleEleCR":35900,
        "DoubleEleCR":35900,
        "SingleMuCR":35900,
        "DoubleMuCR":35900,
        "SignalRegion":1892}

lumi_by_era = {"SingleEleCR":{"B":8294,"C":4242,"D":4025,"E":3104,"F":7565,"G":8410,"H":216},
               "DoubleEleCR":{"B":8294,"C":4242,"D":4025,"E":3104,"F":7565,"G":8410,"H":216},
               "SingleMuCR":{"B":8319,"C":4242,"D":4025,"E":3105,"F":7566,"G":8435,"H":216},
               "DoubleMuCR":{"B":8319,"C":4242,"D":4025,"E":3105,"F":7566,"G":8435,"H":216},
               "SignalRegion":{"F":1892}}

WJets_FileNames = ["postW100to200","postW200to400","postW400to600","postW600to800","postW800to1200","postW1200to2500","postW2500toInf","postWMLM"]

ZJets_FileNames = ["postZ100to200","postZ200to400","postZ400to600","postZ600to800","postZ800to1200","postZ1200to2500","postZ2500toInf"];

GJets_FileNames = ["postGJets40to100","postGJets100to200","postGJets200to400","postGJets400to600","postGJets600toInf"];

DYJets_FileNames = ["postDY100to200","postDY200to400","postDY400to600","postDY600to800","postDY800to1200","postDY1200to2500","postDY2500toInf","postDYMLM"]

TTJets_FileNames = ["postTTJetsMLM"]

DiBoson_FileNames = ["postWW","postWZ","postZZ"]

QCD_FileNames = ["postQCD100to200","postQCD200to300","postQCD300to500","postQCD500to700","postQCD700to1000","postQCD1000to1500","postQCD1500to2000","postQCD2000toInf"];

xsec = {
'postZ100to200': 280.5,
'postZ200to400': 77.67,
'postZ400to600': 10.73,
'postZ600to800': 2.559,
'postZ800to1200': 1.1796,
'postZ1200to2500': 0.28633,
'postZ2500toInf': 0.0006945,

'postWMLM': 50690,
'postW100to200': 1343,
'postW200to400': 359.7,
'postW400to600': 48.91,
'postW600to800': 12.05,
'postW800to1200': 5.501,
'postW1200to2500': 1.329,
'postW2500toInf': 0.03216,

'postDYMLM':4895,
'postDY100to200': 148,
'postDY200to400': 40.94,
'postDY400to600': 5.497,
'postDY600to800': 1.354,
'postDY800to1200': 0.6250,
'postDY1200to2500': 0.1511,
'postDY2500toInf': 0.003647,

'postGJets40to100': 17420,
'postGJets100to200': 5391,
'postGJets200to400': 1168,
'postGJets400to600':132.5,
'postGJets600toInf': 44.05,

'postTTJetsMLM': 831.76,

'postQCD100to200': 27500000,
'postQCD200to300': 1735000,
'postQCD300to500': 367000,
'postQCD500to700': 29370,
'postQCD700to1000': 6524,
'postQCD1000to1500': 1064,
'postQCD1500to2000': 121.5,
'postQCD2000toInf': 25.42,


'postWW': 118.7,
'postWZ': 47.2,
'postZZ': 16.6
}
