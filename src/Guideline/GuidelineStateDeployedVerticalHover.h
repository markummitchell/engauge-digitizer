/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_VERTICAL_HOVER_H
#define GUIDELINE_STATE_DEPLOYED_VERTICAL_HOVER_H

#include "GuidelineStateDeployedVerticalAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_DEPLOYED_VERTICAL
class GuidelineStateDeployedVerticalHover : public GuidelineStateDeployedVerticalAbstract
{
public:
  /// Single constructor.
  GuidelineStateDeployedVerticalHover(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedVerticalHover();

  virtual void begin ();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleShowHide (bool show);
  virtual QString state () const;

private:
  GuidelineStateDeployedVerticalHover();

};

#endif // GUIDELINE_STATE_DEPLOYED_VERTICAL_HOVER_H
