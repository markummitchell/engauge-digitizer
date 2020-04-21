/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_VIEW_STATE_ABSTRACT_BASE_H
#define GUIDELINE_VIEW_STATE_ABSTRACT_BASE_H

#include "GuidelineViewState.h"

class GuidelineViewStateContext;

/// This class tracks the current Guidelines view state so CmdGuidelineViewState objects can be
/// generated with before and after states both available (for redo and undo)
class GuidelineViewStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineViewStateAbstractBase (GuidelineViewStateContext &context);
  virtual ~GuidelineViewStateAbstractBase();

  /// Transition into state
  virtual void begin () = 0;

  /// Transition out of state
  virtual void end () = 0;

  /// User or software changed the current view state widgets
  virtual void handleStateChange (GuidelineViewState state) = 0;

  /// Return state for serializing
  virtual GuidelineViewState state () const = 0;
  
protected:

  /// Context in charge of the state classes
  GuidelineViewStateContext &context () const;

private:
  GuidelineViewStateAbstractBase();

  GuidelineViewStateContext &m_context;
};

#endif // GUIDELINE_VIEW_STATE_ABSTRACT_BASE_H
