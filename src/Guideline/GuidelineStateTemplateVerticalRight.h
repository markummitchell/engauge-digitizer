/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_H
#define GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_H

#include "GuidelineStateTemplateAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT
class GuidelineStateTemplateVerticalRight : public GuidelineStateTemplateAbstract
{
public:
  /// Single constructor.
  GuidelineStateTemplateVerticalRight(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateVerticalRight();

  virtual void begin();
  virtual void end ();
  virtual void handleMousePress ();
  virtual void handleMouseRelease ();

  /// Returns the geometry of a template guideline
  static QLineF templateHomeLine (double lineWidth,
                                  double diagonal,
                                  const QRectF &sceneRect);

private:
  GuidelineStateTemplateVerticalRight();

};

#endif // GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_H
