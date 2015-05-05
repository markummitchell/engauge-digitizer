#include "CheckerMode.h"

QString checkerModeToString (CheckerMode checkerMode)
{
  switch (checkerMode) {
    case CHECKER_MODE_NEVER:
      return "Never";

    case CHECKER_MODE_N_SECONDS:
      return "NSeconds";

    case CHECKER_MODE_FOREVER:
      return "Forever";

    default:
      return "Unknown";
  }
}
