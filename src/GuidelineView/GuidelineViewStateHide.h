/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_VIEW_STATE_HIDE_H
#define GUIDELINE_VIEW_STATE_HIDE_H

#include "GuidelineViewStateAbstractBase.h"

/// Implements guideline behavior for GUIDELINE_VIEW_STATE_HIDE
class GuidelineViewStateHide : public GuidelineViewStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineViewStateHide(GuidelineViewStateContext &context);
  virtual ~GuidelineViewStateHide();

  virtual void begin ();
  virtual void end ();
  virtual void handleStateChange (GuidelineViewState state);
  virtual GuidelineViewState state () const;
  
private:
  GuidelineViewStateHide();

};

#endif // GUIDELINE_VIEW_STATE_HIDE_H
