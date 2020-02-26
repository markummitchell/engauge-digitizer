/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_HANDLE_ABSTRACT_H
#define GUIDELINE_STATE_HANDLE_ABSTRACT_H

#include "GuidelineStateAbstractBase.h"

/// State for an invisible handle which was previously a deployed Guideline but morphed
/// into an invisible handle that the user is dragging. At the end of the drag
/// this reappears. Since the Guideline in this state is invisible we do not
/// have to worry about rotating this to be parallel with an axis. A visible
/// deployed Guideline is dragged along with this handle. We have total freedom 
/// to rotated and/or move (and in the range isocontour case even bend) the
/// slaved deployed Guideline during the dragging
class GuidelineStateHandleAbstract : public GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateHandleAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateHandleAbstract();

  virtual bool doPaint () const;
  virtual void handleActiveChange (bool active);
  virtual void handleGuidelineMode (bool visible,
                                    bool locked);
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleTimeout ();
  virtual void updateWithLatestTransformation ();

protected:
  void beginCommon ();
  
};

#endif // GUIDELINE_STATE_HANDLE_ABSTRACT_H
