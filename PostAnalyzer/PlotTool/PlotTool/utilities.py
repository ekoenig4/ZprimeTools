import os
import sys

def valid_directory(directory):
    if not os.path.isdir(directory): raise ValueError("%s is not a valid directory" % directory)
    return directory

def GetRegion():
    region_pattern = ["postMETdata","postSingleEle","postSingleMu","postDoubleEle_","postDoubleMu"]
    RegionName = ["SignalRegion","SingleEleCR","SingleMuCR","DoubleEleCR","DoubleMuCR"]

    found = False
    for region,pattern in zip(RegionName,region_pattern):
        if os.path.isdir('.output/'):
            if any( pattern in fname for fname in os.listdir('.output/') ): found = True; break
        if any( pattern in fname for fname in os.listdir('.') ): found = True; break
    if not found: return None
    return region
def GetMCxsec(filenames,xsecMap):
    return { fname:xsecMap[fname] for fname in filenames }

def IsSignal(signal):
    return 'Mx' in signal and '_Mv' in signal

def FindConfig():
    wd,wf = os.path.split(__file__)
    def updirectory(path): path += '/../'; return path
    repo_path = os.path.realpath( updirectory(wd) )
    def helper(path):
        if any( directory == 'config' for directory in os.listdir(path) ): return os.path.realpath(path)
        elif os.path.realpath(path) != repo_path: return helper( updirectory(path) )
    config_path = helper('.')
    if config_path == None: print 'year config directory was not found in current or parent directory'; exit(1)
    else: sys.path.append(config_path)
