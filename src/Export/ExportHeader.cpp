/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportHeader.h"
#include <QObject>

QString exportHeaderToString (ExportHeader exportHeader)
{
  switch (exportHeader) {
    case EXPORT_HEADER_GNUPLOT:
      return QObject::tr ("Gnuplot");

    case EXPORT_HEADER_NONE:
      return QObject::tr ("None");

    case EXPORT_HEADER_SIMPLE:
      return QObject::tr ("Simple");

    default:
      return QObject::tr ("Unknown");
  }
}
