config = {
    'year':2016,
    'regions':{'SignalRegion/':'8','DoubleEleCR/':'10','DoubleMuCR/':'10','SingleEleCR/':'10','SingleMuCR/':'10'},
    'Uncertainty':{
        'jes': {
            dir:'JetEnergyScale/',
            'region':[],
            'unc': {
                'jesUp':{id:'11'},
                'jesDown':{id:'12'}
            }
        },
        'pfu': {
            dir:'PFUncertainty/',
            'region':[],
            'unc':{
                'trackerUp'  :{id:'11'} ,'ecalUp'  :{id:'12'},'hcalUp'  :{id:'13'},
                'trackerDown':{id:'14'},'ecalDown':{id:'15'},'hcalDown':{id:'16'}
            }
        }
    }
}
