#!/usr/bin/env python

from Parser import PlotParser as parser
import Plot
from config import config
import os
from plotter import plotter

parser.add_argument("--nhist",help="specify histograms at basic cut level",nargs="*",default=[])
args = parser.parse_args()
region = os.getcwd().split('/')[-1]+'/'
nhist = config['regions'][region]
variables = args.argv
variables += [ '%s_%s' % (variable,int(nhist)) for variable in args.nhist ]
plotter(variables)
