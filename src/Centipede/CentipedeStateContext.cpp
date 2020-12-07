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
#include "CmdGuidelineAddXT.h"
#include "CmdGuidelineAddYR.h"
#include "DigitizeStateGuideline.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QObject>
#include "Transformation.h"

CentipedeStateContext::CentipedeStateContext (DigitizeStateGuideline &stateGuideline) :
  m_stateGuideline (stateGuideline),
  m_scene (nullptr),
  m_transformation (nullptr)
{
  // These states follow the same order as the CentipedeState enumeration
  m_states.insert (CENTIPEDE_STATE_BUILD_CARTESIAN, new CentipedeStateBuildCartesian (*this));
  m_states.insert (CENTIPEDE_STATE_BUILD_POLAR    , new CentipedeStateBuildPolar     (*this));
  m_states.insert (CENTIPEDE_STATE_PREBUILD       , new CentipedeStatePrebuild       (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_CENTIPEDE_STATES);

  m_currentState = NUM_CENTIPEDE_STATES; // Value that forces a transition right away
  requestImmediateStateTransition (CENTIPEDE_STATE_PREBUILD);
}

CentipedeStateContext::~CentipedeStateContext()
{
  // Remove states, one of which may have incomplete in-work graphics items
  QVector<CentipedeStateAbstractBase*>::iterator itr;
  for (itr = m_states.begin (); itr != m_states.end (); itr++) {
    CentipedeStateAbstractBase *state = *itr;
    delete state;
  }

  m_states.clear();
}

void CentipedeStateContext::completeRequestedStateTransitionIfExists ()
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

void CentipedeStateContext::createGuidelineCommand (bool selectedXT,
                                                    double selectedValue)
{
  m_stateGuideline.createGuidelineCommand (selectedXT,
                                           selectedValue);
}

void CentipedeStateContext::handleKeyPress (Qt::Key key,
                                            bool atLeastOneSelectedItem)
{
  m_states [m_currentState]->handleKeyPress (key,
                                             atLeastOneSelectedItem);

  completeRequestedStateTransitionIfExists();

}

void CentipedeStateContext::handleMouseMove (QPointF pos)
{
  m_states [m_currentState]->handleMouseMove (pos);

  completeRequestedStateTransitionIfExists();

}

void CentipedeStateContext::handleMousePress (GraphicsScene *scene,
                                              const Transformation &transformation,
                                              const DocumentModelGuideline &modelGuideline,
                                              const DocumentModelCoords &modelCoords,
                                              QPointF pos,
                                              bool clickedOnItem)
{
  // If a graphics item can be, or was, selected then do not create a new CentipedePair (by
  // skipping the state transition
  if (!clickedOnItem) {

    // Forward context variables
    m_scene = scene;
    m_transformation = new Transformation (transformation);
    m_modelGuideline = modelGuideline;
    m_modelCoords = modelCoords;
    m_posClickScreen = pos;
  
    m_states [m_currentState]->handleMousePress (pos);

    completeRequestedStateTransitionIfExists();
  }
}

void CentipedeStateContext::handleMouseRelease (QPointF pos)
{
  m_states [m_currentState]->handleMouseRelease (pos);

  completeRequestedStateTransitionIfExists();
}

DocumentModelCoords CentipedeStateContext::modelCoords () const
{
  return m_modelCoords;
}

DocumentModelGuideline CentipedeStateContext::modelGuideline () const
{
  return m_modelGuideline;
}

QPointF  CentipedeStateContext::posClickScreen () const
{
  return m_posClickScreen;
}

void CentipedeStateContext::requestDelayedStateTransition (CentipedeState centipedeState)
{
  m_requestedState = centipedeState;
}

void CentipedeStateContext::requestImmediateStateTransition (CentipedeState centipedeState)
{
  m_requestedState = centipedeState;
  completeRequestedStateTransitionIfExists();
}

GraphicsScene &CentipedeStateContext::scene () const
{
  return *m_scene;
}

Transformation CentipedeStateContext::transformation () const
{
  return *m_transformation;
}
