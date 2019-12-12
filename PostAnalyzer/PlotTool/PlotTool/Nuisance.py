from ROOT import TMath

def MakeDiff(self):
    nbins = self.norm.GetNbinsX()
    for ibin in range(1,nbins+1):
        diffUp = self.norm[ibin] - self.up[ibin]; diffDn = self.norm[ibin] - self.dn[ibin]
        self.up[ibin] = abs(max(diffUp,diffDn))
        self.dn[ibin] = abs(min(diffUp,diffDn))

class Nuisance(object):
    unclist = []
    def __init__(self,name,up,dn,norm,type="diff"):
        self.name = name
        self.norm = norm
        self.up,self.dn = up,dn
        if type == "abs": MakeDiff(self)
    def Integral(self,norm):
        nbins = norm.GetNbinsX()
        intUp = sum( norm[ibin] + self.up[ibin] for ibin in range(1,nbins+1) )
        intDn = sum( norm[ibin] - self.dn[ibin] for ibin in range(1,nbins+1) )
        return intUp,intDn
    def GetHistos(self):
        up = self.up.Clone(); dn = self.dn.Clone()
        nbins = self.norm.GetNbinsX()
        for ibin in range(1,nbins+1):
            up[ibin] = self.norm[ibin] + self.up[ibin]
            dn[ibin] = self.norm[ibin] - self.dn[ibin]
        return up,dn
    def add(self,other):
        if self.nuisance != other.nuisance: raise ValueError("%s is not %s" % (self.nuisance,other.nuisance))
        self.norm.Add(other.norm)
        nbins = self.norm.GetNbinsX()
        for ibin in range(1,nbins+1):
            self.up[ibin] = TMath.Sqrt( sum( nuis.up[ibin]**2 for nuis in (self,other) ) )
            self.dn[ibin] = TMath.Sqrt( sum( nuis.dn[ibin]**2 for nuis in (self,other) ) )
