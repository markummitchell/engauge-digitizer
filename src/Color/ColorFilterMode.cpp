#include "ColorFilterMode.h"

QString colorFilterModeToString (ColorFilterMode colorFilterMode)
{
  switch (colorFilterMode) {
    case COLOR_FILTER_MODE_FOREGROUND:
      return "Foreground";

    case COLOR_FILTER_MODE_HUE:
      return "Hue";

    case COLOR_FILTER_MODE_INTENSITY:
      return "Intensity";

    case COLOR_FILTER_MODE_SATURATION:
      return "Saturation";

    case COLOR_FILTER_MODE_VALUE:
      return "Value";

    default:
      return "Unknown";
  }
}
