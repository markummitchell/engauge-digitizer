/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_UNITS_DATE_H
#define COORD_UNITS_DATE_H

#include <QString>

enum CoordUnitsDate {
  COORD_UNITS_DATE_SKIP,
  COORD_UNITS_DATE_MONTH_DAY_YEAR,
  COORD_UNITS_DATE_DAY_MONTH_YEAR,
  COORD_UNITS_DATE_YEAR_MONTH_DAY,
  NUM_COORD_UNITS_DATE
};

extern QString coordUnitsDateToString (CoordUnitsDate coordUnits);

#endif // COORD_UNITS_DATE_H
