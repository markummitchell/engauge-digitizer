#include "CheckerMode.h"
#include <QObject>

QString checkerModeToString (CheckerMode checkerMode)
{
  switch (checkerMode) {
    case CHECKER_MODE_NEVER:
      return QObject::tr ("Never");

    case CHECKER_MODE_N_SECONDS:
      return QObject::tr ("NSeconds");

    case CHECKER_MODE_FOREVER:
      return QObject::tr ("Forever");

    default:
      return QObject::tr ("Unknown");
  }
}
