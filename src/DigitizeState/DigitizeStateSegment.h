#ifndef DIGITIZE_STATE_SEGMENT_H
#define DIGITIZE_STATE_SEGMENT_H

#include "DigitizeStateAbstractBase.h"
#include <QList>
#include <QObject>

class Segment;

/// Digitizing state for creating multiple Points along a highlighted segment.
class DigitizeStateSegment : public QObject, public DigitizeStateAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DigitizeStateSegment(DigitizeStateContext &context);
  virtual ~DigitizeStateSegment();

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

public slots:
  /// Receive signal from Segment that has been clicked on
  void slotMouseClickOnSegment(QPointF);

private:
  DigitizeStateSegment();

  // Identify which Segment owns the SegmentLine that was clicked on
  Segment *segmentFromSegmentStart (const QPointF &posSegmentStart) const;

  QList<Segment*> m_segments;
};

#endif // DIGITIZE_STATE_SEGMENT_H
