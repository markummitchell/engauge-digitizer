/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_NULL_H
#define GUIDELINE_STATE_NULL_H

#include "GuidelineStateAbstractBase.h"

/// Implements guideline behavior for GUIDELINE_STATE_NULL
class GuidelineStateNull : public GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateNull(GuidelineStateContext &context);
  virtual ~GuidelineStateNull();

  virtual bool alwaysVisible () const;
  virtual void begin ();
  virtual GuidelineState cloneState () const;
  virtual void end ();
  virtual bool initialHoverEventsEnable () const;
  virtual QLineF templateHomeLine () const;

private:
  GuidelineStateNull();

};

#endif // GUIDELINE_STATE_NULL_H
