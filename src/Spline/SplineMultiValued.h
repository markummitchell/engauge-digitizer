/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SPLINE_MULTI_VALUED_H
#define SPLINE_MULTI_VALUED_H

#include "SplineAbstract.h"
#include "SplineCoeff.h"
#include "SplinePair.h"
#include <vector>

/// Cubic interpolation given independent and dependent value vectors. X is handled as a dependent variable
/// based on the unitless independent parameter t so curves are not restricted to x(i)!=x(i+1).
class SplineMultiValued : public SplineAbstract
{
  /// For unit testing
  friend class TestSpline;

 public:
  /// Single constructor
  SplineMultiValued(const std::vector<double> &t,
                    const std::vector<SplinePair> &xy,
                    SplineTCheck splineTCheck = SPLINE_ENABLE_T_CHECK);

  virtual ~SplineMultiValued();

  virtual void computeCoefficientsForIntervals (const std::vector<double> &t,
                                                const std::vector<SplinePair> &xy);

private:
  SplineMultiValued();
};

#endif // SPLINE_MULTI_VALUED_H
