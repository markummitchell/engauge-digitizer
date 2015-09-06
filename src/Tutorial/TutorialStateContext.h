#ifndef TUTORIAL_STATE_CONTEXT_H
#define TUTORIAL_STATE_CONTEXT_H

#include <QVector>
#include "TutorialStateAbstractBase.h"

class TutorialDlg;

/// Context class for tutorial state machine. Each state represents one panel in the tutorial
class TutorialStateContext
{
 public:
  /// Single constructor
  TutorialStateContext(TutorialDlg &tutorialDlg);

  /// Request a transition to the specified state from the current state. The transition is delayed until the current state
  /// is off the stack to prevent stack corruption errors
  void requestStateTransition (TutorialState tutorialState);

  /// Access to tutorial dialogs and its scene
  TutorialDlg &tutorialDlg();

 private:

  void completeRequestedStateTransitionIfExists ();

  QVector<TutorialStateAbstractBase*> m_states;
  TutorialState m_currentState;
  TutorialState m_requestedState; // Same as m_currentState until requestStateTransition is called

  TutorialDlg &m_tutorialDlg;
};

#endif // TUTORIAL_STATE_CONTEXT_H
