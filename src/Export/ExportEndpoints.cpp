/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportEndpoints.h"
#include <QObject>

QString exportEndpointsToString (ExportEndpoints exportEndpoints)
{
  switch (exportEndpoints) {
    case EXPORT_ENDPOINTS_OMIT:
      return QObject::tr ("Omit");

    case EXPORT_ENDPOINTS_INCLUDE:
      return QObject::tr ("Include");

    case EXPORT_ENDPOINTS_EXTRAPOLATE_PAST:
      return QObject::tr ("ExtrapolatePast");

    default:
      return QObject::tr ("Unknown");
  }
}
