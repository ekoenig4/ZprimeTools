config = {
    'year':2017,
    'regions':{'SignalRegion/':'8','DoubleEleCR/':'10','DoubleMuCR/':'10','SingleEleCR/':'10','SingleMuCR/':'10'},
    'Uncertainty':{
        'PFU': [ # ID is relative to the regions basic histogram number
            # 'PFU_tracker',
            'PFU_ecal',
            # 'PFU_hcal'
        ],
        'JES': [
            'JES'
        ],
        'QCD': [
            "QCD_Scale",
            "QCD_Shape",
            "QCD_Proc",
            "NNLO_EWK",
            "NNLO_Miss",
            "NNLO_Sud",
            "QCD_EWK_Mix"
        ],
    }
}