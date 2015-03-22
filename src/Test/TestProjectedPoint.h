#ifndef TEST_PROJECTED_POINT_H
#define TEST_PROJECTED_POINT_H

#include <QObject>

/// Unit test of spline library
class TestProjectedPoint : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestProjectedPoint(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testProjectedPoints ();
};

#endif // TEST_PROJECTED_POINT_H
