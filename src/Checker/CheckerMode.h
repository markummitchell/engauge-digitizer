/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
