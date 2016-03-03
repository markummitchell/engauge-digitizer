/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportPointsIntervalUnits.h"
#include <QObject>

QString exportPointsIntervalUnitsToString (ExportPointsIntervalUnits exportPointsIntervalUnits)
{
  switch (exportPointsIntervalUnits) {
  case EXPORT_POINTS_INTERVAL_UNITS_GRAPH:
    return QObject::tr ("Graph Units");

  case EXPORT_POINTS_INTERVAL_UNITS_SCREEN:
    return QObject::tr ("Pixels");

  default:
    return QObject::tr ("Unknown");
  }
}
