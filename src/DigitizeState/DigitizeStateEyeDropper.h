#ifndef DIGITIZE_STATE_EYE_DROPPER_H
#define DIGITIZE_STATE_EYE_DROPPER_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state for selecting a color for DigitizeStateSegment.
class DigitizeStateEyeDropper : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateEyeDropper(DigitizeStateContext &context);
  virtual ~DigitizeStateEyeDropper();

  virtual void begin();
  virtual QCursor cursor () const;
  virtual void end();
  virtual void handleKeyPress (Qt::Key key);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);

private:
  DigitizeStateEyeDropper();
};

#endif // DIGITIZE_STATE_EYE_DROPPER_H
