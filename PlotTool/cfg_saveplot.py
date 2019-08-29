config = {
    'year':2017,
    'regions':{'SignalRegion/':'8','DoubleEleCR/':'10','DoubleMuCR/':'10','SingleEleCR/':'10','SingleMuCR/':'10'},
    'Uncertainty':{
        'pfu': {
            dir:'PFUncertainty/',
            'region':[],
            'unc':{ # ID is relative to the regions basic histogram number
                'trackerUp'  :{id:'2'},'ecalUp'  :{id:'3'},'hcalUp'  :{id:'4'},
                'trackerDown':{id:'5'},'ecalDown':{id:'6'},'hcalDown':{id:'7'}
            }
        },
        'jes': {
            dir:'JetEnergyScale/',
            'region':[],
            'unc': { # ID is relative to the regions basic histogram number
                'jesUp':{id:'8'},
                'jesDown':{id:'9'}
            }
        },
    }
}
