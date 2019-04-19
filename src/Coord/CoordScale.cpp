/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordScale.h"

QString coordScaleToString (CoordScale coordScale)
{
  QString rtn;

  switch (coordScale) {
    case COORD_SCALE_LINEAR:
      rtn ="Linear";
      break;

    case COORD_SCALE_LOG:
      rtn = "Log";
      break;
  }

  return rtn;
}
