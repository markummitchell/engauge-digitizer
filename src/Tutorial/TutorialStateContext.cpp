#include "EngaugeAssert.h"
#include "TutorialStateAbstractBase.h"
#include "TutorialStateContext.h"
#include "TutorialStateIntroduction.h"

TutorialStateContext::TutorialStateContext (TutorialDlg &tutorialDlg) :
    m_tutorialDlg (tutorialDlg)
{
  // These states follow the same order as the TutorialState enumeration
  m_states.insert (TUTORIAL_STATE_INTRODUCTION, new TutorialStateIntroduction (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_TUTORIAL_STATES);

  m_currentState = NUM_TUTORIAL_STATES; // Value that forces a transition right away;
  requestStateTransition (TUTORIAL_STATE_INTRODUCTION);
  completeRequestedStateTransitionIfExists ();
}

void TutorialStateContext::completeRequestedStateTransitionIfExists ()
{
  if (m_currentState != m_requestedState) {

    // A transition is waiting so perform it
    
    if (m_currentState != NUM_TUTORIAL_STATES) {

      // This is not the first state so close the previous state
      m_states [m_currentState]->end ();
    }

    // Start the new state
    m_currentState = m_requestedState;
    m_states [m_requestedState]->begin ();
  }
}

void TutorialStateContext::requestStateTransition (TutorialState tutorialState)
{
  m_requestedState = tutorialState;
}

TutorialDlg &TutorialStateContext::tutorialDlg()
{
  return m_tutorialDlg;
}
