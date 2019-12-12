from ROOT import *
import os
from utilities import GetDirname
from changeBinning import b_info

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
def GetTObject(name,tfile):
    tobject = tfile.Get(name)
    if tobject == None: raise ValueError("Unable to find %s in %s" % (name,tfile.GetName()))
    return tobject
def GetBranch(name,b_template,b_variable,tree,weight,cut):
    histo = b_template.Clone(name); histo.Reset()
    if cut == None: tree.Draw("%s>>%s" % (b_variable,name),weight,'goff')
    else:         tree.Draw("%s>>%s" % (b_variable,name),'%s*(%s)' % (weight,cut),'goff')
    return histo
def HistoEqual(hs1,hs2):
    if hs1 == hs2: return True
    if hs1 is None: return True
    if hs2 is None: return False
    xarray1 = list(hs1.GetXaxis().GetXbins())
    xmin1,xmax1 = hs1.GetXaxis().GetXmin(),hs1.GetXaxis().GetXmax()
    xarray2 = list(hs2.GetXaxis().GetXbins())
    xmin2,xmax2 = hs2.GetXaxis().GetXmin(),hs2.GetXaxis().GetXmax()
    if len(xarray1) != len(xarray2): return False
    if xmin1 != xmin2 or xmax1 != xmax2: return False
    return not any( width1 != width2 for width1,width2 in zip(xarray1,xarray2) )
def GetFileTemplate(tfile,variable):
    dirname,ndir = GetDirname(variable)
    b_variable = variable.replace('_%s' % ndir,'')
    template = tfile.Get('%s/%s' % (dirname,variable)).Clone(b_variable)
    template.Reset()
    return template

class SubProcess(object):
    def __init__(self,name,fname,xsec,year=None,region=None):
        self.process = name; self.name = name; self.year = year; self.region = region
        if region is not None: self.name = "%s_%s" % (region,name)
        if year is not None:   self.name = "%s_%s" % (year,name)
        self.tfile = TFile.Open(fname); self.xsec = xsec; self.treemap = {}

        cutflow = GetTObject("h_cutflow",self.tfile)
        self.cutflow = cutflow.GetBinContent(1)
        self.initVariable()
    def initVariable(self):
        self.nuisances = {}
        self.histo = None
        self.raw_total = 0
        self.scaled_total = 0
    def setGlobal(self,variable):
        self.histo = GetTObject(variable,self.tfile)
    def setNhisto(self,variable):
        dirname,ndir = GetDirname(variable)
        self.histo = GetTObject( '%s/%s' % (dirname,variable),self.tfile).Clone('%s_%s' % (self.name,variable))
    def setBranchInfo(self,b_template,cut,variable):
        if cut != b_info.cut: b_info.cut = cut
        if b_template is None and b_info.template is None: b_info.template = GetFileTemplate(self.tfile,variable)
        elif not HistoEqual(b_template,b_info.template): b_info.template = b_template
    def setTree(self,dirname,treename):
        if treename in self.treemap: return
        self.treemap[treename] = GetTObject('%s/%s' % (dirname,treename),self.tfile)
    def setBranch(self,b_template,variable,treename,weight,cut):
        self.setBranchInfo(b_template,cut,variable)
        dirname,ndir = GetDirname(variable)
        b_template = b_info.template
        b_variable = b_template.GetName()
        self.setTree(dirname,treename)
        self.histo = GetBranch('%s_%s' % (self.name,b_variable),b_template,b_variable,self.treemap[treename],weight,cut)
        if hasattr(b_info,'post'): b_info.post(self.histo)
    def fillRaw(self):
        self.raw_total = self.histo.Integral()
        return self.raw_total != 0
    def scale(self,histo=None,lumi=None):
        #scaling = Luminosity * NNLO-cross-section / Total-Events
        if histo is None:
            histo = self.histo
            self.scaleWidth = any( "%.3f" % histo.GetBinWidth(ibin) != "%.3f" % histo.GetBinWidth(ibin+1) for ibin in range(1,histo.GetNbinsX()) )
            self.lumi = lumi
            if self.xsec is None: self.scaling = 1
            else:                 self.scaling = lumi * self.xsec / self.cutflow
        if self.scaleWidth:     histo.Scale(self.scaling,"width")
        elif self.scaling != 1: histo.Scale(self.scaling)
        if histo == self.histo: self.scaled_total = histo.Integral()
    def addUnc(self,nuisance):
        if nuisance not in self.nuisance: return
        if type(self.nuisances[nuisance] == Nuisance): return
        b_template = b_info.template
        b_variable = b_template.GetName()
        cut = b_info.cut
        isScale = self.nuisances[nuisance] == 'scale'
        name = '%s_%s_%s' % (self.name,b_variable,nuisance)
        if isScale:
            treename = 'trees/norm'
            self.setTree(treename)
            up = GetBranch('%sUp' % name,b_tempalate,b_variable,self.treemap[treename],'%sUp' % nuisance,cut)
            dn = GetBranch('%sDown' % name,b_tempalate,b_variable,self.treemap[treename],'%sDown' % nuisance,cut)
        else:
            treeup = 'trees/%sUp' % nuisance; self.setTree(treeup)
            treedn = 'trees/%sDown' % nuisance; self.setTree(treedn)
            up = GetBranch('%sUp' % name,b_template,b_variable,self.treemap[treeup],'weight',cut)
            dn = GetBranch('%sDown' % name,b_template,b_variable,self.treemap[treeup],'weight',cut)
        self.scale(up); self.scale(dn)
        self.nuisances[nuisance] = Nuisance(nuisance,up,dn,self.histo,type="abs")
    def addStat(self):
        b_variable = b_info.b_variable
        up = self.histo.clone('%s_%s_StatUp' % (self.name,b_variable)); up.Reset()
        dn = self.histo.clone('%s_%s_StatDown' % (self.name,b_variable)); up.Reset()
        nbins = self.histo.GetNbinsX()
        for ibin in range(1,nbins+1):
            up[ibin] = self.histo.GetBinError(ibin)
            dn[ibin] = self.histo.GetBinError(ibin)
        self.nuisances["Stat"] = Nuisance("Stat",up,dn,self.histo)

class Process(object):
    isGlobal = False
    isNhisto = False
    isBranch = False
    def __init__(self,name,filenames,xsecs,proctype,year=None,region=None,leg=None,lumi=1,color=kGray+1):
        self.process = name; self.name = name; self.year = year; self.region = region
        if region is not None: self.name = "%s_%s" % (region,name)
        if year is not None:   self.name = "%s_%s" % (year,name)
        self.filenames = [ filename for filename in filenames ]; self.xsecs = xsecs; self.proctype = proctype
        self.leg = leg; self.lumi = lumi; self.color = color

        self.open()
    def __len__(self): return len(self.filenames)
    def __getitem__(self,i):
        f = self.filenames[i]
        return self.subprocesses[f];
    def __iter__(self):
        for i in range(len(self)): yield self[i]
    def open(self):
        self.subprocesses = {}; self.nuisances = {}
        filelist = list(self.filenames)
        for filename in filelist:
            fname = filename + '.root'
            name = filename.replace('post','')
            if self.proctype == 'data': xsec = None
            else: xsec = self.xsecs[filename]
            if not os.path.isfile(fname): print "No file %s, skipping" % fname; self.filenames.remove(filename); continue
            self.subprocesses[filename] = SubProcess(name,fname,xsec,self.year,self.region)
    def initVariable(self):
        for subprocess in self: subprocess.initVariable()
        self.histo = None
        self.raw_total = 0
        self.scaled_total = 0
        self.nuisances = {}

        Process.isGlobal = False
        Process.isNhisto = False
        Process.isBranch = False
    def setGlobal(self,variable):
        Process.isGlobal = True
        for subprocess in self: subprocess.setGlobal(variable)
    def setNhisto(self,variable):
        Process.isNhisto = True
        for subprocess in self: subprocess.setNhisto(variable)
    def setBranchInfo(self,b_template,cut):
        if cut != b_info.cut: b_info.cut = cut
        if not HistoEqual(b_template,b_info.template): b_info.template = b_template
    def setBranch(self,variable,b_template,cut):
        Process.isBranch = True
        self.setBranchInfo(b_template,cut)
        b_template = b_info.template
        cut = b_info.cut
        for subprocess in self: subprocess.setBranch(b_template,variable,'trees/norm','weight',cut)
    def fillRaw(self):
        self.raw_total = 0
        for subprocess in self:
            subprocess.fillRaw()
            self.raw_total += subprocess.raw_total
    def scale(self):
        self.scaled_total = 0
        for subprocess in self:
            subprocess.scale(lumi=self.lumi)
            self.scaleWidth = subprocess.scaleWidth
            self.scaled_total += subprocess.scaled_total
    def setVariable(self,variable,b_template=None,cut=None):
        self.initVariable()
        tfile = iter(self).next().tfile
        if IsGlobal(variable,tfile): self.setGlobal(variable)
        elif IsBranch(variable,tfile): self.setBranch(variable,b_template,cut)
        elif IsNhisto(variable,tfile): self.setNhisto(variable)
        self.fillRaw()
        self.scale()
        if self.proctype == 'signal': return
        self.histo = None
        for subprocess in self:
            if self.histo is None: self.histo = subprocess.histo.Clone('%s_%s' % (self.name,variable))
            else:                  self.histo.Add(subprocess.histo)
    def addUnc(self,nuisance):
        if not Process.isBranch: return
        for subprocess in self: subprocess.addUnc(nuisance)
        if self.proctype == 'signal': return
        b_template = b_info.b_tempalte
        b_variable = b_template.GetName()
        cut = b_info.cut
        nbins = self.histo.GetNbinsX()
        up = self.histo.Clone("%s_%s_%sUp" % (self.name,b_variable,nuisance))
        dn = self.histo.Clone("%s_%s_%sDown" % (self.name,b_variable,nuisance))
        for ibin in range(1,nbins+1):
            up[ibin] = TMath.Sqrt( sum( subprocess.nuisances[nuisance].up[ibin]**2 for subprocess in self ) )
            dn[ibin] = TMath.Sqrt( sum( subprocess.nuisances[nuisance].dn[ibin]**2 for subprocess in self ) )
        self.nuisances[nuisance] = Nuisance(nuisance,up,dn,self.histo)
    def addStat(self):
        b_template = b_info.b_tempalte
        b_variable = b_template.GetName()
        up = self.histo.Clone('%s_%s_StatUp' % (self.name,b_variable)); up.Reset()
        dn = self.histo.Clone('%s_%s_StatDown' % (self.name,b_variable)); dn.Reset()
        nbins = self.histo.GetNbinsX()
        for ibin in range(1,nbins+1):
            up[ibin] = self.histo.GetBinError(ibin)
            dn[ibin] = self.histo.GetBinError(ibin)
        self.nuisances["Stat"] = Nuisance("Stat",up,dn,self.histo)
    def fullUnc(self,unclist=None,stat=False):
        if not self.isBranch: return
        if self.proctype != 'bkg': return
        
        if unclist is None: unclist = self.nuisances.keys()
        if not stat and 'Stat' in unclist: unclist.remove('Stat')
        elif stat: unclist.append('Stat')

        for nuisance in unclist: self.addUnc(nuisance)
        b_template = b_info.b_tempalte
        b_variable = b_template.GetName()
        up = self.histo.Clone('%s_%s_TotalUp' % (self.name,b_variable));  up.Reset()
        dn = self.histo.Clone('%s_%s_TotalDown' % (self.name,b_variable)); dn.Reset()
        for ibin in range(1,nbins+1):
            if self.histo[ibin] == 0: continue
            up[ibin] = self.histo[ibin] * TMath.Sqrt( sum( (self.nuisances[nuisance].up[ibin]/self.histo[ibin])**2 for nuisance in unclist) )
            dn[ibin] = self.histo[ibin] * TMath.Sqrt( sum( (self.nuisances[nuisance].dn[ibin]/self.histo[ibin])**2 for nuisance in unclist) )
        self.nuisances['Total'] = Nuisance('Total',up,dn,self.histo)
    def add(self,other):
        if self.process != other.process: raise ValueError("%s is not %s" % (self.process,other.process))
        if self.histo is None: self.histo = other.histo.Clone(self.name)
        else: self.histo.Add(other.histo)
        self.raw_total += other.raw_total
        self.scaled_total += other.scaled_total
        for nuisance in other.nuisances:
            if nuisance not in self.nuisances: self.nuisances[nuisance] = other.nuisances[nuisance]
            else: self.nuisances[nuisance].add(other.nuisances[nuisance])
