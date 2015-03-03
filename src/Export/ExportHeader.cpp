#include "ExportHeader.h"

QString exportHeaderToString (ExportHeader exportHeader)
{
  switch (exportHeader) {
    case EXPORT_HEADER_GNUPLOT:
      return "Gnuplot";

    case EXPORT_HEADER_NONE:
      return "None";

    case EXPORT_HEADER_SIMPLE:
      return "Simple";

    default:
      return "Unknown";
  }
}
