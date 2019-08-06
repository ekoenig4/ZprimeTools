config = {
    'year':2016,
    'regions':{'SignalRegion/':'8','DoubleEleCR/':'10','DoubleMuCR/':'10','SingleEleCR/':'10','SingleMuCR/':'10'},
    'Uncertainty':{
        'pfu': {
            dir:'PFUncertainty/',
            'region':[],
            'unc':{ # ID is relative to the regions basic histogram number
                'trackerUp'  :{id:'1'},'ecalUp'  :{id:'2'},'hcalUp'  :{id:'3'},
                'trackerDown':{id:'4'},'ecalDown':{id:'5'},'hcalDown':{id:'6'}
            }
        },
        'jes': {
            dir:'JetEnergyScale/',
            'region':[],
            'unc': { # ID is relative to the regions basic histogram number
                'jesUp':{id:'7'},
                'jesDown':{id:'8'}
            }
        },
        'ewk': {
            dir:'JetEnergyScale/',
            'region':[],
            'unc': { # ID is relative to the regions basic histogram number
                'ewkUp':{id:'9'},
                'ewkDown':{id:'10'}
            }
        },
    }
}
