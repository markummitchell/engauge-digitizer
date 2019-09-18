/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_HORIZONTAL_ABSTRACT_H
#define GUIDELINE_STATE_DEPLOYED_HORIZONTAL_ABSTRACT_H

#include "GuidelineStateDeployedAbstract.h"

/// Compute geometry for deployed horizontal Guideline
class GuidelineStateDeployedHorizontalAbstract : public GuidelineStateDeployedAbstract
{
public:
  /// Single constructor.
  GuidelineStateDeployedHorizontalAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedHorizontalAbstract();

  virtual QLineF lineFromPoint (const QPointF &posScreen) const;

private:
  GuidelineStateDeployedHorizontalAbstract();

};

#endif // GUIDELINE_STATE_DEPLOYED_HORIZONTAL_ABSTRACT_H
