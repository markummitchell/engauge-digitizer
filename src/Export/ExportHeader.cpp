/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportHeader.h"
#include <QObject>

QString exportHeaderToString (ExportHeader exportHeader)
{
  QString rtn;

  switch (exportHeader) {
    case EXPORT_HEADER_GNUPLOT:
      rtn = QObject::tr ("Gnuplot");
      break;

    case EXPORT_HEADER_NONE:
      rtn = QObject::tr ("None");
      break;

    case EXPORT_HEADER_SIMPLE:
      rtn = QObject::tr ("Simple");
      break;
  }

  return rtn;
}
