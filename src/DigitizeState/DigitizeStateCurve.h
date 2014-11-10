#ifndef DIGITIZE_STATE_CURVE_H
#define DIGITIZE_STATE_CURVE_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state for creating Curve Points, one at a time.
class DigitizeStateCurve : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateCurve(DigitizeStateContext &context);
  virtual ~DigitizeStateCurve();

  virtual void begin();
  virtual Qt::CursorShape cursorShape () const;
  virtual void end();
  virtual void handleKeyPress (Qt::Key key);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);

private:
  DigitizeStateCurve();
};

#endif // DIGITIZE_STATE_CURVE_H
