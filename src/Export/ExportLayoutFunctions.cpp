#include "ExportLayoutFunctions.h"
#include <QObject>

QString
exportLayoutFunctionsToString(ExportLayoutFunctions exportLayoutFunctions) {
  switch (exportLayoutFunctions) {
  case EXPORT_LAYOUT_ALL_PER_LINE:
    return QObject::tr("AllPerLine");

  case EXPORT_LAYOUT_ONE_PER_LINE:
    return QObject::tr("OnePerLine");

  default:
    return QObject::tr("Unknown");
  }
}
