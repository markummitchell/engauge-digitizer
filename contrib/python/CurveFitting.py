# Example script for using ParseDig class to extract curves and their points from Engauge DIG file, and apply
# curve fitting
#
# Requirements:
# 1) python3 (versus python2)
# 2) numpy
# 3) DefaultListOrderedDict.py from the Engauge scripts directory
# 4) ParseDig.py from the Engauge scripts directory

from ParseDig import ParseDig
from numpy import poly1d
from numpy import polyfit

import sys

defaultHighestOrder = 3
if len(sys.argv) < 2:
    print ("Usage: python3 CurveFitting.py <dig file> [<highest order>]")
    print ("where:")
    print ("  <dig file>      Version 6 or newer DIG file")
    print ("  <highest order> Highest order of polynomial to be fit to the data. Default is " + defaultHighestOrder)
    print ("Example: python3 CurveFitting.py samples/CurveFitting.dig")
else:
    parseDig = ParseDig (sys.argv [1])
    highestOrderUser = defaultHighestOrder
    if len(sys.argv) == 3:
        highestOrderUser = int (sys.argv [2])
    curveNames = parseDig.curveNames()
    for curveName in curveNames:

        print ()

        # Show (x,y) points as Nx2 matrix
        curve = parseDig.curve (curveName)

        # Show (x,y) points as 2 vectors
        xVector = [row [0] for row in curve]
        yVector = [row [1] for row in curve]

        # Fit linear and higher order polynomials. Highest order is less than number of points to prevent overfitting
        highestOrderNoOverfit = len (xVector) - 1
        for order in range (0, 1 + min (highestOrderUser, highestOrderNoOverfit)):
            z = polyfit (xVector, yVector, order)
            p = poly1d (z)
            rmsError = 0
            for i in range (0, len (xVector)):
                x = xVector [i]
                y = yVector [i]
                rmsError += (p (x) - y) * (p (x) - y)
            print ("Curve '" + curveName + "' with polynomial fit to order " + str (order) + " has rms error " + str (rmsError))

