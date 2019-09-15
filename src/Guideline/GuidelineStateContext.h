/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_CONTEXT_H
#define GUIDELINE_STATE_CONTEXT_H

#include "GuidelineState.h"
#include "GuidelineStateAbstractBase.h"
#include <QColor>
#include <QLineF>
#include <QString>
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

  /// Guideline that owns this context class
  Guideline &guideline ();

  /// If transparent then make visible when hover starts
  void handleHoverEnterEvent ();

  /// If previously transparent before hover enter then make transparent again
  void handleHoverLeaveEvent ();

  /// At the start of dragging, convert the template Guideline into an invisible handle and
  /// visible slaved deployed Guideline
  void handleMousePress ();
  
  /// At the end of dragging, clone the Guideline that owns the state machine where these states live
  void handleMouseRelease ();

  /// Request a state transition
  void requestStateTransition (GuidelineState guidelineState);

  /// Pass replacement Guideline state from template Guidelines to handle Guideline
  void setStateReplacement (GuidelineState stateReplacement);

  /// State as a string for debugging only
  QString state () const;

  /// Get method for replacement state
  GuidelineState stateReplacement () const;

private:
  GuidelineStateContext();

  /// Transition if requested
  void transitionIfRequested ();
  
  Guideline &m_guideline;

  QVector<GuidelineStateAbstractBase*> m_states;
  GuidelineState m_currentState;
  GuidelineState m_nextState;

  GuidelineState m_stateReplacement;
};

#endif // GUIDELINE_STATE_CONTEXT_H
