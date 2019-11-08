from FWCore.PythonUtilities.LumiList import LumiList

from sys import argv

filename1 = argv[1]
filename2 = argv[2]

originalLumiList1 = LumiList(filename=filename1)
originalLumiList2 = LumiList(filename=filename2)
newLumiList = originalLumiList1 - originalLumiList2
newLumiList.writeJSON('my-diff.json')

#config.Data.lumiMask = 'my_lumi_mask.json'
