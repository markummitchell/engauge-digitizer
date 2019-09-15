/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_H
#define GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_H

#include "GuidelineStateTemplateAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT
class GuidelineStateTemplateVerticalLeft : public GuidelineStateTemplateAbstract
{
public:
  /// Single constructor.
  GuidelineStateTemplateVerticalLeft(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateVerticalLeft();

  virtual void begin();
  virtual void end ();
  virtual void handleMousePress ();
  virtual void handleMouseRelease ();
  virtual QString state () const;

  /// Returns the geometry of a template guideline
  static QLineF templateHomeLine (double lineWidth,
                                  double diagonal,
                                  const QRectF &sceneRect);

private:
  GuidelineStateTemplateVerticalLeft();

};

#endif // GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_H
