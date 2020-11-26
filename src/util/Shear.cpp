/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "mmsubs.h"
#include <QLineF>
#include <qmath.h>
#include <QPointF>
#include "Shear.h"

Shear::Shear()
{
}

double Shear::lambdaX (const QPointF &posAAxisScreen,
                       const QPointF &posBAxisScreen) const
{
  // If there waS no shear then these vectors would be 90 degrees apart. From this diagram we have
  // tan (theta) = -lambdaX * y / (-y) = lambdaX
  //
  //           -lambdaX * y
  //          |-------------*
  //          |            *
  //          |           *
  //          |          *
  //          |         *
  //      -y  |        *
  //          |       *
  //          |      *
  //          |     *
  //          |--- *  theta
  //          |   *
  //          |  *
  //          | *
  //          ============================ +x
  double thetaComplement = angleBetweenVectors(posAAxisScreen,
                                               posBAxisScreen);
  double theta = M_PI / 2.0 - thetaComplement;
  return qTan (theta);
}

QPointF Shear::unshear (double lambdaX,
                        const QPointF &posRadial,
                        const QPointF &basisX,
                        const QPointF &basisY) const
{
  // This method assumes posRadial is relative to posCenterScreen, versus to (0,0)

  // Project onto basis vectors
  QPointF posProjected (dot (basisX, posRadial),
                        dot (basisY, posRadial));

  // Transform using (1   lambdaX)
  //                 (0         1)
  //
  // Do NOT arbitrariliy flip the sign on lambdaX without testing everywhere this method is
  // used since the sign here must be synced with outside code (e.g. CentipedeDebugPolar::displayTics
  QPointF posTransformed (posProjected.x () - lambdaX * posProjected.y(),
                          posProjected.y ());

  QPointF posResult = posTransformed.x() * basisX + posTransformed.y() * basisY;

  return posResult;
}
