/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FITTING_STATISTICS_H
#define FITTING_STATISTICS_H

#include "FittingCurveCoefficients.h"
#include "FittingPointsConvenient.h"
#include <QVector>

const int MAX_POLYNOMIAL_ORDER = 9; // Check execution time if this is increased from, say, 6 or 7

class Matrix;

/// This class does the math to compute statistics for FittingWindow
class FittingStatistics
{
public:
  /// Single constructor
  FittingStatistics ();
  virtual ~FittingStatistics ();

  /// Compute the curve fit and the statistics for that curve fit
  /// \param order Requested order of the polynomial to be fitted. This will be reduced if there are not
  ///              enough points just enough to prevent having an undetermined system (=more degrees of freedom
  ///              than constraints) since otherwise there will be an infinite number of solutions
  /// \param pointsConvenient Input data consisting of (x,y) points in graph coordinates
  /// \param coefficients Output coefficients a0, a1, and so on in y = a0 + a1 * x + a2 * x^2 + ...
  /// \param mse Mean squared error between the original data and the fitted curve
  /// \param rms Root mean square error between the original data and the fitted curve
  /// \param rSquared R-squared error between the original data and the fitted curve
  /// \param significantDigits Number of significant digits to be used to determine when determinants are too small
  void calculateCurveFitAndStatistics (unsigned int order,
                                       const FittingPointsConvenient &pointsConvenient,
                                       FittingCurveCoefficients &coefficients,
                                       double &mse,
                                       double &rms,
                                       double &rSquared,
                                       int significantDigits);
  
private:
  
  void calculateCurveFit (int orderReduced,
                          const FittingPointsConvenient &pointsConvenient,
                          FittingCurveCoefficients &coefficients,
                          int significantDigits);
  bool calculateCurveFitReducedFurther (int orderReducedFurther,
                                        const FittingPointsConvenient &pointsConvenient,
                                        int significantDigits,
                                        QVector<double> &a) const;
  void calculateStatistics (const FittingPointsConvenient &pointsConvenient,
                            const FittingCurveCoefficients &coefficients,
                            double &mse,
                            double &rms,
                            double &rSquared);
  void loadXAndYArrays (int orderReduced,
                        const FittingPointsConvenient &pointsConvenient,
                        Matrix &X,
                        QVector<double> &Y) const;
  double yFromXAndCoefficients (const FittingCurveCoefficients &coefficients,
                                double x) const;
};

#endif // FITTING_STATISTICS_H
