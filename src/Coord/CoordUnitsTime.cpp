/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordUnitsTime.h"
#include <QObject>

QString coordUnitsTimeToString (CoordUnitsTime coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_TIME_HOUR_MINUTE:
      return QObject::tr ("HH:MM");

    case COORD_UNITS_TIME_HOUR_MINUTE_SECOND:
      return QObject::tr ("HH:MM:SS");

    case COORD_UNITS_TIME_SKIP:
      return "";

    default:
      return QObject::tr ("unknown");
  }
}
