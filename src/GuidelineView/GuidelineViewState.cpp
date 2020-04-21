/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineViewState.h"
#include <QHash>

typedef QHash<GuidelineViewState, QString> GuidelineViewStateHash;

static GuidelineViewStateHash guidelineViewStateHash;

QString guidelineViewStateAsString (GuidelineViewState state)
{
  if (guidelineViewStateHash.size () == 0) {

    // First time through we load the hash
    guidelineViewStateHash [GUIDELINE_VIEW_STATE_HIDE] = "Hide";
    guidelineViewStateHash [GUIDELINE_VIEW_STATE_EDIT] = "Edit";
    guidelineViewStateHash [GUIDELINE_VIEW_STATE_LOCK] = "Lock";
  }

  if (guidelineViewStateHash.contains (state)) {
    return guidelineViewStateHash [state];
  } else {
    return "?";
  }
}
