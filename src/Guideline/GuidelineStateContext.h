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

  /// Guideline that owns this context class
  Guideline &guideline ();

  /// At the start of dragging, convert the template Guideline into an invisible handle and
  /// visible slaved deployed Guideline
  void handleMousePress ();
  
  /// At the end of dragging, clone the Guideline that owns the state machine where these states live
  void handleMouseRelease ();

  /// True/false to enable/disable hover events initially for the Guideline. This works out to
  /// being enabled initially for deployed states because template guidelines are only enabled
  /// in DigitizeStateSelect so that is the only time deployed guidelines can be created, which
  /// is the only time deployed guidelines can be dragged. Template guidelines are created before
  /// much happens so they are disabled initially (and first enabled by DigitizeStateSelect::begin())
  bool initialHoverEventsEnable () const;

  /// Request a state transition
  void requestStateTransition (GuidelineState guidelineState);

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
