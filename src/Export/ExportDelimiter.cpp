/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportDelimiter.h"
#include <QObject>

QString exportDelimiterToString (ExportDelimiter exportDelimiter)
{
  switch (exportDelimiter) {
    case EXPORT_DELIMITER_COMMA:
      return QObject::tr ("Commas");

    case EXPORT_DELIMITER_SPACE:
      return QObject::tr ("Spaces");

    case EXPORT_DELIMITER_TAB:
      return QObject::tr ("Tabs");

    default:
      return QObject::tr ("Unknown");
  }
}

QString exportDelimiterToText (ExportDelimiter exportDelimiter)
{
  switch (exportDelimiter) {
    case EXPORT_DELIMITER_COMMA:
      return ",";

    case EXPORT_DELIMITER_SPACE:
      return " ";

    case EXPORT_DELIMITER_TAB:
      return "\t";

    default:
      return "?";
  }
}
