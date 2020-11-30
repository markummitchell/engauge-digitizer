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
#include "Shear.h"
#include "Test/TestShear.h"

QTEST_MAIN (TestShear)

TestShear::TestShear(QObject *parent) :
  QObject(parent)
{
}

void TestShear::cleanupTestCase ()
{
}

void TestShear::initTestCase ()
{
}

void TestShear::testNonOrthogonalProjection ()
{
  Shear shear;
  const double UNITY = 1, EPSILON = 0.001;
  
  // Geometry with 30 degrees between orthogonal vector (to basis0) and second nonorthogonal basis vector
  //  |    1     P 
  //  |   1    P   
  //  |  1   P      
  //  | 1  P       
  //  |1 P        
  //  X000000
  double thirtyDegreesAsRadians = qDegreesToRadians (30.0);
  QPointF projectedGot = shear.projectOntoBasisVectors (QPointF (UNITY, 0.0),
                                                        QPointF (UNITY * qSin (thirtyDegreesAsRadians),
                                                                 UNITY * qCos (thirtyDegreesAsRadians)),
                                                        QPointF (1.0 + qSin (thirtyDegreesAsRadians),
                                                                 qCos (thirtyDegreesAsRadians)));
  
  QPointF projectedExpected (1.0,
                             1.0);

  QVERIFY (magnitude (projectedGot - projectedExpected) < EPSILON);
}

void TestShear::testOrthogonalProjection ()
{
  Shear shear;
  const double UNITY = 1, EPSILON = 0.001;
  
  // Geometry with 30 degrees between orthogonal and second basis vector
  //  1     P 
  //  1    P   
  //  1   P      
  //  1  P       
  //  1 P        
  //  X000000
  QPointF projectedGot = shear.projectOntoBasisVectors (QPointF (UNITY, 0.0),
                                                        QPointF (0.0, UNITY),
                                                        QPointF (1.0, 1.0));

  QPointF projectedExpected (1.0,
                             1.0);

  QVERIFY (magnitude (projectedGot - projectedExpected) < EPSILON);
}
