/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Centipeder, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeState.h"
#include <QHash>

typedef QHash<CentipedeState, QString> CentipedeStateHash;

static CentipedeStateHash centipedeStateHash;

QString centipedeStateAsString (CentipedeState state)
{
  if (centipedeStateHash.size () == 0) {

    // First time through we load the hash
    centipedeStateHash [CENTIPEDE_STATE_BUILD_CARTESIAN] = "CentipedeStateBuildCartesian";
    centipedeStateHash [CENTIPEDE_STATE_BUILD_POLAR] = "CentipedeStateBuildPolar";
    centipedeStateHash [CENTIPEDE_STATE_PREBUILD] = "CentipedeStatePrebuild";
  }

  if (centipedeStateHash.contains (state)) {
    return centipedeStateHash [state];
  } else {
    return "?";
  }
}
