/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_ENDPOINTS_POLAR_H
#define CENTIPEDE_ENDPOINTS_POLAR_H

#include "CentipedeEndpointsAbstract.h"
#include "DocumentModelGuideline.h"
#include <QPointF>
#include "Transformation.h"

/// Compute endpoints for polar centipedes
class CentipedeEndpointsPolar : public CentipedeEndpointsAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeEndpointsPolar(const DocumentModelGuideline &modelGuideline,
                          const Transformation &transformation,
                          const QPointF &posClickScreen);
  virtual ~CentipedeEndpointsPolar ();
  
  /// Screen angle at origin from ellipse axis to circle-center/coordinate intersection. Works only for polar coordinates
  double angleScreenConstantYRCenterAngle (double radiusAboutClick) const;

  /// Screen angle at origin from ellipse axis to circle/coordinate intersection in the increasing angle direction (high)
  /// or decreasing angle direction (low). Uses center angle from angleScreenConstantYRCenterAngle. Works only for polar coordinates
  void angleScreenConstantYRHighLowAngles (double radiusAboutClick,
                                           double angleCenter,
                                           double &angleLow,
                                           double &angleHigh) const;

  /// Endpoints for radial line in polar coordinates
  void posScreenConstantYRForXTHighLowAngles (double radius,
                                              QPointF &posLow,
                                              QPointF &posHigh) const;
  
private:
  CentipedeEndpointsPolar();

  double closestAngleToCentralAngle (double angleCenter,
                                     double angleOld) const;

};

#endif // CENTIPEDE_ENDPOINTS_POLAR_H
