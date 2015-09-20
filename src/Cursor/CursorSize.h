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
