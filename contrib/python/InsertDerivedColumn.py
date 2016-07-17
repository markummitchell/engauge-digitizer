#!/usr/bin/python
#
# Usage - python insert_derived_column.py <csv file>
# Purpose - This script reads in a table of (longitude,latitude) data points, and then
#           outputs a set of evenly spaced waypoints through those points assuming a constant
#           velocity (variable velocityMps)
# Installation requirements - 1) sudo apt-get install python
#                             2) sudo apt-get install python-dev (or python-devel)
#                             3) sudo pip install numpy

from datetime import datetime, timedelta
import fileinput
import math
import numpy as np

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False
 
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        return False

def readFieldsWithCommas(line):
    return line.replace ("\n", "").split (",")

def xyzFromLatLonAlt (latLonAlt):
    rearth = 6378160
    pi = 3.1415926535
    radians2degrees = pi / 180.0
    lat = latLonAlt [0] * radians2degrees
    lon = latLonAlt [1] * radians2degrees
    radius = rearth + latLonAlt [2]
    x = radius * math.cos (lat) * math.cos (lon)
    y = radius * math.cos (lat) * math.sin (lon)
    z = radius * math.sin (lat)
    return np.array ([x, y, z])

# User inputs
altitudeM = 5000
velocityMps = 69 # 69 m/s = 250 km/hr
curDateTime = datetime (2015, 1, 1, 0, 0, 0)

# Loop through input file lines
isFirst = True
xyzLast = np.array ([0, 0, 0])
for line in fileinput.input():
    fields = readFieldsWithCommas (line)

    # Skip header which does not have numeric fields
    if is_number (fields [0]) and is_number (fields [1]):

        # Convert latitude and longitude to cartesian x,y,z coordinates
        lat = float (fields [1])
        lon = float (fields [0])

        latLonAlt = np.array ([lat,
                               lon,
                               altitudeM])
        xyz = xyzFromLatLonAlt (latLonAlt)
        xyzDeltaMag = 0
        if isFirst:
            isFirst = False
        else:
            xyzDelta = np.subtract (xyz, xyzLast)
            xyzDeltaMag = np.linalg.norm (xyzDelta)

            # Output
            timestamp = curDateTime.strftime ('"%j %Y %H:%M:%S.%f"')
            fields.insert (0, timestamp)

            # Use one of the following lines. The first is for python2, and the second is for python3
            print ', '.join (str (x) for x in fields)
            #print (', '.join (str (x) for x in fields))

        # Update for next iteration
        timeTraveledS = xyzDeltaMag / velocityMps
        curDateTime = curDateTime + timedelta(seconds = timeTraveledS)
        xyzLast = xyz

