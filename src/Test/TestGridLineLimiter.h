#ifndef TEST_GRID_LINE_LIMITER_H
#define TEST_GRID_LINE_LIMITER_H

#include <QObject>

/// Unit test of GridLineLimiter class
class TestGridLineLimiter : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestGridLineLimiter(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testTransitionLinearToLogX ();
  void testTransitionLinearToLogY ();
};

#endif // TEST_GRID_LINE_LIMITER_H
