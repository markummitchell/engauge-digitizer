/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_HEADER_H
#define EXPORT_HEADER_H

#include <QString>

enum ExportHeader {
  EXPORT_HEADER_NONE,
  EXPORT_HEADER_SIMPLE,
  EXPORT_HEADER_GNUPLOT
};

extern QString exportHeaderToString (ExportHeader exportHeader);

#endif // EXPORT_HEADER_H
