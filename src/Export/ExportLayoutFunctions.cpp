/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportLayoutFunctions.h"
#include <QObject>

QString exportLayoutFunctionsToString (ExportLayoutFunctions exportLayoutFunctions)
{
  QString rtn;

  switch (exportLayoutFunctions) {
    case EXPORT_LAYOUT_ALL_PER_LINE:
      rtn = QObject::tr ("AllPerLine");
      break;

    case EXPORT_LAYOUT_ONE_PER_LINE:
      rtn = QObject::tr ("OnePerLine");
      break;
  }

  return rtn;
}
