/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorFilterMode.h"
#include <QObject>

QString colorFilterModeToString (ColorFilterMode colorFilterMode)
{
  switch (colorFilterMode) {
    case COLOR_FILTER_MODE_FOREGROUND:
      return QObject::tr ("Foreground");

    case COLOR_FILTER_MODE_HUE:
      return QObject::tr ("Hue");

    case COLOR_FILTER_MODE_INTENSITY:
      return QObject::tr ("Intensity");

    case COLOR_FILTER_MODE_SATURATION:
      return QObject::tr ("Saturation");

    case COLOR_FILTER_MODE_VALUE:
      return QObject::tr ("Value");

    default:
      return QObject::tr ("Unknown");
  }
}
