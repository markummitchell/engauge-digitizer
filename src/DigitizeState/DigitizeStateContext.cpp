/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
#include "DocumentModelSegments.h"
#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSize>
#include "QtToString.h"
#include "Transformation.h"

DigitizeStateContext::DigitizeStateContext(MainWindow &mainWindow,
                                           QGraphicsView &view,
                                           bool isGnuplot) :
  m_mainWindow (mainWindow),
  m_view (view),
  m_imageIsLoaded (false),
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
  m_states.insert (DIGITIZE_STATE_SCALE       , new DigitizeStateScale       (*this)); // Out of order since added later
  ENGAUGE_ASSERT (m_states.size () == NUM_DIGITIZE_STATES);

  m_currentState = NUM_DIGITIZE_STATES; // Value that forces a transition right away
  requestImmediateStateTransition (mainWindow.cmdMediator(),
                                   DIGITIZE_STATE_EMPTY);
}

DigitizeStateContext::~DigitizeStateContext()
{
  qDeleteAll (m_states);
}

QString DigitizeStateContext::activeCurve () const
{
  return m_states [m_currentState]->activeCurve ();
}

void DigitizeStateContext::appendNewCmd(CmdMediator *cmdMediator,
                                        QUndoCommand *cmd)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::appendNewCmd";

  cmdMediator->push (cmd);
}

bool DigitizeStateContext::canPaste (const Transformation &transformation,
                                     const QSize &size) const
{
  return m_states [m_currentState]->canPaste (transformation,
                                              size);
}

void DigitizeStateContext::completeRequestedStateTransitionIfExists (CmdMediator *cmdMediator)
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
    m_states [m_requestedState]->begin (cmdMediator,
                                        previousState);

    // If transition was triggered from inside the state machine then MainWindow controls need to be set accordingly
    // as if user had clicked on a digitize button
    mainWindow().updateDigitizeStateIfSoftwareTriggered (m_requestedState);
  }
}

void DigitizeStateContext::handleContextMenuEventAxis (CmdMediator *cmdMediator,
                                                       const QString &pointIdentifier)
{
  m_states [m_currentState]->handleContextMenuEventAxis (cmdMediator,
                                                         pointIdentifier);
}

void DigitizeStateContext::handleContextMenuEventGraph (CmdMediator *cmdMediator,
                                                        const QStringList &pointIdentifiers)
{
  m_states [m_currentState]->handleContextMenuEventGraph (cmdMediator,
                                                          pointIdentifiers);
}

void DigitizeStateContext::handleCurveChange (CmdMediator *cmdMediator)
{
  m_states [m_currentState]->handleCurveChange(cmdMediator);
}

void DigitizeStateContext::handleKeyPress (CmdMediator *cmdMediator,
                                           Qt::Key key,
                                           bool atLeastOneSelectedItem)
{
  m_states [m_currentState]->handleKeyPress (cmdMediator,
                                             key,
                                             atLeastOneSelectedItem);

  completeRequestedStateTransitionIfExists(cmdMediator);

}

void DigitizeStateContext::handleMouseMove (CmdMediator *cmdMediator,
                                            QPointF pos)
{
  m_states [m_currentState]->handleMouseMove (cmdMediator,
                                              pos);

  completeRequestedStateTransitionIfExists(cmdMediator);

}

void DigitizeStateContext::handleMousePress (CmdMediator *cmdMediator,
                                             QPointF pos)
{
  m_states [m_currentState]->handleMousePress (cmdMediator,
                                               pos);

  completeRequestedStateTransitionIfExists(cmdMediator);

}

void DigitizeStateContext::handleMouseRelease (CmdMediator *cmdMediator,
                                               QPointF pos)
{
  m_states [m_currentState]->handleMouseRelease (cmdMediator,
                                                 pos);

  completeRequestedStateTransitionIfExists(cmdMediator);
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

void DigitizeStateContext::requestImmediateStateTransition (CmdMediator *cmdMediator,
                                                            DigitizeState digitizeState)
{
  m_requestedState = digitizeState;
  completeRequestedStateTransitionIfExists(cmdMediator);
}

void DigitizeStateContext::resetOnLoad (CmdMediator *cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::resetOnLoad";

  // Reset current state. At this point, the current state is DIGITIZE_STATE_EMPTY when opening the first document
  // so for consistency we always reset it so succeeding documents work the same way
  if (m_currentState != DIGITIZE_STATE_EMPTY) {
    m_requestedState = DIGITIZE_STATE_EMPTY;
    completeRequestedStateTransitionIfExists(cmdMediator);
  }
}

void DigitizeStateContext::setCursor (CmdMediator *cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::setCursor";

  ENGAUGE_ASSERT(m_currentState < m_states.count());

  m_states [m_currentState]->setCursor (cmdMediator);
}

void DigitizeStateContext::setDragMode (QGraphicsView::DragMode dragMode)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateContext::setDragMode";

  if (m_imageIsLoaded) {
    m_view.setDragMode (dragMode);
  }
}

void DigitizeStateContext::setImageIsLoaded(CmdMediator *cmdMediator,
                                            bool imageIsLoaded)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::setImageIsLoaded";

  m_imageIsLoaded = imageIsLoaded;
  setCursor (cmdMediator);
}

QString DigitizeStateContext::state() const
{
  ENGAUGE_ASSERT (m_currentState != NUM_DIGITIZE_STATES);

  return m_states [m_currentState]->state();
}

void DigitizeStateContext::updateAfterPointAddition ()
{
  ENGAUGE_ASSERT (m_currentState != NUM_DIGITIZE_STATES);

  m_states [m_currentState]->updateAfterPointAddition ();
}

void DigitizeStateContext::updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                                     const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::updateModelDigitizeCurve";

  ENGAUGE_ASSERT(m_currentState < m_states.count());

  m_states [m_currentState]->updateModelDigitizeCurve (cmdMediator,
                                                       modelDigitizeCurve);
}

void DigitizeStateContext::updateModelSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateContext::updateModelSegments";

  ENGAUGE_ASSERT(m_currentState < m_states.count());

  m_states [m_currentState]->updateModelSegments (modelSegments);
}

QGraphicsView &DigitizeStateContext::view()
{
  return m_view;
}
