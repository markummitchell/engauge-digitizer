/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COLOR_FILTER_ENTRY_H
#define COLOR_FILTER_ENTRY_H

#include <QColor>

/// Helper class so ColorFilter class can compute the background color.
struct ColorFilterEntry {
  /// Unique color entry.
  QColor color;

  /// Number of times this color has appeared.
  unsigned int count;
};

#endif // COLOR_FILTER_ENTRY_H
