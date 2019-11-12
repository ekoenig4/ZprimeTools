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
    
def build_dataset(data,path):
    data = data.lower()
    sublist = os.listdir(path)
    sort_nicely(sublist)
    print data
    with open("ntuples/%s.txt" % data,"w") as f:
        for sub in sublist:
            sub_path = os.path.join(path,sub)
            sub = sub.split("_")
            if len(sub) > 1: sub = sub[1]
            else:            sub = sub[0]
            sub = sub.replace("HT","").replace("To","to").replace("-","to").replace("Incl","MLM")
            print '>>%s' % sub
            f.write(">>%s\n" % sub)
            dirlist = fullpath(sub_path)
            for directory in dirlist:
                print directory
                f.write("%s/\n" % directory)
            f.write("\n")
    print

for data in os.listdir(directory): build_dataset(data,os.path.join(directory,data))
