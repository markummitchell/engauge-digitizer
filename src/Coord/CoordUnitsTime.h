#ifndef COORD_UNITS_TIME_H
#define COORD_UNITS_TIME_H

#include <QString>

enum CoordUnitsTime {
  COORD_UNITS_TIME_SKIP,
  COORD_UNITS_TIME_HOUR_MINUTE,
  COORD_UNITS_TIME_HOUR_MINUTE_SECOND,
  NUM_COORD_UNITS_TIME
};

extern QString coordUnitsTimeToString(CoordUnitsTime coordUnits);

#endif // COORD_UNITS_TIME_H
