/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeStatePrebuild.h"
#include "CentipedeStateContext.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGuideline.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include "Transformation.h"

CentipedeStatePrebuild::CentipedeStatePrebuild (CentipedeStateContext &context) :
  CentipedeStateAbstractBase (context)
{
}

CentipedeStatePrebuild::~CentipedeStatePrebuild ()
{
}

void CentipedeStatePrebuild::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeStatePrebuild::begin";
}

void CentipedeStatePrebuild::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeStatePrebuild::end";
}

void CentipedeStatePrebuild::handleKeyPress (Qt::Key /* key */,
                                             bool /* atLeastOneSelectedItem */)
{
  // Noop
}

void CentipedeStatePrebuild::handleMouseMove (QPointF /* posScreen */)
{
  // Noop
}
  
void CentipedeStatePrebuild::handleMousePress (QPointF /* posScreen */)
{
  if (context().modelCoords().coordsType() == COORDS_TYPE_CARTESIAN) {
    context().requestDelayedStateTransition (CENTIPEDE_STATE_BUILD_CARTESIAN);
  } else {
    context().requestDelayedStateTransition (CENTIPEDE_STATE_BUILD_POLAR);
  }
}

void CentipedeStatePrebuild::handleMouseRelease (QPointF /* posScreen */)
{
  // Noop
}
