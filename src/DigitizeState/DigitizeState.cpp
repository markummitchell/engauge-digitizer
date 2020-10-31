/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DigitizeState.h"
#include <QHash>

typedef QHash<DigitizeState, QString> DigitizeStateHash;

static DigitizeStateHash digitizeStateHash;

QString digitizeStateAsString (DigitizeState state)
{
  if (digitizeStateHash.size () == 0) {

    // First time through we load the hash
    digitizeStateHash [DIGITIZE_STATE_AXIS] = "DigitizeStateAxis";
    digitizeStateHash [DIGITIZE_STATE_COLOR_PICKER] = "DigitizeStateColorPicker";
    digitizeStateHash [DIGITIZE_STATE_CURVE] = "DigitizeStateCurve";
    digitizeStateHash [DIGITIZE_STATE_EMPTY] = "DigitizeStateEmpty";
    digitizeStateHash [DIGITIZE_STATE_GUIDELINE] = "DigitizeStateGuideline";    
    digitizeStateHash [DIGITIZE_STATE_POINT_MATCH] = "DigitizeStatePointMatch";
    digitizeStateHash [DIGITIZE_STATE_SEGMENT] = "DigitizeStateSegment";
    digitizeStateHash [DIGITIZE_STATE_SELECT] = "DigitizeStateSelect";
    digitizeStateHash [DIGITIZE_STATE_SCALE] = "DigitizeStateScale";
  }

  if (digitizeStateHash.contains (state)) {
    return digitizeStateHash [state];
  } else {
    return "?";
  }
}
