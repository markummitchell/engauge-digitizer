#ifndef DIGITIZE_STATE_POINT_MATCH_H
#define DIGITIZE_STATE_POINT_MATCH_H

#include "DigitizeStateAbstractBase.h"

class DocumentModelPointMatch;
class QGraphicsEllipseItem;
class QGraphicsPixmapItem;
class QImage;
class QPoint;

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
  virtual void handleMouseMove (QPointF posScreen);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);
  virtual QString state() const;

private:
  DigitizeStatePointMatch();

  QList<QPoint> extractSamplePointPixels (const QImage &img,
                                          const DocumentModelPointMatch &modelPointMatch,
                                          const QPointF &posScreen) const;
  void findPointsAndShowFirstCandidate (const QPointF &posScreen);
  bool pixelIsOnInImage (const QImage &img,
                         int x,
                         int y,
                         int radiusLimit) const;

  QGraphicsEllipseItem *m_outline;
  QGraphicsPixmapItem *m_candidatePoint;
};

#endif // DIGITIZE_STATE_POINT_MATCH_H
