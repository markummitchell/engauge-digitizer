/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_SHOW_H
#define GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_SHOW_H

#include "GuidelineStateTemplateVerticalRightAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT
class GuidelineStateTemplateVerticalRightShow : public GuidelineStateTemplateVerticalRightAbstract
{
public:
  /// Single constructor.
  GuidelineStateTemplateVerticalRightShow(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateVerticalRightShow();

  virtual void begin();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleShowHide (bool show);
  virtual QString state () const;

private:
  GuidelineStateTemplateVerticalRightShow();

};

#endif // GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_SHOW_H
