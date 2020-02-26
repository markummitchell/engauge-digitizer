/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ABSTRACT_H
#define GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ABSTRACT_H

#include "GuidelineStateDeployedAbstract.h"

/// Compute geometry for deployed constant y Guideline
class GuidelineStateDeployedConstantYAbstract : public GuidelineStateDeployedAbstract
{
public:
  /// Single constructor.
  GuidelineStateDeployedConstantYAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedConstantYAbstract();

  virtual QPointF convertGraphCoordinateToScreenPoint (double valueGraph) const;
  virtual double convertScreenPointToGraphCoordinate (const QPointF &posScreen) const;
  virtual EllipseParameters pointToEllipse (const QPointF &posScreen) const;
  virtual QLineF pointToLine (const QPointF &posScreen) const;
  virtual void updateWithLatestTransformation ();

private:
  GuidelineStateDeployedConstantYAbstract();

};

#endif // GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ABSTRACT_H
