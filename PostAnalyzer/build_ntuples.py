import os
import sys
import re
def sort_nicely( l ):
    """ Sort the given list in the way that humans expect.
        """
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
    l.sort( key=alphanum_key )
directory = sys.argv[1]

def fullpath(path):
    dirs = []
    def helper(path,dirs):
        if any( fname.endswith('.root') for fname in os.listdir(path) ): dirs.append(path); return
        for dir in os.listdir(path):
            dir_path = os.path.join(path,dir)
            if os.path.isdir(dir_path): helper(dir_path,dirs)
    helper(path,dirs)
    return dirs

def getSub(sub):
    prefix = ''
    if re.search('\w+1Jets',sub): prefix = '1j'
    if re.search('\w+2Jets',sub): prefix = '2j'
    htbinv2 = re.findall('\d+To.*$',sub)
    if any(htbinv2): return prefix+htbinv2[0].replace('To','to')
    htbin = re.findall('\d+-.*$',sub)
    if any(htbin): return prefix+htbin[0].replace('-','to')
    subtype = re.sub('^\w[^_]+_','',sub)
    if any(subtype): return prefix+subtype
    return sub
    
def build_dataset(data,path):
    data = data.lower()
    sublist = os.listdir(path)
    sort_nicely(sublist)
    print data
    with open("ntuples/%s.txt" % data,"w") as f:
        for sub in sublist:
            sub_path = os.path.join(path,sub)
            sub = getSub(sub)
            dirlist = fullpath(sub_path)
            if not any(dirlist): print "Nothing in %s" % sub_path; continue
            print '>>%s' % sub
            f.write(">>%s\n" % sub)
            for directory in dirlist:
                print directory
                f.write("%s/\n" % directory)
            f.write("\n")
    print

for data in os.listdir(directory):
    build_dataset(data,os.path.join(directory,data))
