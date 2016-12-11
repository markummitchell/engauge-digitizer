#include "FittingStatistics.h"
#include "Logger.h"
#include "MainWindow.h"
#include <qmath.h>
#include <QPointF>
#include <QtTest/QtTest>
#include "Test/TestFitting.h"

QTEST_MAIN (TestFitting)

using namespace std;

TestFitting::TestFitting(QObject *parent) :
  QObject(parent)
{
}

void TestFitting::cleanupTestCase ()
{

}

bool TestFitting::generalTest (int order,
                               int numPoints) const
{
  int orderReduced = qMin (order, numPoints - 1);
  
  const double EPSILON = 0.0001;
  FittingStatistics fitting;
  double mse, rms, rSquared;
  FittingCurveCoefficients coefficientsGot (MAX_POLYNOMIAL_ORDER + 1);

  // Overfitting or underfitting?
  bool isOverfitting = (order >= numPoints - 1);
  
  // Create the points according to y = 0 + 1 * (x + 1) (x + 2) ... (x + order), with y=0 for order=0
  FittingPointsConvenient points;
  for (int iPoint = 0; iPoint < numPoints; iPoint++) {
    double x = iPoint; //  Pick arbitrary x values that are near the zeros
    double y = 0;
    if (orderReduced > 0) {
      y = 1; // Multiply this by successive terms
      for (int ord = 0; ord < orderReduced; ord++) {
        y *= (x + ord + 1);
      }
    }

    points.append (QPointF (x, y));
  }
    
  fitting.calculateCurveFitAndStatistics (order,
                                          points,
                                          coefficientsGot,
                                          mse,
                                          rms,
                                          rSquared);

  bool success = true;

  // Expected coefficients are hardcoded
  FittingCurveCoefficients coefficientsExpected (orderReduced + 1);
  switch (orderReduced)
  {
  case 0: // y=0
    coefficientsExpected [0] = 0;
    break;
  case 1: // y=(x+1)
    coefficientsExpected [0] = 1;
    coefficientsExpected [1] = 1;
    break;
  case 2: // y=(x+1)(x+2)
    coefficientsExpected [0] = 2;
    coefficientsExpected [1] = 3;
    coefficientsExpected [2] = 1;
    break;
  case 3: // y=(x+1)(x+2)(x+3)
    coefficientsExpected [0] = 6;
    coefficientsExpected [1] = 11;
    coefficientsExpected [2] = 6;    
    coefficientsExpected [3] = 1;    
    break;
  case 4: // y=(x+1)(x+2)(x+3)(x+4)
    coefficientsExpected [0] = 24;
    coefficientsExpected [1] = 50;
    coefficientsExpected [2] = 35;
    coefficientsExpected [3] = 10;        
    coefficientsExpected [4] = 1;
    break;
  }

  for (int coef = 0; coef < order + 1; coef++) {
    double coefGot = coefficientsGot [coef];

    double coefExpected = 0;
    if (coef <= orderReduced) {
      coefExpected = coefficientsExpected [coef];
    }
    
    success = (success && ((qAbs (coefGot - coefExpected) < EPSILON)));
  }
  
  if (isOverfitting) {
    // Overfitting case should always have an error of zero
    success = (success && ((qAbs (mse) < EPSILON)));
  }
  
  return success;
}

void TestFitting::initTestCase ()
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

void TestFitting::testExactFit01 ()
{
  QVERIFY (generalTest (0, 1));
}

void TestFitting::testExactFit12 ()
{
  QVERIFY (generalTest (1, 2));
}

void TestFitting::testExactFit23 ()
{
  QVERIFY (generalTest (2, 3));
}

void TestFitting::testExactFit34 ()
{
  QVERIFY (generalTest (3, 4));
}

void TestFitting::testOverfit11 ()
{
  QVERIFY (generalTest (1, 1));
}

void TestFitting::testOverfit22 ()
{
  QVERIFY (generalTest (2, 2));
}

void TestFitting::testOverfit33 ()
{
  QVERIFY (generalTest (3, 3));
}

void TestFitting::testOverfit44 ()
{
  QVERIFY (generalTest (4, 4));
}

void TestFitting::testUnderfit02 ()
{
  QVERIFY (generalTest (0, 2));
}

void TestFitting::testUnderfit13 ()
{
  QVERIFY (generalTest (1, 3));
}

void TestFitting::testUnderfit24 ()
{
  QVERIFY (generalTest (2, 4));
}

void TestFitting::testUnderfit35 ()
{
  QVERIFY (generalTest (3, 5));
}
