/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_ABSTRACT_H
#define GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_ABSTRACT_H

#include "GuidelineStateTemplateAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM
class GuidelineStateTemplateHorizontalBottomAbstract : public GuidelineStateTemplateAbstract
{
public:
  /// Single constructor.
  GuidelineStateTemplateHorizontalBottomAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateHorizontalBottomAbstract();

  /// Returns the geometry of a template guideline. This is static so sceneRect must be passed in as an argument
  static QLineF templateHomeLine (const QRectF &sceneRect);

private:
  GuidelineStateTemplateHorizontalBottomAbstract();

};

#endif // GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_ABSTRACT_H
