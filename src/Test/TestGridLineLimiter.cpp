#include "DocumentModelCoords.h"
#include "DocumentModelGridDisplay.h"
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

void TestGridLineLimiter::testBadStepLinearX ()
{
  bool success = testLinearX (0,
                              0, // Bad
                              100,
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
                           0.001, 0.001,
                           1000, 0.001,
                           0.001, 1000);

  QVERIFY (success);
}

bool TestGridLineLimiter::testLinearX (double start,
                                       double step,
                                       double stop,
                                       double x1, double y1,
                                       double x2, double y2,
                                       double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  DocumentModelGridDisplay modelGrid;
  Transformation transformation;
  double startX, stepX, stopX; // Outputs from GridLineLimiter

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LINEAR);
  modelGrid.setStartX (start);
  modelGrid.setStepX (step);
  modelGrid.setStopX (stop);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForXTheta (document,
                          transformation,
                          modelCoords,
                          modelMainWindow,
                          modelGrid,
                          startX,
                          stepX,
                          stopX);

  bool success = true;

  if (stepX > 0) {

    int gridLineCount = 1 + (stopX - startX) / stepX;
    success = (gridLineCount <= 20);

  } else {

    success = (startX == stopX);

  }

  return success;
}

bool TestGridLineLimiter::testLinearY (double start,
                                       double step,
                                       double stop,
                                       double x1, double y1,
                                       double x2, double y2,
                                       double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  DocumentModelGridDisplay modelGrid;
  Transformation transformation;
  double startY, stepY, stopY; // Outputs from GridLineLimiter

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LINEAR);
  modelGrid.setStartY (start);
  modelGrid.setStepY (step);
  modelGrid.setStopY (stop);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForYRadius (document,
                           transformation,
                           modelCoords,
                           modelMainWindow,
                           modelGrid,
                           startY,
                           stepY,
                           stopY);

  bool success = true;

  if (stepY > 0) {

    int gridLineCount = 1 + (stopY - startY) / stepY;
    success = (gridLineCount <= 20);

  } else {

    success = (startY == stopY);

  }

  return success;
}

bool TestGridLineLimiter::testLogX (double start,
                                    double step,
                                    double stop,
                                    double x1, double y1,
                                    double x2, double y2,
                                    double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  DocumentModelGridDisplay modelGrid;
  Transformation transformation;
  double startX, stepX, stopX; // Outputs from GridLineLimiter

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
  modelGrid.setStartX (start);
  modelGrid.setStepX (step);
  modelGrid.setStopX (stop);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForXTheta (document,
                          transformation,
                          modelCoords,
                          modelMainWindow,
                          modelGrid,
                          startX,
                          stepX,
                          stopX);

  bool success = (startX > 0) && (stepX > 0);

  if (success) {

    int gridLineCount = 1 + (qLn (stopX) - qLn (startX)) / qLn (stepX);
    success = (gridLineCount <= 20);

  }

  return success;
}

bool TestGridLineLimiter::testLogY (double start,
                                    double step,
                                    double stop,
                                    double x1, double y1,
                                    double x2, double y2,
                                    double x3, double y3)
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  DocumentModelGridDisplay modelGrid;
  Transformation transformation;
  double startY, stepY, stopY; // Outputs from GridLineLimiter

  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  modelGrid.setStartY (start);
  modelGrid.setStepY (step);
  modelGrid.setStopY (stop);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (x1, y1), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF (x2, y2), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (x3, y3), QString ("axis3"), 0.0, false);

  limiter.limitForYRadius (document,
                           transformation,
                           modelCoords,
                           modelMainWindow,
                           modelGrid,
                           startY,
                           stepY,
                           stopY);

  bool success = (startY > 0) && (stepY > 0);

  if (success) {

    int gridLineCount = 1 + (qLn (stopY) - qLn (startY)) / qLn (stepY);
    success = (gridLineCount <= 20);

  }

  return success;
}

void TestGridLineLimiter::testTransitionLinearToLogX ()
{
  bool success = testLogX (0,
                           250,
                           1000,
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
                           0.001, 0.001,
                           1000, 0.001,
                           0.001, 1000);

  QVERIFY (success);
}
