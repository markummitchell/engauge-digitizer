/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
  
  /// Get method for a
  SplinePair a () const;

  /// Get method for b
  SplinePair b () const;

  /// Get method for c
  SplinePair c () const;

  /// Get method for d
  SplinePair d () const;

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
