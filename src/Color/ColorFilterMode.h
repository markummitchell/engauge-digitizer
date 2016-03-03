/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COLOR_FILTER_MODE_H
#define COLOR_FILTER_MODE_H

#include <QString>

enum ColorFilterMode {
  COLOR_FILTER_MODE_FOREGROUND,
  COLOR_FILTER_MODE_HUE,
  COLOR_FILTER_MODE_INTENSITY,
  COLOR_FILTER_MODE_SATURATION,
  COLOR_FILTER_MODE_VALUE,
  NUM_COLOR_FILTER_MODES
};

extern QString colorFilterModeToString (ColorFilterMode colorFilterMode);

#endif // COLOR_FILTER_MODE_H
