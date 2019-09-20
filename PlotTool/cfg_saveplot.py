config = {
    'year':2017,
    'regions':{'SignalRegion/':'8','DoubleEleCR/':'10','DoubleMuCR/':'10','SingleEleCR/':'10','SingleMuCR/':'10'},
    'Uncertainty':{
        'PFU': [ # ID is relative to the regions basic histogram number
            'PFU_tracker',
            'PFU_ecal',
            'PFU_hcal'
        ],
        'JES': [
            'JES'
        ],
        'QCD': [
            "QCD_LO",
            "QCD_K_LO",
            "QCD_d1K_LO",
            "QCD_d2K_LO",
            "QCD_K_NLO",
            "QCD_d1K_NLO",
            "QCD_d2K_NLO",
            "QCD_d3K_NLO",
            "QCD_kappa_NLO_EW",
            "QCD_kappa_NNLO_Sud",
            "QCD_kappa_EW",
            "QCD_d1kappa_EW",
            "QCD_d2kappa_EW",
            "QCD_d3kappa_EW",
            "QCD_dK_NLO_mix",
            "QCD_gammaind_LO"
        ],
    }
}
