#ifndef DIGITIZE_STATE_POINT_MATCH_H
#define DIGITIZE_STATE_POINT_MATCH_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state for matching Curve Points, one at a time.
class DigitizeStatePointMatch : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStatePointMatch(DigitizeStateContext &context);
  virtual ~DigitizeStatePointMatch();

  virtual QString activeCurve () const;
  virtual void begin(DigitizeState previousState);
  virtual QCursor cursor () const;
  virtual void end();
  virtual void handleCurveChange();
  virtual void handleKeyPress (Qt::Key key);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);
  virtual QString state() const;

private:
  DigitizeStatePointMatch();
};

#endif // DIGITIZE_STATE_POINT_MATCH_H
