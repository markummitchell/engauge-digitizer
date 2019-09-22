/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DISCARDED_H
#define GUIDELINE_STATE_DISCARDED_H

#include "GuidelineStateAbstractBase.h"

/// Implements guideline behavior for GUIDELINE_STATE_DISCARDED
class GuidelineStateDiscarded : public GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateDiscarded(GuidelineStateContext &context);
  virtual ~GuidelineStateDiscarded();

  virtual void begin ();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleMouseRelease ();
  virtual void handleShowHide (bool show);
  virtual EllipseParameters pointToEllipse (const QPointF &posScreen) const;
  virtual QLineF pointToLine (const QPointF &poscreen) const;
  virtual void setPointGraph (const QPointF &posGraph);
  virtual QString state () const;
  virtual void updateWithLatestTransformation ();

private:
  GuidelineStateDiscarded();

};

#endif // GUIDELINE_STATE_DISCARDED_H
