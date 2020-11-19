/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_ENDPOINTS_CARTESIAN_H
#define CENTIPEDE_ENDPOINTS_CARTESIAN_H

#include "CentipedeEndpointsAbstract.h"
#include "CentipedeIntersectionType.h"
#include "DocumentModelGuideline.h"
#include <QPointF>
#include "Transformation.h"

/// Compute endpoints for cartesian centipedes
class CentipedeEndpointsCartesian : public CentipedeEndpointsAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeEndpointsCartesian(const DocumentModelGuideline &modelGuideline,
                              const Transformation &transformation,
                              const QPointF &posClickScreen);
  virtual ~CentipedeEndpointsCartesian ();

  /// Screen point for X value of circle-center/coordinate intersection
  QPointF posScreenConstantXForCenterY (double radius) const;

  /// Screen point for X value of circle/coordinate intersection in the increasing Y direction
  QPointF posScreenConstantXForHighY (double radius) const;

  /// Screen point for X value of circle/coordinate intersection in the decreasing Y direction
  QPointF posScreenConstantXForLowY (double radius) const;

  /// Screen point for Y value of circle-center/coordinate intersection
  QPointF posScreenConstantYForCenterX (double radius) const;

  /// Screen point for Y value of circle/coordinate intersection in the increasing X direction
  QPointF posScreenConstantYForHighX (double radius) const;

  /// Screen point for Y value of circle/coordinate intersection in the decreasing X direction
  QPointF posScreenConstantYForLowX (double radius) const;
  
private:
  CentipedeEndpointsCartesian();

  /// Solves posScreenConstantXForHighY and posScreenConstantXForLowY  
  QPointF posScreenConstantXCommon (double radius,
                                    CentipedeIntersectionType intersectionType) const;

  /// Solves posScreenConstantYHighX and posScreenConstantYLowX  
  QPointF posScreenConstantYCommon (double radius,
                                    CentipedeIntersectionType intersectionType) const;

};

#endif // CENTIPEDE_ENDPOINTS_CARTESIAN_H
