/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_UNITS_NON_POLAR_THETA_H
#define COORD_UNITS_NON_POLAR_THETA_H

#include "CoordUnitsDate.h"
#include "CoordUnitsTime.h"
#include <QString>

enum CoordUnitsNonPolarTheta {
  COORD_UNITS_NON_POLAR_THETA_NUMBER,
  COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS,
  COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW,
  COORD_UNITS_NON_POLAR_THETA_DATE_TIME,
  NUM_COORD_UNITS_NON_POLAR_THETA
};

extern QString coordUnitsNonPolarThetaToBriefType (CoordUnitsNonPolarTheta coordUnits);
extern QString coordUnitsNonPolarThetaToString (CoordUnitsNonPolarTheta coordUnits);

#endif // COORD_UNITS_NON_POLAR_THETA_H
