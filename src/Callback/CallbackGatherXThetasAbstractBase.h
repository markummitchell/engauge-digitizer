/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_GATHER_X_THETAS_ABSTRACT_BASE_H
#define CALLBACK_GATHER_X_THETAS_ABSTRACT_BASE_H

#include "CallbackSearchReturn.h"
#include "CurveLimits.h"
#include "CurvesIncludedHash.h"
#include "ExportValuesXOrY.h"
#include "Transformation.h"
#include "ValuesVectorXOrY.h"

class Point;

/// Base callback for collecting X/Theta independent variables, for functions, in preparation for exporting
class CallbackGatherXThetasAbstractBase
{
public:
  /// Single constructor.
  CallbackGatherXThetasAbstractBase(bool firstCurveOnly,
                                    bool extrapolateOutsideEndpoints,
                                    const QStringList &curvesIncluded,
                                    const Transformation &transformation);
  virtual ~CallbackGatherXThetasAbstractBase ();

  /// Callback method.
  virtual CallbackSearchReturn callback (const QString &curveName,
                                         const Point &point) = 0;

  /// Endpoint maxima for each curve, if extrapolation has been disabled
  CurveLimits curveLimitsMax () const;

  /// Endpoint minima for each curve, if extrapolation has been disabled
  CurveLimits curveLimitsMin () const;

  /// Resulting x/theta values for all included functions
  ValuesVectorXOrY xThetaValuesRaw () const;

protected:

  /// Save one graph x value
  void addGraphX (double xGraph);
  
  /// Get method for included names
  QStringList curvesIncluded () const;
  
  /// Get method for included names as hash
  CurvesIncludedHash curvesIncludedHash () const;

  /// Get method for transformation
  const Transformation &transformation() const;

  /// Update the tracked min and max values for each curve
  void updateMinMax (const QString &curveName,
                     const Point &point);

private:
  CallbackGatherXThetasAbstractBase();

  bool m_extrapolateOutsideEndpoints;
  QStringList m_curvesIncluded;
  const Transformation m_transformation;
  CurvesIncludedHash m_curvesIncludedHash;
  ValuesVectorXOrY m_xThetaValues;

  // Curve limits that may or may not be merged into m_xThetaValues
  CurveLimits m_curveLimitsMin;
  CurveLimits m_curveLimitsMax;
};

#endif // CALLBACK_GATHER_X_THETAS_ABSTRACT_BASE_H
