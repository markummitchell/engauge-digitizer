/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CURSOR_SIZE_H
#define CURSOR_SIZE_H

/// Custom cursor sizes supported on all platforms for the most part, according to QCursor documentation
enum CursorSize {
  CURSOR_SIZE_16,
  CURSOR_SIZE_32,
  CURSOR_SIZE_48,
  CURSOR_SIZE_64,
  NUM_CURSOR_SIZES
};

extern int CursorSizeToPixels (CursorSize cursorSize);

#endif // CURSOR_SIZE_H
