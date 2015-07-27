#ifndef COORD_UNITS_NON_POLAR_THETA_H
#define COORD_UNITS_NON_POLAR_THETA_H

#include <QString>

enum CoordUnitsNonPolarTheta {
  COORD_UNITS_NON_POLAR_THETA_NUMBER,
  COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS,
  COORD_UNITS_NON_POLAR_THETA_DATE_TIME
};

extern QString coordUnitsNonPolarThetaToString (CoordUnitsNonPolarTheta coordUnitsNonPolarTheta);

#endif // COORD_UNITS_NON_POLAR_THETA_H
