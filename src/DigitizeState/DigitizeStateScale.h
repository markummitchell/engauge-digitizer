/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_SCALE_H
#define DIGITIZE_STATE_SCALE_H

#include "DigitizeStateAbstractBase.h"
#include <QObject>

class GraphicsPoint;
class QGraphicsLineItem;
class QPointF;

/// Digitizing state for creating the scale bar. A scale bar is preferred over an approach using two axis points
/// and DigitizeStateAxis since:
/// -# Fewer clicks are involved to move the scale bar. One click and drag operation moves the scale bar, but two click and
///    drag operations would be needed to move two axis points
/// -# Clicking on a large scale bar is easier than clicking on much smaller axis points
/// -# DigitizeStateAxis solution would have a line, representing the scale bar, that would be unselectable - confusing to users
class DigitizeStateScale : public QObject, public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateScale(DigitizeStateContext &context);
  virtual ~DigitizeStateScale();

  virtual QString activeCurve () const;
  virtual void begin(CmdMediator *cmdMediator,
                     DigitizeState previousState);
  virtual bool canPaste (const Transformation &transformation,
                         const QSize &viewSize) const;
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
  DigitizeStateScale();

  void removeTemporaryPointsAndLine();
  void updateLineGeometry ();

  QString m_pointIdentifier0;
  QString m_pointIdentifier1;
  GraphicsPoint *m_temporaryPoint0;
  GraphicsPoint *m_temporaryPoint1;

  QGraphicsLineItem *m_line;
};

#endif // DIGITIZE_STATE_SCALE_H
