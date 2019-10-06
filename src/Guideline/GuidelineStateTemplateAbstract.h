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

  /// Initialization of graphics item for all template Guidelines
  void beginCommon (const QLineF &line);
  
  virtual void handleActiveChange (bool active);
  virtual void handleMouseRelease (const QPointF &posScene);
  virtual EllipseParameters pointToEllipse (const QPointF &posScreen) const;
  virtual QLineF pointToLine (const QPointF &poscreen) const;

protected:

};

#endif // GUIDELINE_STATE_TEMPLATE_ABSTRACT_H
