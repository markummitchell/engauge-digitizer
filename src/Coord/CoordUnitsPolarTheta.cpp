/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordSymbol.h"
#include "CoordUnitsPolarTheta.h"
#include <QObject>

QString coordUnitsPolarThetaToBriefType (CoordUnitsPolarTheta coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_POLAR_THETA_DEGREES:
      return QObject::tr ("Degrees");

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
      return QObject::tr ("Degrees");

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      return QObject::tr ("Degrees");

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      return QObject::tr ("Degrees");

    case COORD_UNITS_POLAR_THETA_GRADIANS:
      return QObject::tr ("Gradians");

    case COORD_UNITS_POLAR_THETA_RADIANS:
      return QObject::tr ("Radians");

    case COORD_UNITS_POLAR_THETA_TURNS:
      return QObject::tr ("Turns");

    default:
      return QObject::tr ("Unknown");
  }
}

QString coordUnitsPolarThetaToString (CoordUnitsPolarTheta coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_POLAR_THETA_DEGREES:
      return POLAR_UNITS_DEGREES;

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
      return POLAR_UNITS_DEGREES_MINUTES;

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      return POLAR_UNITS_DEGREES_MINUTES_SECONDS;

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      return POLAR_UNITS_DEGREES_MINUTES_SECONDS_NSEW;

    case COORD_UNITS_POLAR_THETA_GRADIANS:
      return POLAR_UNITS_GRADIANS;

    case COORD_UNITS_POLAR_THETA_RADIANS:
      return POLAR_UNITS_RADIANS;

    case COORD_UNITS_POLAR_THETA_TURNS:
      return POLAR_UNITS_TURNS;

    default:
      return QObject::tr ("Unknown");
  }
}
