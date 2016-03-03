/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordSymbol.h"
#include "CoordUnitsNonPolarTheta.h"
#include <QObject>

QString coordUnitsNonPolarThetaToBriefType (CoordUnitsNonPolarTheta coordUnits)
{
  switch (coordUnits) {

  case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
    return QObject::tr ("Date Time");

  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    return QObject::tr ("Degrees");

  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
    return QObject::tr ("Degrees");

  case COORD_UNITS_NON_POLAR_THETA_NUMBER:
    return QObject::tr ("Number");

  default:
    return QObject::tr ("Unknown");
  }
}

QString coordUnitsNonPolarThetaToString (CoordUnitsNonPolarTheta coordUnits)
{
  switch (coordUnits) {

  case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
    return QObject::tr ("Date/Time");
    
  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    return POLAR_UNITS_DEGREES_MINUTES_SECONDS;

  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
    return POLAR_UNITS_DEGREES_MINUTES_SECONDS_NSEW;

  case COORD_UNITS_NON_POLAR_THETA_NUMBER:
    return QObject::tr ("Number");

  default:
    return QObject::tr ("Unknown");
  }
}
