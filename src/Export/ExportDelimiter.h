#ifndef EXPORT_DELIMITER_H
#define EXPORT_DELIMITER_H

#include <QString>

enum ExportDelimiter {
  EXPORT_DELIMITER_COMMA,
  EXPORT_DELIMITER_SPACE,
  EXPORT_DELIMITER_TAB
};

extern QString exportDelimiterToString (ExportDelimiter exportDelimiter);

#endif // EXPORT_DELIMITER_H
