/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_SHOW_H
#define GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_SHOW_H

#include "GuidelineStateTemplateHorizontalBottomAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM
class GuidelineStateTemplateHorizontalBottomShow : public GuidelineStateTemplateHorizontalBottomAbstract
{
public:
  /// Single constructor.
  GuidelineStateTemplateHorizontalBottomShow(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateHorizontalBottomShow();

  virtual void begin ();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleShowHide (bool show);
  virtual QString state () const;

private:
  GuidelineStateTemplateHorizontalBottomShow();

};

#endif // GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_SHOW_H
