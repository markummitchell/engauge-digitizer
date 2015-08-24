#include "CallbackUpdateTransform.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QtTest/QtTest>
#include "Test/TestGraphCoords.h"

QTEST_MAIN (TestGraphCoords)

TestGraphCoords::TestGraphCoords(QObject *parent) :
  QObject(parent)
{
  m_callback = new CallbackUpdateTransform (m_modelCoords);
}

void TestGraphCoords::cleanupTestCase ()
{
}

void TestGraphCoords::initTestCase ()
{
  const QString NO_ERROR_REPORT_LOG_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool DEBUG_FLAG = false;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow w (NO_ERROR_REPORT_LOG_FILE,
                NO_GNUPLOT_LOG_FILES);
  w.show ();
}

void TestGraphCoords::testAnyColumnsRepeatNo ()
{
  double m [3] [3];

  // No points repeat
  m [0] [0] = 100;
  m [1] [0] = 100;
  m [2] [0] = 1;

  m [0] [1] = 300;
  m [1] [1] = 100;
  m [2] [1] = 1;

  m [0] [2] = 200;
  m [1] [2] = 200;
  m [2] [2] = 1;

  QVERIFY (!m_callback->anyColumnsRepeat (m, 3));
}

void TestGraphCoords::testAnyColumnsRepeatYes ()
{
  double m [3] [3];

  // First two points repeat
  m [0] [0] = 100;
  m [1] [0] = 100;
  m [2] [0] = 1;

  m [0] [1] = 100;
  m [1] [1] = 100;
  m [2] [1] = 1;

  m [0] [2] = 200;
  m [1] [2] = 200;
  m [2] [2] = 1;

  QVERIFY (m_callback->anyColumnsRepeat (m, 3));
}

void TestGraphCoords::testThreeCollinearPointsNo ()
{
  double m [3] [3];

  // Points are not collinear
  m [0] [0] = 100;
  m [1] [0] = 100;
  m [2] [0] = 1;

  m [0] [1] = 300;
  m [1] [1] = 150;
  m [2] [1] = 1;

  m [0] [2] = 200;
  m [1] [2] = 200;
  m [2] [2] = 1;

  QVERIFY (!m_callback->threePointsAreCollinear (m, 3));
}

void TestGraphCoords::testThreeCollinearPointsYes ()
{
  double m [3] [3];

  // Points are collinear
  m [0] [0] = 100;
  m [1] [0] = 100;
  m [2] [0] = 1;

  m [0] [1] = 150;
  m [1] [1] = 150;
  m [2] [1] = 1;

  m [0] [2] = 200;
  m [1] [2] = 200;
  m [2] [2] = 1;

  QVERIFY (m_callback->threePointsAreCollinear (m, 3));
}
