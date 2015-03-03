#include "FilterMode.h"

QString filterModeToString (FilterMode filterMode)
{
  switch (filterMode) {
    case FILTER_MODE_FOREGROUND:
      return "Foreground";

    case FILTER_MODE_HUE:
      return "Hue";

    case FILTER_MODE_INTENSITY:
      return "Intensity";

    case FILTER_MODE_SATURATION:
      return "Saturation";

    case FILTER_MODE_VALUE:
      return "Value";

    default:
      return "Unknown";
  }
}
