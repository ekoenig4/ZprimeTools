from ROOT import *
from utilities import *

class Transfer:
    tranunc = [
            "QCD_Scale",
            "QCD_Shape",
            "QCD_Proc",
            "NNLO_EWK",
            "NNLO_Miss",
            "NNLO_Sud",
            "QCD_EWK_Mix"]
    def __init__(self,name,num,den):
        self.name = name; self.num = num; self.den = den
        self.tf = GetRatio(num.histo,den.histo)

        self.nuisances = {}
        for nuisance in Transfer.tranunc:
            #Numerator Variation
            numup,numdn = num.nuisances[nuisance].GetHistos()
            tfnumup = GetRatio(numup,den.histo)
            tfnumdn = GetRatio(numdn,den.histo)
            numunc = '%s_%s' % (num.process,nuisance)
            self.nuisances[numunc] = Nuisance(self.name,numunc,tfnumup,tfnumdn,self.tf,type='abs')

            #Denomenator Variation
            denup,dendn = den.nuisances[nuisance].GetHistos()
            tfdenup = GetRatio(denup,den.histo)
            tfdendn = GetRatio(dendn,den.histo)
            denunc = '%s_%s' % (den.process,nuisance)
            self.nuisances[denunc] = Nuisance(self.name,denunc,tfdenup,tfdendn,self.tf,type='abs')
        
