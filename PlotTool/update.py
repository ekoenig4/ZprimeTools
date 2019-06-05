import os

projects = {
    "2016":{dir:"/nfs_scratch/ekoenig4/MonoZprimeJet/ZprimeTools2016/CMSSW_8_0_26_patch1/src/ZprimeTools2016/PlotTool"},
    "2017":{dir:"/nfs_scratch/ekoenig4/MonoZprimeJet/ZprimeTools2017/CMSSW_10_2_10/src/ZprimeTools2017/PlotTool"},
    "2018":{dir:"/nfs_scratch/ekoenig4/MonoZprimeJet/ZprimeTools2018/CMSSW_10_2_10/src/ZprimeTools2018/PlotTool"}
}

independents = [
    "mcinfo.py"
]

for year in projects:
    files = [{str:f,id:os.path.getmtime(projects[year][dir]+"/"+f)}
             for f in os.listdir(projects[year][dir])
             if f not in independents and '.pyc' not in f and '~' != f[-1]]
    projects[year][file] = files

update = {
    "2016":{},
    "2017":{},
    "2018":{}
}
for year in projects:
    for f in projects[year][file]:
        for y in projects:
            if year not in update[y]: update[y][year] = []
            if y == year: continue
            tmp = [g for g in projects[y][file] if g[str] == f[str]]
            if not any(tmp):update[y][year].append(f[str])
            else:
                g = tmp[0]
                diff = f[id] - g[id]
                if diff == 0: continue
                elif diff > 0: update[y][year].append(f[str])
            

print update
