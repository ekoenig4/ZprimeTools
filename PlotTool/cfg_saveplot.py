config = {
    'year':2018,
    'regions':{'SignalRegion/':'9','DoubleEleCR/':'11','DoubleMuCR/':'11','SingleEleCR/':'11','SingleMuCR/':'11'},
    'Uncertainty':{
        'psw': {
            'region':[],
            'unc':{
                'isrRedUp':{id:'1', eval:'muRfac=0.707'},'fsrRedUp':{id:'2', eval:'muRfac=0.707'}, 'isrRedDown':{id:'3', eval:'muRfac=1.414'},'fsrRedDown':{id:'4', eval:'muRfac=1.414' },
                'isrDefUp':{id:'5', eval:'muRfac=0.5'  },'fsrDefUp':{id:'6', eval:'muRfac=0.5'  }, 'isrDefDown':{id:'7', eval:'muRfac=2.0'  },'fsrDefDown':{id:'8', eval:'muRfac=2.0'   },
                'isrConUp':{id:'9', eval:'muRfac=0.25' },'fsrConUp':{id:'10', eval:'muRfac=0.25' }, 'isrConDown':{id:'11', eval:'muRfac=4.0'  },'fsrConDown':{id:'12', eval:'uRfac=4.0'  },
                # 'fsr_G2GG_muRDown':{id:'13',eval:'G2GG:muRfac=0.5'},
                # 'fsr_G2GG_muRUp':  {id:'14',eval:'G2GG:muRfac=2.0'},
                # 'fsr_G2QQ_muRDown':{id:'15',eval:'G2QQ:muRfac=0.5'},
                # 'fsr_G2QQ_muRUp':  {id:'16',eval:'G2QQ:muRfac=2.0'},
                # 'fsr_Q2QG_muRDown':{id:'17',eval:'Q2QG:muRfac=0.5'},
                # 'fsr_Q2QG_muRUp':  {id:'18',eval:'Q2QG:muRfac=2.0'},
                # 'fsr_X2XG_muRDown':{id:'19',eval:'X2XG:muRfac=0.5'},
                # 'fsr_X2XG_muRUp':  {id:'20',eval:'X2XG:muRfac=2.0'},
                # 'fsr_G2GG_cNSDown':{id:'21',eval:'G2GG:cNS=-2.0'  },
                # 'fsr_G2GG_cNSUp':  {id:'22',eval:'G2GG:cNS=2.0'   },
                # 'fsr_G2QQ_cNSDown':{id:'23',eval:'G2QQ:cNS=-2.0'  },
                # 'fsr_G2QQ_cNSUp':  {id:'24',eval:'G2QQ:cNS=2.0'   },
                # 'fsr_Q2QG_cNSDown':{id:'25',eval:'Q2QG:cNS=-2.0'  },
                # 'fsr_Q2QG_cNSUp':  {id:'26',eval:'Q2QG:cNS=2.0'   },
                # 'fsr_X2XG_cNSDown':{id:'27',eval:'X2XG:cNS=-2.0'  },
                # 'fsr_X2XG_cNSUp':  {id:'28',eval:'X2XG:cNS=2.0'   },
                # 'isr_G2GG_muRDown':{id:'29',eval:'G2GG:muRfac=0.5'},
                # 'isr_G2GG_muRUp':  {id:'30',eval:'G2GG:muRfac=2.0'},
                # 'isr_G2QQ_muRDown':{id:'31',eval:'G2QQ:muRfac=0.5'},
                # 'isr_G2QQ_muRUp':  {id:'32',eval:'G2QQ:muRfac=2.0'},
                # 'isr_Q2QG_muRDown':{id:'33',eval:'Q2QG:muRfac=0.5'},
                # 'isr_Q2QG_muRUp':  {id:'34',eval:'Q2QG:muRfac=2.0'},
                # 'isr_X2XG_muRDown':{id:'35',eval:'X2XG:muRfac=0.5'},
                # 'isr_X2XG_muRUp':  {id:'36',eval:'X2XG:muRfac=2.0'},
                # 'isr_G2GG_cNSDown':{id:'37',eval:'G2GG:cNS=-2.0'  },
                # 'isr_G2GG_cNSUp':  {id:'38',eval:'G2GG:cNS=2.0'   },
                # 'isr_G2QQ_cNSDown':{id:'39',eval:'G2QQ:cNS=-2.0'  },
                # 'isr_G2QQ_cNSUp':  {id:'40',eval:'G2QQ:cNS=2.0'   },
                # 'isr_Q2QG_cNSDown':{id:'41',eval:'Q2QG:cNS=-2.0'  },
                # 'isr_Q2QG_cNSUp':  {id:'42',eval:'Q2QG:cNS=2.0'   },
                # 'isr_X2XG_cNSDown':{id:'43',eval:'X2XG:cNS=-2.0'  },
                # 'isr_X2XG_cNSUp':  {id:'44',eval:'X2XG:cNS=2.0'   }
            }
        },
        'pfu': {
            'region':[],
            'unc':{
                'trackerUp'  :{id:'45'},'ecalUp'  :{id:'46'},'hcalUp'  :{id:'47'},
                'trackerDown':{id:'48'},'ecalDown':{id:'49'},'hcalDown':{id:'50'}
            }
        },
        'jes': {
            'region':[],
            'unc': {
                'jesUp':  {id:'51'},
                'jesDown':{id:'52'}
            }
        },
        'ewk':{
            'region':[],
            'unc': {
                'ewkUp':  {id:'53'},
                'ewkDown':{id:'54'},
            }
        },
    }
}
