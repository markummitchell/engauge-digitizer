#include "Version.h"

QString engaugeWindowTitle()
{
  QString str = QString ("Engauge - %1").arg (VERSION_NUMBER);

  return str;
}
