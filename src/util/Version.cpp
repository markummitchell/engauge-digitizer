#include "Version.h"

const char *VERSION_NUMBER = "7.0";

QString engaugeWindowTitle()
{
  QString str = QString ("Engauge - %1").arg (VERSION_NUMBER);

  return str;
}
