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

  /// Screen point for XT value of circle-center/coordinate intersection. Works for both cartesian and polar coordinates
  QPointF posScreenConstantXTForCenterYR (double radius) const;

  /// Screen point for XT value of circle/coordinate intersection in the increasing YR direction. Works for both cartesian and polar coordinates
  QPointF posScreenConstantXTForHighYR (double radius) const;

  /// Screen point for XT value of circle/coordinate intersection in the decreasing YR direction. Works for both cartesian and polar coordinates
  QPointF posScreenConstantXTForLowYR (double radius) const;

  /// Screen point for YR value of circle-center/coordinate intersection. Works for both cartesian and polar coordinates
  QPointF posScreenConstantYRForCenterXT (double radius) const;

  /// Screen point for YR value of circle/coordinate intersection in the increasing XT direction. Works for both cartesian and polar coordinates
  QPointF posScreenConstantYRForHighXT (double radius) const;

  /// Screen point for YR value of circle/coordinate intersection in the decreasing XT direction. Works for both cartesian and polar coordinates
  QPointF posScreenConstantYRForLowXT (double radius) const;
  
private:
  CentipedeEndpointsCartesian();

  /// Solves posScreenConstantXTForHighYR and posScreenConstantXTForLowYR  
  QPointF posScreenConstantXTCommon (double radius,
                                     CentipedeIntersectionType intersectionType) const;

  /// Solves posScreenConstantYRHighXT and posScreenConstantYRLowXT  
  QPointF posScreenConstantYRCommon (double radius,
                                     CentipedeIntersectionType intersectionType) const;

};

#endif // CENTIPEDE_ENDPOINTS_CARTESIAN_H
