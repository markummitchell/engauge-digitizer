/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_H
#define DIGITIZE_STATE_H

#include <QString>

/// Set of possible states of Digitize toolbar.
enum DigitizeState {
  DIGITIZE_STATE_AXIS,
  DIGITIZE_STATE_COLOR_PICKER,
  DIGITIZE_STATE_CURVE,
  DIGITIZE_STATE_EMPTY,
  DIGITIZE_STATE_POINT_MATCH,
  DIGITIZE_STATE_SEGMENT,
  DIGITIZE_STATE_SELECT,
  DIGITIZE_STATE_SCALE, // Out of order for backwards compatibility with pre-version 10
  DIGITIZE_STATE_GUIDELINE, // Out of order for backwards compatibility with pre-version 13
  NUM_DIGITIZE_STATES
};

extern QString digitizeStateAsString (DigitizeState state);

#endif // DIGITIZE_STATE_H
