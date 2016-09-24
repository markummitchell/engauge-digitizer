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

void TestGridLineLimiter::testTransitionLinearToLogX ()
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  DocumentModelGridDisplay modelGrid;
  Transformation transformation;
  double startX, stepX; // Outputs from GridLineLimiter

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
  modelGrid.setStartX (0);
  modelGrid.setStopX (1000.0);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (0.001, 0.001), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF ( 1000, 0.001), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (0.001,  1000), QString ("axis3"), 0.0, false);

  limiter.limitForXTheta (document,
                          transformation,
                          modelCoords,
                          modelMainWindow,
                          modelGrid,
                          startX,
                          stepX);

  bool success = (startX > 0) && (stepX > 0);

  if (success) {

    bool stopX = modelGrid.stopX ();
    int gridLineCount = 1 + (qLn (stopX) - qLn (startX)) / qLn (stepX);
    success = (gridLineCount <= 20);

  }

  QVERIFY (success);
}

void TestGridLineLimiter::testTransitionLinearToLogY ()
{
  GridLineLimiter limiter;
  QImage image;
  Document document (image);
  DocumentModelCoords modelCoords;
  MainWindowModel modelMainWindow;
  DocumentModelGridDisplay modelGrid;
  Transformation transformation;
  double startY, stepY; // Outputs from GridLineLimiter

  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  modelGrid.setStartY (0);
  modelGrid.setStopY (1000.0);
  modelMainWindow.setMaximumGridLines (5);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  ,   0), QPointF (0.001, 0.001), QString ("axis1"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (100,   0), QPointF ( 1000, 0.001), QString ("axis2"), 0.0, false);
  document.addPointAxisWithSpecifiedIdentifier (QPointF (0  , 100), QPointF (0.001,  1000), QString ("axis3"), 0.0, false);

  limiter.limitForYRange (document,
                          transformation,
                          modelCoords,
                          modelMainWindow,
                          modelGrid,
                          startY,
                          stepY);

  bool success = (startY > 0) && (stepY > 0);

  if (success) {

    bool stopY = modelGrid.stopY ();
    int gridLineCount = 1 + (qLn (stopY) - qLn (startY)) / qLn (stepY);
    success = (gridLineCount <= 20);

  }

  QVERIFY (success);
}
