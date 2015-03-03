#include "ExportDelimiter.h"

QString exportDelimiterToString (ExportDelimiter exportDelimiter)
{
  switch (exportDelimiter) {
    case EXPORT_DELIMITER_COMMA:
      return "Commas";

    case EXPORT_DELIMITER_SPACE:
      return "Spaces";

    case EXPORT_DELIMITER_TAB:
      return "Tabs";

    default:
      return "Unknown";
  }
}
