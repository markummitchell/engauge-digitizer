from ParseDig import ParseDig
import sys

if len(sys.argv) < 2:
    print ("Usage: python3 ExampleParseDig.py <dig file>")
else:
    parseDig = ParseDig (sys.argv [1])
    curveNames = parseDig.curveNames()
    print ("Curve names = ", curveNames)
    for curveName in curveNames:
        curve = parseDig.curve (curveName)
        print ("Curve ", curveName, " = ", curve);
