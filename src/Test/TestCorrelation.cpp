#include "Correlation.h"
#include "Logger.h"
#include "MainWindow.h"
#include <qmath.h>
#include <QtTest/QtTest>
#include "Test/TestCorrelation.h"

QTEST_MAIN (TestCorrelation)

TestCorrelation::TestCorrelation(QObject *parent) :
  QObject(parent)
{
}

void TestCorrelation::cleanupTestCase ()
{
}

void TestCorrelation::initTestCase ()
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

void TestCorrelation::loadSinusoid (double function [],
                                    int n,
                                    int center) const
{
  for (int i = 0; i < n; i++) {
    int x = i - center;
    if (x == 0)  {
      function [i] = 1.0;
    } else {
      function [i] = qSin (x) / x;
    }
  }
}

void TestCorrelation::loadThreeTriangles (double function [],
                                          int n,
                                          int center) const
{
  const int PEAK_SEPARATION = 50, PEAK_HALF_WIDTH = 5;

  int x;
  for (int i = 0; i < n; i++) {

    // First try for peak at center
    x = i - center;
    if (x > PEAK_HALF_WIDTH) {

      // Failed, so try again for peak at center-separation
      x = i - (center - PEAK_SEPARATION);
      if (x > PEAK_HALF_WIDTH) {

        // Failed, so try again for peak at center+separation
        x = i - (center + PEAK_SEPARATION);
      }
    }

    if (x < PEAK_HALF_WIDTH) {

      // Map 0<x<PEAK_HALF_WIDTH to 1<function<0
      function [i] = (double) (PEAK_HALF_WIDTH - x) / (double) PEAK_HALF_WIDTH;

    } else {

      function [i] = 0;
    }
  }
}

void TestCorrelation::testShiftSinusoidNonPowerOf2 ()
{
  const int N = 1000; // Non power of  2
  const int INDEX_MAX = 200, INDEX_SHIFT = 50;

  int binStartMax;
  double function1 [N], function2 [N], correlations [N];
  double corrMax;

  Correlation correlation (N);

  // Function1 peak is at INDEX_MAX
  // Function2 peak is at INDEX_MAX + INDEX_SHIFT
  loadSinusoid (function1, N, INDEX_MAX);
  loadSinusoid (function2, N, INDEX_MAX + INDEX_SHIFT);

  correlation.correlateWithShift (N,
                                  function1,
                                  function2,
                                  binStartMax,
                                  corrMax,
                                  correlations);

  QVERIFY (binStartMax = INDEX_SHIFT);
}

void TestCorrelation::testShiftSinusoidPowerOf2 ()
{
  const int N = 1024; // Power of  2
  const int INDEX_MAX = 200, INDEX_SHIFT = 50;

  int binStartMax;
  double function1 [N], function2 [N], correlations [N];
  double corrMax;

  Correlation correlation (N);

  // Function1 peak is at INDEX_MAX
  // Function2 peak is at INDEX_MAX + INDEX_SHIFT
  loadSinusoid (function1, N, INDEX_MAX);
  loadSinusoid (function2, N, INDEX_MAX + INDEX_SHIFT);

  correlation.correlateWithShift (N,
                                  function1,
                                  function2,
                                  binStartMax,
                                  corrMax,
                                  correlations);

  QVERIFY (binStartMax = INDEX_SHIFT);
}

void TestCorrelation::testShiftThreeTrianglesNonPowerOf2 ()
{
  const int N = 1000; // Non power of  2
  const int INDEX_MAX = 200, INDEX_SHIFT = 50;

  int binStartMax;
  double function1 [N], function2 [N], correlations [N];
  double corrMax;

  Correlation correlation (N);

  // Function1 peak is at INDEX_MAX
  // Function2 peak is at INDEX_MAX + INDEX_SHIFT
  loadThreeTriangles (function1, N, INDEX_MAX);
  loadThreeTriangles (function2, N, INDEX_MAX + INDEX_SHIFT);

  correlation.correlateWithShift (N,
                                  function1,
                                  function2,
                                  binStartMax,
                                  corrMax,
                                  correlations);

  QVERIFY (binStartMax = INDEX_SHIFT);
}

void TestCorrelation::testShiftThreeTrianglesPowerOf2 ()
{
  const int N = 1024; // Power of  2
  const int INDEX_MAX = 200, INDEX_SHIFT = 50;

  int binStartMax;
  double function1 [N], function2 [N], correlations [N];
  double corrMax;

  Correlation correlation (N);

  // Function1 peak is at INDEX_MAX
  // Function2 peak is at INDEX_MAX + INDEX_SHIFT
  loadThreeTriangles (function1, N, INDEX_MAX);
  loadThreeTriangles (function2, N, INDEX_MAX + INDEX_SHIFT);

  correlation.correlateWithShift (N,
                                  function1,
                                  function2,
                                  binStartMax,
                                  corrMax,
                                  correlations);

  QVERIFY (binStartMax = INDEX_SHIFT);
}
