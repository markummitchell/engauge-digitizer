#ifndef TEST_EXPORT_ALIGN_H
#define TEST_EXPORT_ALIGN_H

#include <QObject>

/// Unit test of ExportAlign classes
class TestExportAlign : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestExportAlign(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testLinearDigits1 (); // Range is over one significant digit
  void testLinearDigits2 (); // Range is over two significant digits
  void testLinearDigits3 (); // Range is over three significant digits
  void testLinearHighDynamicRangeNegNeg (); // Range spans orders of magnitude with two negatives
  void testLinearHighDynamicRangeNegPos (); // Range spans orders of magnitude with negative and positive
  void testLinearHighDynamicRangePosPos (); // Range spans orders of magnitude with two positives
  void testLinearLowDynamicRangeNegNeg (); // Range spans single order of magnitude with two negatives
  void testLinearLowDynamicRangeNegPos (); // Range spans single order of magnitude with negative and positive
  void testLinearLowDynamicRangePosPos (); // Range spans single order of magnitude with two positives
  void testLinearRelativelySmallRangeNeg (); // Range is orders of magnitude smaller than bounds with two negatives
  void testLinearRelativelySmallRangePos (); // Range is orders of magnitude smaller than bounds with two positives
  void testLogDigits1 (); // Range is over one significant digit
  void testLogDigits2 (); // Range is over two significant digits
  void testLogDigits3 (); // Range is over three significant digits
  void testLogHighDynamicRangeNegNeg (); // Range spans orders of magnitude with two negative exponents
  void testLogHighDynamicRangeNegPos (); // Range spans orders of magnitude with negative and positive exponents
  void testLogHighDynamicRangePosPos (); // Range spans orders of magnitude with two positive exponents
  void testLogLowDynamicRangeNegNeg (); // Range spans single order of magnitude with two negative exponents
  void testLogLowDynamicRangeNegPos (); // Range spans single order of magnitude with negative and positive exponents
  void testLogLowDynamicRangePosPos (); // Range spans single order of magnitude with two positive exponents
  void testLogRelativelySmallRangeNeg (); // Range is orders of magnitude smaller than bounds with two negative exponents
  void testLogRelativelySmallRangePos (); // Range is orders of magnitude smaller than bounds with two positive exponents

private:

  bool epsilonTest (double a,
                    double b) const; // Compensates for roundoff errors due to log and exponent functions
  double testLinearGeneric (double xMin,
                            double xMax) const;
  double testLogGeneric (double xMinExponent,
                         double xMaxExponent) const; // For simplicity, returns exponent rather than 10^exponent

};

#endif // TEST_EXPORT_ALIGN_H
