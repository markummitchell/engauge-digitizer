/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORDS_TYPE_H
#define COORDS_TYPE_H

#include <QString>

enum CoordsType {
  COORDS_TYPE_CARTESIAN,
  COORDS_TYPE_POLAR
};

extern QString coordsTypeToString (CoordsType coordsType);

#endif // COORDS_TYPE_H
