/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ABSTRACT_H
#define GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ABSTRACT_H

#include "GuidelineStateDeployedAbstract.h"

/// Compute geometry for deployed constant x Guideline
class GuidelineStateDeployedConstantXAbstract : public GuidelineStateDeployedAbstract
{
public:
  /// Single constructor.
  GuidelineStateDeployedConstantXAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedConstantXAbstract();

  virtual QPointF convertGraphCoordinateToScreenPoint (double valueGraph) const;
  virtual double convertScreenPointToGraphCoordinate (const QPointF &posScreen) const;
  virtual EllipseParameters pointToEllipse (const QPointF &posScreen) const;
  virtual QLineF pointToLine (const QPointF &posScreen) const;
  virtual void updateWithLatestTransformation ();

private:
  GuidelineStateDeployedConstantXAbstract();

};

#endif // GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ABSTRACT_H
