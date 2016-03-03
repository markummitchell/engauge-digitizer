/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_UNITS_TIME_H
#define COORD_UNITS_TIME_H

#include <QString>

enum CoordUnitsTime {
  COORD_UNITS_TIME_SKIP,
  COORD_UNITS_TIME_HOUR_MINUTE,
  COORD_UNITS_TIME_HOUR_MINUTE_SECOND,
  NUM_COORD_UNITS_TIME
};

extern QString coordUnitsTimeToString (CoordUnitsTime coordUnits);

#endif // COORD_UNITS_TIME_H
