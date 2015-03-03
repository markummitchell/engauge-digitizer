#ifndef EXPORT_HEADER_H
#define EXPORT_HEADER_H

#include <QString>

enum ExportHeader {
  EXPORT_HEADER_NONE,
  EXPORT_HEADER_SIMPLE,
  EXPORT_HEADER_GNUPLOT
};

extern QString exportHeaderToString (ExportHeader exportHeader);

#endif // EXPORT_HEADER_H
