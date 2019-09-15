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

  void beginCommon (const QLineF &line);
  virtual bool doPaint () const;
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual QLineF lineFromPoint (const QPointF &point) const;

protected:

  /// Common mouse press handling
  void handleMousePressCommon (const QPointF &pos,
                               GuidelineState stateDeployed,
                               GuidelineState stateReplacement);

};

#endif // GUIDELINE_STATE_TEMPLATE_ABSTRACT_H
