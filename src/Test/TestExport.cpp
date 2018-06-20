#include "CurveConnectAs.h"
#include "Document.h"
#include "DocumentModelExportFormat.h"
#include "ExportFileFunctions.h"
#include "ExportFileRelations.h"
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

const bool NOT_USING_GNUPLOT = false;
const bool EXPORT_ONLY= true;
const QString NO_ERROR_REPORT_LOG_FILE;
const QString NO_REGRESSION_OPEN_FILE;
const bool NO_GNUPLOT_LOG_FILES = false;
const bool NO_REGRESSION_IMPORT = false;
const bool NO_RESET = false;
const bool NO_EXPORT_ONLY = false;
const bool DEBUG_FLAG = false;
const QStringList NO_LOAD_STARTUP_FILES;
const QString STARTUP_DIG_LOWER_CASE ("/tmp/export_only.dig");
const QString STARTUP_DIG_UPPER_CASE ("/tmp/export_only.DIG");
const QStringList ONE_LOAD_STARTUP_FILE_LOWER_CASE (STARTUP_DIG_LOWER_CASE);
const QStringList ONE_LOAD_STARTUP_FILE_UPPER_CASE (STARTUP_DIG_UPPER_CASE);
const bool REGRESSION_IMPORT = true;

TestExport::TestExport(QObject *parent) :
  QObject(parent),
  m_mainWindow (0),
  m_document (0)
{
}

bool TestExport::checkCommasInFunctionsForDelimiter (ExportDelimiter delimiter,
                                                     QLocale::Country country,
                                                     QString &output)
{
  initData (false,
            delimiter,
            country);

  QTextStream str (&output);
  bool success = true;
  QString dummy;

  try {
    bool isLogXTheta = (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LOG);
    bool isLogYRadius = (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG);
    unsigned int numWritesSoFar = 0;

    ExportFileFunctions exportFile;    
    exportFile.exportAllPerLineXThetaValuesMerged (m_modelExportOverride,
                                                   *m_document,
                                                   m_modelMainWindow,
                                                   m_curvesIncluded,
                                                   m_xThetaValues,
                                                   exportDelimiterToText (delimiter, NOT_USING_GNUPLOT),
                                                   m_transformation,
                                                   isLogXTheta,
                                                   isLogYRadius,
                                                   str,
                                                   numWritesSoFar);
  }
  catch (...)
  {
    success = false;
  }
  
  return (success);
}

bool TestExport::checkCommasInRelationsForDelimiter (ExportDelimiter delimiter,
                                                     QLocale::Country country,
                                                     QString &output)
{
  initData (false,
            delimiter,
            country);

  QTextStream str (&output);
  bool success = true;
  QString dummy;

  try {
    bool isLogXTheta = (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LOG);
    bool isLogYRadius = (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG);
    unsigned int numWritesSoFar = 0;
    
    ExportFileRelations exportFile;
    exportFile.exportAllPerLineXThetaValuesMerged (m_modelExportOverride,
                                                   *m_document,
                                                   m_modelMainWindow,
                                                   m_curvesIncluded,
                                                   exportDelimiterToText (delimiter, NOT_USING_GNUPLOT),
                                                   m_transformation,
                                                   isLogXTheta,
                                                   isLogYRadius,
                                                   str,
                                                   numWritesSoFar);
  }
  catch (...)
  {
    success = false;
  }
  
  return (success);
}

void TestExport::cleanupTestCase ()
{
}

void TestExport::initData (bool isLog,
                           ExportDelimiter delimiter,
                           QLocale::Country country)
{
  const QString CURVE_NAME ("Curve1");
  const int LINE_WIDTH = 2, POINT_LINE_WIDTH = 1;
  const ColorPalette LINE_COLOR = COLOR_PALETTE_BLACK, POINT_COLOR = COLOR_PALETTE_BLACK;
  const int RADIUS = 5;

  QImage nullImage;
  m_document = new Document (nullImage);

  m_curvesIncluded.clear ();
  m_curvesIncluded << CURVE_NAME;

  CurveStyles curveStyles (m_document->coordSystem ());
  CurveStyle curveStyle (LineStyle (LINE_WIDTH,
                                    LINE_COLOR,
                                    CONNECT_AS_FUNCTION_SMOOTH),
                         PointStyle (POINT_SHAPE_CIRCLE,
                                     RADIUS,
                                     POINT_LINE_WIDTH,
                                     POINT_COLOR));
  curveStyles.setCurveStyle (CURVE_NAME, curveStyle);
  if (isLog) {
    m_modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
    m_modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  } else {
    m_modelCoords.setCoordScaleXTheta (COORD_SCALE_LINEAR);
    m_modelCoords.setCoordScaleYRadius (COORD_SCALE_LINEAR);    
  }
  m_modelCoords.setCoordsType (COORDS_TYPE_CARTESIAN);
  m_modelGeneral.setCursorSize (3);
  m_modelGeneral.setExtraPrecision (1);

  m_modelExportOverride.setPointsSelectionFunctions (EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);
  m_modelExportOverride.setDelimiter (delimiter);

  m_document->setModelExport (m_modelExportOverride);
  m_document->setModelCurveStyles (curveStyles);
  m_document->setModelCoords (m_modelCoords);
  m_document->setModelGeneral (m_modelGeneral);

  m_modelMainWindow.setLocale (QLocale::English,
                               country);
    
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (845, 305), "Curve1\t0", 0);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (850, 294), "Curve1\t1", 1);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (862, 272), "Curve1\t2", 2);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (876, 244), "Curve1\t3", 3);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (887, 222), "Curve1\t4", 4);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (899, 200), "Curve1\t5", 5);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (910, 177), "Curve1\t6", 6);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (922, 155), "Curve1\t7", 7);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (933, 133), "Curve1\t8", 8);
  m_document->addPointGraphWithSpecifiedIdentifier (CURVE_NAME, QPointF (945, 110), "Curve1\t9", 9);

  m_xThetaValues.clear ();
  m_xThetaValues << 0.0009999; // Just outside of the coordinates added to the document
  m_xThetaValues << 0.001;
  m_xThetaValues << 0.01;
  m_xThetaValues << 0.1;
  m_xThetaValues << 1;
  m_xThetaValues << 10;
  m_xThetaValues << 100;
  m_xThetaValues << 1000;
  QTransform matrixScreen ( 51, 52, 1123,
                           548, 10,  548,
                             1,  1,    1);
  QTransform matrixGraph (qLn (0.001), qLn (0.001), qLn (1000),
                          qLn (    1), qLn (  100), qLn (   1),
                                    1,           1,          1);
  m_transformation.updateTransformFromMatrices (matrixScreen,
                                                matrixGraph);
  m_transformation.setModelCoords (m_modelCoords,
                                   m_modelGeneral,
                                   m_modelMainWindow);
}

void TestExport::initTestCase ()
{
  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  m_mainWindow = new MainWindow (NO_ERROR_REPORT_LOG_FILE,
                                 NO_REGRESSION_OPEN_FILE,
                                 NO_REGRESSION_IMPORT,                
                                 NO_GNUPLOT_LOG_FILES,
                                 NO_RESET,
                                 NO_EXPORT_ONLY,
                                 NO_LOAD_STARTUP_FILES);

  m_mainWindow->show ();
}

void TestExport::testCommasInFunctionsForCommasSwitzerland ()
{
  QString outputExpectedIfCommaSeparator =
    "x,Curve1\n"
    "\"0,001\",\"-1,27563\"\n"
    "\"0,001\",\"-1,27563\"\n"
    "\"0,01\",\"-1,26683\"\n"
    "\"0,1\",\"-1,17881\"\n"
    "1,\"-0,29658\"\n"
    "10,\"-706,15184\"\n"
    "100,\"-3997814,14355\"\n"
    "1000,\"-4541901224,06376\"\n";
  QString outputExpectedIfPeriodSeparator =
    "x,Curve1\n"
    "0.001,-1.27563\n"
    "0.001,-1.27563\n"
    "0.01,-1.26683\n"
    "0.1,-1.17881\n"
    "1,-0.29658\n"
    "10,-706.15184\n"
    "100,-3997814.14355\n"
    "1000,-4541901224.06376\n";
  
  QString outputGot;
  bool success = checkCommasInFunctionsForDelimiter (EXPORT_DELIMITER_COMMA,
                                                     QLocale::Switzerland,
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }
    
  QVERIFY (outputGot == outputExpectedIfCommaSeparator ||
	   outputGot == outputExpectedIfPeriodSeparator);
}

void TestExport::testCommasInFunctionsForCommasUnitedStates ()
{
  QString outputExpected = 
    "x,Curve1\n"
    "0.001,-1.27563\n"
    "0.001,-1.27563\n"
    "0.01,-1.26683\n"
    "0.1,-1.17881\n"
    "1,-0.29658\n"
    "10,-706.15184\n"
    "100,-3997814.14355\n"
    "1000,-4541901224.06376\n";
  
  QString outputGot;
  bool success = checkCommasInFunctionsForDelimiter (EXPORT_DELIMITER_COMMA,
                                                     QLocale::UnitedStates,                                                     
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }

  QVERIFY (outputGot == outputExpected);
}

void TestExport::testCommasInFunctionsForTabsSwitzerland ()
{
  QString outputExpectedIfCommaSeparator =
    "x\tCurve1\n"
    "0,001\t-1,27563\n"
    "0,001\t-1,27563\n"
    "0,01\t-1,26683\n"
    "0,1\t-1,17881\n"
    "1\t-0,29658\n"
    "10\t-706,15184\n"
    "100\t-3997814,14355\n"
    "1000\t-4541901224,06376\n";
  QString outputExpectedIfPeriodSeparator =
    "x\tCurve1\n"
    "0.001\t-1.27563\n"
    "0.001\t-1.27563\n"
    "0.01\t-1.26683\n"
    "0.1\t-1.17881\n"
    "1\t-0.29658\n"
    "10\t-706.15184\n"
    "100\t-3997814.14355\n"
    "1000\t-4541901224.06376\n";
  
  QString outputGot;
  bool success = checkCommasInFunctionsForDelimiter (EXPORT_DELIMITER_TAB,
                                                     QLocale::Switzerland,
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }

  QVERIFY (outputGot == outputExpectedIfCommaSeparator ||
	   outputGot == outputExpectedIfPeriodSeparator);
}

void TestExport::testCommasInFunctionsForTabsUnitedStates ()
{
  QString outputExpected =
    "x\tCurve1\n"
    "0.001\t-1.27563\n"
    "0.001\t-1.27563\n"
    "0.01\t-1.26683\n"
    "0.1\t-1.17881\n"
    "1\t-0.29658\n"
    "10\t-706.15184\n"
    "100\t-3997814.14355\n"
    "1000\t-4541901224.06376\n";
  
  QString outputGot;
  bool success = checkCommasInFunctionsForDelimiter (EXPORT_DELIMITER_TAB,
                                                     QLocale::UnitedStates,
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }

  QVERIFY (outputGot == outputExpected);
}

void TestExport::testCommasInRelationsForCommasSwitzerland ()
{
  QString outputExpectedIfCommaSeparator =
    "x,Curve1\n"
    "\"3,3192\",\"2,08003\"\n"
    "\"3,3723\",\"2,15796\"\n"
    "\"3,432\",\"2,23368\"\n"
    "\"3,4935\",\"2,30883\"\n"
    "\"3,5539\",\"2,38438\"\n"
    "\"3,6113\",\"2,46094\"\n"
    "\"3,6687\",\"2,5375\"\n"
    "\"3,7261\",\"2,61406\"\n"
    "\"3,7836\",\"2,69062\"\n"
    "\"3,841\",\"2,76718\"\n"
    "\"3,9012\",\"2,84276\"\n"
    "\"3,9628\",\"2,91791\"\n"
    "\"4,0231\",\"2,99345\"\n"
    "\"4,0785\",\"3,07067\"\n"
    "\"4,1339\",\"3,14789\"\n"
    "\"4,1932\",\"3,22378\"\n"
    "\"4,2547\",\"3,29893\"\n"
    "\"4,3156\",\"3,37426\"\n"
    "\"4,3731\",\"3,45082\"\n"
    "\"4,4305\",\"3,52738\"\n"
    "\"4,4892\",\"3,60349\"\n"
    "\"4,5486\",\"3,67938\"\n";
  QString outputExpectedIfPeriodSeparator =
    "x,Curve1\n"
    "3.3192,2.08003\n"
    "3.3723,2.15796\n"
    "3.432,2.23368\n"
    "3.4935,2.30883\n"
    "3.5539,2.38438\n"
    "3.6113,2.46094\n"
    "3.6687,2.5375\n"
    "3.7261,2.61406\n"
    "3.7836,2.69062\n"
    "3.841,2.76718\n"
    "3.9012,2.84276\n"
    "3.9628,2.91791\n"
    "4.0231,2.99345\n"
    "4.0785,3.07067\n"
    "4.1339,3.14789\n"
    "4.1932,3.22378\n"
    "4.2547,3.29893\n"
    "4.3156,3.37426\n"
    "4.3731,3.45082\n"
    "4.4305,3.52738\n"
    "4.4892,3.60349\n"
    "4.5486,3.67938\n";
  
  QString outputGot;
  bool success = checkCommasInRelationsForDelimiter (EXPORT_DELIMITER_COMMA,
                                                     QLocale::Switzerland,
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }

  QVERIFY (outputGot == outputExpectedIfCommaSeparator ||
	   outputGot == outputExpectedIfPeriodSeparator);
}

void TestExport::testCommasInRelationsForCommasUnitedStates ()
{
  QString outputExpected =
    "x,Curve1\n"
    "3.3192,2.08003\n"
    "3.3723,2.15796\n"
    "3.432,2.23368\n"
    "3.4935,2.30883\n"
    "3.5539,2.38438\n"
    "3.6113,2.46094\n"
    "3.6687,2.5375\n"
    "3.7261,2.61406\n"
    "3.7836,2.69062\n"
    "3.841,2.76718\n"
    "3.9012,2.84276\n"
    "3.9628,2.91791\n"
    "4.0231,2.99345\n"
    "4.0785,3.07067\n"
    "4.1339,3.14789\n"
    "4.1932,3.22378\n"
    "4.2547,3.29893\n"
    "4.3156,3.37426\n"
    "4.3731,3.45082\n"
    "4.4305,3.52738\n"
    "4.4892,3.60349\n"
    "4.5486,3.67938\n";
    
  QString outputGot;
  bool success = checkCommasInRelationsForDelimiter (EXPORT_DELIMITER_COMMA,
                                                     QLocale::UnitedStates,
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }

  QVERIFY (outputGot == outputExpected);
}

void TestExport::testCommasInRelationsForTabsSwitzerland ()
{
  QString outputExpectedIfCommaSeparator =
    "x\tCurve1\n"
    "3,3192\t2,08003\n"
    "3,3723\t2,15796\n"
    "3,432\t2,23368\n"
    "3,4935\t2,30883\n"
    "3,5539\t2,38438\n"
    "3,6113\t2,46094\n"
    "3,6687\t2,5375\n"
    "3,7261\t2,61406\n"
    "3,7836\t2,69062\n"
    "3,841\t2,76718\n"
    "3,9012\t2,84276\n"
    "3,9628\t2,91791\n"
    "4,0231\t2,99345\n"
    "4,0785\t3,07067\n"
    "4,1339\t3,14789\n"
    "4,1932\t3,22378\n"
    "4,2547\t3,29893\n"
    "4,3156\t3,37426\n"
    "4,3731\t3,45082\n"
    "4,4305\t3,52738\n"
    "4,4892\t3,60349\n"
    "4,5486\t3,67938\n";
  QString outputExpectedIfPeriodSeparator =
    "x\tCurve1\n"
    "3.3192\t2.08003\n"
    "3.3723\t2.15796\n"
    "3.432\t2.23368\n"
    "3.4935\t2.30883\n"
    "3.5539\t2.38438\n"
    "3.6113\t2.46094\n"
    "3.6687\t2.5375\n"
    "3.7261\t2.61406\n"
    "3.7836\t2.69062\n"
    "3.841\t2.76718\n"
    "3.9012\t2.84276\n"
    "3.9628\t2.91791\n"
    "4.0231\t2.99345\n"
    "4.0785\t3.07067\n"
    "4.1339\t3.14789\n"
    "4.1932\t3.22378\n"
    "4.2547\t3.29893\n"
    "4.3156\t3.37426\n"
    "4.3731\t3.45082\n"
    "4.4305\t3.52738\n"
    "4.4892\t3.60349\n"
    "4.5486\t3.67938\n";
  
  QString outputGot;
  bool success = checkCommasInRelationsForDelimiter (EXPORT_DELIMITER_TAB,
                                                     QLocale::Switzerland,
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }

  QVERIFY (outputGot == outputExpectedIfCommaSeparator ||
	   outputGot == outputExpectedIfPeriodSeparator);
}

void TestExport::testCommasInRelationsForTabsUnitedStates ()
{
  QString outputExpected =
    "x\tCurve1\n"
    "3.3192\t2.08003\n"
    "3.3723\t2.15796\n"
    "3.432\t2.23368\n"
    "3.4935\t2.30883\n"
    "3.5539\t2.38438\n"
    "3.6113\t2.46094\n"
    "3.6687\t2.5375\n"
    "3.7261\t2.61406\n"
    "3.7836\t2.69062\n"
    "3.841\t2.76718\n"
    "3.9012\t2.84276\n"
    "3.9628\t2.91791\n"
    "4.0231\t2.99345\n"
    "4.0785\t3.07067\n"
    "4.1339\t3.14789\n"
    "4.1932\t3.22378\n"
    "4.2547\t3.29893\n"
    "4.3156\t3.37426\n"
    "4.3731\t3.45082\n"
    "4.4305\t3.52738\n"
    "4.4892\t3.60349\n"
    "4.5486\t3.67938\n";
  
  QString outputGot;
  bool success = checkCommasInRelationsForDelimiter (EXPORT_DELIMITER_TAB,
                                                     QLocale::UnitedStates,
                                                     outputGot);
  if (!success) {
    outputGot = "";
  }

  QVERIFY (outputGot == outputExpected);
}

void TestExport::testExportOnlyNonRegressionLowerCase ()
{
  m_mainWindow->m_isErrorReportRegressionTest = NO_REGRESSION_IMPORT;
  m_mainWindow->setCurrentFile (STARTUP_DIG_LOWER_CASE);
  
  QString outputGot = m_mainWindow->fileNameForExportOnly ();
  QString outputWanted = STARTUP_DIG_LOWER_CASE;
  outputWanted = outputWanted.replace (".dig", ".csv");
  
  QVERIFY (outputGot == outputWanted);
}

void TestExport::testExportOnlyNonRegressionUpperCase ()
{
  m_mainWindow->m_isErrorReportRegressionTest = NO_REGRESSION_IMPORT;
  m_mainWindow->setCurrentFile (STARTUP_DIG_UPPER_CASE);
  
  QString outputGot = m_mainWindow->fileNameForExportOnly ();
  QString outputWanted = STARTUP_DIG_UPPER_CASE;
  outputWanted = outputWanted.replace (".DIG", ".csv");
  
  QVERIFY (outputGot == outputWanted);
}

void TestExport::testExportOnlyRegressionLowerCase ()
{
  m_mainWindow->m_isErrorReportRegressionTest = REGRESSION_IMPORT;
  m_mainWindow->m_regressionFile = STARTUP_DIG_LOWER_CASE;
  
  QString outputGot = m_mainWindow->fileNameForExportOnly ();
  QString outputWanted = STARTUP_DIG_LOWER_CASE;
  outputWanted = outputWanted.replace (".dig", ".csv_actual_1");
  
  QVERIFY (outputGot == outputWanted);
}

void TestExport::testExportOnlyRegressionUpperCase ()
{
  m_mainWindow->m_isErrorReportRegressionTest = REGRESSION_IMPORT;
  m_mainWindow->m_regressionFile = STARTUP_DIG_UPPER_CASE;

  QString outputGot = m_mainWindow->fileNameForExportOnly ();
  QString outputWanted = STARTUP_DIG_UPPER_CASE;
  outputWanted = outputWanted.replace (".DIG", ".csv_actual_1");
  
  QVERIFY (outputGot == outputWanted);
}

void TestExport::testLogExtrapolationFunctionsAll ()
{
  initData (true,
            EXPORT_DELIMITER_COMMA,
            QLocale::UnitedStates);
  
  bool success = true;
  QString dummy;
  QTextStream str (&dummy);
  
  try {
    bool isLogXTheta = (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LOG);
    bool isLogYRadius = (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG);
    unsigned int numWritesSoFar = 0;
    
    ExportFileFunctions exportFile;    
    exportFile.exportAllPerLineXThetaValuesMerged (m_modelExportOverride,
                                                   *m_document,
                                                   m_modelMainWindow,
                                                   m_curvesIncluded,
                                                   m_xThetaValues,
                                                   " ",
                                                   m_transformation,
                                                   isLogXTheta,
                                                   isLogYRadius,
                                                   str,
                                                   numWritesSoFar);
  }
  catch (...)
  {
    success = false;
  }

  QVERIFY (success);
}
