#ifndef DIGITIZE_STATE_POINT_MATCH_H
#define DIGITIZE_STATE_POINT_MATCH_H

#include "DigitizeStateAbstractBase.h"
#include "PointMatchPixel.h"
#include <QList>
#include <QPoint>

class DocumentModelPointMatch;
class QGraphicsEllipseItem;
class QGraphicsPixmapItem;
class QImage;

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
  virtual void handleKeyPress (Qt::Key key,
                               bool atLeastOneSelectedItem);
  virtual void handleMouseMove (QPointF posScreen);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);
  virtual QString state() const;
  virtual void updateModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments);

private:
  DigitizeStatePointMatch();

  void createPermanentPoint (const QPointF &posScreen);
  void createTemporaryPoint (const QPoint &posScreen);
  QList<PointMatchPixel> extractSamplePointPixels (const QImage &img,
                                                   const DocumentModelPointMatch &modelPointMatch,
                                                   const QPointF &posScreen) const;
  void findPointsAndShowFirstCandidate (const QPointF &posScreen);
  bool pixelIsOnInImage (const QImage &img,
                         int x,
                         int y,
                         int radiusLimit) const;
  void popCandidatePoint ();
  void promoteCandidatePointToPermanentPoint();

  QGraphicsEllipseItem *m_outline;
  QGraphicsPixmapItem *m_candidatePoint;

  // Candidate points sorted from best match to worst match. Once accepted, each is removed since there
  // is now an "official" point in the Document and GraphicsScene
  QList<QPoint> m_candidatePoints;

  QPoint m_posCandidatePoint;
};

#endif // DIGITIZE_STATE_POINT_MATCH_H
