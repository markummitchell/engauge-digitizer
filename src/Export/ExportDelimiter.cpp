#include "ExportDelimiter.h"

QString exportDelimiterToString (ExportDelimiter exportDelimiter)
{
  switch (exportDelimiter) {
    case EXPORT_DELIMITER_COMMA:
      return "Comma";

    case EXPORT_DELIMITER_SPACE:
      return "Space";

    case EXPORT_DELIMITER_TAB:
      return "Tab";

    default:
      return "Unknown";
  }
}
