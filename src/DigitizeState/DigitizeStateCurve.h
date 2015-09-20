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

  virtual QString activeCurve () const;
  virtual void begin(DigitizeState previousState);
  virtual QCursor cursor () const;
  virtual void end();
  virtual void handleCurveChange();
  virtual void handleKeyPress (Qt::Key key,
                               bool atLeastOneSelectedItem);
  virtual void handleMouseMove (QPointF posScreen);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);
  virtual QString state() const;
  virtual void updateModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments);

private:
  DigitizeStateCurve();
};

#endif // DIGITIZE_STATE_CURVE_H
