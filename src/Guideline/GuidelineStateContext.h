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

/// Context class for state machine that belongs to the Guideline class
class GuidelineStateContext
{
public:
  /// Single constructor.
  GuidelineStateContext (Guideline &guideline,
                         GuidelineState guidelineStateInitial);
  virtual ~GuidelineStateContext();

  /// True/false to keep object always visible (typically for deployed/template respectively)
  bool alwaysVisible () const;

  /// Clone the Guideline that owns the state machine where these states live
  void cloneDraggedGuideline();
  
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

  /// Make immediate state transition. This is called from outside the state machine only.
  /// This CANNOT be called from a state class or else the stack will be corrupted (in that
  /// case use requestStateTransition and let this class call transitionIfRequested when that
  /// is safe to do)
  void makeStateTransition (GuidelineState guidelineState);

  /// Request a state transition
  void requestStateTransition (GuidelineState guidelineState);
  
  /// Current state. This should be used when cloning only, and should never be used
  /// with if/then logic
  GuidelineState state () const;

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
