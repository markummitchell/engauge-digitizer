/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SHEAR_H
#define SHEAR_H

#include <QPointF>

class QLineF;

/// Computations for shear transformation. We assume lambdaY is zero for simplicity
/// so shifting is only parallel to x axis
// <pre>
// (1        lambdaX)
// (labmbdaY       1)
// </pre>
class Shear
{
 public:
  Shear();

  /// Convert angle in graph coordinates to angle in screen coordinates. There are 2 cases:
  /// - No shear (lambdaX = 0) in which case the angles in graph and screen coordinates are
  ///   evenly spaced and just differ by the angle the ellipse is rotated from the +x screen direction
  /// - With shear (lambdaX != 0) in which case we:
  ///    -# convert the (angle, radius) point in graph coordinates to a position in screen coordinates
  ///    -# compute the (inverse) shear transformation
  ///    -# apply shear transformation
  /// Convert angle that applies to ellipse that has nonzero or zero (in terms of lambdaX)
  /// into angle that applies to ellipse in which shear has been removed. In both cases
  /// we have an ellipse, but in the second case the ellipse's principal axes are aligned
  /// along posScreen0 or its orthogonal vector
  double convertAngleGraphToAngleScreenWithShear (double angleSheared,
                                                  double radiusSheared,
                                                  const QPointF &posOriginScreen,
                                                  const QPointF &posScreen0,
                                                  const QPointF &posScreen90) const;

  /// Return lambdaX in the shear transformation
  double lambdaX (const QPointF &posAAxisScreen,
                  const QPointF &posBAxisScreen) const;

  /// Remove shear from the posRadial position by applying a shear transform with magnitude
  /// specified by lambdaX. This should have no effect when lambdaX = 0
  QPointF unshear (double lambdaX,
                          const QPointF &posRadial,
                          const QPointF &basisX,
                          const QPointF &basisY) const;
};

#endif // SHEAR_H
