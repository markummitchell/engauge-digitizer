#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "Logger.h"
#include <QtTest/QtTest>
#include "Test/TestExportAlign.h"

QTEST_MAIN (TestExportAlign)

using namespace std;

const bool DEBUG_FLAG = false;

TestExportAlign::TestExportAlign(QObject *parent) :
  QObject(parent)
{
}

void TestExportAlign::cleanupTestCase ()
{
}

bool TestExportAlign::epsilonTest (double a,
                                   double b) const
{
  double epsilon = qMax (qAbs (a), qAbs (b)) / 100000.0;
  if (epsilon == 0) {
    epsilon = 1e-6;
  }

  return qAbs (a - b) <= epsilon;
}

void TestExportAlign::initTestCase ()
{
  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);
}

void TestExportAlign::testLinearDigits1 ()
{
  QVERIFY (testLinearGeneric (4, 6) == 4); // 4, 5, 6
}

void TestExportAlign::testLinearDigits2 ()
{
  QVERIFY (testLinearGeneric (4.4, 4.6) == 4.4); // 4.4, 4.5, 4.6
}

void TestExportAlign::testLinearDigits3 ()
{
  QVERIFY (testLinearGeneric (4.44, 4.46) == 4.44); // 4.44, 4.45, 4.46
}

double TestExportAlign::testLinearGeneric (double xMin,
                                           double xMax) const
{
  ExportAlignLinear align (xMin, xMax);
  return align.firstSimplestNumber ();
}

void TestExportAlign::testLinearHighDynamicRangeNegNeg ()
{
  QVERIFY (testLinearGeneric (-4.3, -0.002) == -5.0); // -5,-4,-3-,-2,-1,0,1
}

void TestExportAlign::testLinearHighDynamicRangeNegPos ()
{
  QVERIFY (testLinearGeneric (-0.002, 4.3) == -1.0); // -1,0,1,2,3,4,5
}

void TestExportAlign::testLinearHighDynamicRangePosPos ()
{
  QVERIFY (testLinearGeneric (0.002, 4.3) == 0.0); // 0,1,2,3,4,5
}

void TestExportAlign::testLinearLowDynamicRangeNegNeg ()
{
  QVERIFY (testLinearGeneric (-4.3, -0.2) == -5.0); // -5,-4,-3,-2,-1,0,1
}

void TestExportAlign::testLinearLowDynamicRangeNegPos ()
{
  QVERIFY (testLinearGeneric (-4.3, 0.2) == -5.0); // -5,-4,-3,-2,-1,0,1
}

void TestExportAlign::testLinearLowDynamicRangePosPos ()
{
  QVERIFY (testLinearGeneric (0.2, 4.3) == 0.0); // 0,1,2,3,4,5
}

void TestExportAlign::testLinearRelativelySmallRangeNeg ()
{
  QVERIFY (testLinearGeneric (-4.9995, -4.9993) == -4.9995); // -4.9995, -4.9994, -4.9993
}

void TestExportAlign::testLinearRelativelySmallRangePos ()
{
  QVERIFY (testLinearGeneric (4.9993, 4.9995) == 4.9993); // 4.9993, 4.9994, 4.9995
}

void TestExportAlign::testLogDigits1 ()
{
  QVERIFY (epsilonTest (testLogGeneric (4, 6), 4)); // 10^4, 10^5, 10^6
}

void TestExportAlign::testLogDigits2 ()
{
  QVERIFY (epsilonTest (testLogGeneric (4.4, 4.6), 4.4)); // 10^4.4, 10^4.5, 10^4.6
}

void TestExportAlign::testLogDigits3 ()
{
  QVERIFY (epsilonTest (testLogGeneric (4.44, 4.46), 4.44)); // 10^4.44, 10^4.45, 10^4.46
}

double TestExportAlign::testLogGeneric (double xMinExponent,
                                        double xMaxExponent) const
{
  double xMin = qPow (10.0, xMinExponent);
  double xMax = qPow (10.0, xMaxExponent);

  ExportAlignLog align (xMin, xMax);
  double result = align.firstSimplestNumber ();
  double resultExponent = qLn (result) / qLn (10.0);

  return resultExponent;
}

void TestExportAlign::testLogHighDynamicRangeNegNeg ()
{
  QVERIFY (epsilonTest (testLogGeneric (-4.3, -0.002), -5.0)); // -5,-4,-3-,-2,-1,0,1
}

void TestExportAlign::testLogHighDynamicRangeNegPos ()
{
  QVERIFY (epsilonTest (testLogGeneric (-0.002, 4.3), -1.0)); // -1,0,1,2,3,4,5
}

void TestExportAlign::testLogHighDynamicRangePosPos ()
{
  QVERIFY (epsilonTest (testLogGeneric (0.002, 4.3), 0.0)); // 0,1,2,3,4,5
}

void TestExportAlign::testLogLowDynamicRangeNegNeg ()
{
  QVERIFY (epsilonTest (testLogGeneric (-4.3, -0.2), -5.0)); // -5,-4,-3,-2,-1,0,1
}

void TestExportAlign::testLogLowDynamicRangeNegPos ()
{
  QVERIFY (epsilonTest (testLogGeneric (-4.3, 0.2), -5.0)); // -5,-4,-3,-2,-1,0,1
}

void TestExportAlign::testLogLowDynamicRangePosPos ()
{
  QVERIFY (epsilonTest (testLogGeneric (0.2, 4.3), 0.0)); // 0,1,2,3,4,5
}

void TestExportAlign::testLogRelativelySmallRangeNeg ()
{
  QVERIFY (epsilonTest (testLogGeneric (-4.9995, -4.9993), -4.9995)); // -4.9995, -4.9994, -4.9993
}

void TestExportAlign::testLogRelativelySmallRangePos ()
{
  QVERIFY (epsilonTest (testLogGeneric (4.9993, 4.9995), 4.9993)); // 4.9993, 4.9994, 4.9995
}
