#include "Logger.h"
#include "MainWindow.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QtTest/QtTest>
#include "Spline.h"
#include "SplinePair.h"
#include "Test/TestProjectedPoint.h"

QTEST_MAIN (TestProjectedPoint)

using namespace std;

const double PI = 3.1415926535;
const double RADIANS_TO_DEGREES = 180.0 / PI;

TestProjectedPoint::TestProjectedPoint(QObject *parent) :
  QObject(parent)
{
}

void TestProjectedPoint::cleanupTestCase ()
{

}

void TestProjectedPoint::initTestCase ()
{
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

void TestProjectedPoint::testProjectedPoints ()
{
  double radiusCircle = 1.0, radiusProjection = 2.0 * radiusCircle;
  double xToProjectRight = radiusProjection, yToProjectRight = 0.0;
  double xToProjectUp = 0.0, yToProjectUp = 2.0 * radiusCircle;
  double xProjectionRight, yProjectionRight, projectedDistanceOutsideLineRight;
  double xProjectionUp, yProjectionUp, projectedDistanceOutsideLineUp;
  double distanceToLine; // Ignored

  // To prevent ambiguity at multiples of angleCriticalRight and angleCriticalUp, the angle step is NOT a factor of the
  // critical angles
  int angleStep = 13;

  // Critical angle in degrees
  int angleCriticalRight = (int) (0.5 + qAcos (radiusCircle / radiusProjection) * RADIANS_TO_DEGREES);
  int angleCriticalUp = (int) (0.5 + qAsin (radiusCircle / radiusProjection) * RADIANS_TO_DEGREES);

  for (int angle = 0; angle <= 360; angle += angleStep) {

    double xStart = radiusCircle * cos (angle * PI / 180.0);
    double yStart = radiusCircle * sin (angle * PI / 180.0);
    double xStop = -1.0 * xStart;
    double yStop = -1.0 * yStart;

    double xMin = qMin (xStart, xStop);
    double yMin = qMin (yStart, yStop);
    double xMax = qMax (xStart, xStop);
    double yMax = qMax (yStart, yStop);

    // Project point on right
    projectPointOntoLine (xToProjectRight,
                          yToProjectRight,
                          xStart,
                          yStart,
                          xStop,
                          yStop,
                          &xProjectionRight,
                          &yProjectionRight,
                          &projectedDistanceOutsideLineRight,
                          &distanceToLine);

    // If and only if angle is between angleCritical to 180 - angleCritical, and 
    // 180 + angleCritical to 360 - angleCritical will there be a projection inside the line
    if ((angleCriticalRight <= angle && angle <= 180 - angleCriticalRight) ||
        (180 + angleCriticalRight <= angle && angle <= 360 - angleCriticalRight)) {

      QVERIFY ((projectedDistanceOutsideLineRight == 0));
    } else {
      QVERIFY ((projectedDistanceOutsideLineRight != 0));
    }
    QVERIFY ((xMin <= xProjectionRight));
    QVERIFY ((yMin <= yProjectionRight));
    QVERIFY ((xProjectionRight <= xMax));
    QVERIFY ((yProjectionRight <= yMax));

    // Project point that is up
    projectPointOntoLine (xToProjectUp,
                          yToProjectUp,
                          xStart,
                          yStart,
                          xStop,
                          yStop,
                          &xProjectionUp,
                          &yProjectionUp,
                          &projectedDistanceOutsideLineUp,
                          &distanceToLine);

    // If and only if angle is between -angleCritical to angleCritical, and 
    // 180 - angleCritical to 180 + angleCritical will there be a projection inside the line
    if ((angle <= angleCriticalUp) ||
        (180 - angleCriticalUp <= angle && angle <= 180 + angleCriticalUp) ||
        (360 - angleCriticalUp <= angle)) {

      QVERIFY ((projectedDistanceOutsideLineUp == 0));
    } else {
      QVERIFY ((projectedDistanceOutsideLineUp != 0));
    }
    QVERIFY ((xMin <= xProjectionUp));
    QVERIFY ((yMin <= yProjectionUp));
    QVERIFY ((xProjectionUp <= xMax));
    QVERIFY ((yProjectionUp <= yMax));
  }
}
