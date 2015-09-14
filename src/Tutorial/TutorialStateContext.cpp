#include "EngaugeAssert.h"
#include "Logger.h"
#include <QTimer>
#include "TutorialDlg.h"
#include "TutorialStateAbstractBase.h"
#include "TutorialStateAxisPoints.h"
#include "TutorialStateChecklistWizardLines.h"
#include "TutorialStateChecklistWizardPoints.h"
#include "TutorialStateColorFilter.h"
#include "TutorialStateContext.h"
#include "TutorialStateCurveSelection.h"
#include "TutorialStateCurveType.h"
#include "TutorialStateIntroduction.h"
#include "TutorialStatePointMatch.h"
#include "TutorialStateSegmentFill.h"

const int TIMER_INTERVAL = 1;

TutorialStateContext::TutorialStateContext (TutorialDlg &tutorialDlg) :
    m_tutorialDlg (tutorialDlg)
{
  createStates ();
  createTimer ();
}

void TutorialStateContext::createStates ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateContext::createStates";

  // These states follow the same order as the TutorialState enumeration
  m_states.insert (TUTORIAL_STATE_AXIS_POINTS            , new TutorialStateAxisPoints            (*this));
  m_states.insert (TUTORIAL_STATE_CHECKLIST_WIZARD_LINES , new TutorialStateChecklistWizardLines  (*this));
  m_states.insert (TUTORIAL_STATE_CHECKLIST_WIZARD_POINTS, new TutorialStateChecklistWizardPoints (*this));
  m_states.insert (TUTORIAL_STATE_COLOR_FILTER           , new TutorialStateColorFilter           (*this));
  m_states.insert (TUTORIAL_STATE_CURVE_SELECTION        , new TutorialStateCurveSelection        (*this));
  m_states.insert (TUTORIAL_STATE_CURVE_TYPE             , new TutorialStateCurveType             (*this));
  m_states.insert (TUTORIAL_STATE_INTRODUCTION           , new TutorialStateIntroduction          (*this));
  m_states.insert (TUTORIAL_STATE_POINT_MATCH            , new TutorialStatePointMatch            (*this));
  m_states.insert (TUTORIAL_STATE_SEGMENT_FILL           , new TutorialStateSegmentFill           (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_TUTORIAL_STATES);

  m_currentState = NUM_TUTORIAL_STATES; // Value that forces a transition right away;
  requestImmediateStateTransition (TUTORIAL_STATE_INTRODUCTION);
  completeRequestedStateTransitionIfExists ();
}

void TutorialStateContext::createTimer ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateContext::createTimer";

  m_timer = new QTimer ();
  m_timer->setInterval (TIMER_INTERVAL);
  m_timer->setSingleShot (true);
  connect (m_timer, SIGNAL (timeout ()), this, SLOT (slotTimeout ()));
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

void TutorialStateContext::requestDelayedStateTransition (TutorialState tutorialState)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateContext::requestDelayedStateTransition";

  m_requestedState = tutorialState;

  m_timer->start ();
}

void TutorialStateContext::requestImmediateStateTransition (TutorialState tutorialState)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateContext::requestImmediateStateTransition";

  m_requestedState = tutorialState;
}

void TutorialStateContext::slotTimeout()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateContext::slotTimeout";

  completeRequestedStateTransitionIfExists();
}

TutorialDlg &TutorialStateContext::tutorialDlg()
{
  return m_tutorialDlg;
}
