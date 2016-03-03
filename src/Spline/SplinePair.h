/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SPLINE_PAIR_H
#define SPLINE_PAIR_H

/// Single X/Y pair for cubic spline interpolation initialization and calculations
class SplinePair
{
 public:
  /// Default constructor. Normally used only by generic container classes
  SplinePair();

  /// Constructor for filling vector with a single scalar. Provided for convenience over preferred constructor
  SplinePair (double scalar);

  /// Preferred constructor. Used when default constructor is not being used by generic container classes
  SplinePair(double x,
             double y);

  /// Assigment constructor
  SplinePair(const SplinePair&other);

  /// Addition operator
  SplinePair operator+(const SplinePair &other) const;

  /// Subtraction operator
  SplinePair operator-(const SplinePair &other) const;

  /// Multiplication operator
  SplinePair operator*(const SplinePair &other) const;

  /// Division operator
  SplinePair operator/(const SplinePair &other) const;

  /// Get method for x
  double x() const;

  /// Get method for y
  double y() const;

 private:

  double m_x;
  double m_y;
};

#endif // SPLINE_PAIR_H
