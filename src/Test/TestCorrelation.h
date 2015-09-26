#ifndef TEST_CORRELATION_H
#define TEST_CORRELATION_H

#include <QObject>

/// Unit tests of fast correlation algorithm
class TestCorrelation : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestCorrelation(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();
  void loadSinusoid (double function [],
                     int n,
                     int center) const;
  void loadThreeTriangles (double function [],
                           int n,
                           int center) const;

  void testShiftSinusoidNonPowerOf2 ();
  void testShiftSinusoidPowerOf2 ();
  void testShiftThreeTrianglesNonPowerOf2 ();
  void testShiftThreeTrianglesPowerOf2 ();

private:

};

#endif // TEST_CORRELATION_H
