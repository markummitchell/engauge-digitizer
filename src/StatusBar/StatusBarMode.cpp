/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "StatusBarMode.h"

QString statusBarModeToString (StatusBarMode statusBarMode)
{
  QString rtn;

  switch (statusBarMode) {
    case STATUS_BAR_MODE_ALWAYS:
      rtn = "Always";
      break;

    case STATUS_BAR_MODE_NEVER:
      rtn = "Never";
      break;

    case STATUS_BAR_MODE_TEMPORARY:
      rtn = "Temporary";
      break;      
  }

  return rtn;
}
