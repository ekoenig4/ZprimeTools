config = {
    'year':2018,
    'regions':{'SignalRegion/':'9','DoubleEleCR/':'11','DoubleMuCR/':'11','SingleEleCR/':'11','SingleMuCR/':'11'},
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
        'PSW': [
            # "PSW_isrRed",   
	    # "PSW_fsrRed",      
	    # "PSW_isrDef",    
	    # "PSW_fsrDef",  
	    "PSW_isrCon",
	    "PSW_fsrCon",      
	    # "PSW_fsr_G2GG_muR",
	    # "PSW_fsr_G2QQ_muR",
	    # "PSW_fsr_Q2QG_muR",
	    # "PSW_fsr_X2XG_muR",
	    # "PSW_fsr_G2GG_cNS",
	    # "PSW_fsr_G2QQ_cNS",
	    # "PSW_fsr_Q2QG_cNS",
	    # "PSW_fsr_X2XG_cNS",
	    # "PSW_isr_G2GG_muR",
	    # "PSW_isr_G2QQ_muR",
	    # "PSW_isr_Q2QG_muR",
	    # "PSW_isr_X2XG_muR",
	    # "PSW_isr_G2GG_cNS",
	    # "PSW_isr_G2QQ_cNS",
	    # "PSW_isr_Q2QG_cNS",
	    # "PSW_isr_X2XG_cNS"
        ]
    }
}
