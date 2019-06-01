#include "FittingStatistics.h"
#include "Logger.h"
#include "MainWindow.h"
#include <qmath.h>
#include <QPointF>
#include <QtTest/QtTest>
#include "Test/TestFitting.h"

QTEST_MAIN (TestFitting)

using namespace std;

const int NOMINAL_ORDER = 6;
const int NOMINAL_SIGNIFICANT_DIGITS = 7;

TestFitting::TestFitting(QObject *parent) :
  QObject(parent)
{
}

void TestFitting::cleanupTestCase ()
{

}

bool TestFitting::generalFunctionTest (int order,
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
                                          rSquared,
                                          NOMINAL_SIGNIFICANT_DIGITS);

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

bool TestFitting::generalNonFunctionTest () const
{
  const double EPSILON = 0.0001;
  FittingStatistics fitting;
  double mse, rms, rSquared;
  FittingCurveCoefficients coefficientsGot (MAX_POLYNOMIAL_ORDER);

  // Create the points according to y = 0 + 1 * (x + 1) (x + 2) ... (x + order), with y=0 for order=0
  FittingPointsConvenient points;
  const double Y1 = 1, Y2 = 2;
  points.append (QPointF (1, Y1));
  points.append (QPointF (1, Y2));
    
  fitting.calculateCurveFitAndStatistics (1,
                                          points,
                                          coefficientsGot,
                                          mse,
                                          rms,
                                          rSquared,
                                          NOMINAL_SIGNIFICANT_DIGITS);

  bool success = true;

  // Expected coefficients are hardcoded
  FittingCurveCoefficients coefficientsExpected (2);
  coefficientsExpected [0] = (Y1 + Y2) / 2.0;
  coefficientsExpected [1] = 0;

  for (int coef = 0; coef < 2; coef++) {
    double coefGot = coefficientsGot [coef];

    double coefExpected = coefficientsExpected [coef];

    success = (success && ((qAbs (coefGot - coefExpected) < EPSILON)));
  }

  return success;
}

void TestFitting::initTestCase ()
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

int TestFitting::orderReducedVersusOrderAndSignificantDigits (int order,
                                                              int significantDigits) const
{
  FittingPointsConvenient points;
  FittingCurveCoefficients coefficients (MAX_POLYNOMIAL_ORDER + 1);

  // Hyperbola points
  FittingStatistics fittingStatistics;    
  for (double x = 1; x <= 10; x += 1) {
    double y = 100.0 / x;
    points.append (QPointF (x, y));
  }
  
  fittingStatistics.calculateCurveFit (order,
                                       points,
                                       coefficients,
                                       significantDigits);

  // Find first nonzero coefficient. Two cases for 0th order are y<>0 (not all coefficients are zero)
  // and y=0 (all coefficients are zero). In all other cases the order is the highest nonzero coefficient
  int orderReduced;
  for (orderReduced = MAX_POLYNOMIAL_ORDER; orderReduced > 0; orderReduced--) {
    if (coefficients [orderReduced] != 0) {
      return orderReduced;
    }
  }
  
  return orderReduced;
}

void TestFitting::testFunctionExactFit01 ()
{
  QVERIFY (generalFunctionTest (0, 1));
}

void TestFitting::testFunctionExactFit12 ()
{
  QVERIFY (generalFunctionTest (1, 2));
}

void TestFitting::testFunctionExactFit23 ()
{
  QVERIFY (generalFunctionTest (2, 3));
}

void TestFitting::testFunctionExactFit34 ()
{
  QVERIFY (generalFunctionTest (3, 4));
}

void TestFitting::testFunctionOverfit11 ()
{
  QVERIFY (generalFunctionTest (1, 1));
}

void TestFitting::testFunctionOverfit22 ()
{
  QVERIFY (generalFunctionTest (2, 2));
}

void TestFitting::testFunctionOverfit33 ()
{
  QVERIFY (generalFunctionTest (3, 3));
}

void TestFitting::testFunctionOverfit44 ()
{
  QVERIFY (generalFunctionTest (4, 4));
}

void TestFitting::testFunctionUnderfit02 ()
{
  QVERIFY (generalFunctionTest (0, 2));
}

void TestFitting::testFunctionUnderfit13 ()
{
  QVERIFY (generalFunctionTest (1, 3));
}

void TestFitting::testFunctionUnderfit24 ()
{
  QVERIFY (generalFunctionTest (2, 4));
}

void TestFitting::testFunctionUnderfit35 ()
{
  QVERIFY (generalFunctionTest (3, 5));
}

void TestFitting::testNonFunction ()
{
  QVERIFY (generalNonFunctionTest ());
}

void TestFitting::testOrderReduced3 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (3, NOMINAL_SIGNIFICANT_DIGITS) == 3);
}

void TestFitting::testOrderReduced4 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (4, NOMINAL_SIGNIFICANT_DIGITS) == 4);
}

void TestFitting::testOrderReduced5 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (5, NOMINAL_SIGNIFICANT_DIGITS) == 5);
}

void TestFitting::testOrderReduced6 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (6, NOMINAL_SIGNIFICANT_DIGITS) == 6);
}

void TestFitting::testSignificantDigits3 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (NOMINAL_ORDER, 3) == NOMINAL_ORDER);
}

void TestFitting::testSignificantDigits4 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (NOMINAL_ORDER, 4) == NOMINAL_ORDER);
}

void TestFitting::testSignificantDigits5 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (NOMINAL_ORDER, 5) == NOMINAL_ORDER);
}

void TestFitting::testSignificantDigits6 ()
{
  QVERIFY (orderReducedVersusOrderAndSignificantDigits (NOMINAL_ORDER, 6) == NOMINAL_ORDER);
}
