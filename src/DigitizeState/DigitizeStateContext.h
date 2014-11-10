#ifndef DIGITIZE_STATE_CONTEXT_H
#define DIGITIZE_STATE_CONTEXT_H

#include "DigitizeStateAbstractBase.h"
#include <QGraphicsView>
#include <QObject>
#include <QVector>

class CmdAbstractBase;
class CmdMediator;
class DigitizeStateAbstractBase;
class MainWindow;
class QGraphicsPixmapItem;
class QUndoCommand;

/// Container for all DigitizeStateAbstractBase subclasses. This functions as the context class in a standard state machine implementation
class DigitizeStateContext : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  DigitizeStateContext(MainWindow &mainWindow,
                       QGraphicsView &view);
  virtual ~DigitizeStateContext ();

  /// Append just-created QUndoCommand to command stack. This is called from DigitizeStateAbstractBase subclasses
  void appendNewCmd(QUndoCommand *cmd);

  /// Bind to CmdMediator class. Binding occurs from the single instance of this class to each new CmdMediator
  void bindToCmdMediator (CmdMediator *cmdMediator);

  /// Provide CmdMediator for indirect access to the Document.
  CmdMediator &cmdMediator ();

  /// See DigitizeStateAbstractBase::handleContextMenuEvent.
  void handleContextMenuEvent (const QString &pointIdentifier);

  /// See DigitizeStateAbstractBase::handleKeyPress.
  void handleKeyPress (Qt::Key key);

  /// See DigitizeStateAbstractBase::handleLeave.
  void handleLeave ();

  /// See DigitizeStateAbstractBase::handleMousePress.
  void handleMousePress (QPointF pos);

  /// See DigitizeStateAbstractBase::handleMouseRelease.
  void handleMouseRelease (QPointF pos);

  /// See DigitizeStateAbstractBase::handleSetOverrideCursor
  void handleSetOverrideCursor (Qt::CursorShape cursorShape);

  /// Reference to the MainWindow, without const.
  MainWindow &mainWindow ();

  /// Reference to the MainWindow, with const.
  const MainWindow &mainWindow () const;

  /// Initiate state transition to be performed later, when DigitizeState is off the stack
  void requestDelayedStateTransition (DigitizeState digitizeState);

  /// Perform immediate state transition. Called from outside state machine
  void requestImmediateStateTransition (DigitizeState digitizeState);

  /// Set cursor after asking state for the new cursor shape.
  void setCursor ();

  /// Set QGraphicsView drag mode (in m_view). Called from DigitizeStateAbstractBase subclasses
  void setDragMode (QGraphicsView::DragMode dragMode);

  /// Set the image so QGraphicsView cursor and drag mode are accessible
  void setImage (QGraphicsPixmapItem *item);

  /// QGraphicsView for use by DigitizeStateAbstractBase subclasses
  QGraphicsView &view();

private:
  DigitizeStateContext();

  void completeRequestedStateTransitionIfExists ();

  MainWindow &m_mainWindow;
  QGraphicsView &m_view;
  QGraphicsPixmapItem *m_image; // Pixmap image. This is used for changing the cursor

  QVector<DigitizeStateAbstractBase*> m_states;
  DigitizeState m_currentState;
  DigitizeState m_requestedState; // Same as m_currentState until requestStateTransition is called

  CmdMediator *m_cmdMediator;
};

#endif // DIGITIZE_STATE_CONTEXT_H
