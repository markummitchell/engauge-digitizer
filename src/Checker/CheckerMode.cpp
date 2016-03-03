/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CheckerMode.h"
#include <QObject>

QString checkerModeToString (CheckerMode checkerMode)
{
  switch (checkerMode) {
    case CHECKER_MODE_NEVER:
      return QObject::tr ("Never");

    case CHECKER_MODE_N_SECONDS:
      return QObject::tr ("NSeconds");

    case CHECKER_MODE_FOREVER:
      return QObject::tr ("Forever");

    default:
      return QObject::tr ("Unknown");
  }
}
