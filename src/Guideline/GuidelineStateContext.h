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

/// Context class for state machine that wraps around GuidelineStateAbstract. This is
/// a strange state machine since:
/// # There are no transitions from one state to another
/// # Instead of state transitions, there is cloning of a template state object into
///   a corresponding deployed state object
/// However, the state machine's ability to nicely encapsulate behaviors according to
/// the situation make the state machine approach attractive
class GuidelineStateContext
{
public:
  /// Single constructor.
  GuidelineStateContext (Guideline &guideline,
                         GuidelineState guidelineStateInitial);
  virtual ~GuidelineStateContext();

  /// True/false to keep object always visible (typically for deployed/template respectively)
  bool alwaysVisible () const;

  /// Initial state of clone made from this Guideline
  GuidelineState cloneState () const;

  /// Guideline that owns this context class
  Guideline &guideline ();

  /// True/false to enable/disable hover events initially for the Guideline. This works out to
  /// being enabled initially for deployed states because template guidelines are only enabled
  /// in DigitizeStateSelect so that is the only time deployed guidelines can be created, which
  /// is the only time deployed guidelines can be dragged. Template guidelines are created before
  /// much happens so they are disabled initially (and first enabled by DigitizeStateSelect::begin())
  bool initialHoverEventsEnable () const;

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
