#!/usr/bin/python3

# Script that outputs the graph and screen coordinates of each point in a DIG file.
# The format is:
# 1) "xGraph yGraph xScreen yScreen" on each line
# 2) Between each field is the export delimiter selected in the DIG file
#
# Requirements:
# 1) python3 (versus python2)
# 2) numpy
# 3) DefaultListOrderedDict.py from the Engauge scripts directory
# 4) ParseDig.py from the Engauge scripts directory

import os
from ParseDig import ParseDig
import sys

if len(sys.argv) != 2 or not os.path.exists (sys.argv [1]):
    print ("Usage: python3 DumpGraphAndScreenCoordinates.py <dig file>")
else:
    parseDig = ParseDig (sys.argv [1])
    curveNames = parseDig.curveNames()
    exportDelimiter = parseDig.exportDelimiter()
    for curveName in curveNames:

        print ("# {}" . format (curveName))
        curve = parseDig.curve (curveName)

        for row in curve:
            xGraph = row [0]
            yGraph = row [1]
            (xScreen, yScreen) = row [2], row [3] #parseDig.transformGraphToScreen (xGraph, yGraph)
            print ("{}{}{}{}{}{}{}" . format (xGraph, exportDelimiter,
                                              yGraph, exportDelimiter,
                                              xScreen, exportDelimiter,
                                              yScreen))
