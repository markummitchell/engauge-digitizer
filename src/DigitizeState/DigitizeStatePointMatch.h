/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
  virtual void begin(CmdMediator *cmdMediator,
                     DigitizeState previousState);
  virtual QCursor cursor (CmdMediator *cmdMediator) const;
  virtual void end();
  virtual void handleContextMenuEventAxis (CmdMediator *cmdMediator,
                                           const QString &pointIdentifier);
  virtual void handleContextMenuEventGraph (CmdMediator *cmdMediator,
                                            const QStringList &pointIdentifiers);
  virtual void handleCurveChange(CmdMediator *cmdMediator);
  virtual void handleKeyPress (CmdMediator *cmdMediator,
                               Qt::Key key,
                               bool atLeastOneSelectedItem);
  virtual void handleMouseMove (CmdMediator *cmdMediator,
                                QPointF posScreen);
  virtual void handleMousePress (CmdMediator *cmdMediator,
                                 QPointF posScreen);
  virtual void handleMouseRelease (CmdMediator *cmdMediator,
                                   QPointF posScreen);
  virtual QString state() const;
  virtual void updateAfterPointAddition ();
  virtual void updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                         const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments);

private:
  DigitizeStatePointMatch();

  void createPermanentPoint (CmdMediator *cmdMediator,
                             const QPointF &posScreen);
  void createTemporaryPoint (CmdMediator *cmdMediator,
                             const QPoint &posScreen);
  QList<PointMatchPixel> extractSamplePointPixels (const QImage &img,
                                                   const DocumentModelPointMatch &modelPointMatch,
                                                   const QPointF &posScreen) const;
  void findPointsAndShowFirstCandidate (CmdMediator *cmdMediator,
                                        const QPointF &posScreen);
  bool pixelIsOnInImage (const QImage &img,
                         int x,
                         int y,
                         int radiusLimit) const;
  void popCandidatePoint (CmdMediator *cmdMediator);
  void promoteCandidatePointToPermanentPoint(CmdMediator *cmdMediator);

  QGraphicsEllipseItem *m_outline;
  QGraphicsPixmapItem *m_candidatePoint;

  // Candidate points sorted from best match to worst match. Once accepted, each is removed since there
  // is now an "official" point in the Document and GraphicsScene
  QList<QPoint> m_candidatePoints;

  QPoint m_posCandidatePoint;
};

#endif // DIGITIZE_STATE_POINT_MATCH_H
