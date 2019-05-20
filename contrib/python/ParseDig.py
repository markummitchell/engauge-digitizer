# This file converts non-xml dig files to xml if required. Directly reading non-xml
# files (=binary) was attempted but the unpredictable length of the QPixMap in the
# middle of the binary data, and use of string (versus bytes) by pyside2 prevented
# that option from succeeding
from xml.etree import ElementTree
from DefaultListOrderedDict import DefaultListOrderedDict
import numpy as np
import os
import subprocess
import sys

class ParseDig:
    def __init__(self, digFile):
        # Hash table of curve name to lists, with each list consisting of graph points
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

    def parseXml(self, tree):
        # (xG1 xG2 xG3) = screen * (m11 m12 m13)
        # (yG1 yG2 yG3) = screen * (m21 m22 m23)
        # (1   1   1  ) = screen * (m31 m32 m33)
        # where
        # screen = (xS1 yS1 1)
        #          (xS2 yS2 1)
        #          (xS3 yS3 1)
        rowsGraph = 0
        rowsScreen = 0
        screen = np.empty(shape=(3, 3))
        graphX = np.empty(shape=(3, 1))
        graphY = np.empty(shape=(3, 1))
        graph1 = np.empty(shape=(3, 1))
        self._screenToGraph = np.array([])
        self._delimiter = ','
        for node in tree.iter():
            # print (node.tag, '<->', node.attrib)
            if (node.tag == 'Export'):
                delimiterEnum = node.attrib.get('Delimiter')
                delimiter = self.delimiterEnumToDelimiter(delimiterEnum)
            elif (node.tag == 'Curve'):
                curveName = node.attrib.get('CurveName')
                if (curveName == 'Axes'):
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
                                    x = vecGraph[0]
                                    y = vecGraph[1]
                                    # print ('Computed positionGraph', x, y)
                                    self._curves[curveName].append([x, y])

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

        # Create the upgrade
        subprocess.call (["../../bin/engauge",
                         "-upgrade",
                         digFile])

        return digFileUpgraded
