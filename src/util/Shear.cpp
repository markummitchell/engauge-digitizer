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
                                                       double angleRotation,
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

  // In unsheared coordinates the angle between the semimajor a/x axis and the x/t graph axis can be
  // simply added
  angleUnsheared += angleRotation;

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

QPointF Shear::projectOntoBasisVectors (const QPointF &basis0,
                                        const QPointF &basis1,
                                        const QPointF &vector) const
{
  // Basis vectors should be normalized to unit length, but this method normalizes
  // them (again) just in case they are not already normalized
  //
  // It is assumed that upstream prevents very small angles between basis0 and basis1 since
  // the geometry would be computationally intractable
  //
  // If basis vectors are orthogonal then this method effectively just takes the dot product
  // to get the components.
  //
  // If basis vectors are non-orthogonal then the components are coupled. We will compute new 
  // vector W with its a0 and a1 components
  //    V = a0 * basis0 + a1 * basis1
  // Taking dot product of V with basis0 and basis1 we get
  //    V dot basis0 = a0 + a1 * (basis1 dot basis0)
  //    V dot basis1 = a0 * (basis0 dot basis1) + a1
  // But all three dot products can be computed with the initial geometry, turning
  // this into 2 equations 2 unknowns

  QPointF basis0Norm = basis0 / magnitude (basis0);
  QPointF basis1Norm = basis1 / magnitude (basis1);
  
  double vDotB0 = dot (vector, basis0Norm);
  double vDotB1 = dot (vector, basis1Norm);
  double b0DotB1 = dot (basis0Norm, basis1Norm);

  // Kramers Rule with (vDotB0) = (1  b0DotB1) (a0)
  //                   (vDotB1) = (b0DotB1  1) (a1)
  double a0Numerator = vDotB0 * 1 - b0DotB1 * vDotB1;
  double a1Numerator = 1 * vDotB1 - vDotB1 * b0DotB1;
  double denominator = 1 - b0DotB1 * b0DotB1;

  return QPointF (a0Numerator / denominator,
                  a1Numerator / denominator);
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
