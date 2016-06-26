/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Version.h"

const char *VERSION_NUMBER = "8.3";

QString engaugeWindowTitle()
{
  QString str = QString ("Engauge - %1").arg (VERSION_NUMBER);

  return str;
}
