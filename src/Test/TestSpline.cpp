#include "Logger.h"
#include "MainWindow.h"
#include <qmath.h>
#include <QtTest/QtTest>
#include "Spline.h"
#include "SplinePair.h"
#include "Test/TestSpline.h"

QTEST_MAIN (TestSpline)

using namespace std;

TestSpline::TestSpline(QObject *parent) :
  QObject(parent)
{
}

void TestSpline::cleanupTestCase ()
{

}

void TestSpline::initTestCase ()
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

void TestSpline::testSplinesAsControlPoints ()
{
  const int T_START = 1, T_STOP = 7;
  const double SPLINE_EPSILON = 0.01;
  const int NUM_T = 60;

  bool success = true;

  vector<double> t;
  vector<SplinePair> xy;
  
  // Independent variable must be evenly spaced
  t.push_back (T_START);
  t.push_back (2);
  t.push_back (3);
  t.push_back (4);
  t.push_back (5);
  t.push_back (6);
  t.push_back (T_STOP);

  // Simple curve, with x values tweaked slightly (from even spacing) to make the test data more stressing
  xy.push_back (SplinePair (1, 0.22));
  xy.push_back (SplinePair (1.8, 0.04));
  xy.push_back (SplinePair (3.2, -0.13));
  xy.push_back (SplinePair (4.3, -0.17));
  xy.push_back (SplinePair (5, -0.04));
  xy.push_back (SplinePair (5.8, 0.09));
  xy.push_back (SplinePair (7, 0.11));

  Spline s (t, xy);

  for (int i = 0; i <= NUM_T; i++) {
    double t = T_START + (double) i * (T_STOP - T_START) / (double) NUM_T;
    SplinePair spCoeff = s.interpolateCoeff (t);
    SplinePair spBezier = s.interpolateControlPoints (t);

    double xCoeff = spCoeff.x();
    double yCoeff = spCoeff.y();
    double xControl = spBezier.x();
    double yControl = spBezier.y();

    if (qAbs (xCoeff - xControl) > SPLINE_EPSILON) {
      success = false;
    }

    if (qAbs (yCoeff - yControl) > SPLINE_EPSILON) {
      success = false;
    }
  }

  QVERIFY (success);
}
