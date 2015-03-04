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
