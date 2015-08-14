#ifndef DIGITIZE_STATE_SCALE_H
#define DIGITIZE_STATE_SCALE_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state for creating a scale bar. Scale bars are for maps, for which there is no
/// two-dimensional set of coordinates but instead a length scale defined by the scale bar.
class DigitizeStateScale : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateScale(DigitizeStateContext &context);
  virtual ~DigitizeStateScale();

  virtual QString activeCurve () const;
  virtual void begin(DigitizeState previousState);
  virtual QCursor cursor () const;
  virtual void end();
  virtual void handleCurveChange();
  virtual void handleKeyPress (Qt::Key key);
  virtual void handleMouseMove (QPointF posScreen);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);
  virtual QString state() const;

private:
  DigitizeStateScale();
};

#endif // DIGITIZE_STATE_SCALE_H
