config = {
    'year':2018,
    'regions':{'SignalRegion/':'9','DoubleEleCR/':'11','DoubleMuCR/':'11','SingleEleCR/':'11','SingleMuCR/':'11'},
    'Uncertainty':{
        'psw': {
            dir:'PS_Weights/',
            'region':[],
            'unc':{
                'isrRedUp':{id:'2', eval:'muRfac=0.707'},'fsrRedUp':{id:'3', eval:'muRfac=0.707'}, 'isrRedDown':{id:'4', eval:'muRfac=1.414'},'fsrRedDown':{id:'5', eval:'muRfac=1.414' },
                'isrDefUp':{id:'6', eval:'muRfac=0.5'  },'fsrDefUp':{id:'7', eval:'muRfac=0.5'  }, 'isrDefDown':{id:'8', eval:'muRfac=2.0'  },'fsrDefDown':{id:'9', eval:'muRfac=2.0'   },
                'isrConUp':{id:'10', eval:'muRfac=0.25' },'fsrConUp':{id:'11', eval:'muRfac=0.25' }, 'isrConDown':{id:'12', eval:'muRfac=4.0'  },'fsrConDown':{id:'13', eval:'uRfac=4.0'  },
                # 'fsr_G2GG_muRDown':{id:'14',eval:'G2GG:muRfac=0.5'},
                # 'fsr_G2GG_muRUp':  {id:'15',eval:'G2GG:muRfac=2.0'},
                # 'fsr_G2QQ_muRDown':{id:'16',eval:'G2QQ:muRfac=0.5'},
                # 'fsr_G2QQ_muRUp':  {id:'17',eval:'G2QQ:muRfac=2.0'},
                # 'fsr_Q2QG_muRDown':{id:'18',eval:'Q2QG:muRfac=0.5'},
                # 'fsr_Q2QG_muRUp':  {id:'19',eval:'Q2QG:muRfac=2.0'},
                # 'fsr_X2XG_muRDown':{id:'20',eval:'X2XG:muRfac=0.5'},
                # 'fsr_X2XG_muRUp':  {id:'21',eval:'X2XG:muRfac=2.0'},
                # 'fsr_G2GG_cNSDown':{id:'22',eval:'G2GG:cNS=-2.0'  },
                # 'fsr_G2GG_cNSUp':  {id:'23',eval:'G2GG:cNS=2.0'   },
                # 'fsr_G2QQ_cNSDown':{id:'24',eval:'G2QQ:cNS=-2.0'  },
                # 'fsr_G2QQ_cNSUp':  {id:'25',eval:'G2QQ:cNS=2.0'   },
                # 'fsr_Q2QG_cNSDown':{id:'26',eval:'Q2QG:cNS=-2.0'  },
                # 'fsr_Q2QG_cNSUp':  {id:'27',eval:'Q2QG:cNS=2.0'   },
                # 'fsr_X2XG_cNSDown':{id:'28',eval:'X2XG:cNS=-2.0'  },
                # 'fsr_X2XG_cNSUp':  {id:'29',eval:'X2XG:cNS=2.0'   },
                # 'isr_G2GG_muRDown':{id:'30',eval:'G2GG:muRfac=0.5'},
                # 'isr_G2GG_muRUp':  {id:'31',eval:'G2GG:muRfac=2.0'},
                # 'isr_G2QQ_muRDown':{id:'32',eval:'G2QQ:muRfac=0.5'},
                # 'isr_G2QQ_muRUp':  {id:'33',eval:'G2QQ:muRfac=2.0'},
                # 'isr_Q2QG_muRDown':{id:'34',eval:'Q2QG:muRfac=0.5'},
                # 'isr_Q2QG_muRUp':  {id:'35',eval:'Q2QG:muRfac=2.0'},
                # 'isr_X2XG_muRDown':{id:'36',eval:'X2XG:muRfac=0.5'},
                # 'isr_X2XG_muRUp':  {id:'37',eval:'X2XG:muRfac=2.0'},
                # 'isr_G2GG_cNSDown':{id:'38',eval:'G2GG:cNS=-2.0'  },
                # 'isr_G2GG_cNSUp':  {id:'39',eval:'G2GG:cNS=2.0'   },
                # 'isr_G2QQ_cNSDown':{id:'40',eval:'G2QQ:cNS=-2.0'  },
                # 'isr_G2QQ_cNSUp':  {id:'41',eval:'G2QQ:cNS=2.0'   },
                # 'isr_Q2QG_cNSDown':{id:'42',eval:'Q2QG:cNS=-2.0'  },
                # 'isr_Q2QG_cNSUp':  {id:'43',eval:'Q2QG:cNS=2.0'   },
                # 'isr_X2XG_cNSDown':{id:'44',eval:'X2XG:cNS=-2.0'  },
                # 'isr_X2XG_cNSUp':  {id:'45',eval:'X2XG:cNS=2.0'   }
            }
        },
        'pfu': {
            dir:'PFUncertainty/',
            'region':[],
            'unc':{
                'trackerUp'  :{id:'46'},'ecalUp'  :{id:'47'},'hcalUp'  :{id:'48'},
                'trackerDown':{id:'49'},'ecalDown':{id:'50'},'hcalDown':{id:'51'}
            }
        },
        'jes': {
            dir:'JetEnergyScale/',
            'region':[],
            'unc': {
                'jesUp':  {id:'52'},
                'jesDown':{id:'53'}
            }
        },
    }
}
