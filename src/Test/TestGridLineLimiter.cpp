#include "DocumentModelCoords.h"
#include "GridLineLimiter.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <qmath.h>
#include <QtTest/QtTest>
#include "Test/TestGridLineLimiter.h"
#include "Transformation.h"

QTEST_MAIN (TestGridLineLimiter)

using namespace std;

TestGridLineLimiter::TestGridLineLimiter(QObject *parent) :
  QObject(parent)
{
}

void TestGridLineLimiter::cleanupTestCase ()
{
}

void TestGridLineLimiter::initTestCase ()
{
  const bool NO_DROP_REGRESSION = false;
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool NO_RESET = false;
  const bool NO_EXPORT_ONLY = false;
  const bool NO_EXTRACT_IMAGE_ONLY = false;
  const QString NO_EXTRACT_IMAGE_EXTENSION;
  const bool DEBUG_FLAG = false;
  const QStringList NO_LOAD_STARTUP_FILES;
  const QStringList NO_COMMAND_LINE;
  
  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow w (NO_ERROR_REPORT_LOG_FILE,
                NO_REGRESSION_OPEN_FILE,
                NO_DROP_REGRESSION,
                NO_REGRESSION_IMPORT,                
                NO_GNUPLOT_LOG_FILES,
                NO_RESET,
                NO_EXPORT_ONLY,
                NO_EXTRACT_IMAGE_ONLY,
                NO_EXTRACT_IMAGE_EXTENSION,
                NO_LOAD_STARTUP_FILES,
                NO_COMMAND_LINE);
  w.show ();
}

void TestGridLineLimiter::testBadStepLinearX ()
{
  bool success = testLinearX (0,
                              0, // Bad
                              100,
                              10,
                              0.001, 0.001,
                              1000, 0.001,
                              0.001, 1000);

  QVERIFY (success);
}

void TestGridLineLimiter::testBadStepLinearY ()
{
  bool success = testLinearY (0,
                              0, // Bad
                              100,
                              10,
                              0.001, 0.001,
                              1000, 0.001,
                              0.001, 1000);

  QVERIFY (success);
}

void TestGridLineLimiter::testBadStepLogX ()
{
  bool success = testLogX (0, // Bad
                           1, // Bad
                           100,
                           10,
                           0.001, 0.001,
                           1000, 0.001,
                           0.001, 1000);

  QVERIFY (success);
}

void TestGridLineLimiter::testBadStepLogY ()
{
  bool success = testLogY (0, // Bad
                           1, // Bad
                           100,
                           10,
                           0.001, 0.001,
                           1000, 0.001,
                           0.001, 1000);

  QVERIFY (success);
}

bool TestGridLineLimiter::testLinearX (double start,
                                       double step,
                                       double stop,
                                       unsigned int num,
                                       double x1, double y1,
                                       double x2, double y2,
                                       double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  Transformation transformation;

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LINEAR);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForXTheta (document,
                          transformation,
                          modelCoords,
                          modelMainWindow,
                          start,
                          step,
                          stop,
                          num);

  bool success = true;

  if (step > 0) {

    int gridLineCount = 1 + (stop - start) / step;
    success = (gridLineCount <= 20);

  } else {

    success = (start == stop);

  }

  return success;
}

bool TestGridLineLimiter::testLinearY (double start,
                                       double step,
                                       double stop,
                                       unsigned int num,
                                       double x1, double y1,
                                       double x2, double y2,
                                       double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  Transformation transformation;

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LINEAR);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForYRadius (document,
                           transformation,
                           modelCoords,
                           modelMainWindow,
                           start,
                           step,
                           stop,
                           num);

  bool success = true;

  if (step > 0) {

    int gridLineCount = 1 + (stop - start) / step;
    success = (gridLineCount <= 20);

  } else {

    success = (start == stop);

  }

  return success;
}

bool TestGridLineLimiter::testLogX (double start,
                                    double step,
                                    double stop,
                                    unsigned int num,
                                    double x1, double y1,
                                    double x2, double y2,
                                    double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  Transformation transformation;

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForXTheta (document,
                          transformation,
                          modelCoords,
                          modelMainWindow,
                          start,
                          step,
                          stop,
                          num);

  bool success = (start > 0) && (step > 0);

  if (success) {

    int gridLineCount = 1 + (qLn (stop) - qLn (start)) / qLn (step);
    success = (gridLineCount <= 20);

  }

  return success;
}

bool TestGridLineLimiter::testLogY (double start,
                                    double step,
                                    double stop,
                                    unsigned int num,
                                    double x1, double y1,
                                    double x2, double y2,
                                    double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  Transformation transformation;

  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForYRadius (document,
                           transformation,
                           modelCoords,
                           modelMainWindow,
                           start,
                           step,
                           stop,
                           num);

  bool success = (start > 0) && (step > 0);

  if (success) {

    int gridLineCount = 1 + (qLn (stop) - qLn (start)) / qLn (step);
    success = (gridLineCount <= 20);

  }

  return success;
}

void TestGridLineLimiter::testTransitionLinearToLogX ()
{
  bool success = testLogX (0,
                           250,
                           1000,
                           10,
                           0.001, 0.001,
                           1000, 0.001,
                           0.001, 1000);

  QVERIFY (success);
}

void TestGridLineLimiter::testTransitionLinearToLogY ()
{
  bool success = testLogY (0,
                           250,
                           1000,
                           10,                           
                           0.001, 0.001,
                           1000, 0.001,
                           0.001, 1000);

  QVERIFY (success);
}
