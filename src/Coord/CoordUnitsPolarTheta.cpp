#include "CoordSymbol.h"
#include "CoordUnitsPolarTheta.h"

QString coordUnitsPolarThetaToBriefType (CoordUnitsPolarTheta coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_POLAR_THETA_DEGREES:
      return "Degrees";

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
      return "Degrees";

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      return "Degrees";

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      return "Degrees";

    case COORD_UNITS_POLAR_THETA_GRADIANS:
      return "Gradians";

    case COORD_UNITS_POLAR_THETA_RADIANS:
      return "Radians";

    case COORD_UNITS_POLAR_THETA_TURNS:
      return "Turns";

    default:
      return "Unknown";
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
      return "Unknown";
  }
}
