/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeState.h"
#include "CentipedeStateBuildCartesian.h"
#include "CentipedeStateBuildPolar.h"
#include "CentipedeStateContext.h"
#include "CentipedeStatePrebuild.h"
#include "CmdMediator.h"
#include "EngaugeAssert.h"
#include "Logger.h"

CentipedeStateContext::CentipedeStateContext (CmdMediator &cmdMediator) :
  m_cmdMediator (cmdMediator)
{
  // These states follow the same order as the CentipedeState enumeration
  m_states.insert (CENTIPEDE_STATE_BUILD_CARTESIAN, new CentipedeStateBuildCartesian (*this));
  m_states.insert (CENTIPEDE_STATE_BUILD_POLAR    , new CentipedeStateBuildPolar     (*this));
  m_states.insert (CENTIPEDE_STATE_PREBUILD       , new CentipedeStatePrebuild       (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_CENTIPEDE_STATES);

  m_currentState = NUM_CENTIPEDE_STATES; // Value that forces a transition right away
  requestImmediateStateTransition (&cmdMediator,
                                   CENTIPEDE_STATE_PREBUILD);
}

CentipedeStateContext::~CentipedeStateContext()
{
}

CmdMediator &CentipedeStateContext::cmdMediator ()
{
  return m_cmdMediator;
}

void CentipedeStateContext::completeRequestedStateTransitionIfExists (CmdMediator *cmdMediator)
{
  if (m_currentState != m_requestedState) {

    // A transition is waiting so perform it

    if (m_currentState != NUM_CENTIPEDE_STATES) {

      // This is not the first state so close the previous state
      m_states [m_currentState]->end ();
    }

    // Start the new state
    m_currentState = m_requestedState;
    m_states [m_requestedState]->begin ();
  }
}

void CentipedeStateContext::handleKeyPress (CmdMediator &cmdMediator,
                                            Qt::Key key,
                                            bool atLeastOneSelectedItem)
{
  m_states [m_currentState]->handleKeyPress (cmdMediator,
                                             key,
                                             atLeastOneSelectedItem);

  completeRequestedStateTransitionIfExists(&cmdMediator);

}

void CentipedeStateContext::handleMouseMove (CmdMediator *cmdMediator,
                                             QPointF pos)
{
  m_states [m_currentState]->handleMouseMove (cmdMediator,
                                              pos);

  completeRequestedStateTransitionIfExists(cmdMediator);

}

void CentipedeStateContext::handleMousePress (CmdMediator *cmdMediator,
                                              QPointF pos)
{
  m_states [m_currentState]->handleMousePress (cmdMediator,
                                               pos);

  completeRequestedStateTransitionIfExists(cmdMediator);

}

void CentipedeStateContext::handleMouseRelease (CmdMediator *cmdMediator,
                                                QPointF pos)
{
  m_states [m_currentState]->handleMouseRelease (cmdMediator,
                                                 pos);

  completeRequestedStateTransitionIfExists(cmdMediator);
}

void CentipedeStateContext::requestDelayedStateTransition (CentipedeState centipedeState)
{
  m_requestedState = centipedeState;
}

void CentipedeStateContext::requestImmediateStateTransition (CmdMediator *cmdMediator,
                                                             CentipedeState centipedeState)
{
  m_requestedState = centipedeState;
  completeRequestedStateTransitionIfExists(cmdMediator);
}
