#include "ExportLayoutFunctions.h"

QString exportLayoutFunctionsToString (ExportLayoutFunctions exportLayoutFunctions)
{
  switch (exportLayoutFunctions) {
    case EXPORT_LAYOUT_ALL_PER_LINE:
      return "AllPerLine";

    case EXPORT_LAYOUT_ONE_PER_LINE:
      return "OnePerLine";

    default:
      return "Unknown";
  }
}
