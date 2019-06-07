import os

#Relevant project directories to keep track of
projects = {
    "2016":{dir:"/nfs_scratch/ekoenig4/MonoZprimeJet/ZprimeTools2016/CMSSW_8_0_26_patch1/src/ZprimeTools2016/PlotTool/"},
    "2017":{dir:"/nfs_scratch/ekoenig4/MonoZprimeJet/ZprimeTools2017/CMSSW_10_2_10/src/ZprimeTools2017/PlotTool/"},
    "2018":{dir:"/nfs_scratch/ekoenig4/MonoZprimeJet/ZprimeTools2018/CMSSW_10_2_10/src/ZprimeTools2018/PlotTool/"}
}

#Files to be ignored in all projects
independents = [
    "mcinfo.py"
]

#Get the relevant files from each year
#Ignore all .pyc files
#Ignore all files that are in the independent list
for year in projects:
    files = [{str:f,id:os.path.getmtime(projects[year][dir]+"/"+f)}
             for f in os.listdir(projects[year][dir])
             if f not in independents and '.pyc' not in f and '~' != f[-1]]
    projects[year][file] = files

#Hold the files to copy over to the specific project
update = { year:{} for year in projects }

#Checks through all files being considered for update and chooses the most up to date one
def check(update,year,f):
    for y in update:
        if y == year: continue
        tmp = [g for g in update[y] if g[str] == f[str]]
        if not any(tmp): update[year].append(f)
        else:
            g = tmp[0]
            if f[id] == g[id]: continue
            elif f[id] > g[id]:
                update[year].append(f)
                update[y].remove(g)
            

#Loop through all the projects and get the files that need to be updated
for year in projects:
    for f in projects[year][file]:
        for y in projects:
            if y == year: continue
            if year not in update[y]: update[y][year] = []
            tmp = [g for g in projects[y][file] if g[str] == f[str]]
            if not any(tmp): check(update[y],year,f)
            else:
                g = tmp[0]
                if f[id] == g[id]: continue
                elif f[id] > g[id]: check(update[y],year,f)

#Map all files to their filenames
for year in update:
    for y in update[year]:
        update[year][y] = [f[str] for f in update[year][y]]

#Update all projects as necessary
for year in update:
    print "Updating:",year
    for y in update[year]:
        print "\tFrom:",y
        for file in update[year][y]:
            print "\t\tFile:",file
            os.system("cp "+projects[y][dir]+file+" "+projects[year][dir]+file)
