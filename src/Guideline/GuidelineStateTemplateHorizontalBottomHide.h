/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE_H
#define GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE_H

#include "GuidelineStateTemplateHorizontalBottomAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM
class GuidelineStateTemplateHorizontalBottomHide : public GuidelineStateTemplateHorizontalBottomAbstract
{
public:
  /// Single constructor.
  GuidelineStateTemplateHorizontalBottomHide(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateHorizontalBottomHide();

  virtual void begin ();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleVisibleChange (bool visible);
  virtual QString state () const;
  virtual void updateWithLatestTransformation();

private:
  GuidelineStateTemplateHorizontalBottomHide();

};

#endif // GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE_H
