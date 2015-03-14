/* "THE BEER-WARE LICENSE" (Revision 42): Devin Lane wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return. */

#ifndef SPLINE_COEFF
#define SPLINE_COEFF

#include "SplinePair.h"

/// Four element vector of a,b,c,d coefficients and the associated x value, for one interval of a set
/// of piecewise-defined intervals
class SplineCoeff
{
public:
  /// Partial constructor for use mostly by container classes
  SplineCoeff(double t);

  /// Full constructor
  SplineCoeff(double t,
              const SplinePair &a,
              const SplinePair &b,
              const SplinePair &c,
              const SplinePair &d);

  /// Comparison operator for collection
  bool operator<(const SplineCoeff &e) const;

  /// Comparison operator for collection
  bool operator<(double t) const;
  
  /// Evaluate the value using the a,b,c,d coefficients, over this interval
  SplinePair eval(double t) const;

  /// T value associated with these a,b,c,d coefficients
  double t () const;
  
private:
  SplineCoeff();

  double m_t;
  SplinePair m_a;
  SplinePair m_b;
  SplinePair m_c;
  SplinePair m_d;
};

#endif // SPLINE_COEFF
