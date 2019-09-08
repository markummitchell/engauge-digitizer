/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_CONTEXT_H
#define GUIDELINE_STATE_CONTEXT_H

#include "GuidelineState.h"
#include "GuidelineStateAbstractBase.h"
#include <QLineF>
#include <QVector>

class Guideline;

/// Context class for state machine that wraps around GuidelineStateAbstract
class GuidelineStateContext
{
public:
  /// Single constructor.
  GuidelineStateContext (Guideline &guideline,
                         GuidelineState guidelineStateInitial);
  virtual ~GuidelineStateContext();

  /// Initial state of clone made from this Guideline
  GuidelineState cloneState () const;

  /// Guideline that owns this context class
  Guideline &guideline ();

  /// Use this method to distinguish template and cloned guidelines
  bool isTemplate () const;

  /// Request a state transition
  void requestStateTransition (GuidelineState guidelineState);
  
  /// Returns the geometry of a template guideline
  QLineF templateHomeLine () const;

private:
  GuidelineStateContext();

  /// Transition if requested
  void transitionIfRequested ();
  
  Guideline &m_guideline;

  QVector<GuidelineStateAbstractBase*> m_states;
  GuidelineState m_currentState;
  GuidelineState m_nextState;
};

#endif // GUIDELINE_STATE_CONTEXT_H
