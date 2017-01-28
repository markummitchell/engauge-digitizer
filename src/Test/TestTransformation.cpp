#include "DocumentModelCoords.h"
#include "DocumentModelGeneral.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <qmath.h>
#include <QtTest/QtTest>
#include "Test/TestTransformation.h"
#include "Transformation.h"

QTEST_MAIN (TestTransformation)

const double EPSILON = 1.0;

using namespace std;

TestTransformation::TestTransformation(QObject *parent) :
  QObject(parent)
{
}

void TestTransformation::cleanupTestCase ()
{

}

double TestTransformation::differenceMagnitude (const QPointF &vector1,
                                                const QPointF &vector2) const
{
  QPointF difference = vector1 - vector2;
  return qSqrt (difference.x() * difference.x() +
                difference.y() * difference.y());
}
void TestTransformation::initTestCase ()
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

void TestTransformation::initTransformation (const QPointF &s0,
                                             const QPointF &s1,
                                             const QPointF &s2,
                                             const QPointF &g0,
                                             const QPointF &g1,
                                             const QPointF &g2,
                                             const DocumentModelCoords &modelCoords,
                                             const DocumentModelGeneral &modelGeneral)
{
  QTransform matrixScreen (s0.x(), s1.x(), s2.x(),
                           s0.y(), s1.y(), s2.y(),
                           1.0, 1.0, 1.0);
  QTransform matrixGraph (g0.x(), g1.x(), g2.x(),
                          g0.y(), g1.y(), g2.y(),
                          1.0, 1.0, 1.0);

  Transformation t;
  MainWindowModel mainWindowModel;
  t.setModelCoords (modelCoords,
                    modelGeneral,
                    mainWindowModel);
  t.updateTransformFromMatrices(matrixScreen,
                                matrixGraph);

  t.transformScreenToRawGraph (s0,
                               m_g0Transformed);
  t.transformScreenToRawGraph (s1,
                               m_g1Transformed);
  t.transformScreenToRawGraph (s2,
                               m_g2Transformed);
  t.transformRawGraphToScreen (g0,
                               m_s0Transformed);
  t.transformRawGraphToScreen (g1,
                               m_s1Transformed);
  t.transformRawGraphToScreen (g2,
                               m_s2Transformed);
}

DocumentModelCoords TestTransformation::modelCoordsDefault() const
{
  DocumentModelCoords modelCoords;

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LINEAR);
  modelCoords.setCoordScaleYRadius (COORD_SCALE_LINEAR);
  modelCoords.setCoordsType (COORDS_TYPE_CARTESIAN);
  modelCoords.setCoordUnitsDate(COORD_UNITS_DATE_YEAR_MONTH_DAY);
  modelCoords.setCoordUnitsRadius (COORD_UNITS_NON_POLAR_THETA_NUMBER);
  modelCoords.setCoordUnitsTheta (COORD_UNITS_POLAR_THETA_DEGREES);
  modelCoords.setCoordUnitsTime (COORD_UNITS_TIME_HOUR_MINUTE_SECOND);
  modelCoords.setCoordUnitsX (COORD_UNITS_NON_POLAR_THETA_NUMBER);
  modelCoords.setCoordUnitsY (COORD_UNITS_NON_POLAR_THETA_NUMBER);
  modelCoords.setOriginRadius (0.0);

  return modelCoords;
}

DocumentModelGeneral TestTransformation::modelGeneralDefault() const
{
  DocumentModelGeneral modelGeneral;

  modelGeneral.setCursorSize (5);
  modelGeneral.setExtraPrecision (1);

  return modelGeneral;
}

void TestTransformation::testCartesianLinearLinear ()
{
  QPointF s0 (10, 1000);
  QPointF s1 (1000, 1000);
  QPointF s2 (10, 10);
  QPointF g0 (1, 1);
  QPointF g1 (10, 1);
  QPointF g2 (1, 10);

  initTransformation (s0,
                      s1,
                      s2,
                      g0,
                      g1,
                      g2,
                      modelCoordsDefault(),
                      modelGeneralDefault());

  QVERIFY ((differenceMagnitude (s0, m_s0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s1, m_s1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s2, m_s2Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g0, m_g0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g1, m_g1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g2, m_g2Transformed) < EPSILON));
}

void TestTransformation::testCartesianLinearLog ()
{
  QPointF s0 (10, 1000);
  QPointF s1 (1000, 1000);
  QPointF s2 (10, 10);
  QPointF g0 (1, 1);
  QPointF g1 (10, 1);
  QPointF g2 (1, 10);

  DocumentModelCoords modelCoords = modelCoordsDefault();
  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  initTransformation (s0,
                      s1,
                      s2,
                      g0,
                      g1,
                      g2,
                      modelCoordsDefault(),
                      modelGeneralDefault());

  QVERIFY ((differenceMagnitude (s0, m_s0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s1, m_s1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s2, m_s2Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g0, m_g0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g1, m_g1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g2, m_g2Transformed) < EPSILON));
}

void TestTransformation::testCartesianLogLinear ()
{
  QPointF s0 (10, 1000);
  QPointF s1 (1000, 1000);
  QPointF s2 (10, 10);
  QPointF g0 (1, 1);
  QPointF g1 (10, 1);
  QPointF g2 (1, 10);

  DocumentModelCoords modelCoords = modelCoordsDefault();
  modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
  initTransformation (s0,
                      s1,
                      s2,
                      g0,
                      g1,
                      g2,
                      modelCoordsDefault(),
                      modelGeneralDefault());

  QVERIFY ((differenceMagnitude (s0, m_s0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s1, m_s1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s2, m_s2Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g0, m_g0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g1, m_g1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g2, m_g2Transformed) < EPSILON));
}

void TestTransformation::testCartesianLogLog ()
{
  QPointF s0 (10, 1000);
  QPointF s1 (1000, 1000);
  QPointF s2 (10, 10);
  QPointF g0 (1, 1);
  QPointF g1 (10, 1);
  QPointF g2 (1, 10);

  DocumentModelCoords modelCoords = modelCoordsDefault();
  modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  initTransformation (s0,
                      s1,
                      s2,
                      g0,
                      g1,
                      g2,
                      modelCoordsDefault(),
                      modelGeneralDefault());

  QVERIFY ((differenceMagnitude (s0, m_s0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s1, m_s1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s2, m_s2Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g0, m_g0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g1, m_g1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g2, m_g2Transformed) < EPSILON));
}

void TestTransformation::testPolarLinear ()
{
  QPointF s0 (500, 1000);
  QPointF s1 (1000, 500);
  QPointF s2 (500, 500); // Origin at center
  QPointF g0 (-90, 100);
  QPointF g1 (0, 100);
  QPointF g2 (0, 0);

  DocumentModelCoords modelCoords = modelCoordsDefault();
  modelCoords.setCoordsType (COORDS_TYPE_POLAR);
  initTransformation (s0,
                      s1,
                      s2,
                      g0,
                      g1,
                      g2,
                      modelCoordsDefault(),
                      modelGeneralDefault());

  QVERIFY ((differenceMagnitude (s0, m_s0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s1, m_s1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s2, m_s2Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g0, m_g0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g1, m_g1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g2, m_g2Transformed) < EPSILON));
}

void TestTransformation::testPolarLogOffset1 ()
{
  QPointF s0 (500, 1000);
  QPointF s1 (1000, 500);
  QPointF s2 (500, 500); // Origin at center
  QPointF g0 (-90, 100);
  QPointF g1 (0, 100);
  QPointF g2 (0, 1);

  DocumentModelCoords modelCoords = modelCoordsDefault();
  modelCoords.setCoordsType (COORDS_TYPE_POLAR);
  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  modelCoords.setOriginRadius (1.0);
  initTransformation (s0,
                      s1,
                      s2,
                      g0,
                      g1,
                      g2,
                      modelCoordsDefault(),
                      modelGeneralDefault());

  QVERIFY ((differenceMagnitude (s0, m_s0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s1, m_s1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s2, m_s2Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g0, m_g0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g1, m_g1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g2, m_g2Transformed) < EPSILON));
}

void TestTransformation::testPolarLogOffset10 ()
{
  QPointF s0 (500, 1000);
  QPointF s1 (1000, 500);
  QPointF s2 (500, 500); // Origin at center
  QPointF g0 (-90, 100);
  QPointF g1 (0, 100);
  QPointF g2 (0, 10);

  DocumentModelCoords modelCoords = modelCoordsDefault();
  modelCoords.setCoordsType (COORDS_TYPE_POLAR);
  modelCoords.setCoordScaleYRadius (COORD_SCALE_LOG);
  modelCoords.setOriginRadius (10.0);
  initTransformation (s0,
                      s1,
                      s2,
                      g0,
                      g1,
                      g2,
                      modelCoordsDefault(),
                      modelGeneralDefault());

  QVERIFY ((differenceMagnitude (s0, m_s0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s1, m_s1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (s2, m_s2Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g0, m_g0Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g1, m_g1Transformed) < EPSILON));
  QVERIFY ((differenceMagnitude (g2, m_g2Transformed) < EPSILON));
}
