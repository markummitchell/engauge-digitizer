/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_VERTICAL_ABSTRACT_H
#define GUIDELINE_STATE_DEPLOYED_VERTICAL_ABSTRACT_H

#include "GuidelineStateDeployedAbstract.h"

class GuidelineStateDeployedVerticalAbstract : public GuidelineStateDeployedAbstract
{
public:
  /// Single constructor.
  GuidelineStateDeployedVerticalAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedVerticalAbstract();

  virtual QLineF lineFromPoint (const QPointF &posScreen) const;

private:
  GuidelineStateDeployedVerticalAbstract();

};

#endif // GUIDELINE_STATE_DEPLOYED_VERTICAL_ABSTRACT_H
