/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_VIEW_STATE_CONTEXT_H
#define GUIDELINE_VIEW_STATE_CONTEXT_H

#include "GuidelineViewState.h"
#include "GuidelineViewStateAbstractBase.h"
#include <QVector>

class MainWindow;

/// Context class for state machine that tracks the View / Guidelines mode. This is needed to track before
/// and after states for generating CmdGuidelineViewState
class GuidelineViewStateContext
{
public:
  /// Single constructor.
  GuidelineViewStateContext ();
  virtual ~GuidelineViewStateContext();

  /// Handle user or code generated change in  selected guideline view mode
  void handleStateChange (GuidelineViewState state);
  
  /// Request a state transition
  void requestStateTransition (GuidelineViewState guidelineState);

  /// Current state for serializing
  GuidelineViewState state () const;

private:

  /// For CmdAbstract constructor only, via MainWindow, we offer the state to friend class  MainWindow
  friend class MainWindow;
  GuidelineViewState guidelineViewState () const;

  /// Transition if requested
  void transitionIfRequested ();
  
  QVector<GuidelineViewStateAbstractBase*> m_states;
  GuidelineViewState m_currentState;
  GuidelineViewState m_nextState;
};

#endif // GUIDELINE_VIEW_STATE_CONTEXT_H
