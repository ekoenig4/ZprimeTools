from ROOT import *
import os

def ValidProctype(proctype):
    if not (proctype == 'data' or proctype == 'bkg' or proctype == 'signal'):
        raise ValueError('Invalid proctype: %s' % proctype)
def GetDirname(variable,sub=None):
    ndir = variable.split('_')[-1]
    dirname = 'ZprimeJet_%s' % ndir
    if sub != None: dirname += '/%s' % sub
    return dirname,ndir
def GetTObject(name,tfile):
    tobject = tfile.Get(name)
    if tobject == None: raise ValueError("Unable to find %s in %s" % (name,tfile.GetName()))
    return tobject
def IsGlobal(variable,tfile):
    return tfile.GetListOfKeys().Contains(variable)
def IsNhisto(variable,tfile):
    dirname,ndir = GetDirname(variable)
    tdir = tfile.GetDirectory(dirname)
    if tdir == None: return False
    isNhisto = tdir.GetListOfKeys().Contains(variable)
    # tdir.Close()
    return isNhisto
def IsBranch(variable,tfile):
    dirname,ndir = GetDirname(variable,sub='trees')
    tdir = tfile.GetDirectory(dirname)
    if tdir == None: return False
    b_variable = variable.replace('_%s' % ndir,'')
    tree = tdir.Get('norm')
    isBranch = tree.GetListOfBranches().Contains(b_variable)
    # tdir.Close()
    return isBranch
def GetBranch(b_template,b_name,b_variable,tree,weight,cut):
    histo = b_template.Clone(b_name); histo.Reset()
    if not tree.GetListOfBranches().Contains(weight): weight = 'weight'
    if cut == '': tree.Draw('%s>>%s' % (b_variable,b_name),weight,'goff')
    else:         tree.Draw('%s>>%s' % (b_variable,b_name),'%s*(%s%s)' % (weight,b_variable,cut),'goff')
    return histo
def GetNuisanceList(tfile,dirname):
    tdir = tfile.GetDirectory(dirname)
    shapelist = [ key.GetName().replace('Up','') for key in tdir.GetListOfKeys() if 'Up' in key.GetName() ]
    tree = tdir.Get('norm')
    scalelist = [ key.GetName().replace('Up','') for key in tree.GetListOfBranches() if 'Up' in key.GetName() ]
    nuisances = {}
    for shape in shapelist: nuisances[shape] = {type:'shape'}
    for scale in scalelist: nuisances[scale] = {type:'scale'}
    nuisances['Stat'] = True
    return nuisances
class Nuisance(object):
    def __init__(self,name,up,dn,norm=None):
        self.name = name
        self.up,self.dn = up,dn
        if norm is None: return
        nbins = norm.GetNbinsX()
        for ibin in range(1,nbins+1):
            diffUp = norm[ibin] - up[ibin]; diffDn = norm[ibin] - dn[ibin]
            self.up[ibin] = abs(max(diffUp,diffDn))
            self.dn[ibin] = abs(min(diffUp,diffDn))
    def Integral(self,norm):
        nbins = norm.GetNbinsX()
        intUp = sum( norm[ibin] + self.up[ibin] for ibin in range(1,nbins+1) )
        intDn = sum( norm[ibin] - self.dn[ibin] for ibin in range(1,nbins+1) )
        return intUp,intDn
    def GetHistos(self,norm):
        up = self.up.Clone(); dn = self.dn.Clone()
        nbins = norm.GetNbinsX()
        for ibin in range(1,nbins+1):
            up[ibin] = norm[ibin] + self.up[ibin]
            dn[ibin] = norm[ibin] - self.dn[ibin]
        return up,dn
class SubProcess(object):
    def __init__(self,name,filename,tfile,xsec):
        self.name = name
        self.filename = filename
        self.tfile = tfile
        self.xsec = xsec
        # self.tdir = None
        self.dirname = None
        self.nuisances = {}
        self.tree = None
        self.cutflow = 0
        self.init()
    def init(self):
        self.nuisances = {}
        self.histo = None
        self.raw_total = 0
        self.scaled_total = 0
    def getCutflow(self):
        cutflow = GetTObject("h_cutflow",self.tfile)
        cutflow = cutflow.GetBinContent(1)
        self.cutflow = cutflow
    def getGlobal(self,variable):
        self.histo = GetTObject(variable,self.tfile)
    def setDir(self,dirname):
        # if self.tdir != None: self.tdir.Close()
        # self.tdir = self.tfile.Get(dirname)
        self.dirname = dirname
    def setTree(self,treename):
        if self.tree is None or treename != self.tree.GetName():
            self.tree = GetTObject('%s/%s' % (self.dirname,treename),self.tfile)
    def getNhisto(self,variable):
        self.tfile.cd()
        self.b_variable = variable
        hs = GetTObject('%s/%s' % (self.dirname,variable),self.tfile).Clone('%s_%s' % (variable,self.filename))
        self.histo = hs
    def getBranch(self,b_template,b_variable,treename,weight,cut):
        self.tfile.cd()
        self.setTree(treename)
        self.b_variable = b_variable
        if self.tree.GetName() == "norm": self.nuisances = GetNuisanceList(self.tfile,self.dirname)
        self.histo = GetBranch(b_template,'%s_%s' % (b_variable,self.filename),b_variable,self.tree,weight,cut)
        if 'post' in dir(b_template): b_template.post(self.histo)
    def fillRaw(self):
        self.raw_total = self.histo.Integral()
        return self.raw_total != 0
    def scale(self,lumi):
        #Scaling = (1/TotalEvents)*Luminosity*NNLO-cross-section
        self.scaling = (1./self.cutflow) * self.xsec * lumi
        self.histo.Scale(self.scaling)
        self.scaled_total = self.histo.Integral()
        self.addStat()
    def addStat(self):
        self.tfile.cd()
        up = self.histo.Clone('%s_%s_StatUp' % (self.b_variable,self.filename)); up.Reset()
        dn = self.histo.Clone('%s_%s_StatDn' % (self.b_variable,self.filename)); dn.Reset()
        nbins = self.histo.GetNbinsX()
        for ibin in range(1,nbins+1):
            up[ibin] = self.histo.GetBinError(ibin)
            dn[ibin] = self.histo.GetBinError(ibin)
        self.nuisances['Stat'] = Nuisance('Stat',up,dn)
    def addUnc(self,nuisance,b_template,b_variable,cut):
        if nuisance not in self.nuisances:
            up = self.histo.Clone('%s_%s_%sUp'% (b_variable,self.filename,nuisance) )
            dn = self.histo.Clone('%s_%s_%sDown'% (b_variable,self.filename,nuisance) )
            self.nuisances[nuisance] = Nuisance(nuisance,up,dn,self.histo)
            return
        if type(self.nuisances[nuisance]) == Nuisance: return
        info = self.nuisances[nuisance]
        isScale = info[type] == 'scale'
        self.tfile.cd()
        tmpmap = {}
        for variation in ('Up','Down'):
            b_name = '%s_%s_%s%s' % (b_variable,self.filename,nuisance,variation)
            if isScale:
                self.setTree('norm')
                hs_unc = GetBranch(b_template,b_name,b_variable,self.tree,nuisance+variation,cut)
            else:
                self.setTree(nuisance+variation)
                hs_unc = GetBranch(b_template,b_name,b_variable,self.tree,'weight',cut)
            hs_unc.Scale(self.scaling)
            tmpmap[variation] = hs_unc
        self.nuisances[nuisance] = Nuisance(nuisance,tmpmap['Up'],tmpmap['Down'],self.histo)
class Process(object):
    def __init__(self,name,filenames,xsecs,proctype,leg=None,lumi=1,color=None):
        ValidProctype(proctype)
        self.name = name
        self.leg = leg
        if self.leg is None: self.leg = self.name
        self.filenames = [ filename for filename in filenames ]
        self.xsecs = xsecs
        self.proctype = proctype
        
        self.lumi = lumi

        self.color = color

        self.variable = None
        self.dirname = None
        self.ndir = None
        self.b_template = None
        self.b_variable = None
        
        self.subprocesses = {}
        self.nuisances = {}
        
        self.histo = None
        self.raw_total = 0
        self.scaled_total = 0

        self.isGlobal = False
        self.isNhisto = False
        self.isBranch = False
        self.isOpen = False
    def __len__(self): return len(self.filenames)
    def __getitem__(self,i):
        f = self.filenames[i]
        return self.subprocesses[f]
    def __iter__(self):
        for i in range( len(self) ):
            yield self[i]
    def open(self):
        self.isOpen = True
        filelist = [ file for file in self.filenames ]
        for filename in filelist:
            fname = filename + '.root'
            name = filename.replace('post','')
            if not os.path.isfile(fname): print 'No file %s, skipping...' % fname; self.filenames.remove(filename); continue
            tfile = TFile.Open(fname)
            if self.proctype != 'data': xsec = self.xsecs[filename]
            else:                  xsec = None
            subprocess = SubProcess(name,filename,tfile,xsec)
            self.subprocesses[filename] = subprocess
    def getCutflow(self):
        for subprocess in self: subprocess.getCutflow()
    def getGlobal(self,variable):
        self.isGlobal = True
        self.variable = variable
        for subprocess in self: subprocess.getGlobal(self.variable)
    def setDir(self,dirname,ndir):
        self.dirname = dirname
        self.ndir = ndir
        for subprocess in self: subprocess.setDir(dirname)
    def getNhisto(self,variable):
        self.isNhisto = True
        dirname,ndir = GetDirname(variable)
        if self.dirname != dirname:
            self.setDir(dirname,ndir)
            self.variable = variable
        for subprocess in self: subprocess.getNhisto(variable)
    def getFileTemplate(self,variable):
        tfile = iter(self).next().tfile
        dirname,_ = GetDirname(variable)
        tdir = tfile.Get(dirname)
        self.b_template = tdir.Get(variable).Clone('%s_%s_temp' % (self.name,variable))
    def getBranch(self,variable,b_template,cut):
        self.isBranch = True
        if b_template == None: self.getFileTemplate(variable);
        elif self.b_template != b_template: self.b_template = b_template
        self.cut = cut
        
        dirname,ndir = GetDirname(variable,sub='trees')
        if self.dirname != dirname:
            self.setDir(dirname,ndir)
            self.variable = variable
        self.b_variable = variable.replace('_%s' % ndir,'')
        for subprocess in self:
            subprocess.getBranch(self.b_template,self.b_variable,'norm','weight',cut)
            self.nuisances.update( subprocess.nuisances )
    def fillRaw(self):
        self.raw_total = 0
        for subprocess in self:
            subprocess.fillRaw()
            self.raw_total += subprocess.raw_total
    def scale(self):
        if self.proctype == 'data': return
        self.scaled_total = 0
        for subprocess in self:
            subprocess.scale(self.lumi)
            self.scaled_total += subprocess.scaled_total
    def combine(self):
        self.histo = iter(self).next().histo.Clone('%s_%s' % (self.variable,self.name))
        self.histo.Reset()
        for subprocess in self: self.histo.Add(subprocess.histo)
    def initVariable(self):
        if not self.isOpen:
            self.open()
            self.getCutflow()

        for subprocess in self: subprocess.init()

        self.b_template = None
        self.histo = None
        self.raw_total = 0
        self.scaled_total = 0
        self.nuisances = {}
        
        self.isGlobal = False
        self.isNhisto = False
        self.isBranch = False
    def getVariable(self,variable,b_template,cut):
        self.initVariable()
        tfile = iter(self).next().tfile
        if IsGlobal(variable,tfile):   self.getGlobal(variable)
        elif IsBranch(variable,tfile): self.getBranch(variable,b_template,cut)
        elif IsNhisto(variable,tfile): self.getNhisto(variable)
        self.fillRaw()
        self.scale()
        if self.proctype != 'signal': self.combine()
    def addUnc(self,nuisance,show=False):
        if not self.isBranch: return
        if nuisance not in self.nuisances:
            self.nuisances[nuisance] = {}
        for subprocess in self: subprocess.addUnc(nuisance,self.b_template,self.b_variable,self.cut)
        if self.proctype == 'signal': return
        nbins = self.histo.GetNbinsX()
        up = self.histo.Clone('%s_%s_%sUp' % (self.b_variable,self.name,nuisance))
        dn = self.histo.Clone('%s_%s_%sDown' % (self.b_variable,self.name,nuisance))
        for ibin in range(1,nbins+1):
            up[ibin] = TMath.Sqrt( sum( subprocess.nuisances[nuisance].up[ibin]**2 for subprocess in self ) )
            dn[ibin] = TMath.Sqrt( sum( subprocess.nuisances[nuisance].dn[ibin]**2 for subprocess in self ) )
        self.nuisances[nuisance] = Nuisance(nuisance,up,dn)
        if not show or self.scaled_total == 0: return
        intUp,intDn = self.nuisances[nuisance].Integral(self.histo)
	varup = intUp/self.scaled_total
        vardn = intDn/self.scaled_total
        print '{0:<20}'.format('%s %s' % (nuisance,self.name))+'+%f/-%f' % (varup,vardn)
    def removeUnc(self,nuisance):
        if nuisance not in self.nuisances: return
        if self.proctype == 'signal':
            for subprocess in self:
                subprocess.nuisances.pop(nuisance)
        else:
            self.nuisances.pop(nuisance)
    def fullUnc(self,unclist=None,stat=True,show=False):
        if not self.isBranch: return
        if self.proctype != 'bkg': return
        if unclist is None: unclist = self.nuisances.keys()
        if not stat and 'Stat' in unclist: unclist.remove('Stat')
        elif stat: unclist.append('Stat')
        for nuisance in unclist: self.addUnc(nuisance,show=show)
        up = self.b_template.Clone('%s_TotalUp' % self.name);  up.Reset()
        dn = self.b_template.Clone('%s_TotalDown' % self.name); dn.Reset()
        norm = self.histo
        for ibin in range(1,norm.GetNbinsX()+1):
            if norm[ibin] == 0: continue
            up[ibin] = norm[ibin] * TMath.Sqrt( sum( (self.nuisances[nuisance].up[ibin]/norm[ibin])**2 for nuisance in unclist) )
            dn[ibin] = norm[ibin] * TMath.Sqrt( sum( (self.nuisances[nuisance].dn[ibin]/norm[ibin])**2 for nuisance in unclist) )
        self.nuisances['Total'] = Nuisance('Total',up,dn)
    def add(self,other):
        if self.name != other.name: raise ValueError("%s is not %s" % (self.name,other.name))
        # if self.variable != other.variable: raise ValueError("%s is not %s" % (self.variable,other.variable))
        self.histo.Add(other.histo)
        self.raw_total += other.raw_total
        self.scaled_total += self.scaled_total
        # self.subprocess.update(other.subprocesses)
