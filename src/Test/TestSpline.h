#ifndef TEST_SPLINE_H
#define TEST_SPLINE_H

#include <QObject>

/// Unit test of spline library
class TestSpline : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestSpline(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testSplinesAsControlPoints ();
};

#endif // TEST_SPLINE_H
