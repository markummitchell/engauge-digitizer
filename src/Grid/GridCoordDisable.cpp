/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GridCoordDisable.h"
#include <QObject>

QString gridCoordDisableToString (GridCoordDisable gridCoordDisable)
{
  switch (gridCoordDisable) {
    case GRID_COORD_DISABLE_COUNT:
      return QObject::tr ("Count");

    case GRID_COORD_DISABLE_START:
      return QObject::tr ("Start");

    case GRID_COORD_DISABLE_STEP:
      return QObject::tr ("Step");

    case GRID_COORD_DISABLE_STOP:
      return QObject::tr ("Stop");

    default:
      return QObject::tr ("Unknown");
  }
}
