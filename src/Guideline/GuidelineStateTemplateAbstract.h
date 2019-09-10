/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_TEMPLATE_ABSTRACT_H
#define GUIDELINE_STATE_TEMPLATE_ABSTRACT_H

#include "GuidelineStateAbstractBase.h"
#include <QPointF>

/// Abstract class for template states
class GuidelineStateTemplateAbstract : public GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateTemplateAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateTemplateAbstract();

  /// Clone the Guideline that owns the state machine where these states live. This
  /// overrides the parent class implementation
  virtual void cloneDraggedGuideline();

  virtual bool initialHoverEventsEnable () const;
};

#endif // GUIDELINE_STATE_TEMPLATE_ABSTRACT_H
