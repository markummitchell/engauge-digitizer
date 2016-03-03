/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CursorSize.h"
#include "EngaugeAssert.h"

int CursorSizeToPixels (CursorSize cursorSize)
{
  ENGAUGE_ASSERT (cursorSize < NUM_CURSOR_SIZES);

  switch (cursorSize) {
  case CURSOR_SIZE_16:
    return 16;

  case CURSOR_SIZE_32:
    return 32;

  case CURSOR_SIZE_48:
    return 48;

  case CURSOR_SIZE_64:
    return 64;

  default:
    break;
  }

  ENGAUGE_ASSERT (false);
  return 0;
}
