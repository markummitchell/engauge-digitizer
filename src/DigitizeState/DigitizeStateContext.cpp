#include "CmdMediator.h"
#include "DigitizeStateAxis.h"
#include "DigitizeStateColorPicker.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateCurve.h"
#include "DigitizeStateEmpty.h"
#include "DigitizeStatePointMatch.h"
#include "DigitizeStateSegment.h"
#include "DigitizeStateSelect.h"
#include "DocumentModelSegments.h"
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
                                           QGraphicsView &view,
                                           bool isGnuplot) :
  m_mainWindow (mainWindow),
  m_view (view),
  m_imageIsLoaded (false),
  m_cmdMediator (0),
  m_isGnuplot (isGnuplot)
{
  // These states follow the same order as the DigitizeState enumeration
  m_states.insert (DIGITIZE_STATE_AXIS        , new DigitizeStateAxis        (*this));
  m_states.insert (DIGITIZE_STATE_COLOR_PICKER, new DigitizeStateColorPicker (*this));
  m_states.insert (DIGITIZE_STATE_CURVE       , new DigitizeStateCurve       (*this));
  m_states.insert (DIGITIZE_STATE_EMPTY       , new DigitizeStateEmpty       (*this));
  m_states.insert (DIGITIZE_STATE_POINT_MATCH , new DigitizeStatePointMatch  (*this));
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

void DigitizeStateContext::bindToCmdMediatorAndResetOnLoad (CmdMediator *cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::bindToCmdMediatorAndResetOnLoad";

  m_cmdMediator = cmdMediator;

  // Reset current state. At this point, the current state is DIGITIZE_STATE_EMPTY when opening the first document
  // so for consistency we always reset it so succeeding documents work the same way. This is done without
  if (m_currentState != DIGITIZE_STATE_EMPTY) {
    m_requestedState = DIGITIZE_STATE_EMPTY;
    completeRequestedStateTransitionIfExists();
  }
}

CmdMediator &DigitizeStateContext::cmdMediator ()
{
  ENGAUGE_ASSERT (m_cmdMediator != 0);

  return *m_cmdMediator;
}

const CmdMediator &DigitizeStateContext::cmdMediator () const
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

    // If transition was triggered from inside the state machine then MainWindow controls need to be set accordingly
    // as if user had clicked on a digitize button
    mainWindow().updateDigitizeStateIfSoftwareTriggered (m_requestedState);
  }
}

void DigitizeStateContext::handleContextMenuEvent (const QString &pointIdentifier)
{
  m_states [m_currentState]->handleContextMenuEvent (pointIdentifier);
}

void DigitizeStateContext::handleCurveChange ()
{
  m_states [m_currentState]->handleCurveChange();
}

void DigitizeStateContext::handleKeyPress (Qt::Key key,
                                           bool atLeastOneSelectedItem)
{
  m_states [m_currentState]->handleKeyPress (key,
                                             atLeastOneSelectedItem);

  completeRequestedStateTransitionIfExists();

}

void DigitizeStateContext::handleLeave ()
{
  m_states [m_currentState]->handleLeave ();

  completeRequestedStateTransitionIfExists();

}

void DigitizeStateContext::handleMouseMove (QPointF pos)
{
  m_states [m_currentState]->handleMouseMove (pos);

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

bool DigitizeStateContext::isGnuplot () const
{
  return m_isGnuplot;
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

QString DigitizeStateContext::state() const
{
  ENGAUGE_ASSERT (m_currentState != NUM_DIGITIZE_STATES);

  return m_states [m_currentState]->state();
}

void DigitizeStateContext::updateModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::updateModelDigitizeCurve";

  m_states [m_currentState]->updateModelDigitizeCurve (modelDigitizeCurve);
}

void DigitizeStateContext::updateModelSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::updateModelSegments";

  m_states [m_currentState]->updateModelSegments (modelSegments);
}

QGraphicsView &DigitizeStateContext::view()
{
  return m_view;
}
