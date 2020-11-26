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
