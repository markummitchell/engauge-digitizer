/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_H
#define GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_H

#include "GuidelineStateTemplateAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM
class GuidelineStateTemplateHorizontalBottom : public GuidelineStateTemplateAbstract
{
public:
  /// Single constructor.
  GuidelineStateTemplateHorizontalBottom(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateHorizontalBottom();

  virtual bool alwaysVisible () const;
  virtual void begin ();
  virtual GuidelineState cloneState () const;
  virtual void end ();
  virtual QLineF templateHomeLine () const;

private:
  GuidelineStateTemplateHorizontalBottom();

};

#endif // GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_H
