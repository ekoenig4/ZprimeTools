config = {
    'year':2016,
    'regions':{'SignalRegion/':'8','DoubleEleCR/':'10','DoubleMuCR/':'10','SingleEleCR/':'10','SingleMuCR/':'10'},
    'Uncertainty':{
        'jes': {
            dir:'JetEnergyScale/',
            'region':['SignalRegion/'],
            'unc': {
                'jesUp':{id:'9'},
                'jesDown':{id:'10'}
            }
        },
        'pfu': {
            dir:'PFUncertainty/',
            'region':['SignalRegion/'],
            'unc':{
                'trackerUp'  :{id:'9'} ,'ecalUp'  :{id:'10'},'hcalUp'  :{id:'11'},
                'trackerDown':{id:'12'},'ecalDown':{id:'13'},'hcalDown':{id:'14'}
            }
        }
    }
}
