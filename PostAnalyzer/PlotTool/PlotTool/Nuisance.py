class Nuisance(object):
    def __init__(self,name,norm=None,up=None,dn=None):
        self.name = name
        if norm is None and up is None and dn is None: return
        nbins = norm.GetNbinsX()
        self.up,self.dn = up,dn
        for ibin in range(1,nbins+1):
            diffUp = norm[ibin] - up[ibin]; diffDn = norm[ibin] - dn[ibin]
            self.up[ibin] = abs(max(diffUp,diffDn))
            self.dn[ibin] = abs(min(diffUp,diffDn))
