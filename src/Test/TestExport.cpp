#include "CurveConnectAs.h"
#include "Document.h"
#include "DocumentModelExportFormat.h"
#include "ExportFileFunctions.h"
#include "ExportValuesXOrY.h"
#include "LineStyle.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include "PointStyle.h"
#include <QImage>
#include <qmath.h>
#include <QtTest/QtTest>
#include "Spline.h"
#include "SplinePair.h"
#include "Test/TestExport.h"
#include "Transformation.h"

QTEST_MAIN (TestExport)

using namespace std;

TestExport::TestExport(QObject *parent) :
  QObject(parent)
{
}

void TestExport::cleanupTestCase ()
{

}

void TestExport::initTestCase ()
{
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool NO_RESET = false;
  const bool DEBUG_FLAG = false;
  const QStringList NO_LOAD_STARTUP_FILES;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow w (NO_ERROR_REPORT_LOG_FILE,
                NO_REGRESSION_OPEN_FILE,
                NO_GNUPLOT_LOG_FILES,
                NO_REGRESSION_IMPORT,
                NO_RESET,
                NO_LOAD_STARTUP_FILES);
  w.show ();
}

void TestExport::testLogExtrapolationFunctionsAll ()
{
  const QString CURVE_NAME ("Curve1");
  const QString DELIMITER (" ");
  const int LINE_WIDTH = 2, POINT_LINE_WIDTH = 1;
  const ColorPalette LINE_COLOR = COLOR_PALETTE_BLACK, POINT_COLOR = COLOR_PALETTE_BLACK;
  const int RADIUS = 5;
  
  QImage nullImage;
  DocumentModelCoords modelCoords;
  DocumentModelExportFormat modelExportOverride;
  DocumentModelGeneral modelGeneral;
  Document document (nullImage);
  MainWindowModel modelMainWindow;
  QStringList curvesIncluded (CURVE_NAME);
  ExportValuesXOrY xThetaValues;
  Transformation transformation;
  QString dummy;
  QTextStream str (&dummy);

  CurveStyles curveStyles (document.coordSystem ());
  CurveStyle curveStyle (LineStyle (LINE_WIDTH,
                                    LINE_COLOR,
                                    CONNECT_AS_FUNCTION_SMOOTH),
                         PointStyle (POINT_SHAPE_CIRCLE,
                                     RADIUS,
                                     POINT_LINE_WIDTH,
                                     POINT_COLOR));
  curveStyles.setCurveStyle (CURVE_NAME, curveStyle);
  modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  modelCoords.setCoordsType (COORDS_TYPE_CARTESIAN);
  modelGeneral.setCursorSize (3);
  modelGeneral.setExtraPrecision (1);
  
  document.setModelCurveStyles (curveStyles);
  document.setModelCoords (modelCoords);
  document.setModelGeneral (modelGeneral);

  modelExportOverride.setPointsSelectionFunctions (EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (845, 305), "Curve1\t0", 0);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (850, 294), "Curve1\t1", 1);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (862, 272), "Curve1\t2", 2);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (876, 244), "Curve1\t3", 3);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (887, 222), "Curve1\t4", 4);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (899, 200), "Curve1\t5", 5);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (910, 177), "Curve1\t6", 6);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (922, 155), "Curve1\t7", 7);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (933, 133), "Curve1\t8", 8);
  document.addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (945, 110), "Curve1\t9", 9);
  xThetaValues << 0.0009999; // Just outside of the coordinates added to the document
  xThetaValues << 0.001;
  xThetaValues << 0.01;
  xThetaValues << 0.1;
  xThetaValues << 1;
  xThetaValues << 10;
  xThetaValues << 100;
  xThetaValues << 1000;
  QTransform matrixScreen ( 51, 52, 1123,
                           548, 10,  548,
                             1,  1,    1);
  QTransform matrixGraph (qLn (0.001), qLn (0.001), qLn (1000),
                          qLn (    1), qLn (  100), qLn (   1),
                                    1,           1,          1);
  transformation.updateTransformFromMatrices (matrixScreen,
                                              matrixGraph);
  transformation.setModelCoords (modelCoords,
                                 modelGeneral,
                                 modelMainWindow);

  bool success = true;
  try {
    bool isLogXTheta = (modelCoords.coordScaleXTheta() == COORD_SCALE_LOG);
    bool isLogYRadius = (modelCoords.coordScaleYRadius() == COORD_SCALE_LOG);

    ExportFileFunctions exportFile;    
    exportFile.exportAllPerLineXThetaValuesMerged (modelExportOverride,
                                                   document,
                                                   modelMainWindow,
                                                   curvesIncluded,
                                                   xThetaValues,
                                                   DELIMITER,
                                                   transformation,
                                                   isLogXTheta,
                                                   isLogYRadius,
                                                   str);
  }
  catch (...)
  {
    success = false;
  }

  QVERIFY (success);
}
