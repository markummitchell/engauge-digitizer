/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_DEPLOYED_ABSTRACT_H
#define GUIDELINE_STATE_DEPLOYED_ABSTRACT_H

#include "CoordsType.h"
#include "GuidelineFormat.h"
#include "GuidelineStateAbstractBase.h"
#include <QPointF>

/// Abstract class for deployed states
class GuidelineStateDeployedAbstract : public GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateDeployedAbstract(GuidelineStateContext &context);
  virtual ~GuidelineStateDeployedAbstract();

  virtual void end ();
  virtual void handleMouseRelease (const QPointF &posScene);

  /// Coordinates type associated with the last time Transformation matrix was used
  CoordsType lastCoordsType () const;

  /// Save coordinates type associated with the current Transformation matrix
  void saveLastCoordsType ();

protected:

  /// Initialization common to all states
  void beginCommon (GuidelineFormat::HoverOption hoverOption);

private:

  /// Track coordinates type (cartesian or polar) used with last Transformation. If there
  /// is a transition than we need to throw all deployed Guidelines
  CoordsType m_lastCoordsType;
};

#endif // GUIDELINE_STATE_DEPLOYED_ABSTRACT_H
