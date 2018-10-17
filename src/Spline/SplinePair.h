/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SPLINE_PAIR_H
#define SPLINE_PAIR_H

#include <ostream>

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

  /// Get method for x coordinate value that is less confusing when t values are actually stored in x coordinate
  double arg1() const;

  /// Get method for y coordinate value that is less confusing when x values are actually stored in y coordinate
  double arg2() const;

  /// Addition operator
  SplinePair operator+(const SplinePair &other) const;

  /// Subtraction operator
  SplinePair operator-(const SplinePair &other) const;

  /// Multiplication operator
  SplinePair operator*(const SplinePair &other) const;

  /// Division operator
  SplinePair operator/(const SplinePair &other) const;

  /// Get method for x coordinate
  double x() const;

  /// Get method for y coordinate
  double y() const;

 private:

  double m_x;
  double m_y;
};

/// Insertion operator for qDebug and Logger
std::ostream &operator<< (std::ostream &str, const SplinePair &pair);

#endif // SPLINE_PAIR_H
