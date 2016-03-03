/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportLayoutFunctions.h"
#include <QObject>

QString exportLayoutFunctionsToString (ExportLayoutFunctions exportLayoutFunctions)
{
  switch (exportLayoutFunctions) {
    case EXPORT_LAYOUT_ALL_PER_LINE:
      return QObject::tr ("AllPerLine");

    case EXPORT_LAYOUT_ONE_PER_LINE:
      return QObject::tr ("OnePerLine");

    default:
      return QObject::tr ("Unknown");
  }
}
