#ifndef DIGITIZE_STATE_COLOR_PICKER_H
#define DIGITIZE_STATE_COLOR_PICKER_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state for selecting a color for DigitizeStateSegment.
class DigitizeStateColorPicker : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateColorPicker(DigitizeStateContext &context);
  virtual ~DigitizeStateColorPicker();

  virtual void begin();
  virtual QCursor cursor () const;
  virtual void end();
  virtual void handleKeyPress (Qt::Key key);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);

private:
  DigitizeStateColorPicker();
};

#endif // DIGITIZE_STATE_COLOR_PICKER_H
