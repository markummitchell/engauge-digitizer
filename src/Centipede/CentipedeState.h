/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_STATE_H
#define CENTIPEDE_STATE_H

#include <QString>

/// Set of possible states of Centipede construction
enum CentipedeState {
  CENTIPEDE_STATE_BUILD_CARTESIAN,
  CENTIPEDE_STATE_BUILD_POLAR,
  CENTIPEDE_STATE_PREBUILD,
  NUM_CENTIPEDE_STATES
};

extern QString centipedeStateAsString (CentipedeState state);

#endif // CENTIPEDE_STATE_H
