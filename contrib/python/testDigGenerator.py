# lxml supports CDATA and xml.etree.ElementTree does not
# See https://lxml.de/tutorial.html
from lxml.etree import CDATA, Element, SubElement, tostring
import pandas as pd

def addAxisPoint (curvePoints, identifierNumber, ordinal, xScreen, yScreen, xGraph, yGraph, IsXOnly = 'False'):
    point = SubElement (curvePoints, 'Point')
    point.set ('Identifier', 'Axes\tpoint\t{}' . format (identifierNumber))
    point.set ('Ordinal', '{}' . format (ordinal))
    point.set ('IsAxisPoint', 'True')
    point.set ('IsXOnly', IsXOnly)
    point.set ('Index', '329')
    positionScreen = SubElement (point, 'PositionScreen')
    positionScreen.set ('X', '{}' . format (xScreen))
    positionScreen.set ('Y', '{}' . format (yScreen))
    positionGraph = SubElement (point, 'PositionGraph')
    positionGraph.set ('X', '{}' . format (xGraph))
    positionGraph.set ('Y', '{}' . format (yGraph))
    
def addGraphPoint (curvePoints, identifierIndex, ordinal, xScreen, yScreen):
    point = SubElement (curvePoints, 'Point')
    point.set ('Identifier', 'Curve1\tpoint\t{}' . format (identifierIndex))
    point.set ('Ordinal', '0')
    point.set ('IsAxisPoint', 'False')
    point.set ('IsXOnly', 'False')
    point.set ('Index', '329')
    positionScreen = SubElement (point, 'PositionScreen')
    positionScreen.set ('X', '{}' . format (xScreen))
    positionScreen.set ('Y', '{}' . format (yScreen))

def createTestCase(xAxes, yAxes, xData, yData, xScale, yScale, title):
    """xAxes looks like [xScreen, xGraph], where xScreen is an array of
    x pixel values for the axes, and xGraph is the corresponding graph 
    coordinates. yAxes is similar.
    If passing four axis points, the first two rows should be for the x axis
    and the next two values for the y axis. 
    xData and yData are both 1D arrays of the pixel values of the
    data points.
    xScale and yScale are the various scale types (e.g. Linear, Log).
    title is the desired title of the output."""
    
    document = Element ('Document')
    document.set ('VersionNumber', '11.0')
    document.set ('AxesPointsRequired', '0')
    
    image = SubElement (document, 'Image')
    image.set ('Width', '605')
    image.set ('Height', '340')
    image.text = CDATA ('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')

    coordSystem = SubElement (document, 'CoordSystem')
    general = SubElement (coordSystem, 'General')
    general.set ('CursorSize', '3')
    general.set ('ExtraPrecision', '1')
    coords = SubElement (coordSystem, 'Coords')
    coords.set ('Type', '0')
    coords.set ('TypeString', 'Cartesian')
    coords.set ('Coords', '0')
	
    if (xScale == 'Linear'):
        coords.set ('ScaleXTheta', '0')
    elif (xScale == 'Log'):
        coords.set ('ScaleXTheta', '1')
    coords.set ('ScaleXThetaString', xScale)
	
    if (yScale == 'Linear'):
        coords.set ('ScaleYRadius', '0')
    elif (yScale == 'Log'):
        coords.set ('ScaleYRadius', '1')
    coords.set ('ScaleYRadiusString', yScale)
	
    coords.set ('UnitsX', '0')
    coords.set ('UnitsXString', 'Number')
    coords.set ('UnitsY', '0')
    coords.set ('UnitsYString', 'Number')
    coords.set ('UnitsTheta', '0')
    coords.set ('UnitsThetaString', 'Degrees (DDD.DDDDD)')
    coords.set ('UnitsRadius', '0')
    coords.set ('UnitsRadiusString', 'Number')
    coords.set ('UnitsDate', '3')
    coords.set ('UnitsDateString', 'YYYY/MM/DD')
    coords.set ('UnitsTime', '2')
    coords.set ('UnitsTimeString', 'HH:MM:SS')
    digitizeCurve = SubElement (coordSystem, 'DigitizeCurve')
    digitizeCurve.set ('CursorInnerRadius', '5')
    digitizeCurve.set ('CursorLineWidth', '2')
    digitizeCurve.set ('CursorSize', '1')
    digitizeCurve.set ('CursorStandardCross', 'True')
    export = SubElement (coordSystem, 'Export')
    export.set ('PointsSelectionFunctions', '1')
    export.set ('PointsSelectionFunctionsString', 'InterpolateFirstCurve')
    export.set ('PointsIntervalFunctions', '10')
    export.set ('PointsIntervalUnitsFunctions', '1')
    export.set ('PointsSelectionRelations', '0')
    export.set ('PointsSelectionRelationsString', 'Interpolate')
    export.set ('PointsIntervalUnitsRelations', '1')
    export.set ('PointsIntervalRelations', '10')
    export.set ('LayoutFunctions', '0')
    export.set ('LayoutFunctionsString', 'AllPerLine')
    export.set ('Delimiter', '0')
    export.set ('OverrideCsvTsv', 'False')
    export.set ('DelimiterString', 'Commas')
    export.set ('ExtrapolateOutsideEndpoints', 'True')
    export.set ('Header', '1')
    export.set ('HeaderString', 'Simple')
    export.set ('XLabel', 'x')
    curveNamesNotExported = SubElement (export, 'CurveNamesNotExported')
    axesChecker = SubElement (coordSystem, 'AxesChecker')
    axesChecker.set ('Mode', '1')
    axesChecker.set ('Seconds', '3')
    axesChecker.set ('LineColor', '6')
    gridDisplay = SubElement (coordSystem, 'GridDisplay')
    gridDisplay.set ('Stable', 'True')
    gridDisplay.set ('DisableX', '0')
    gridDisplay.set ('CountX', '4')
    gridDisplay.set ('StartX', '0')
    gridDisplay.set ('StepX', '5')
    gridDisplay.set ('StopX', '15')
    gridDisplay.set ('DisableY', '0')
    gridDisplay.set ('CountY', '5')
    gridDisplay.set ('StartY', '-2')
    gridDisplay.set ('StepY', '1')
    gridDisplay.set ('StopY', '2')
    gridDisplay.set ('Color', '0')
    gridDisplay.set ('ColorString', 'Black')
    gridRemoval = SubElement (coordSystem, 'GridRemoval')
    gridRemoval.set ('Stable', 'False')
    gridRemoval.set ('DefinedGridLines', 'False') 
    gridRemoval.set ('CloseDistance', '10') 
    gridRemoval.set ('CoordDisableX', '0') 
    gridRemoval.set ('CoordDisableXString', 'Count') 
    gridRemoval.set ('CountX', '2') 
    gridRemoval.set ('StartX', '-0.256806') 
    gridRemoval.set ('StepX', '3.07889') 
    gridRemoval.set ('StopX', '2.82208') 
    gridRemoval.set ('CoordDisableY', '0') 
    gridRemoval.set ('CoordDisableYString', 'Count') 
    gridRemoval.set ('CountY', '24') 
    gridRemoval.set ('StartY', '-0.986309') 
    gridRemoval.set ('StepY', '0.0866021') 
    gridRemoval.set ('StopY', '1.00554')
    pointMatch = SubElement (coordSystem, 'PointMatch')
    pointMatch.set ('PointSize', '48')
    pointMatch.set ('ColorAccepted', '4')
    pointMatch.set ('ColorAcceptedString', 'Green')
    pointMatch.set ('ColorCandidate', '7')
    pointMatch.set ('ColorCandidateString', 'Yellow')
    pointMatch.set ('ColorRejected', '6')
    pointMatch.set ('ColorRejectedString', 'Red')
    segments = SubElement (coordSystem, 'Segments')
    segments.set ('PointSeparation', '25')
    segments.set ('MinLength', '2')
    segments.set ('FillCorners', 'False')
    segments.set ('LineWidth', '4')
    segments.set ('LineColor', '4')
    segments.set ('LineColorString', 'Green')
    curve = SubElement (coordSystem, 'Curve')
    curve.set ('CurveName', 'Axes')
    colorFilter = SubElement (curve, 'ColorFilter')
    colorFilter.set ('CurveName', 'Axes')
    colorFilter.set ('Mode', '1')
    colorFilter.set ('ModeString', 'Intensity')
    colorFilter.set ('IntensityLow', '0')
    colorFilter.set ('IntensityHigh', '50')
    colorFilter.set ('ForegroundLow', '0')
    colorFilter.set ('ForegroundHigh', '10')
    colorFilter.set ('HueLow', '180')
    colorFilter.set ('HueHigh', '360')
    colorFilter.set ('SaturationLow', '50')
    colorFilter.set ('SaturationHigh', '100')
    colorFilter.set ('ValueLow', '0')
    colorFilter.set ('ValueHigh', '50')
    curveStyle = SubElement (curve, 'CurveStyle')
    curveStyle.set ('CurveName', 'Axes')
    lineStyle = SubElement (curveStyle, 'LineStyle')
    lineStyle.set ('Width', '0')
    lineStyle.set ('Color', '8')
    lineStyle.set ('ColorString', 'Transparent')
    lineStyle.set ('ConnectAs', '4')
    lineStyle.set ('ConnectAsString', 'ConnectSkipForAxisCurve')
    pointStyle = SubElement (curveStyle, 'PointStyle')
    pointStyle.set ('Radius', '10')
    pointStyle.set ('LineWidth', '1')
    pointStyle.set ('Color', '6')
    pointStyle.set ('ColorString', 'Red')
    pointStyle.set ('Shape', '1')
    pointStyle.set ('ShapeString', 'Cross')
    curvePoints = SubElement (curve, 'CurvePoints')
    xScreen = xAxes[0]
    xGraph = xAxes[1]
    yScreen = yAxes[0]
    yGraph = yAxes[1]
    # When adding the axis points, make sure to account for four axis points.
    if (len(xScreen) == 3):
        addAxisPoint (curvePoints, 209, 1, xScreen[0], 
                      yScreen[0], xGraph[0], yGraph[0])
        addAxisPoint (curvePoints, 211, 2, xScreen[1], 
                      yScreen[1], xGraph[1], yGraph[1])
        addAxisPoint (curvePoints, 213, 3, xScreen[2], 
                      yScreen[2], xGraph[2], yGraph[2])
    else:
        addAxisPoint (curvePoints, 209, 1, xScreen[0], 
                      yScreen[0], xGraph[0], 0, IsXOnly = 'True')
        addAxisPoint (curvePoints, 211, 2, xScreen[1], 
                      yScreen[1], xGraph[1], 0, IsXOnly = 'True')
        addAxisPoint (curvePoints, 213, 3, xScreen[2], 
                      yScreen[2], 0, yGraph[2])
        addAxisPoint (curvePoints, 215, 4, xScreen[3], 
                      yScreen[3], 0, yGraph[3])
    
    curvesGraphs = SubElement (coordSystem, 'CurvesGraphs')
    curve = SubElement (curvesGraphs, 'Curve')
    curve.set ('CurveName', 'Curve1')
    
    colorFilter = SubElement (curve, 'ColorFilter')
    colorFilter.set ('CurveName', 'Curve1')
    colorFilter.set ('Mode', '1')
    colorFilter.set ('ModeString', 'Hue')
    colorFilter.set ('IntensityLow', '0')
    colorFilter.set ('IntensityHigh', '50')
    colorFilter.set ('ForegroundLow', '0')
    colorFilter.set ('ForegroundHigh', '10')
    colorFilter.set ('HueLow', '204')
    colorFilter.set ('HueHigh', '211')
    colorFilter.set ('SaturationLow', '50')
    colorFilter.set ('SaturationHigh', '100')
    colorFilter.set ('ValueLow', '0')
    colorFilter.set ('ValueHigh', '50')
    curveStyle = SubElement (curve, 'CurveStyle')
    curveStyle.set ('CurveName', 'Curve1')
    lineStyle = SubElement (curveStyle, 'LineStyle')
    lineStyle.set ('Width', '1')
    lineStyle.set ('Color', '1')
    lineStyle.set ('ColorString', 'Blue')
    lineStyle.set ('ConnectAs', '0')
    lineStyle.set ('ConnectAsString', 'FunctionSmooth')
    pointStyle = SubElement (curveStyle, 'PointStyle')
    pointStyle.set ('Radius', '10')
    pointStyle.set ('LineWidth', '1')
    pointStyle.set ('Color', '1')
    pointStyle.set ('ColorString', 'Blue')
    pointStyle.set ('Shape', '1')
    pointStyle.set ('ShapeString', 'Cross')
    curvePoints = SubElement (curve, 'CurvePoints')
    
    addGraphPoint (curvePoints, 290, 0, xData, yData)
    testFile = (tostring (document,
                     pretty_print = True,
                     xml_declaration = True,
                     encoding = 'UTF-8',
                     doctype = '<!DOCTYPE engauge>').decode ('utf-8'))

    try: 
        f = open(title, 'w')
    except Exception as e:
        f = open(title, 'w+')
    f.write(testFile)
    f.close()