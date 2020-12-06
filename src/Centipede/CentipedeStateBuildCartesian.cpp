/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeStateBuildCartesian.h"
#include "Logger.h"

CentipedeStateBuildCartesian::CentipedeStateBuildCartesian (CentipedeStateContext &context) :
  CentipedeStateAbstractBase (context)
{
}

CentipedeStateBuildCartesian::~CentipedeStateBuildCartesian ()
{
}

void CentipedeStateBuildCartesian::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeStateBuildCartesian::begin";
}

void CentipedeStateBuildCartesian::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeStateBuildCartesian::end";
}

void CentipedeStateBuildCartesian::handleKeyPress (Qt::Key key,
                                                   bool atLeastOneSelectedItem)
{
}

void CentipedeStateBuildCartesian::handleMouseMove (QPointF posScreen)
{
}
  
void CentipedeStateBuildCartesian::handleMousePress (QPointF posScreen)
{
}

void CentipedeStateBuildCartesian::handleMouseRelease (QPointF posScreen)
{
}
