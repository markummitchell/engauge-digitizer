/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordUnitsDate.h"
#include <QObject>

QString coordUnitsDateToString (CoordUnitsDate coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_DATE_DAY_MONTH_YEAR:
      return QObject::tr ("DD/MM/YYYY");

    case COORD_UNITS_DATE_MONTH_DAY_YEAR:
      return QObject::tr ("MM/DD/YYYY");

    case COORD_UNITS_DATE_YEAR_MONTH_DAY:
      return QObject::tr ("YYYY/MM/DD");

    case COORD_UNITS_DATE_SKIP:
      return "";

    default:
      return QObject::tr ("unknown");
  }
}
