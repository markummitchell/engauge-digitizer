/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GridCoordDisable.h"
#include <QObject>

QString gridCoordDisableToString (GridCoordDisable gridCoordDisable)
{
  QString rtn;

  switch (gridCoordDisable) {
    case GRID_COORD_DISABLE_COUNT:
      rtn = QObject::tr ("Count");
      break;

    case GRID_COORD_DISABLE_START:
      rtn = QObject::tr ("Start");
      break;

    case GRID_COORD_DISABLE_STEP:
      rtn = QObject::tr ("Step");
      break;

    case GRID_COORD_DISABLE_STOP:
      rtn = QObject::tr ("Stop");
      break;
  }

  return rtn;
}
