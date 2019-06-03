#include "Logger.h"
#include "MainWindow.h"
#include <QtTest/QtTest>
#include "Test/TestZoomTransition.h"
#include "ZoomTransition.h"

QTEST_MAIN (TestZoomTransition)

using namespace std;

const bool FILL_CHECKED = true;
const bool FILL_UNCHECKED = false;
const double M11 = 1.9;
const double M22 = 1.49;

TestZoomTransition::TestZoomTransition(QObject *parent) :
  QObject(parent)
{
}

void TestZoomTransition::cleanupTestCase ()
{

}

void TestZoomTransition::initTestCase ()
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

void TestZoomTransition::testInAtClosestEnum ()
{
  ZoomTransition zoomTransition;
  ZoomFactor zoomFactorNew = zoomTransition.zoomIn (ZOOM_16_TO_1,
                                                    M11,
                                                    M22,
                                                    FILL_UNCHECKED);

  // Should be unchanged since cannot go further
  QVERIFY (zoomFactorNew == ZOOM_16_TO_1);
}

void TestZoomTransition::testInBeforeClosestFromEnum ()
{
  ZoomTransition zoomTransition;
  ZoomFactor zoomFactorNew = zoomTransition.zoomIn (ZOOM_1_TO_1,
                                                    M11,
                                                    M22,
                                                    FILL_UNCHECKED);

  QVERIFY (zoomFactorNew == ZOOM_1_TO_1_CLOSER);
}

void TestZoomTransition::testInBeforeClosestFromFill ()
{
  ZoomTransition zoomTransition;
  ZoomFactor zoomFactorNew = zoomTransition.zoomIn (ZOOM_FILL,
                                                    M11,
                                                    M22,
                                                    FILL_CHECKED);

  QVERIFY (zoomFactorNew == ZOOM_2_TO_1);
}

void TestZoomTransition::testOutAtFarthestEnum ()
{
  ZoomTransition zoomTransition;
  ZoomFactor zoomFactorNew = zoomTransition.zoomOut (ZOOM_1_TO_16,
                                                     M11,
                                                     M22,
                                                     FILL_UNCHECKED);

  // Should be unchanged since cannot go further
  QVERIFY (zoomFactorNew == ZOOM_1_TO_16);
}

void TestZoomTransition::testOutBeforeFarthestFromEnum ()
{
  ZoomTransition zoomTransition;
  ZoomFactor zoomFactorNew = zoomTransition.zoomOut (ZOOM_1_TO_1,
                                                     M11,
                                                     M22,
                                                     FILL_UNCHECKED);

  QVERIFY (zoomFactorNew == ZOOM_1_TO_1_FARTHER);
}

void TestZoomTransition::testOutBeforeFarthestFromFill ()
{
  ZoomTransition zoomTransition;
  ZoomFactor zoomFactorNew = zoomTransition.zoomOut (ZOOM_FILL,
                                                     M11,
                                                     M22,
                                                     FILL_CHECKED);

  QVERIFY (zoomFactorNew == ZOOM_1_TO_1_CLOSER);
}
