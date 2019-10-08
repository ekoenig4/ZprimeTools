version="2017"

lumi = {"SingleEleCR":23192,
        "DoubleEleCR":23192,
        "SingleMuCR":41486,
        "DoubleMuCR":41486,
        "SignalRegion":1198}

lumi_by_era = {"SingleEleCR":{"B":4793,"C":9631,"D":4248,"E":9314,"F":13498},
               "DoubleEleCR":{"B":4793,"C":9631,"D":4248,"E":9314,"F":13498},
               "SingleMuCR":{"B":4793,"C":9633,"D":4248,"E":9314,"F":13498},
               "DoubleMuCR":{"B":4793,"C":9633,"D":4248,"E":9314,"F":13498},
               "SignalRegion":{"B":1198}}

WJets_FileNames = ["postW100to200","postW200to400","postW400to600","postW600to800","postW800to1200","postW1200to2500","postW2500toInf","postWJets_MLM"]

ZJets_FileNames = ["postZ100to200","postZ200to400","postZ400to600","postZ600to800","postZ800to1200","postZ1200to2500","postZ2500toInf"];

GJets_FileNames = ["postGJets40to100","postGJets100to200","postGJets200to400","postGJets400to600","postGJets600toInf"];

DYJets_FileNames = ["postDY70to100","postDY100to200","postDY200to400","postDY400to600","postDY600to800","postDY800to1200","postDY1200to2500","postDY2500toInf"]

TTJets_FileNames = ["postTTJetsDiLept"];#"postTTJets_MLM

DiBoson_FileNames = ["postWW","postWWto4Q","postWWtoLNuQQ","postWZ","postZZ","postWWto2L2Nu"]#,"postWWto2L2NuPS"]

QCD_FileNames = ["postQCD100to200","postQCD200to300","postQCD300to500","postQCD500to700","postQCD700to1000","postQCD1000to1500","postQCD1500to2000","postQCD2000toInf"];

xsec = {
"postZ100to200":3.045e+02,
"postZ200to400":9.185e+01,
"postZ400to600":1.311e+01,
"postZ600to800":3.257e+00,
"postZ800to1200":1.499e+00,
"postZ1200to2500":3.430e-01,
"postZ2500toInf":5.146e-03,
    
"postWJets_MLM":5.279e+04,
"postW100to200":1.395e+03,
"postW200to400":4.093e+02,
"postW400to600":5.791e+01,
"postW600to800":1.293e+01,
"postW800to1200":5.395e+00,
"postW1200to2500":1.080e+00,
"postW2500toInf":8.053e-03,
    
"postDY70to100":1.471e+02,
"postDY100to200":1.610e+02,
"postDY200to400":4.858e+01,
"postDY400to600":6.982e+00,
"postDY600to800":1.747e+00,
"postDY800to1200":8.052e-01,
"postDY1200to2500":1.927e-01,
"postDY2500toInf":3.478e-03,
    
"postGJets40to100":1.862e+04,
"postGJets100to200":8.622e+03,
"postGJets200to400":2.193e+03,
"postGJets400to600":2.585e+02,
"postGJets600toInf":8.521e+01,
    
"postTTJetsDiLept":5.424e+01,
    
"postQCD100to200":2.369e+07,
"postQCD200to300":1.556e+06,
"postQCD300to500":3.236e+05,
"postQCD500to700":2.999e+04,
"postQCD700to1000":6.351e+03,
"postQCD1000to1500":1.094e+03,
"postQCD1500to2000":9.901e+01,
"postQCD2000toInf":2.023e+01,
    
"postWW":7.590e+01,
"postWWtoLNuQQ":4.599e+01,
"postWWto2L2Nu":1.108e+01,
"postWWto4Q":4.773e+01,
    
"postWZ":2.757e+01,
"postZZ":1.214e+01
}

usama_xsec = {
'postZ100to200': 280.5,
'postZ200to400': 77.67,
'postZ400to600': 10.73,
'postZ600to800': 2.559,
'postZ800to1200': 1.1796,
'postZ1200to2500': 0.28633,
'postZ2500toInf': 0.0006945,

'postWJets_MLM': 50690,
'postW100to200': 1343,
'postW200to400': 359.7,
'postW400to600': 48.91,
'postW600to800': 12.05,
'postW800to1200': 5.501,
'postW1200to2500': 1.329,
'postW2500toInf': 0.03216,

'postDY70to100':147.1,
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

"postTTJetsDiLept":5.424e+01,
"postTTJetsSingleLeptFromT":1.092e+02,
'postTTJets_MLM': 831.76,

'postQCD100to200': 27500000,
'postQCD200to300': 1735000,
'postQCD300to500': 367000,
'postQCD500to700': 29370,
'postQCD700to1000': 6524,
'postQCD1000to1500': 1064,
'postQCD1500to2000': 121.5,
'postQCD2000toInf': 25.42,


'postWW': 118.7,
"postWWtoLNuQQ":4.599e+01,
"postWWto2L2Nu":1.108e+01,
"postWWto4Q":4.773e+01,
    
'postWZ': 47.2,
'postZZ': 16.6
}
