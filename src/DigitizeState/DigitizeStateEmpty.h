#ifndef DIGITIZE_STATE_EMPTY_H
#define DIGITIZE_STATE_EMPTY_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state before a Document has been  created. In this state, the cursor is Qt::ArrowCursor.
class DigitizeStateEmpty : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateEmpty(DigitizeStateContext &context);
  virtual ~DigitizeStateEmpty();

  virtual void begin();
  virtual Qt::CursorShape cursorShape () const;
  virtual void end();
  virtual void handleKeyPress (Qt::Key key);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);

private:
  DigitizeStateEmpty();
};

#endif // DIGITIZE_STATE_EMPTY_H
