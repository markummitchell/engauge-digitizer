#ifndef DIGITIZE_STATE_EMPTY_H
#define DIGITIZE_STATE_EMPTY_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state before a Document has been created. In this state, the cursor is Qt::ArrowCursor.
class DigitizeStateEmpty : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateEmpty(DigitizeStateContext &context);
  virtual ~DigitizeStateEmpty();

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
  DigitizeStateEmpty();
};

#endif // DIGITIZE_STATE_EMPTY_H
