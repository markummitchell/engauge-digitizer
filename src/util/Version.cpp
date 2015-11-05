#include "Version.h"

const char *VERSION_NUMBER = "6.2";

QString engaugeWindowTitle()
{
  QString str = QString ("Engauge - %1").arg (VERSION_NUMBER);

  return str;
}
