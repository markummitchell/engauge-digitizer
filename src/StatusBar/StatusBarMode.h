/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef STATUS_BAR_MODE_H
#define STATUS_BAR_MODE_H

#include <QString>

enum StatusBarMode {
  STATUS_BAR_MODE_ALWAYS,
  STATUS_BAR_MODE_NEVER,
  STATUS_BAR_MODE_TEMPORARY
};

extern QString statusBarModeToString (StatusBarMode statusBarMode);

#endif // STATUS_BAR_MODE_H
