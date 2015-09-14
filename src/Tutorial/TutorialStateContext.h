#ifndef TUTORIAL_STATE_CONTEXT_H
#define TUTORIAL_STATE_CONTEXT_H

#include <QObject>
#include <QVector>
#include "TutorialStateAbstractBase.h"

class QTimer;
class TutorialDlg;

/// Context class for tutorial state machine. Each state represents one panel in the tutorial
/// Tutorial assumptions:
/// -# Dealing with multiple curves is postponed until the end of the tutorial.
class TutorialStateContext : public QObject
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateContext(TutorialDlg &tutorialDlg);

  /// Request a transition to the specified state from the current state. A timer is used. This assumes TutorialStateContext
  /// is NOT on the stack - probably since an external event (mouse click, ...) resulted in a callback to the current state
  void requestDelayedStateTransition (TutorialState tutorialState);

  /// Request a transition to the specified state from the current state. The transition is delayed until the current state
  /// is off the stack to prevent stack corruption errors. This assumes TutorialStateContext is on the stack to finish
  /// the transition after execution returns from the state
  void requestImmediateStateTransition (TutorialState tutorialState);

  /// Access to tutorial dialogs and its scene
  TutorialDlg &tutorialDlg();

 private slots:
  void slotTimeout ();

 private:

  void completeRequestedStateTransitionIfExists ();
  void createStates ();
  void createTimer ();

  QVector<TutorialStateAbstractBase*> m_states;
  TutorialState m_currentState;
  TutorialState m_requestedState; // Same as m_currentState until requestStateTransition is called

  TutorialDlg &m_tutorialDlg;

  // Timer for delayed state transitions
  QTimer *m_timer;
};

#endif // TUTORIAL_STATE_CONTEXT_H
