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
