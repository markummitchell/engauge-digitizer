#ifndef EXPORT_LAYOUT_FUNCTIONS_H
#define EXPORT_LAYOUT_FUNCTIONS_H

#include <QString>

enum ExportLayoutFunctions {
  EXPORT_LAYOUT_ALL_PER_LINE,
  EXPORT_LAYOUT_ONE_PER_LINE
};

extern QString exportLayoutFunctionsToString (ExportLayoutFunctions exportLayoutFunctions);

#endif // EXPORT_LAYOUT_FUNCTIONS_H
