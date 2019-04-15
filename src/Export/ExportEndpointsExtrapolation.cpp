/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportEndpointsExtrapolation.h"
#include <QObject>

QString exportEndpointsExtrapolationToString (ExportEndpointsExtrapolation exportEndpointsExtrapolation)
{
  switch (exportEndpointsExtrapolation) {
    case EXPORT_ENDPOINTS_EXTRAPOLATION_STAY_WITHIN:
      return QObject::tr ("Stay Within");

    case EXPORT_ENDPOINTS_EXTRAPOLATION_EXTRAPOLATE_OUTSIDE:
      return QObject::tr ("Extrapolate Outside");

    default:
      return QObject::tr ("Unknown");
  }
}
