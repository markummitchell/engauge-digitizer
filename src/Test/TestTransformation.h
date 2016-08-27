#ifndef TEST_TRANSFORMATION_H
#define TEST_TRANSFORMATION_H

#include "DocumentModelCoords.h"
#include "DocumentModelGeneral.h"
#include <QObject>
#include <QPointF>

/// Unit test of transformation class. Checking mostly involves verifying forward/reverse are inverses of each other
class TestTransformation : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestTransformation(QObject *parent = 0);

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testCartesianLinearLinear ();
  void testCartesianLinearLog ();
  void testCartesianLogLinear ();
  void testCartesianLogLog ();
  void testPolarLinear ();
  void testPolarLogOffset1 ();
  void testPolarLogOffset10 ();

private:
  DocumentModelCoords modelCoordsDefault() const;
  DocumentModelGeneral modelGeneralDefault() const;

  double differenceMagnitude (const QPointF &vector1,
                              const QPointF &vector2) const;
  void initTransformation (const QPointF &s0,
                           const QPointF &s1,
                           const QPointF &s2,
                           const QPointF &g0,
                           const QPointF &g1,
                           const QPointF &g2,
                           const DocumentModelCoords &modelCoords,
                           const DocumentModelGeneral &modelGeneral);

  QPointF m_g0Transformed;
  QPointF m_g1Transformed;
  QPointF m_g2Transformed;
  QPointF m_s0Transformed;
  QPointF m_s1Transformed;
  QPointF m_s2Transformed;
};

#endif // TEST_TRANSFORMATION_H
