# Example script for using ParseDig class to extract curves and their points from Engauge DIG file. This
# script can be converted to other uses by replacing the local print statements with new code to export
# to a new format
#
# Requirements:
# 1) python3 (versus python2)
# 2) numpy
# 3) DefaultListOrderedDict.py from the Engauge scripts directory
# 4) ParseDig.py from the Engauge scripts directory

from ParseDig import ParseDig
import sys

if len(sys.argv) < 2:
    print ("Usage: python3 ExampleParseDig.py <dig file>")
else:
    parseDig = ParseDig (sys.argv [1])
    curveNames = parseDig.curveNames()
    print ("Curve names = ", curveNames, "\n")
    for curveName in curveNames:
        curve = parseDig.curve (curveName)
        print ("Curve ", "'" + curveName + "'", " = ", curve, "\n");
