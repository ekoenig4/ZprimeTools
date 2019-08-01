config = {
    'year':2016,
    'regions':{'SignalRegion/':'8','DoubleEleCR/':'10','DoubleMuCR/':'10','SingleEleCR/':'10','SingleMuCR/':'10'},
    'Uncertainty':{
        'jes': {
            dir:'JetEnergyScale/',
            'region':[],
            'unc': {
                'jesUp':{id:'12'},
                'jesDown':{id:'13'}
            }
        },
        'pfu': {
            dir:'PFUncertainty/',
            'region':[],
            'unc':{
                'trackerUp'  :{id:'12'} ,'ecalUp'  :{id:'13'},'hcalUp'  :{id:'14'},
                'trackerDown':{id:'15'},'ecalDown':{id:'16'},'hcalDown':{id:'17'}
            }
        },
        'psw': {
            dir:'PS_Weights/',
            'region':[],
            'unc':{
                'isrRedUp':{id:'14', eval:'muRfac=0.707'},'fsrRedUp':{id:'15', eval:'muRfac=0.707'}, 'isrRedDown':{id:'16', eval:'muRfac=1.414'},'fsrRedDown':{id:'17', eval:'muRfac=1.414' },
                'isrDefUp':{id:'18', eval:'muRfac=0.5'  },'fsrDefUp':{id:'19', eval:'muRfac=0.5'  }, 'isrDefDown':{id:'20', eval:'muRfac=2.0'  },'fsrDefDown':{id:'21', eval:'muRfac=2.0'   },
                'isrConUp':{id:'22', eval:'muRfac=0.25' },'fsrConUp':{id:'23', eval:'muRfac=0.25' }, 'isrConDown':{id:'24', eval:'muRfac=4.0'  },'fsrConDown':{id:'25', eval:'uRfac=4.0'  },
                # 'fsr_G2GG_muRDown':{id:'26',eval:'G2GG:muRfac=0.5'},
                # 'fsr_G2GG_muRUp':  {id:'27',eval:'G2GG:muRfac=2.0'},
                # 'fsr_G2QQ_muRDown':{id:'28',eval:'G2QQ:muRfac=0.5'},
                # 'fsr_G2QQ_muRUp':  {id:'29',eval:'G2QQ:muRfac=2.0'},
                # 'fsr_Q2QG_muRDown':{id:'30',eval:'Q2QG:muRfac=0.5'},
                # 'fsr_Q2QG_muRUp':  {id:'31',eval:'Q2QG:muRfac=2.0'},
                # 'fsr_X2XG_muRDown':{id:'32',eval:'X2XG:muRfac=0.5'},
                # 'fsr_X2XG_muRUp':  {id:'33',eval:'X2XG:muRfac=2.0'},
                # 'fsr_G2GG_cNSDown':{id:'34',eval:'G2GG:cNS=-2.0'  },
                # 'fsr_G2GG_cNSUp':  {id:'35',eval:'G2GG:cNS=2.0'   },
                # 'fsr_G2QQ_cNSDown':{id:'36',eval:'G2QQ:cNS=-2.0'  },
                # 'fsr_G2QQ_cNSUp':  {id:'37',eval:'G2QQ:cNS=2.0'   },
                # 'fsr_Q2QG_cNSDown':{id:'38',eval:'Q2QG:cNS=-2.0'  },
                # 'fsr_Q2QG_cNSUp':  {id:'39',eval:'Q2QG:cNS=2.0'   },
                # 'fsr_X2XG_cNSDown':{id:'40',eval:'X2XG:cNS=-2.0'  },
                # 'fsr_X2XG_cNSUp':  {id:'41',eval:'X2XG:cNS=2.0'   },
                # 'isr_G2GG_muRDown':{id:'42',eval:'G2GG:muRfac=0.5'},
                # 'isr_G2GG_muRUp':  {id:'43',eval:'G2GG:muRfac=2.0'},
                # 'isr_G2QQ_muRDown':{id:'44',eval:'G2QQ:muRfac=0.5'},
                # 'isr_G2QQ_muRUp':  {id:'45',eval:'G2QQ:muRfac=2.0'},
                # 'isr_Q2QG_muRDown':{id:'46',eval:'Q2QG:muRfac=0.5'},
                # 'isr_Q2QG_muRUp':  {id:'47',eval:'Q2QG:muRfac=2.0'},
                # 'isr_X2XG_muRDown':{id:'48',eval:'X2XG:muRfac=0.5'},
                # 'isr_X2XG_muRUp':  {id:'49',eval:'X2XG:muRfac=2.0'},
                # 'isr_G2GG_cNSDown':{id:'50',eval:'G2GG:cNS=-2.0'  },
                # 'isr_G2GG_cNSUp':  {id:'51',eval:'G2GG:cNS=2.0'   },
                # 'isr_G2QQ_cNSDown':{id:'52',eval:'G2QQ:cNS=-2.0'  },
                # 'isr_G2QQ_cNSUp':  {id:'53',eval:'G2QQ:cNS=2.0'   },
                # 'isr_Q2QG_cNSDown':{id:'54',eval:'Q2QG:cNS=-2.0'  },
                # 'isr_Q2QG_cNSUp':  {id:'55',eval:'Q2QG:cNS=2.0'   },
                # 'isr_X2XG_cNSDown':{id:'56',eval:'X2XG:cNS=-2.0'  },
                # 'isr_X2XG_cNSUp':  {id:'57',eval:'X2XG:cNS=2.0'   }
            }
        }
    }
}
