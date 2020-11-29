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
#include "Transformation.h"

Shear::Shear()
{
}

double Shear::convertAngleGraphToAngleScreenWithShear (double angleSheared,
                                                       double radiusSheared,
                                                       const QPointF &posOriginScreen,
                                                       const QPointF &posScreen0,
                                                       const QPointF &posScreen90) const
{
  double lambda = lambdaX (posScreen0 - posOriginScreen,
                           posScreen90 - posOriginScreen);

  // Orthogonal basis vectors of ellipse with x basis along major axis and y basis
  // at right angles (ignoring shear)
  QPointF basis0 = (posScreen0 - posOriginScreen) / magnitude (posScreen0 - posOriginScreen);
  QPointF basis90 (basis0.y(),
                  -1.0 * basis0.x());

  // Point in screen coordinates. Zero value for angleSheared is along screen +x
  QPointF posScreen = posOriginScreen + radiusSheared * QPointF (qCos (angleSheared),
                                                                 -1.0 * qSin (angleSheared));

  // Now apply shear transformation
  QPointF posUnsheared = unshear (lambda,
                                  posScreen - posOriginScreen,
                                  basis0,
                                  basis90);

  double angleUnsheared = qAtan2 (-1.0 * posUnsheared.y (),
                                  posUnsheared.x ()); // Implicit basis vectors are (1,0) and (0,-1)

  return angleUnsheared;
}

double Shear::lambdaX (const QPointF &posAAxisScreen,
                       const QPointF &posBAxisScreen) const
{
  // If there was no shear then these vectors would be 90 degrees apart. From this diagram we have
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
                        const QPointF &basis0,
                        const QPointF &basis90) const
{
  // This method assumes posRadial is relative to posOriginScreen, versus to (0,0)

  // Project onto basis vectors
  QPointF posProjected (dot (basis0, posRadial),
                        dot (basis90, posRadial));

  // Transform using (1   lambdaX)
  //                 (0         1)
  //
  // Do NOT arbitrariliy flip the sign on lambdaX without testing everywhere this method is
  // used since the sign here must be synced with outside code (e.g. CentipedeDebugPolar::displayTics
  QPointF posTransformed (posProjected.x () - lambdaX * posProjected.y(),
                          posProjected.y ());

  QPointF posResult = posTransformed.x() * basis0 + posTransformed.y() * basis90;

  return posResult;
}
