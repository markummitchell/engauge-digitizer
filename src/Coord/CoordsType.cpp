/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordsType.h"

QString coordsTypeToString (CoordsType coordsType)
{
  QString rtn;

  switch (coordsType) {
    case COORDS_TYPE_CARTESIAN:
      rtn = "Cartesian";
      break;

     case COORDS_TYPE_POLAR:
      rtn = "Polar";
      break;
  }

  return rtn;
}
