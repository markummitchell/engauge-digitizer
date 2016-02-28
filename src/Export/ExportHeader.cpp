#include "ExportHeader.h"
#include <QObject>

QString exportHeaderToString (ExportHeader exportHeader)
{
  switch (exportHeader) {
    case EXPORT_HEADER_GNUPLOT:
      return QObject::tr ("Gnuplot");

    case EXPORT_HEADER_NONE:
      return QObject::tr ("None");

    case EXPORT_HEADER_SIMPLE:
      return QObject::tr ("Simple");

    default:
      return QObject::tr ("Unknown");
  }
}
