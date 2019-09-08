/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_CONTEXT_H
#define GUIDELINE_STATE_CONTEXT_H

#include "GuidelineStateAbstractBase.h"
#include <QLineF>
#include <QVector>

/// Context class for state machine that wraps around GuidelineStateAbstract
class GuidelineStateContext
{
public:
  /// Single constructor.
  GuidelineStateContext(GuidelineState guidelineStateInitial);
  virtual ~GuidelineStateContext();

  //// Request a state transition
  void requestStateTransition (GuidelineState guidelineState);
  
private:
  GuidelineStateContext();

  /// Transition if requested
  void transitionIfRequested ();
  
  QVector<GuidelineStateAbstractBase*> m_states;
  GuidelineState m_currentState;
  GuidelineState m_nextState;
};

#endif // GUIDELINE_STATE_CONTEXT_H
