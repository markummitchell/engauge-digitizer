/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_UNITS_POLAR_THETA_H
#define COORD_UNITS_POLAR_THETA_H

#include <QString>

extern const QChar THETA;

enum CoordUnitsPolarTheta {
  COORD_UNITS_POLAR_THETA_DEGREES, // Degrees symbol is optional on input, and not included on output for easier postprocessing
  COORD_UNITS_POLAR_THETA_DEGREES_MINUTES,
  COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS,
  COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW,
  COORD_UNITS_POLAR_THETA_GRADIANS,
  COORD_UNITS_POLAR_THETA_RADIANS,
  COORD_UNITS_POLAR_THETA_TURNS,
  NUM_COORD_UNITS_POLAR_THETA
};

extern QString coordUnitsPolarThetaToBriefType (CoordUnitsPolarTheta coordUnits);
extern QString coordUnitsPolarThetaToString (CoordUnitsPolarTheta coordUnitsPolarTheta);

#endif // COORD_UNITS_POLAR_THETA_H
