#ifndef FILTER_COLOR_ENTRY_H
#define FILTER_COLOR_ENTRY_H

#include <QColor>

/// Helper class so Filter class can compute the background color.
struct FilterColorEntry {
  /// Unique color entry.
  QColor color;

  /// Number of times this color has appeared.
  unsigned int count;
};

#endif // FILTER_COLOR_ENTRY_H
