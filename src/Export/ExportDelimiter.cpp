/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportDelimiter.h"
#include <QObject>

QString exportDelimiterToString (ExportDelimiter exportDelimiter)
{
  QString rtn;

  switch (exportDelimiter) {
    case EXPORT_DELIMITER_COMMA:
      rtn = QObject::tr ("Commas");
      break;

    case EXPORT_DELIMITER_SEMICOLON:
      rtn = QObject::tr ("Semicolons");
      break;

    case EXPORT_DELIMITER_SPACE:
      rtn = QObject::tr ("Spaces");
      break;

    case EXPORT_DELIMITER_TAB:
      rtn = QObject::tr ("Tabs");
      break;
  }

  return rtn;
}

QString exportDelimiterToText (ExportDelimiter exportDelimiter,
                               bool isGnuplotDelimiter)
{
  QString rtn;

  switch (exportDelimiter) {
    case EXPORT_DELIMITER_COMMA:
      if (isGnuplotDelimiter) {
        rtn = ", "; // Gnuplot needs a space
      } else {
        rtn = ",";
      }
      break;

    case EXPORT_DELIMITER_SEMICOLON:
      rtn = ";";
      break;

    case EXPORT_DELIMITER_SPACE:
      rtn = " ";
      break;

    case EXPORT_DELIMITER_TAB:
      rtn = "\t";
      break;
  }

  return rtn;
}
