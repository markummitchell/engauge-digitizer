#include "CentipedeEndpointsCartesian.h"
#include "CentipedeEndpointsPolar.h"
#include "DocumentModelGeneral.h"
#include "DocumentModelGuideline.h"
#include "Logger.h"
#include "MainWindowModel.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QTransform>
#include <QtTest/QtTest>
#include "Test/TestCentipedeEndpoints.h"

QTEST_MAIN (TestCentipedeEndpoints)

TestCentipedeEndpoints::TestCentipedeEndpoints(QObject *parent) :
  QObject(parent)
{
}

void TestCentipedeEndpoints::cleanupTestCase ()
{
}

void TestCentipedeEndpoints::initTestCase ()
{
  // Member variables not initialized here are fine with defaults
  
  const bool DEBUG_FLAG = false;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  initTestCaseCommon ();
  initTestCaseCartesian ();
  initTestCasePolarLog ();
}

void TestCentipedeEndpoints::initTestCaseCartesian ()
  {
  // Cartesian/linear
  //   screen     graph
  //   (100,100)  (0,0)
  //   (150,100)  (1,0))
  //   (200,100)  (0,1)

  QPointF posScreen0 = QPointF (m_windowSize.width() / 2,
                                m_windowSize.height() / 2); // Center
  QPointF posScreen1 = QPointF (m_windowSize.width(),
                                m_windowSize.height() / 2); // Right
  QPointF posScreen2 = QPointF (m_windowSize.width() / 2,
                                0); // Top

  const double RADIUS = 1;
  m_modelCoordsCartesian.setCoordsType (COORDS_TYPE_CARTESIAN);
  DocumentModelGeneral modelGeneral; // For formatting only which this testing does not use
  MainWindowModel mainWindowModel; // For formatting only which this testing does not use
  QTransform matrixScene (posScreen0.x(), posScreen1.x(), posScreen2.x(),
                          posScreen0.y(), posScreen1.y(), posScreen2.y(),
                                       1,              1,              1);
  QTransform matrixGraph (0, RADIUS,      0,
                          0,      0, RADIUS,
                          1,      1,      1);
  m_transformationCartesian.updateTransformFromMatrices (matrixScene,
                                                         matrixGraph);
  m_transformationCartesian.setModelCoords (m_modelCoordsPolarLog,
                                            modelGeneral,
                                            mainWindowModel);
}

void TestCentipedeEndpoints::initTestCaseCommon ()
{
  // Common values. All test cases share common 200x200 image with origin at (100,100)
  m_windowSize = QSize (200, 200);
  QPointF center (m_windowSize.width () / 2,
                  m_windowSize.height () / 2);
  m_posClickScreen = QPointF (center.x() + m_windowSize.width() / 4,
                              center.y() - m_windowSize.height() / 4);
}

void TestCentipedeEndpoints::initTestCasePolarLog ()
  {
  // Polar/log-radius 
  //   screen     graph
  //   (100,100)  (0,1)
  //   (150,100)  (0,10)
  //   (200,100)  (0,100)

  QPointF posScreen0 = QPointF (m_windowSize.width() / 2,
                                m_windowSize.height() / 2); // Center
  QPointF posScreen1 = QPointF (m_windowSize.width(),
                                m_windowSize.height() / 2); // Right
  QPointF posScreen2 = QPointF (m_windowSize.width() / 2,
                                0); // Top

  const double LOG_RADIUS_MIN = 1;
  const double LOG_RADIUS_MAX = 100;
  m_modelCoordsPolarLog.setCoordsType (COORDS_TYPE_POLAR);
  m_modelCoordsPolarLog.setCoordScaleYRadius (COORD_SCALE_LOG);
  m_modelCoordsPolarLog.setOriginRadius (LOG_RADIUS_MIN);
  DocumentModelGeneral modelGeneral; // For formatting only which this testing does not use
  MainWindowModel mainWindowModel; // For formatting only which this testing does not use
  QTransform matrixScene (posScreen0.x(), posScreen1.x(), posScreen2.x(),
                          posScreen0.y(), posScreen1.y(), posScreen2.y(),
                                       1,              1,              1);
  QTransform matrixGraph (             0,             90,              0,
                          LOG_RADIUS_MIN, LOG_RADIUS_MAX, LOG_RADIUS_MAX,
                                       1,              1,              1);
  m_transformationPolarLog.updateTransformFromMatrices (matrixScene,
                                                        matrixGraph);
  m_transformationPolarLog.setModelCoords (m_modelCoordsPolarLog,
                                           modelGeneral,
                                           mainWindowModel);
}

void TestCentipedeEndpoints::testCartesianXPosition ()
{
  const double EPSILON = 0.001;

  DocumentModelGuideline modelGuideline;
  
  CentipedeEndpointsCartesian endpoints (modelGuideline,
                                         m_transformationCartesian,
                                         m_posClickScreen);

  QPointF posLow = endpoints.posScreenConstantYForLowX (modelGuideline.creationCircleRadius());
  QPointF posHigh = endpoints.posScreenConstantYForHighX (modelGuideline.creationCircleRadius());

  QVERIFY (magnitude (posLow - QPointF (130, 50)) < EPSILON);
  QVERIFY (magnitude (posHigh - QPointF (170, 50)) < EPSILON);
}

void TestCentipedeEndpoints::testCartesianYPosition ()
{
  const double EPSILON = 0.001;

  DocumentModelGuideline modelGuideline;
    
  CentipedeEndpointsCartesian endpoints (modelGuideline,
                                         m_transformationCartesian,
                                         m_posClickScreen);

  QPointF posLow = endpoints.posScreenConstantXForLowY (modelGuideline.creationCircleRadius());
  QPointF posHigh = endpoints.posScreenConstantXForHighY (modelGuideline.creationCircleRadius());

  QVERIFY (magnitude (posLow - QPointF (150, 70)) < EPSILON);
  QVERIFY (magnitude (posHigh - QPointF (150, 30)) < EPSILON);
}

void TestCentipedeEndpoints::testPolarRPosition ()
{
  const double EPSILON = 0.001;

  DocumentModelGuideline modelGuideline;

  QPointF posOriginScreen (100, 100);
  CentipedeEndpointsPolar endpoints (m_modelCoordsPolarLog,
                                     modelGuideline,
                                     m_transformationPolarLog,
                                     m_posClickScreen,
                                     posOriginScreen);

  QPointF posLow, posHigh;
  endpoints.posScreenConstantTForRHighLow (modelGuideline.creationCircleRadius(),
                                           posLow,
                                           posHigh);

  QVERIFY (magnitude (posLow - QPointF (135.616, 64.6746)) < EPSILON);
  QVERIFY (magnitude (posHigh - QPointF (163.840, 35.880)) < EPSILON);
}

void TestCentipedeEndpoints::testPolarTPosition ()
{
  const double EPSILON = 0.001;

  DocumentModelGuideline modelGuideline;

  QPointF posOriginScreen (100, 100);
  CentipedeEndpointsPolar endpoints (m_modelCoordsPolarLog,
                                     modelGuideline,
                                     m_transformationPolarLog,
                                     m_posClickScreen,
                                     posOriginScreen);

  QPointF posLow = endpoints.posScreenConstantRForLowT (modelGuideline.creationCircleRadius());
  QPointF posHigh = endpoints.posScreenConstantRForHighT (modelGuideline.creationCircleRadius());  

  QVERIFY (magnitude (posLow - QPointF (161.2417, 66.5416)) < EPSILON);
  QVERIFY (magnitude (posHigh - QPointF (138.2443, 33.8197)) < EPSILON);
}
