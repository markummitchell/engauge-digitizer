#ifndef TEST_CENTIPEDE_ENDPOINTS_H
#define TEST_CENTIPEDE_ENDPOINTS_H

#include "DocumentModelCoords.h"
#include "DocumentModelGuideline.h"
#include <QObject>
#include <QPointF>
#include <QSize>
#include "Transformation.h"

/// Unit tests of centipede endpoints
class TestCentipedeEndpoints : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestCentipedeEndpoints(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testCartesianXPosition ();
  void testCartesianYPosition ();
  void testPolarRPosition ();
  void testPolarTAngle ();
  void testPolarTPosition ();
  
private:

  void initTestCaseCartesian ();
  void initTestCaseCommon ();  
  void initTestCasePolarLog ();

  // Common
  QSize m_windowSize;
  QPointF m_posClickScreen;

  // Cartesian linear
  DocumentModelCoords m_modelCoordsCartesian;
  Transformation m_transformationCartesian;  

  // Polar log
  DocumentModelCoords m_modelCoordsPolarLog;
  Transformation m_transformationPolarLog;
};

#endif // TEST_CENTIPEDE_ENDPOINTS_H
