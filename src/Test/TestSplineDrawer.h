#ifndef TEST_SPLINE_DRAWER_H
#define TEST_SPLINE_DRAWER_H

#include <QObject>
#include <QString>
#include "SplinePair.h"
#include <vector>

class Spline;

/// Unit test of spline drawer, which classifies single- versus multi-valued data
class TestSplineDrawer : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestSplineDrawer(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testMultiValuedLeadingOverlap (); /// Overlap in first segment, and once in middle
  void testMultiValuedTrailingOverlap (); /// Overlap in final segment, and once in middle

private:

  bool testMultiValuedGeneric (const std::vector<SplinePair> &xy,
                               const std::vector<bool> &isMultiValued) const;
};

#endif // TEST_SPLINE_DRAWER_H
