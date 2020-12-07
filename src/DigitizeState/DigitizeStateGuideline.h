/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_GUIDELINE_H
#define DIGITIZE_STATE_GUIDELINE_H

#include "DigitizeStateAbstractBase.h"
#include <QPoint>

class CentipedeStateContext;
class DocumentModelPointMatch;
class MainWindow;
class QGraphicsEllipseItem;
class QGraphicsPixmapItem;
class QImage;

/// Digitizing state for creating, moving and removing guidelines
///
/// A challenge for creating guidelines was reconciling the multistep nature of
/// creating a guideline (click, move, move, ..., move done) with control-z. Initially
/// the control-z was grabbed by the command stack which would remove the previous
/// command while leaving the partially-complete guideline. Very confusing.
/// Three options were studied for reconciling the command stack and the guideline steps:
/// - Create a new command for each operation (mouse press, mouse move, and key press to
///   catch Escape key). Then use QUndoGroup to lump multiple commands into one big command.
///   This added multiple command and much complexity
/// - Use QUndoStack's beginMacro and endMacro which had same issues as first option
/// - Turn off QUndoStack and just have single stack command when finished. This option
///   was selected since the complexity is kept within DigitizeStateGuideline. This
///   calls QUndoStack::setActive to enable/disable the command stack
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

  /// Create command to add Guideline for CentipedeStateContext
  void createGuidelineCommand (bool selectedXT,
                               double valueSelected);

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

  bool hitTestForGraphics (const QPointF &posScreen);
  void lockNonGuidelinesAndUnlockGuidelines (bool lockdown);

  // State machine wrapping the temporary graphics items the user interacts with
  // to specify the guideline as X/T or Y/R
  CentipedeStateContext *m_context;
};

#endif // DIGITIZE_STATE_GUIDELINE_H
