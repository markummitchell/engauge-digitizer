#include "CmdMediator.h"
#include "DigitizeStateAxis.h"
#include "DigitizeStateColorPicker.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateCurve.h"
#include "DigitizeStateEmpty.h"
#include "DigitizeStatePointMatch.h"
#include "DigitizeStateScale.h"
#include "DigitizeStateSegment.h"
#include "DigitizeStateSelect.h"
#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "QtToString.h"

DigitizeStateContext::DigitizeStateContext(MainWindow &mainWindow,
                                           QGraphicsView &view) :
  m_mainWindow (mainWindow),
  m_view (view),
  m_imageIsLoaded (false),
  m_cmdMediator (0)
{
  // These states follow the same order as the DigitizeState enumeration
  m_states.insert (DIGITIZE_STATE_AXIS        , new DigitizeStateAxis        (*this));
  m_states.insert (DIGITIZE_STATE_COLOR_PICKER, new DigitizeStateColorPicker (*this));
  m_states.insert (DIGITIZE_STATE_CURVE       , new DigitizeStateCurve       (*this));
  m_states.insert (DIGITIZE_STATE_EMPTY       , new DigitizeStateEmpty       (*this));
  m_states.insert (DIGITIZE_STATE_POINT_MATCH , new DigitizeStatePointMatch  (*this));
  m_states.insert (DIGITIZE_STATE_SCALE       , new DigitizeStateScale       (*this));
  m_states.insert (DIGITIZE_STATE_SEGMENT     , new DigitizeStateSegment     (*this));
  m_states.insert (DIGITIZE_STATE_SELECT      , new DigitizeStateSelect      (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_DIGITIZE_STATES);

  m_currentState = NUM_DIGITIZE_STATES; // Value that forces a transition right away
  requestImmediateStateTransition (DIGITIZE_STATE_EMPTY);
}

DigitizeStateContext::~DigitizeStateContext()
{
}

QString DigitizeStateContext::activeCurve () const
{
  return m_states [m_currentState]->activeCurve ();
}

void DigitizeStateContext::appendNewCmd(QUndoCommand *cmd)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::appendNewCmd";

  ENGAUGE_ASSERT (m_cmdMediator != 0);
  m_cmdMediator->push (cmd);
}

void DigitizeStateContext::bindToCmdMediator (CmdMediator *cmdMediator)
{
  m_cmdMediator = cmdMediator;
}

CmdMediator &DigitizeStateContext::cmdMediator ()
{
  ENGAUGE_ASSERT (m_cmdMediator != 0);

  return *m_cmdMediator;
}

void DigitizeStateContext::completeRequestedStateTransitionIfExists ()
{
  if (m_currentState != m_requestedState) {

    // A transition is waiting so perform it

    if (m_currentState != NUM_DIGITIZE_STATES) {

      // This is not the first state so close the previous state
      m_states [m_currentState]->end ();
    }

    // Start the new state
    DigitizeState previousState = m_currentState;
    m_currentState = m_requestedState;
    m_states [m_requestedState]->begin (previousState);
  }
}

void DigitizeStateContext::handleContextMenuEvent (const QString &pointIdentifier)
{
  m_states [m_currentState]->handleContextMenuEvent (pointIdentifier);
}

void DigitizeStateContext::handleKeyPress (Qt::Key key)
{
  m_states [m_currentState]->handleKeyPress (key);

  completeRequestedStateTransitionIfExists();

}

void DigitizeStateContext::handleLeave ()
{
  m_states [m_currentState]->handleLeave ();

  completeRequestedStateTransitionIfExists();

}

void DigitizeStateContext::handleMousePress (QPointF pos)
{
  m_states [m_currentState]->handleMousePress (pos);

  completeRequestedStateTransitionIfExists();

}

void DigitizeStateContext::handleMouseRelease (QPointF pos)
{
  m_states [m_currentState]->handleMouseRelease (pos);

  completeRequestedStateTransitionIfExists();
}

void DigitizeStateContext::handleSetOverrideCursor (const QCursor &cursor)
{
  m_states [m_currentState]->handleSetOverrideCursor (cursor);
}

MainWindow &DigitizeStateContext::mainWindow ()
{
  return m_mainWindow;
}

const MainWindow &DigitizeStateContext::mainWindow () const
{
  return m_mainWindow;
}

void DigitizeStateContext::requestDelayedStateTransition (DigitizeState digitizeState)
{
  m_requestedState = digitizeState;
}

void DigitizeStateContext::requestImmediateStateTransition (DigitizeState digitizeState)
{
  m_requestedState = digitizeState;
  completeRequestedStateTransitionIfExists();
}

void DigitizeStateContext::setCursor ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::setCursor";

  m_states [m_currentState]->setCursor ();
}

void DigitizeStateContext::setDragMode (QGraphicsView::DragMode dragMode)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateContext::setDragMode";

  if (m_imageIsLoaded) {
    m_view.setDragMode (dragMode);
  }
}

void DigitizeStateContext::setImageIsLoaded(bool imageIsLoaded)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::setImageIsLoaded";

  m_imageIsLoaded = imageIsLoaded;
  setCursor ();
}

QGraphicsView &DigitizeStateContext::view()
{
  return m_view;
}
