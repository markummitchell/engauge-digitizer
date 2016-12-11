#ifndef TEST_FITTING_H
#define TEST_FITTING_H

#include <QObject>

/// Unit test of Fitting classes
class TestFitting : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestFitting(QObject *parent = 0);

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  // Test exact fit cases, for which the order equals the number of points minus 1
  void testExactFit01 ();
  void testExactFit12 ();
  void testExactFit23 ();
  void testExactFit34 ();

  // Test overfitted cases, for which the order is equal to, or greater than, the number of points
  void testOverfit11 ();
  void testOverfit22 ();
  void testOverfit33 ();
  void testOverfit44 ();

  // Test underfitted cases, for which the order is less than the number of points minus 1
  void testUnderfit02 ();
  void testUnderfit13 ();
  void testUnderfit24 ();
  void testUnderfit35 ();
  
 private:
  bool generalTest (int order,
                    int numPoints) const;
};

#endif // TEST_FITTING_H
