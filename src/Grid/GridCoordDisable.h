/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_COORD_DISABLE_H
#define GRID_COORD_DISABLE_H

#include <QString>

enum GridCoordDisable {
  GRID_COORD_DISABLE_COUNT,
  GRID_COORD_DISABLE_START,
  GRID_COORD_DISABLE_STEP,
  GRID_COORD_DISABLE_STOP
};

extern QString gridCoordDisableToString (GridCoordDisable gridCoordDisable);

#endif // GRID_COORD_DISABLE_H
