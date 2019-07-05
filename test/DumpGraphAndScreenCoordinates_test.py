#!/usr/bin/python3

# Script that outputs the graph and screen coordinates of each point in a DIG file.
# The format is:
# 1) "xGraph yGraph xScreen yScreen" on each line
# 2) Between each field is the export delimiter selected in the DIG file
#
# Requirements:
# 1) python3 (versus python2)
# 2) numpy and pandas
# 3) DefaultListOrderedDict.py from the Engauge scripts directory
# 4) ParseDig.py from the Engauge scripts directory

import faulthandler
import inspect
import numpy as np
import pandas as pd
import subprocess
import sys
import testDigGenerator as TDG

sys.path.insert (0, '../contrib/python')
from ParseDig import ParseDig

def parseDigFile (fileName):
    parseDig = ParseDig (fileName)
    curveNames = parseDig.curveNames ()
    exportDelimiter = parseDig.exportDelimiter ()
    try:
        f = open (fileName[:-4] + 'Parsed.csv', 'w')
    except Exception as e:
        f = open (fileName[:-4] + 'Parsed.csv', 'w+')
    for curveName in curveNames:

        header = ("# {}" . format (curveName))
        f.write (header + exportDelimiter + exportDelimiter + exportDelimiter + '\n')
        curve = parseDig.curve (curveName)

        for row in curve:
            xGraph = row [0]
            yGraph = row [1]
            (xScreen, yScreen) = parseDig.transformGraphToScreen (xGraph, yGraph)
            dataLine = ("{}{}{}{}{}{}{}" . format (xGraph, exportDelimiter,
                                                   yGraph, exportDelimiter,
                                                   xScreen, exportDelimiter,
                                                   yScreen))
            f.write(dataLine + '\n')
    f.close()
    return pd.read_csv(fileName[:-4] + 'Parsed.csv')

def showResults (result, testName):
    GREEN = '\033[32m'
    RED = '\033[31m'
    ENDCOLOR = '\033[0m'
    passFail = (GREEN + "PASS" + ENDCOLOR) if result else (RED + "FAIL" + ENDCOLOR)
    print ('{}   : {}' . format (passFail, testName))
    
def TestFourAxesInfiniteSlope ():
    xScreen = [45, 587, 45, 45]
    yScreen = [171, 171, 15, 327]
    xGraph = [0, 14, 0, 0]
    yGraph = [0, 0, 1.5, -1.5]
    xPoints = 55
    yPoints = 96
    title = '.TestFourAxesInfiniteSlope.dig'
    print ('hello2')    
    TDG.createTestCase(np.array ([xScreen, xGraph]),
                       np.array ([yScreen, yGraph]),
                       xPoints, yPoints,
                       'Linear', 'Linear', title)
    print ('hello3')    
    ParseDig.callEngauge (['-exportonly', title])
    engaugeOutput = pd.read_csv (title [:-3] + 'csv')
    parsedData = np.array (parseDigFile (title).iloc [:, :2])[0]
    testData = np.array (engaugeOutput.iloc [:, :2]) [0]
    print ('hello4')        
    for i in range (len (testData)):
        decimalIndex = str (testData [i]).find ('.')
        decimals = len (str (testData [i])) - decimalIndex - 1
        parsedData[i] = np.round (parsedData [i], decimals)
    print ('hello4')            
    showResults ((parsedData == testData).all(),
                 inspect.stack () [0] [3])
      
def TestInfiniteSlope():
    print ('hello5')                
    xScreen = [45, 587, 45]
    yScreen = [327, 171, 15]
    xGraph = [0, 14, 0]
    yGraph = [-1.5, 0, 1.5]
    xPoints = 55
    yPoints = 96
    title = '.TestInfiniteSlope.dig'
    TDG.createTestCase (np.array ([xScreen, xGraph]), 
                        np.array ([yScreen, yGraph]),
                        xPoints, yPoints,
                        'Linear', 'Linear', title)
    ParseDig.callEngauge (['-exportonly', title])
    engaugeOutput = pd.read_csv (title [:-3] + 'csv')
    parsedData = np.array (parseDigFile (title).iloc [:, :2]) [0]
    testData = np.array (engaugeOutput.iloc [:, :2]) [0]
    for i in range (len (testData)):
        decimalIndex = str (testData[i]).find ('.')
        decimals = len (str (testData [i])) - decimalIndex - 1
        parsedData[i] = np.round (parsedData [i], decimals)
    showResults ((parsedData == testData).all(),
                 inspect.stack () [0] [3])
    print ('hello6')
    
def TestRandomSlope ():
    print ('hello7')                    
    xScreen = [np.random.randint(100, 150), 587, 45]
    yScreen = [327, 171, 15]
    xGraph = [0, 14, 0]
    yGraph = [-1.5, 0, 1.5]
    xPoints = 55
    yPoints = 96
    title = '.TestRandomSlope.dig'
    TDG.createTestCase (np.array ([xScreen, xGraph]),
                        np.array ([yScreen, yGraph]),
                        xPoints, yPoints,
                        'Linear', 'Linear', title)
    ParseDig.callEngauge (['-exportonly', title])
    engaugeOutput = pd.read_csv (title [:-3] + 'csv')
    parsedData = np.array (parseDigFile (title).iloc [:, :2]) [0]
    testData = np.array (engaugeOutput.iloc [:, :2]) [0]
    for i in range (len (testData)):
        decimalIndex = str (testData[i]).find ('.')
        decimals = len(str (testData[i])) - decimalIndex - 1
        parsedData [i] = np.round (parsedData [i], decimals)
    showResults ((parsedData == testData).all(),
                 inspect.stack () [0] [3])
    print ('hello8')
    
print ('hello1')
faulthandler.enable ()    
TestFourAxesInfiniteSlope ()
TestInfiniteSlope ()
TestRandomSlope ()
