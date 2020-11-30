#ifndef TEST_SHEAR_H
#define TEST_SHEAR_H

#include <QObject>
#include <QPointF>
#include <QSize>

/// Unit tests of shear computations
class TestShear : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestShear(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testNonOrthogonalProjection ();
  void testOrthogonalProjection ();
  
private:

};

#endif // TEST_SHEAR_H
