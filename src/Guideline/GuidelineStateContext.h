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
class Guidelines;

/// Context class for state machine that belongs to the Guideline class. See Guideline
/// class for more information
class GuidelineStateContext
{
public:
  /// Single constructor.
  GuidelineStateContext (Guideline &guideline,
                         Guidelines &guidelines,
                         GuidelineState guidelineStateInitial);
  virtual ~GuidelineStateContext();

  /// Factory method for creating a new Guideline
  Guideline *createGuideline (GuidelineState stateInitial) const;

  /// Allow/skip painting of the owner Guideline. This prevents display of selection markings on
  /// otherwise-invisible handle Guideline
  bool doPaint () const;

  /// Guideline that owns this context class
  Guideline &guideline ();

  /// Show/hide this Guideline
  void handleShowHide (bool show);

  /// If transparent then make visible when hover starts
  void handleHoverEnterEvent ();

  /// If previously transparent before hover enter then make transparent again
  void handleHoverLeaveEvent ();

  /// At the start of dragging, convert the template Guideline into an invisible handle and
  /// visible slaved deployed Guideline
  void handleMousePress (const QPointF &posScene);
  
  /// At the end of dragging, clone the Guideline that owns the state machine where these states live
  void handleMouseRelease ();

  /// Return line parallel to an axis line, that passes through the specified point
  QLineF lineFromPoint (const QPointF &point) const;

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
  Guidelines &m_guidelines;

  QVector<GuidelineStateAbstractBase*> m_states;
  GuidelineState m_currentState;
  GuidelineState m_nextState;

  GuidelineState m_stateReplacement;
};

#endif // GUIDELINE_STATE_CONTEXT_H
