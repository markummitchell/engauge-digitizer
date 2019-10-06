/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef ELLIPSE_PARAMETERS_H
#define ELLIPSE_PARAMETERS_H

#include <QPointF>

/// Parameters that define an ellipse about the specified center, at the specified angle from
/// alignment with the axes. Neglecting the rotation for simplicity, the ellipse is defined
/// as (x - xCenter)^2 / a^2 + (y - yCenter)^2 / b^2 = 1
class EllipseParameters
{
public:
  /// Constructor when this class is expected to be never used
  EllipseParameters();
  /// Standard constructor
  EllipseParameters (const QPointF &posCenter,
                     double angleRadians,
                     double a,
                     double b);
  /// Assignment constructor
  EllipseParameters &operator= (const EllipseParameters &other);
  /// Copy constructor
  EllipseParameters (const EllipseParameters &other);
  virtual ~EllipseParameters();

  /// Get method for a
  double a () const;

  /// Get method for angle in radians
  double angleRadians () const;
  
  /// Get method for b
  double b () const;

  /// Get method for center
  QPointF posCenter () const;

private:

  QPointF m_posCenter;
  double m_angleRadians;
  double m_a;
  double m_b;
};

#endif // ELLIPSE_PARAMETERS_H
