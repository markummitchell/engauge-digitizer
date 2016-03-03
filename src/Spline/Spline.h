/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "SplineCoeff.h"
#include "SplinePair.h"
#include <vector>

/// Cubic interpolation given independent and dependent value vectors. X is handled as a dependent variable
/// based on the unitless independent parameter t so curves are not restricted to x(i)!=x(i+1).
///
/// This class has two modes that can be run side by side:
/// -# Coefficient mode, where each interval has coefficients a,b,c,d in xy=ai+bi*(t-ti)+ci*(t-ti)^2+di*(t-ti)^3
/// -# Bezier mode, where each interval has 2 endpoints and 2 control points in 
///    P=(1-s)^3*P0+3*(1-s)^2*s*P1+3*(1-s)*s^2*P2+s^3*P3. Although interpolation can be performed in bezier mode,
///    this interpolation was just to verify consistent operation between the two modes. The real purpose of this
///    mode is to produce reliable control points, p1 and p2, for each interval. The control points can be used by
///    external code that relies on control points to perform its own interpolation 
class Spline 
{
 public:
  /// Initialize spline with independent (t) and dependent (x and y) value vectors. Besides initializing
  /// the a,b,c,d coefficients for each interval, this constructor initializes bezier points (P1 and P2)
  /// for each interval, where P0 and P3 are the start and end points for each interval.
  Spline(const std::vector<double> &t,
         const std::vector<SplinePair> &xy);

  virtual ~Spline();

  /// Use bisection algorithm to iteratively find the SplinePair interpolated to best match the specified x value.
  /// This assumes the curve is a function since otherwise there is the potential for multiple solutions
  SplinePair findSplinePairForFunctionX (double x,
                                         int numIterations) const;

  /// Return interpolated y for specified x. The appropriate interval is selected from the entire
  /// set of piecewise-defined intervals, then the corresponding a,b,c,d coefficients are applied
  SplinePair interpolateCoeff (double t) const;

  /// Return interpolated y for specified x, for testing. This uses the bezier points. If the t values
  /// are not separated by +1 consistently then this algorithm will probably need additional effort to work right
  SplinePair interpolateControlPoints (double t) const;

  /// Bezier p1 control point for specified interval. P0 is m_xy[i] and P3 is m_xy[i+1]
  SplinePair p1 (unsigned int i) const;

  /// Bezier p2 control point for specified interval. P0 is m_xy[i] and P3 is m_xy[i+1]
  SplinePair p2 (unsigned int i) const;

private:
  Spline();

  // Although coefficient interpolation works for successive t values not 1.0 apart, the control point interpolation
  // does not so we check the increments. Note that the starting value is arbitrary. Removing this restriction will
  // mean upgrading the code to allow arbitrary t increments
  void checkTIncrements (const std::vector<double> &t) const;

  void computeCoefficientsForIntervals (const std::vector<double> &t,
                                        const std::vector<SplinePair> &xy);
  void computeControlPointsForIntervals ();

  // Coefficients a,b,c,d
  std::vector<SplineCoeff> m_elements;

  // Input times
  std::vector<double> m_t;

  // Input points
  std::vector<SplinePair> m_xy;

  // Control points for each interval
  std::vector<SplinePair> m_p1;
  std::vector<SplinePair> m_p2;
};
