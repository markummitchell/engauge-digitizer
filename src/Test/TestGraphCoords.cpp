#include "CallbackUpdateTransform.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QtTest/QtTest>
#include "Test/TestGraphCoords.h"

QTEST_MAIN (TestGraphCoords)

TestGraphCoords::TestGraphCoords(QObject *parent) :
  QObject(parent)
{
  m_callback = new CallbackUpdateTransform (m_modelCoords,
                                            DOCUMENT_AXES_POINTS_REQUIRED_3);
}

void TestGraphCoords::cleanupTestCase ()
{
}

void TestGraphCoords::initTestCase ()
{
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool DEBUG_FLAG = false;
  const QStringList NO_LOAD_STARTUP_FILES;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow w (NO_ERROR_REPORT_LOG_FILE,
                NO_REGRESSION_OPEN_FILE,
                NO_GNUPLOT_LOG_FILES,
                NO_REGRESSION_IMPORT,
                NO_LOAD_STARTUP_FILES);
  w.show ();
}

void TestGraphCoords::testAnyColumnsRepeatNo ()
{
  CoordPairVector vector;

  vector.push_back (QPointF (100, 100));
  vector.push_back (QPointF (300, 100));
  vector.push_back (QPointF (200, 200));

  QVERIFY (!m_callback->anyPointsRepeatPair (vector));
}

void TestGraphCoords::testAnyColumnsRepeatYes ()
{
  CoordPairVector vector;

  // First two points repeat
  vector.push_back (QPointF (100, 100));
  vector.push_back (QPointF (100, 100));
  vector.push_back (QPointF (200, 200));

  QVERIFY (m_callback->anyPointsRepeatPair (vector));
}

void TestGraphCoords::testThreeCollinearPointsNo ()
{
  // Points are not collinear
  QTransform m (100, 300, 200,
                100, 150, 200,
                1  , 1  , 1  );

  QVERIFY (!m_callback->threePointsAreCollinear (m));
}

void TestGraphCoords::testThreeCollinearPointsYes ()
{
  // Points are collinear
  QTransform m (100, 150, 200,
                100, 150, 200,
                1  , 1  , 1  );

  QVERIFY (m_callback->threePointsAreCollinear (m));
}
