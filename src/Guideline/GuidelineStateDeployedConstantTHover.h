/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER_H
#define GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER_H

#include "GuidelineStateDeployedConstantTAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_DEPLOYED_CONSTANT_T
class GuidelineStateDeployedConstantTHover : public GuidelineStateDeployedConstantTAbstract
{
public:
  /// Single constructor.
  GuidelineStateDeployedConstantTHover(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedConstantTHover();

  virtual void begin ();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleActiveChange (bool active);
  virtual void handleGuidelineMode (bool visible,
                                    bool locked);
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual QString stateName () const;

private:
  GuidelineStateDeployedConstantTHover();

};

#endif // GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER_H
