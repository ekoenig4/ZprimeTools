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
def GetBranch(b_template,b_variable,tree,weight,cut):
    b_template.Reset()
    b_name = 'template_%s_%s_%s' % (b_variable,tree.GetName(),weight)
    histo = b_template.Clone(b_name)
    histo.SetDirectory(gDirectory)
    if not tree.GetListOfBranches().Contains(weight): weight = 'weight'
    if cut == '': tree.Draw('%s>>%s' % (b_variable,b_name),weight,'goff')
    else:         tree.Draw('%s>>%s' % (b_variable,b_name),'%s*(%s%s)' % (weight,b_variable,cut),'goff')
    histo.SetDirectory(0)
    return histo
def GetNuisanceList(tfile,dirname):
    return {}
    tdir = tfile.GetDirectory(dirname)
    shapelist = [ key.GetName().replace('Up','') for key in tdir.GetListOfKeys() if 'Up' in key.GetName() ]
    tree = tdir.Get('norm')
    scalelist = [ key.GetName().replace('Up','') for key in tree.GetListOfBranches() if 'Up' in key.GetName() ]
    nuisances = {}
    for shape in shapelist: nuisances[shape] = {type:'shape'}
    for scale in scalelist: nuisances[scale] = {type:'scale'}
    return nuisances
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
        hs = GetTObject('%s/%s' % (self.dirname,variable),self.tfile).Clone('%s_%s' % (variable,self.filename))
        hs.SetDirectory(0)
        self.histo = hs
    def getBranch(self,b_template,b_variable,treename,weight,cut):
        self.tfile.cd()
        self.setTree(treename)
        if self.tree.GetName() == "norm": self.nuisances = GetNuisanceList(self.tfile,self.dirname)
        self.histo = GetBranch(b_template,b_variable,self.tree,weight,cut)
        self.histo.SetName('%s_%s' % (b_variable,self.filename))
        if 'post' in dir(b_template): b_template.post(self.histo)
    def fillRaw(self):
        self.raw_total = self.histo.Integral()
        return self.raw_total != 0
    def scale(self,lumi):
        #Scaling = (1/TotalEvents)*Luminosity*NNLO-cross-section
        self.scaling = (1./self.cutflow) * self.xsec * lumi
        self.histo.Scale(self.scaling)
        self.scaled_total = self.histo.Integral()
    def addUnc(self,nuisance,b_template,b_variable,cut):
        if nuisance not in self.nuisances:
            self.nuisances[nuisance] = {'Up':self.histo,'Down':self.histo}
            return
        info = self.nuisances[nuisance]
        isScale = info[type] == 'scale'
        self.tfile.cd()
        for variation in ('Up','Down'):
            if isScale:
                self.setTree('norm')
                hs_unc = GetBranch(b_template,b_variable,self.tree,nuisance+variation,cut)
            else:
                self.setTree(nuisance+variation)
                hs_unc = GetBranch(b_template,b_variable,self.tree,'weight',cut)
            hs_unc.SetName('%s_%s_%s%s' % (b_variable,self.filename,nuisance,variation))
            hs_unc.Scale(self.scaling)
            info[variation] = hs_unc
class Process(object):
    def __init__(self,name,filenames,xsecs,proctype,lumi=1,color = None):
        ValidProctype(proctype)
        self.name = name
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
        if 'jetPt' in variable:    variable = variable.replace('jetPt','j1pT')
        if 'recoil' in variable: variable = variable.replace('recoil','pfMET')
        self.b_template = tdir.Get(variable)
    def getBranch(self,variable,b_template,cut):
        self.isBranch = True
        if b_template == None: self.getFileTemplate(variable);
        else: self.b_template = b_template
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
    def addUnc(self,nuisance):
        if not self.isBranch: return
        if nuisance not in self.nuisances:
            self.nuisances[nuisance] = {}
        for subprocess in self: subprocess.addUnc(nuisance,self.b_template,self.b_variable,self.cut)
        if self.proctype == 'signal': return
        for variation in ('Up','Down'):
            histo = self.b_template.Clone('%s_%s%s' % (self.name,nuisance,variation))
            histo.Reset()
            for subprocess in self:
                histo.Add(subprocess.nuisances[nuisance][variation])
                subprocess.nuisances[nuisance].pop(variation)
            histo.SetDirectory(0)
            self.nuisances[nuisance][variation] = histo
    def removeUnc(self,nuisance):
        if nuisance not in self.nuisances: return
        if self.proctype == 'signal':
            for subprocess in self:
                subprocess.nuisances[nuisance].pop('Up')
                subprocess.nuisances[nuisance].pop('Down')
        else:
            self.nuisances[nuisance].pop('Up')
            self.nuisances[nuisance].pop('Down')
