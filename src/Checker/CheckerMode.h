#ifndef CHECKER_MODE_H
#define CHECKER_MODE_H

#include <QString>

/// Options for axes checker mode. Specifically, how long the checker is displayed after a change.
enum CheckerMode
{
  CHECKER_MODE_NEVER,
  CHECKER_MODE_N_SECONDS,
  CHECKER_MODE_FOREVER
};

extern QString checkerModeToString (CheckerMode checkerMode);

#endif // CHECKER_MODE_H
