/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_HANDLE_H
#define GUIDELINE_STATE_HANDLE_H

#include "GuidelineStateAbstractBase.h"

/// State for an invisible handle which was previously a template but morphed
/// into an invisible handle that the user is dragging. At the end of the drag
/// this disappears. Since the Guideline in this state is invisible we do not
/// have to worry about rotating this to be parallel with an axis. A visible
/// deployed Guideline is dragged along with this handle. We have total freedom 
/// to rotated and/or move (and in the range isocontour case even bend) the
/// slaved deployed Guideline during the dragging
class GuidelineStateHandle : public GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateHandle(GuidelineStateContext &context);
  virtual ~GuidelineStateHandle();

  virtual void begin ();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleMouseRelease ();
  virtual void handleShowHide (bool show);
  virtual QLineF lineFromPoint (const QPointF &posScreen) const;
  virtual QString state () const;

};

#endif // GUIDELINE_STATE_HANDLE_H
