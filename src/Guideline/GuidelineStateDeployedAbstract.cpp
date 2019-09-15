/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedAbstract.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

const Qt::GlobalColor COLOR_DEPLOYED = Qt::green;

GuidelineStateDeployedAbstract::GuidelineStateDeployedAbstract (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateDeployedAbstract::~GuidelineStateDeployedAbstract ()
{
}

void GuidelineStateDeployedAbstract::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedAbstract::begin";

  context().guideline().setZValue (Z_VALUE_GUIDELINE_DEPLOYED);
  context().guideline().setVisible (true);
  context().guideline().setFlags (QGraphicsItem::ItemIsFocusable |
                                  QGraphicsItem::ItemIsSelectable |
                                  QGraphicsItem::ItemIsMovable);
  context().guideline().setAcceptHoverEvents (false);
  context().guideline().setPenColor (COLOR_DEPLOYED);
}

bool GuidelineStateDeployedAbstract::doPaint () const
{
  return true;
}

void GuidelineStateDeployedAbstract::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedAbstract::end";
}

void GuidelineStateDeployedAbstract::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedAbstract::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedAbstract::handleMousePress ()
{
  // Noop
}

void GuidelineStateDeployedAbstract::handleMouseRelease ()
{
  // Noop
}
