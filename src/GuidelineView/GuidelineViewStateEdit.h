/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_VIEW_STATE_EDIT_H
#define GUIDELINE_VIEW_STATE_EDIT_H

#include "GuidelineViewStateAbstractBase.h"

/// Implements guideline behavior for GUIDELINE_VIEW_STATE_HIDE
class GuidelineViewStateEdit : public GuidelineViewStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineViewStateEdit(GuidelineViewStateContext &context);
  virtual ~GuidelineViewStateEdit();

  virtual void begin ();
  virtual void end ();
  virtual void handleStateChange (GuidelineViewState state);
  virtual GuidelineViewState state () const;
  
private:
  GuidelineViewStateEdit();

};

#endif // GUIDELINE_VIEW_STATE_EDIT_H
