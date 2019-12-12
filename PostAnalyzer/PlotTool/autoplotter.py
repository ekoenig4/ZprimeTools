#!/usr/bin/env python

from PlotTool import parser
import config
import os
from plotter import plotter

parser.add_argument("--nhist",help="specify histograms at basic cut level",nargs="*",default=[])
args = parser.parse_args()
region = os.getcwd().split('/')[-1]
nhist = config.regions[region]
variables = args.argv

def getVariable(variable,nhist):
    return variable+'_'+nhist
variables += [ getVariable(variable,nhist) for variable in args.nhist ]
plotter(variables)
