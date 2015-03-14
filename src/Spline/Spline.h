/* "THE BEER-WARE LICENSE" (Revision 42): Devin Lane wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return. */

#include "SplineCoeff.h"
#include "SplinePair.h"
#include <vector>

/// Cubic interpolation given independent and dependent value vectors. X is handled as a dependent variable
/// based on the unitless independent parameter t so curves are not restricted to x(i)!=x(i+1)
class Spline 
{
 public:
  /// Initialize spline with independent (t) and dependent (x and y) value vectors
  Spline(const std::vector<double> &t,
         const std::vector<SplinePair> &xy);
  virtual ~Spline();

  /// Return interpolated y for specified x. The appropriate interval is selected from the entire
  /// set of piecewise-defined intervals
  SplinePair interpolate(double t) const;

private:
  Spline();
    
  std::vector<SplineCoeff> m_elements;
};
