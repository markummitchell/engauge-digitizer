/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SPLINE_SINGLE_VALUED_H
#define SPLINE_SINGLE_VALUED_H

#include "SplineAbstract.h"
#include "SplineCoeff.h"
#include "SplinePair.h"
#include <vector>

/// Cubic interpolation given independent and dependent value vectors. Y is a function of independent variable X to
/// ensure single-valuedness. X is handled as a dependent variable of T for consistency with SplineMultiValued
class SplineSingleValued : public SplineAbstract
{
  /// For unit testing
  friend class TestSpline;

 public:
  /// Single constructor
  SplineSingleValued(const std::vector<double> &t,
                     const std::vector<SplinePair> &xy,
                     SplineTCheck splineTCheck = SPLINE_ENABLE_T_CHECK);

  virtual ~SplineSingleValued();

  virtual void computeCoefficientsForIntervals (const std::vector<double> &t,
                                                const std::vector<SplinePair> &xy);

private:
  SplineSingleValued();
};

#endif // SPLINE_SINGLE_VALUED_H
