/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SPLINE_FACTORY_H
#define SPLINE_FACTORY_H

#include "CurveConnectAs.h"
#include "SplineAbstract.h"
#include "SplinePair.h"
#include <vector>

/// Factory class for Spline algorithms
class SplineFactory
{
 public:
  /// Single constructor
  SplineFactory();
  virtual ~SplineFactory();

  /// Factory method for splines
  SplineAbstract *create (CurveConnectAs curveConnectAs,
                          const std::vector<double> &t,
                          const std::vector<SplinePair> &xy) const;

};

#endif // SPLINE_FACTORY_H
