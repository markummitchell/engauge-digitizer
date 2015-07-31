#include "CoordSymbol.h"
#include "CoordUnitsNonPolarTheta.h"

QString coordUnitsNonPolarThetaToBriefType (CoordUnitsNonPolarTheta coordUnits)
{
  switch (coordUnits) {

  case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
    return "Date Time";

  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    return "Degrees";

  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
    return "Degrees";

  case COORD_UNITS_NON_POLAR_THETA_NUMBER:
    return "Number";

  default:
    return "Unknown";
  }
}

QString coordUnitsNonPolarThetaToString (CoordUnitsNonPolarTheta coordUnits)
{
  switch (coordUnits) {

  case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
    return "Date/Time";
    
  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    return POLAR_UNITS_DEGREES_MINUTES_SECONDS;

  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
    return POLAR_UNITS_DEGREES_MINUTES_SECONDS_NSEW;

  case COORD_UNITS_NON_POLAR_THETA_NUMBER:
    return "Number";

  default:
    return "Unknown";
  }
}
