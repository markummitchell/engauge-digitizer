#ifndef DIGITIZE_STATE_SEGMENT_H
#define DIGITIZE_STATE_SEGMENT_H

#include "DigitizeStateAbstractBase.h"
#include <QList>
#include <QObject>

class Segment;

/// Digitizing state for creating multiple Points along a highlighted segment.
class DigitizeStateSegment : public QObject, public DigitizeStateAbstractBase {
  Q_OBJECT;

public:
  /// Single constructor.
  DigitizeStateSegment(DigitizeStateContext &context);
  virtual ~DigitizeStateSegment();

  virtual QString activeCurve() const;
  virtual void begin(CmdMediator *cmdMediator, DigitizeState previousState);
  virtual QCursor cursor(CmdMediator *cmdMediator) const;
  virtual void end();
  virtual void handleCurveChange(CmdMediator *cmdMediator);
  virtual void handleKeyPress(CmdMediator *cmdMediator, Qt::Key key,
                              bool atLeastOneSelectedItem);
  virtual void handleMouseMove(CmdMediator *cmdMediator, QPointF posScreen);
  virtual void handleMousePress(CmdMediator *cmdMediator, QPointF posScreen);
  virtual void handleMouseRelease(CmdMediator *cmdMediator, QPointF posScreen);
  virtual QString state() const;
  virtual void updateModelDigitizeCurve(
      CmdMediator *cmdMediator,
      const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments);

public slots:
  /// Receive signal from Segment that has been clicked on. The CmdMediator from
  /// the begin method will be used
  void slotMouseClickOnSegment(QPointF);

private:
  DigitizeStateSegment();

  // Identify which Segment owns the SegmentLine that was clicked on
  Segment *segmentFromSegmentStart(const QPointF &posSegmentStart) const;

  QList<Segment *> m_segments;
  CmdMediator *m_cmdMediator;
};

#endif // DIGITIZE_STATE_SEGMENT_H
