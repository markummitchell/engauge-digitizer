#include "Logger.h"
#include "MainWindow.h"
#include <QtTest/QtTest>
#include "Test/TestGraphCoords.h"

QTEST_MAIN (TestGraphCoords)

TestGraphCoords::TestGraphCoords(QObject *parent) :
  QObject(parent)
{
}

void TestGraphCoords::cleanupTestCase ()
{

}

void TestGraphCoords::initTestCase ()
{
  initializeLogging ("engauge_test",
                     "engauge_test.log");

  MainWindow w;
  w.show ();
}

void TestGraphCoords::testThreeGoodPoints ()
{
  QVERIFY (false);
}

void TestGraphCoords::testThreeCollinearPoints ()
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
