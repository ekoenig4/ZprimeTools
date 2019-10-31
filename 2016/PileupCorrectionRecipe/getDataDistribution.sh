# Following https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/613/2/1/1/1.html
json=processedLumisG.json
pileup=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt
bins=75
minBias="69200"
uncert="1.046"

pileupCalc.py \
  -i $json \
  --inputLumiJSON $pileup \
  --calcMode true \
  --minBiasXsec $minBias \
  --maxPileupBin $bins \
  --numPileupBins $bins \
  dataPileup.root

# variations
pileupCalc.py \
  -i $json \
  --inputLumiJSON $pileup \
  --calcMode true \
  --minBiasXsec $(echo "$minBias * $uncert"|bc) \
  --maxPileupBin $bins \
  --numPileupBins $bins \
  dataPileup_minBiasUP.root

pileupCalc.py \
  -i $json \
  --inputLumiJSON $pileup \
  --calcMode true \
  --minBiasXsec $(echo "$minBias * (2-$uncert)"|bc) \
  --maxPileupBin $bins \
  --numPileupBins $bins \
  dataPileup_minBiasDOWN.root
