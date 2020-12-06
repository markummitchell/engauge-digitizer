/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_ENDPOINTS_POLAR_H
#define CENTIPEDE_ENDPOINTS_POLAR_H

#include "CentipedeEndpointsAbstract.h"
#include "CentipedeIntersectionType.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGuideline.h"
#include <QPointF>
#include "Transformation.h"

class CentipedeDebugPolar;

/// Compute endpoints for polar centipedes
class CentipedeEndpointsPolar : public CentipedeEndpointsAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeEndpointsPolar(const DocumentModelCoords &modelCoords,
                          const DocumentModelGuideline &modelGuideline,
                          const Transformation &transformation,
                          const QPointF &posClickScreen,
                          const QPointF &posOriginScreen);
  virtual ~CentipedeEndpointsPolar ();

  /// Ellipse for R value of circle/coordinate intersection. Start/span angles are calculated separately
  void ellipseScreenConstantRForTHighLowAngles (const Transformation &transformation,
                                                const QPointF &posClickScreen,
                                                double &angleRotation,
                                                QRectF &rectBounding,
                                                CentipedeDebugPolar &DebugPolar);


  /// Screen point for R value of circle/coordinate intersection in the increasing T direction
  QPointF posScreenConstantRForHighT (double radius) const;

  /// Screen point for R value of circle/coordinate intersection in the decreasing T direction
  QPointF posScreenConstantRForLowT (double radius) const;

  /// Return two points (posLow and posHigh) where circle around posClickScreen intersects
  /// constant-radiusAboutClick ellipse
  void posScreenConstantRHighLow (double radiusAboutClick,
                                  QPointF &posLow,
                                  QPointF &posHigh) const;

  /// Endpoints for radial line segmentin polar coordinates
  void posScreenConstantTForRHighLow (double radius,
                                            QPointF &posLow,
                                            QPointF &posHigh) const;
  
private:
  CentipedeEndpointsPolar();

  double closestAngleToCentralAngle (double angleCenter,
                                     double angleOld) const;

  /// Generate a pair of points next to each other along a screen circle with the specified radius, given the index
  void generatePreviousAndNextPointsConstantR (double radius,
                                               int iPrevious,
                                               int iNext,
                                               QPointF &posGraphPrevious,
                                               QPointF &posGraphNext,
                                               QPointF &posScreen) const;

  /// Solves posScreenConstantRHighT and posScreenConstantRLowT  
  QPointF posScreenConstantRCommon (double radius,
                                    CentipedeIntersectionType intersectionType) const;

  double rAtOrigin () const;
  double tAtOrigin () const;

  DocumentModelCoords m_modelCoords;
  QPointF m_posOriginScreen;
};

#endif // CENTIPEDE_ENDPOINTS_POLAR_H
