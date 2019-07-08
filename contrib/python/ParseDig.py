# This file converts non-xml dig files to xml if required. Directly reading non-xml
# files (=binary) was attempted but the unpredictable length of the QPixMap in the
# middle of the binary data, and use of string (versus bytes) by pyside2 prevented
# that option from succeeding
from xml.etree import ElementTree
from DefaultListOrderedDict import DefaultListOrderedDict
import numpy as np
import os
from signal import SIGSEGV
import subprocess
import sys

class ParseDig:
    def __init__(self, digFile):
        # Hash table of curve name to lists, with each list consisting of graph points 
        # and screen coordinates
        self._curves = DefaultListOrderedDict()

        try:
            with open(digFile, 'rt') as f:
                tree = ElementTree.parse (f)
            self.parseXml (tree)
        except Exception as e:
            digFileUpgraded = self.upgrade (digFile)
            try:
                with open(digFileUpgraded, 'rt') as f:
                    tree = ElementTree.parse (f)
                os.remove (digFileUpgraded)
                self.parseXml (tree)
            except Exception as e:
                print ("Could not load {} even after trying an upgrade" . format (digFile))

    @staticmethod
    def callEngauge (argumentsArray, debug = False):
        # Operating system dependent location of Engauge executable. Some typical values are:
        #  cygwin      /usr/bin/engauge-digitizer.exe
        #  linux       /usr/bin/engauge
        #  osx         /Applications/Engauge\ Digitizer.app/Contents/MacOS/Engauge\ Digitizer
        #  windows     C:/Program Files/Engauge Digitizer/engauge.exe
        envTag = 'ENGAUGE_EXECUTABLE'
        if envTag in os.environ and os.environ [envTag] != '':
            engaugeExecutable = os.environ [envTag]
        else:
            engaugeExecutable = "/usr/bin/engauge"

        if not os.path.exists (engaugeExecutable):

            # Show error message            
            noExeError = '{} {} - {}. {} {} {}.' . format (
                'Could not execute Engauge at',
                engaugeExecutable,
                'Path does not exist',
                'Try setting environment variable',
                envTag,
                'to the executable path')

            print (noExeError)
            sys.exit (0)

        debugArgs = []
        if (debug):
            debugArgs = ['-debug']
        fullArgs = [engaugeExecutable] + debugArgs + argumentsArray

        # Linux has a bug where using shell requires arguments to be joined or else only first is seen. So if shell=True
        # is added then first argument becomes ' '.join (fullArgs)
        p = subprocess.Popen (fullArgs,
                              stdin = subprocess.PIPE,
                              stdout = subprocess.PIPE,
                              stderr = subprocess.PIPE)
        out, err = p.communicate ()
        preturncode = p.returncode
        if preturncode == -SIGSEGV:
            # On Travis engauge segfaults when running engauge with -exportonly, but after high level code has completed
            preturncode = 0
        if preturncode:
            # Dump log file but only, for simplicity, if it exists in the executable directory
            engaugeLogFilename = os.path.dirname (engaugeExecutable) + os.sep + '.engauge.log'
            if os.path.exists (engaugeLogFilename):
                with open (engaugeLogFilename, 'r') as engaugeLogFile:
                    for line in engaugeLogFile:
                        print (line, end='')

            # Show error message
            noExeError = "{} {} - return={}.\nCommand line '{}'\nout='{}'\nerr='{}'\n{}" . format (
                'Error while executing Engauge at',
                engaugeExecutable,
                preturncode,
                fullArgs,
                out.decode ('utf-8'),
                err.decode ('utf-8'),
                'Version 11.3 or newer is required')
            
            print (noExeError)
            sys.exit (0)

    def computeAffineTransformation (self, screen, graphX, graphY, graph1):
        # Compute screen-to-graph affine transformation from screen and graph points in axes
        screenInverse = np.linalg.inv (screen)
        m1 = np.dot (screenInverse, graphX)
        m2 = np.dot (screenInverse, graphY)
        m3 = np.dot (screenInverse, graph1)
        screenToGraph = np.array ([m1.flatten(), m2.flatten(), m3.flatten()])
        return screenToGraph
      
    def curve (self, curveName):
        return list (self._curves [curveName])

    def curveNames (self):
        return list (self._curves.keys ())

    def delimiterEnumToDelimiter (self, delimiterEnum):
        # Mapping ExportDelimiter enum
        switcher = {
            0: ',',
            1: ' ',
            2: '\t',
            3: ';'
            }
        return switcher.get (delimiterEnum, ' ')

    def exportDelimiter (self):
        return self._delimiter

    def getScreenAndGraph(self, node):
        #Get screen and graph coordinates from axis data
        #Allows for three or four axis points
        rowsGraph = 0
        rowsScreen = 0
        screen = np.empty(shape=(3, 3))
        graphX = np.empty(shape=(3, 1))
        graphY = np.empty(shape=(3, 1))
        graph1 = np.ones(3)
        try:
            for nodeAxes in node.iter():
                if (nodeAxes.tag == 'Point'):
                    for nodePoint in nodeAxes.iter():
                        if (nodePoint.tag == 'PositionScreen'):
                            x = float(nodePoint.attrib.get('X'))
                            y = float(nodePoint.attrib.get('Y'))
                            screen[rowsScreen][0] = x
                            screen[rowsScreen][1] = y
                            screen[rowsScreen][2] = 1
                            # print ('Input positionScreenAxes', x, y)
                            rowsScreen += 1
                        elif (nodePoint.tag == 'PositionGraph'):
                            x = float(nodePoint.attrib.get('X'))
                            y = float(nodePoint.attrib.get('Y'))
                            graphX[rowsGraph] = x
                            graphY[rowsGraph] = y
                            graph1[rowsGraph] = 1
                            # print ('Input positionGraphAxes', x, y)
                            rowsGraph += 1
            return screen, graphX, graphY, np.ones(3), rowsGraph, rowsScreen
        except Exception as e:
            screenX = []
            screenY = []
            screenXNew = []
            screenYNew = []
            graphX = []
            graphY = []
            IsXOnly = np.array([], dtype='str')
            for nodeAxes in node.iter():
                if (nodeAxes.tag == 'Point'):
                    for nodePoint in nodeAxes.iter():
                        if (nodePoint.tag == 'Point'):
                            IsXOnly = np.append(IsXOnly, nodePoint.attrib.get('IsXOnly'))
                        if (nodePoint.tag == 'PositionScreen'):
                            x = float(nodePoint.attrib.get('X'))
                            screenX.append(x)
                            y = float(nodePoint.attrib.get('Y')) 
                            screenY.append(y)
                        elif (nodePoint.tag == 'PositionGraph'):
                            x = float(nodePoint.attrib.get('X'))
                            graphX.append(x)
                            y = float(nodePoint.attrib.get('Y'))
                            graphY.append(y)
            graphX = np.array(graphX)
            graphX = graphX[IsXOnly == 'True']
            graphX = np.append(graphX, graphX[0])
            graphY = np.array(graphY)
            graphY = graphY[IsXOnly == 'False']
            graphY = np.append(graphY, graphY[1])
            graphY[1] = graphY[0]
            screenX = np.array(screenX)
            screenY = np.array(screenY)
            xAxesScreenX = screenX[IsXOnly == 'True']
            xAxesScreenY = screenY[IsXOnly == 'True']
            yAxesScreenX = screenX[IsXOnly == 'False']
            yAxesScreenY = screenY[IsXOnly == 'False']
            #The below section calculates the screen coords of intersections of 
            #lines formed by the x and y axes
            if ((yAxesScreenX[1] - yAxesScreenX[0]) != 0):
                m1 = (yAxesScreenY[1] - yAxesScreenY[0]) / (yAxesScreenX[1] - yAxesScreenX[0])
            else:
                m1 = np.inf
            m3 = (xAxesScreenY[1] - xAxesScreenY[0]) / (xAxesScreenX[1] - xAxesScreenX[0])
            m2 = m1
            m4 = m3
            b1 = xAxesScreenY[0] - m1 * xAxesScreenX[0]
            b2 = xAxesScreenY[1] - m2 * xAxesScreenX[1]
            b3 = yAxesScreenY[0] - m3 * yAxesScreenX[0]
            b4 = yAxesScreenY[1] - m4 * yAxesScreenX[1]
            #Use a slightly different procedure if the y-axis
            #has an infinite slope
            if ((m1 == np.inf) or (m1 == -np.inf)):
                screenXNew.append(xAxesScreenX[0])
                screenYNew.append(m3 * screenXNew[0] + b3)
                screenXNew.append(xAxesScreenX[1])
                screenYNew.append(m3 * screenXNew[1] + b3)
                screenXNew.append(xAxesScreenX[0])
                screenYNew.append(m4 * screenXNew[2] + b4)
            else:
                screenXNew.append((b1 - b3) / (m3 - m1))
                screenYNew.append(m3 * screenXNew[0] + b3)
                screenXNew.append((b2 - b3) / (m3 - m2))
                screenYNew.append(m3 * screenXNew[1] + b3)
                screenXNew.append((b1 - b4) / (m4 - m1))
                screenYNew.append(m4 * screenXNew[2] + b4)
            return np.array([screenXNew, screenYNew, np.ones(3)]).T, graphX, graphY, np.ones(3), rowsGraph, rowsScreen  

    def parseXml(self, tree):
        # (xG1 xG2 xG3) = screen * (m11 m12 m13)
        # (yG1 yG2 yG3) = screen * (m21 m22 m23)
        # (1   1   1  ) = screen * (m31 m32 m33)
        # where
        # screen = (xS1 yS1 1)
        #          (xS2 yS2 1)
        #          (xS3 yS3 1)
        self.LogPlot = False
        self._screenToGraph = np.array([])
        self._delimiter = ','
        for node in tree.iter():
            # print (node.tag, '<->', node.attrib)
            if (node.tag == 'Coords'):
                self.xAxisType = node.attrib.get('ScaleXThetaString')
                self.yAxisType = node.attrib.get('ScaleYRadiusString')
                if ((self.xAxisType == 'Log') or (self.yAxisType == 'Log')):
                    self.LogPlot = True
                    #sys.exit (1)
            elif (node.tag == 'Export'):
                # delimiterEnum = node.attrib.get('Delimiter')
                pass
            elif (node.tag == 'Curve'):
                curveName = node.attrib.get('CurveName')
                if (curveName == 'Axes'):
                    screen, graphX, graphY, graph1, rowsGraph, rowsScreen = self.getScreenAndGraph(node)
                    self.xScreenMax = screen[:, 0].max()
                    self.yScreenMax = screen[:, 1].max()
                    self.xScreenMin = screen[:, 0].min()
                    self.yScreenMin = screen[:, 1].min()
                    self.xMin = min(graphX)
                    self.yMin = min(graphY)
                    self.xMax = max(graphX)
                    self.yMax = max(graphY)
                    #print(self.yScreenMin)
                    #print(self.yScreenMax)
                    #print(self.yMin)
                    #print(self.yMax)
                    #print(screen)
                    if rowsGraph < 3 or rowsScreen < 3:
                        print ('This script requires three axes points. Quitting')
                        sys.exit (1)
                    self._screenToGraph = self.computeAffineTransformation(screen, graphX, graphY, graph1)
                else:
                    for nodeGraph in node.iter():
                        if (nodeGraph.tag == 'Point'):
                            for nodePoint in nodeGraph.iter():
                                if (nodePoint.tag == 'PositionScreen'):
                                    x = float(nodePoint.attrib.get('X'))
                                    y = float(nodePoint.attrib.get('Y'))
                                    # print ('Input positionScreen', x, y)
                                    vecScreen = np.array([x, y, 1])
                                    vecGraph = np.dot(self._screenToGraph,
                                                      vecScreen)
                                    xGraph = vecGraph[0]
                                    yGraph = vecGraph[1]
                                    if (self.xAxisType == 'Log'):
                                        xGraph = np.exp( (xGraph - self.xMin) \
                                                 * (np.log(self.xMax) - np.log(self.xMin)) \
                                                 / (self.xMax - self.xMin) \
                                                 + np.log(self.xMin) )[0]
                                    if (self.yAxisType == 'Log'):
                                        yGraph = np.exp( (yGraph - self.yMin) \
                                                 * (np.log(self.yMax) - np.log(self.yMin)) \
                                                 / (self.yMax - self.yMin) \
                                                 + np.log(self.yMin) )[0]
                                    # print ('Computed positionGraph', x, y)
                                    self._curves[curveName].append([xGraph, yGraph, x, y]) 

    def transformGraphToScreen (self, xGraph, yGraph):
        graphToScreen = np.linalg.inv (self._screenToGraph)
        vecGraph = np.array ([xGraph, yGraph, 1])
        vecScreen = np.dot (graphToScreen,
                            vecGraph)
        return int (0.5 + vecScreen [0]), int (0.5 + vecScreen [1])

    def upgrade (self, digFile):
        # File naming consistent with main.cpp
        FILE_SUFFIX = '.dig'
        UPGRADE_TOKEN = '_upgrade'
        count = len (FILE_SUFFIX)
        if digFile [-count:].lower () == FILE_SUFFIX.lower ():
            # xyz.dig turns into xyz_upgrade.dig
            digFileWithoutSuffix = digFile [: -count]
            digFileUpgraded = '{}{}{}' . format (digFileWithoutSuffix,
                                                 UPGRADE_TOKEN,
                                                 FILE_SUFFIX)
        else:
            # xyz turns into xyz_upgrade
            digFileUpgraded = '{}{}' . format (digFile,
                                               UPGRADE_TOKEN)

        # Stop if this could overwrite valuable information
        if os.path.exists (digFileUpgraded):
            print ('Upgrade file exists and will not be overwritten. Quitting')
            sys.exit (0)

        # Create the upgrade from the old dig file. It will be removed after
        callEngauge (["-upgrade",
                      digFile])

        return digFileUpgraded

        

