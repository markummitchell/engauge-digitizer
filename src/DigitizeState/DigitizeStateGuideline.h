/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_GUIDELINE_H
#define DIGITIZE_STATE_GUIDELINE_H

#include "DigitizeStateAbstractBase.h"
#include <QPoint>

class CentipedePair;
class DocumentModelPointMatch;
class QGraphicsEllipseItem;
class QGraphicsPixmapItem;
class QImage;

/// Digitizing state for creating, moving and removing guidelines
class DigitizeStateGuideline : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateGuideline(DigitizeStateContext &context);
  virtual ~DigitizeStateGuideline();

  virtual QString activeCurve () const;
  virtual void begin(CmdMediator *cmdMediator,
                     DigitizeState previousState);
  virtual bool canPaste (const Transformation &transformation,
                         const QSize &viewSize) const;
  virtual QCursor cursor (CmdMediator *cmdMediator) const;
  virtual void end();
  virtual bool guidelinesAreSelectable () const;
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
  virtual void updateAfterPointAddition();
  virtual void updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                         const DocumentModelDigitizeCurve &curve);
  virtual void updateModelSegments (const DocumentModelSegments &modelSegments);
  
private:
  DigitizeStateGuideline();

  void killCentipede ();

  // Temporary graphics object the user interacts with to specify the guideline as X/T or Y/R
  CentipedePair *m_centipedePair;
};

#endif // DIGITIZE_STATE_GUIDELINE_H
