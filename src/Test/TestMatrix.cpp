#include "Logger.h"
#include "MainWindow.h"
#include <QtTest/QtTest>
#include "Test/TestMatrix.h"

QTEST_MAIN (TestMatrix)

TestMatrix::TestMatrix(QObject *parent) :
  QObject(parent)
{
}

void TestMatrix::cleanupTestCase ()
{
}

void TestMatrix::initTestCase ()
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

void TestMatrix::testDeterminant ()
{
  Matrix m (3);
  double a00 = 1, a01 = 2, a10 = 3, a11 = 4;
  
  m.set (0, 0, a00);
  m.set (0, 1, a01);
  m.set (1, 0, a10);
  m.set (1, 1, a11);
  QVERIFY (m.determinant () == a00 * a11 - a01 * a10);
}
