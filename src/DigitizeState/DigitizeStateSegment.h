#ifndef DIGITIZE_STATE_SEGMENT_H
#define DIGITIZE_STATE_SEGMENT_H

#include "DigitizeStateAbstractBase.h"
#include <QList>

class Segment;

/// Digitizing state for creating multiple Points along a highlighted segment.
class DigitizeStateSegment : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateSegment(DigitizeStateContext &context);
  virtual ~DigitizeStateSegment();

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
  DigitizeStateSegment();

  QList<Segment*> m_segments;
};

#endif // DIGITIZE_STATE_SEGMENT_H
