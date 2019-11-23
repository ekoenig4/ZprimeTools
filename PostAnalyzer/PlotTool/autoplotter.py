#!/usr/bin/env python

from PlotTool import parser
from config import config
import os
from plotter import plotter

parser.add_argument("--nhist",help="specify histograms at basic cut level",nargs="*",default=[])
args = parser.parse_args()
region = os.getcwd().split('/')[-1]+'/'
nhist = config['regions'][region]
variables = args.argv

def getVariable(variable,nhist):
    cut = ''
    if '+' in variable: cut = '+'+variable.split('+')[-1]
    if '-' in variable: cut = '-'+variable.split('-')[-1]
    varname = variable.replace('>','+').replace('<','-')
    variable = variable.replace(cut,'')
    return variable+'_'+nhist+cut.replace('+','>').replace('-','<')
variables += [ getVariable(variable,nhist) for variable in args.nhist ]
plotter(variables)
