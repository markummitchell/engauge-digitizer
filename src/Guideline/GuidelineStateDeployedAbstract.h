/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_ABSTRACT_H
#define GUIDELINE_STATE_DEPLOYED_ABSTRACT_H

#include "GuidelineStateAbstractBase.h"
#include <QPointF>

/// Abstract class for deployed states
class GuidelineStateDeployedAbstract : public GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateDeployedAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedAbstract();

  virtual bool initialHoverEventsEnable () const;
  virtual QLineF templateHomeLine () const;
};

#endif // GUIDELINE_STATE_DEPLOYED_ABSTRACT_H
