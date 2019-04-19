/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "FittingCurveCoefficients.h"
#include "FittingStatistics.h"
#include "Logger.h"
#include "Matrix.h"
#include <QApplication>
#include <qmath.h>

FittingStatistics::FittingStatistics ()
{
}

FittingStatistics::~FittingStatistics()
{
}

void FittingStatistics::calculateCurveFit (int orderReduced,
                                           const FittingPointsConvenient &pointsConvenient,
                                           FittingCurveCoefficients &coefficients,
                                           int significantDigits)
{
  QVector<double> a; // Unused if there are no points

  if (0 <= orderReduced) {

    // We further reduce the order in case the inputs are badly defined. Known bad data example
    // is trying to linearly fit two points with same x but different y values (=infinite slope).
    // Retries are done with successively reduced order. With good inputs no reduction is required
    // so orderReducedFurther succeeds with the same value as orderReduced
    int orderReducedFurther = orderReduced;
    while (!calculateCurveFitReducedFurther (orderReducedFurther,
                                             pointsConvenient,
                                             significantDigits,
                                             a)) {

      // Retry if possible with lower order
      --orderReducedFurther;
      if (orderReducedFurther < 0) {
        break;
      }
    }
  }

  // Copy coefficients into member variable and into list for sending as a signal
  FittingCurveCoefficients fittingCurveCoef;
  for (int order = 0; order <= MAX_POLYNOMIAL_ORDER; order++) {

    if (order < a.size ()) {

      // Copy from polynomial regression vector
      coefficients [order] = a [order];
      fittingCurveCoef.append (a [order]);

    } else if (order < coefficients.size ()) {

      // Set to zero in case value gets used somewhere
      coefficients [order] = 0;

    }
  }
}

bool FittingStatistics::calculateCurveFitReducedFurther (int orderReducedFurther,
                                                         const FittingPointsConvenient &pointsConvenient,
                                                         int significantDigits,
                                                         QVector<double> &a) const
{
  // Calculate X and y arrays in y = X a
  Matrix X (pointsConvenient.size (), orderReducedFurther + 1);
  QVector<double> Y (pointsConvenient.size ());
  loadXAndYArrays (orderReducedFurther,
                   pointsConvenient,
                   X,
                   Y);

  // Solve for the coefficients a in y = X a + epsilon using a = (Xtranpose X)^(-1) Xtranspose y. Solution
  // uses more complicated transposes rather than just using a = X^(-1) y since the transpose approach
  // can handle when the a matrix is nonsquare
  Matrix denominator = X.transpose () * X;
  LOG4CPP_DEBUG_S ((*mainCat)) << "FittingStatistics::calculateCurveFitReducedFurther determinant=" << denominator.determinant();

  MatrixConsistent matrixConsistent = MATRIX_CONSISTENT;
  Matrix inv = denominator.inverse (significantDigits,
                                    matrixConsistent);

  if (matrixConsistent == MATRIX_INCONSISTENT) {

    LOG4CPP_DEBUG_S ((*mainCat)) << "FittingStatistics::calculateCurveFitReducedFurther failed with order="
                                 << orderReducedFurther;

    return false;
  }

  a = inv * X.transpose () * Y;
  Matrix expectedIdentity = denominator * inv;

  LOG4CPP_DEBUG_S ((*mainCat)) << "FittingStatistics::calculateCurveFitReducedFurther succeeded with order="
                               << orderReducedFurther
                               << " expectedIdentity="
                               << expectedIdentity.toString ().toLatin1().data ();

  return true;
}

void FittingStatistics::calculateCurveFitAndStatistics (unsigned int order,
                                                        const FittingPointsConvenient &pointsConvenient,
                                                        FittingCurveCoefficients &coefficients,
                                                        double &mse,
                                                        double &rms,
                                                        double &rSquared,
                                                        int significantDigits)
{
  // Let user know something is happening if a high order was picked since that can take a long time
  qApp->setOverrideCursor (Qt::WaitCursor);

  // To prevent having an underdetermined system with an infinite number of solutions (which will result
  // in divide by zero when computing an inverse) we reduce the order here if necessary.
  // In other words, we limit the order to -1 for no points, 0 for one point, 1 for two points, and so on
  int orderReduced = qMin (qFloor (order),
                           pointsConvenient.size() - 1);

  calculateCurveFit (orderReduced,
                     pointsConvenient,
                     coefficients,
                     significantDigits);
  calculateStatistics (pointsConvenient,
                       coefficients,
                       mse,
                       rms,
                       rSquared);

  qApp->restoreOverrideCursor();
}

void FittingStatistics::calculateStatistics (const FittingPointsConvenient &pointsConvenient,
                                             const FittingCurveCoefficients &coefficients,
                                             double &mse,
                                             double &rms,
                                             double &rSquared)
{
  // First pass to get average y
  double ySum = 0;
  FittingPointsConvenient::const_iterator itrC;
  for (itrC = pointsConvenient.begin (); itrC != pointsConvenient.end (); itrC++) {

    const QPointF &pointC = *itrC;
    ySum += pointC.y();
  }
  double yAverage = ySum / pointsConvenient.length();

  // Second pass to compute squared terms
  mse = 0;
  rms = 0;
  rSquared = 0;

  if (pointsConvenient.count() > 0) {

    double mseSum = 0, rSquaredNumerator = 0, rSquaredDenominator = 0;
    for (itrC = pointsConvenient.begin(); itrC != pointsConvenient.end (); itrC++) {

      const QPointF &pointC = *itrC;
      double yActual = pointC.y();
      double yCurveFit = yFromXAndCoefficients (coefficients,
                                                pointC.x());

      mseSum              += (yCurveFit - yActual ) * (yCurveFit - yActual );
      rSquaredNumerator   += (yCurveFit - yAverage) * (yCurveFit - yAverage);
      rSquaredDenominator += (yActual   - yAverage) * (yActual   - yAverage);
    }

    mse = mseSum / pointsConvenient.count ();
    rms = qSqrt (mse);
    rSquared = (rSquaredDenominator > 0 ?
                       rSquaredNumerator / rSquaredDenominator :
                       0);
  }
}

void FittingStatistics::loadXAndYArrays (int orderReduced,
                                         const FittingPointsConvenient &pointsConvenient,
                                         Matrix &X,
                                         QVector<double> &Y) const
{
  ENGAUGE_ASSERT (Y.size () == X.rows ());

  // Construct the matrices
  int row;
  FittingPointsConvenient::const_iterator itr;
  for (row = 0, itr = pointsConvenient.begin(); itr != pointsConvenient.end(); itr++, row++) {

    const QPointF &p = *itr;
    double x = p.x ();
    double y = p.y ();

    for (int order = 0; order <= orderReduced; order++) {

      X.set (row, order, qPow (x, order));
    }

    Y [row] = y;
  }
}

double FittingStatistics::yFromXAndCoefficients (const FittingCurveCoefficients &coefficients,
                                                 double x) const
{
  double sum = 0;

  for (int order = 0; order <= MAX_POLYNOMIAL_ORDER; order++) {
    double coef = 0;
    if (order < coefficients.size ()) {
      coef = coefficients [order];
    }
    sum += coef * qPow (x, double (order));
  }

  return sum;
}
