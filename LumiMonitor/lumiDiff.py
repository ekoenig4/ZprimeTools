from FWCore.DataStructs.LumiList import LumiList

originalLumiList1 = LumiList(filename='Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt')
originalLumiList2 = LumiList(filename='processedLumis_EGdata_D.json')
newLumiList = originalLumiList1 - originalLumiList2
newLumiList.writeJSON('my-diff.json')

#config.Data.lumiMask = 'my_lumi_mask.json'
