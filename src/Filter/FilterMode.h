#ifndef FILTER_MODE_H
#define FILTER_MODE_H

#include <QString>

enum FilterMode {
  FILTER_MODE_FOREGROUND,
  FILTER_MODE_HUE,
  FILTER_MODE_INTENSITY,
  FILTER_MODE_SATURATION,
  FILTER_MODE_VALUE,
  NUM_FILTER_MODES
};

extern QString filterModeToString (FilterMode filterMode);

#endif // FILTER_MODE_H
