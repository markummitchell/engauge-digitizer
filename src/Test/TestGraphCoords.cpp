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
  const bool DEBUG_FLAG = false;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow w (NO_ERROR_REPORT_LOG_FILE);
  w.show ();
}

void TestGraphCoords::testThreeCollinearPoints ()
{
  QVERIFY (false);
}

void TestGraphCoords::testThreeGoodPoints ()
{
  QVERIFY (false);
}

void TestGraphCoords::testTwoPointsSharingGraphCoords ()
{
  QVERIFY (true);
}

void TestGraphCoords::testTwoPointsSharingScreenCoords ()
{
  QCOMPARE (3, 5);
}
