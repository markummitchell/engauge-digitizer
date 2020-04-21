/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_VIEW_STATE_H
#define GUIDELINE_VIEW_STATE_H

#include <QString>

/// Set of possible Guideline view states
enum GuidelineViewState {
  GUIDELINE_VIEW_STATE_EDIT,
  GUIDELINE_VIEW_STATE_HIDE,
  GUIDELINE_VIEW_STATE_LOCK,
  NUM_GUIDELINE_VIEW_STATES
};

extern QString guidelineViewStateAsString (GuidelineViewState state);

#endif // GUIDELINE_VIEW_STATE_H
