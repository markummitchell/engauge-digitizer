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

  void testBadStepLinearX ();
  void testBadStepLinearY ();
  void testBadStepLogX ();
  void testBadStepLogY ();
  void testTransitionLinearToLogX ();
  void testTransitionLinearToLogY ();

private:
  bool testLinearX (double start,
                    double step,
                    double stop,
                    double x1, double y1,
                    double x2, double y2,
                    double x3, double y3);
  bool testLinearY (double start,
                    double step,
                    double stop,
                    double x1, double y1,
                    double x2, double y2,
                    double x3, double y3);
  bool testLogX (double start,
                 double step,
                 double stop,
                 double x1, double y1,
                 double x2, double y2,
                 double x3, double y3);
  bool testLogY (double start,
                 double step,
                 double stop,
                 double x1, double y1,
                 double x2, double y2,
                 double x3, double y3);
};

#endif // TEST_GRID_LINE_LIMITER_H
