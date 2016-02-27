from xml.etree import ElementTree
from DefaultListOrderedDict import DefaultListOrderedDict
import numpy as np

class ParseDig:
    curves = DefaultListOrderedDict () # Hash table of curve name to lists, with each list consisting of graph points
    def __init__(self, digFile):
        with open(digFile, 'rt') as f:
            tree = ElementTree.parse (f)

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
        screenToGraph = np.array([])
        for node in tree.iter():
            # print (node.tag, '<->', node.attrib)
            if (node.tag == 'Curve'):
                curveName = node.attrib.get ('CurveName');
                if (curveName == 'Axes'):
                    for nodeAxes in node.iter():
                        if (nodeAxes.tag == 'Point'):
                            for nodePoint in nodeAxes.iter():
                                if (nodePoint.tag == 'PositionScreen'):
                                    x = float (nodePoint.attrib.get ('X'))
                                    y = float (nodePoint.attrib.get ('Y'))
                                    screen [rowsScreen] [0] = x
                                    screen [rowsScreen] [1] = y
                                    screen [rowsScreen] [2] = 1
                                    # print ('Input positionScreenAxes', x, y)
                                    rowsScreen = rowsScreen + 1;
                                elif (nodePoint.tag == 'PositionGraph'):
                                    x = float (nodePoint.attrib.get ('X'))
                                    y = float (nodePoint.attrib.get ('Y'))
                                    graphX [rowsGraph] = x;
                                    graphY [rowsGraph] = y;
                                    graph1 [rowsGraph] = 1;
                                    # print ('Input positionGraphAxes', x, y)
                                    rowsGraph = rowsGraph + 1;
                    screenToGraph = self.computeAffineTransformation(screen, graphX, graphY, graph1)
                else:
                    for nodeGraph in node.iter():
                        if (nodeGraph.tag == 'Point'):
                            for nodePoint in nodeGraph.iter():
                                if (nodePoint.tag == 'PositionScreen'):
                                    x = float (nodePoint.attrib.get ('X'))
                                    y = float (nodePoint.attrib.get ('Y'))
                                    # print ('Input positionScreen', x, y)
                                    vecScreen = np.array ([x, y, 1])
                                    vecGraph = np.dot (screenToGraph, 
                                                       vecScreen)
                                    x = vecGraph [0]
                                    y = vecGraph [1]
                                    # print ('Computed positionGraph', x, y)
                                    self.curves [curveName].append ([x, y]);
    def computeAffineTransformation (self, screen, graphX, graphY, graph1):
        # Compute screen-to-graph affine transformation from screen and graph points in axes
        screenInverse = np.linalg.inv (screen)
        m1 = np.dot (screenInverse, graphX)
        m2 = np.dot (screenInverse, graphY)
        m3 = np.dot (screenInverse, graph1)
        screenToGraph = np.array ([m1.flatten(), m2.flatten(), m3.flatten()])
        return screenToGraph
    def curve (self, curveName):
        return list (self.curves [curveName]);
    def curveNames (self):
        return list (self.curves.keys ());
