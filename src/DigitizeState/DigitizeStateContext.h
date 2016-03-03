/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_CONTEXT_H
#define DIGITIZE_STATE_CONTEXT_H

#include "DigitizeStateAbstractBase.h"
#include "PointStyle.h"
#include <QCursor>
#include <QGraphicsView>
#include <QObject>
#include <QVector>

class CmdAbstractBase;
class DocumentModelDigitizeCurve;
class DocumentModelSegments;
class MainWindow;
class QUndoCommand;

/// Container for all DigitizeStateAbstractBase subclasses. This functions as the context class in a standard state machine implementation
class DigitizeStateContext : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  DigitizeStateContext(MainWindow &mainWindow,
                       QGraphicsView &view,
                       bool isGnuplot);
  virtual ~DigitizeStateContext ();

  /// Curve name for active Curve. This can include AXIS_CURVE_NAME, and empty string
  QString activeCurve () const;

  /// Append just-created QUndoCommand to command stack. This is called from DigitizeStateAbstractBase subclasses
  void appendNewCmd(CmdMediator *cmdMediator,
                    QUndoCommand *cmd);

  /// See DigitizeStateAbstractBase::handleContextMenuEvent.
  void handleContextMenuEvent (CmdMediator *cmdMediator,
                               const QString &pointIdentifier);

  /// See DigitizeStateAbstractBase::handleCurveChange.
  void handleCurveChange (CmdMediator *cmdMediator);

  /// See DigitizeStateAbstractBase::handleKeyPress.
  void handleKeyPress (CmdMediator *cmdMediator,
                       Qt::Key key,
                       bool atLeastOneSelectedItem);

  /// See DigitizeStateAbstractBase::handleLeave.
  void handleLeave (CmdMediator *cmdMediator);

  /// See DigitizeStateAbstractBase::handleMouseMove.
  void handleMouseMove (CmdMediator *cmdMediator,
                        QPointF pos);

  /// See DigitizeStateAbstractBase::handleMousePress.
  void handleMousePress (CmdMediator *cmdMediator,
                         QPointF pos);

  /// See DigitizeStateAbstractBase::handleMouseRelease.
  void handleMouseRelease (CmdMediator *cmdMediator,
                           QPointF pos);

  /// See DigitizeStateAbstractBase::handleSetOverrideCursor
  void handleSetOverrideCursor (CmdMediator *cmdMediator,
                                const QCursor &cursor);

  /// Get method for gnuplot flag
  bool isGnuplot () const;

  /// Reference to the MainWindow, without const.
  MainWindow &mainWindow ();

  /// Reference to the MainWindow, with const.
  const MainWindow &mainWindow () const;

  /// Initiate state transition to be performed later, when DigitizeState is off the stack
  void requestDelayedStateTransition (DigitizeState digitizeState);

  /// Perform immediate state transition. Called from outside state machine
  void requestImmediateStateTransition (CmdMediator *cmdMediator,
                                        DigitizeState digitizeState);

  /// Resetting makes re-initializes for documents after the first
  void resetOnLoad (CmdMediator *cmdMediator);

  /// Set cursor after asking state for the new cursor shape.
  void setCursor (CmdMediator *cmdMediator);

  /// Set QGraphicsView drag mode (in m_view). Called from DigitizeStateAbstractBase subclasses
  void setDragMode (QGraphicsView::DragMode dragMode);

  /// Set the image so QGraphicsView cursor and drag mode are accessible
  void setImageIsLoaded (CmdMediator *cmdMediator,
                         bool imageIsLoaded);

  /// State name for debugging
  QString state() const;

  /// Update the digitize curve settings
  void updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                 const DocumentModelDigitizeCurve &modelDigitizeCurve);

  /// Update the segments given the new settings
  void updateModelSegments(const DocumentModelSegments &modelSegments);

  /// QGraphicsView for use by DigitizeStateAbstractBase subclasses
  QGraphicsView &view();

private:
  DigitizeStateContext();

  void completeRequestedStateTransitionIfExists (CmdMediator *cmdMediator);

  MainWindow &m_mainWindow;
  QGraphicsView &m_view;
  bool m_imageIsLoaded; // Cursor and dragging can be affected by whether or not image is loaded

  QVector<DigitizeStateAbstractBase*> m_states;
  DigitizeState m_currentState;
  DigitizeState m_requestedState; // Same as m_currentState until requestDelayedStateTransition is called

  bool m_isGnuplot;
};

#endif // DIGITIZE_STATE_CONTEXT_H
