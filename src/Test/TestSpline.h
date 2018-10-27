#ifndef TEST_SPLINE_H
#define TEST_SPLINE_H

#include <QObject>
#include <QString>
#include "SplinePair.h"
#include <vector>

class Spline;

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

  void testCoefficientsFromOrdinals (); /// Compare with third party calculations on a web page
  void testSharpTransition (); /// Uses x values in t array to get single-valued function across sharp transition
  void testSplinesAsControlPoints ();

private:
  bool coefCheckX (const std::vector<double> &t,
                   const std::vector<SplinePair> &xy,
                   const Spline &s) const;
  bool coefCheckY (const std::vector<double> &t,
                   const std::vector<SplinePair> &xy,
                   const Spline &s) const;
  void coefShow (const QString &leftHandSide,
                 const QString &independentVariable,
                 double tLow,
                 double tHigh,
                 double a,
                 double b,
                 double c,
                 double d) const;
};

#endif // TEST_SPLINE_H
