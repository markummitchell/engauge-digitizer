/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "Guideline.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedAbstract.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

GuidelineStateDeployedAbstract::GuidelineStateDeployedAbstract (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateDeployedAbstract::~GuidelineStateDeployedAbstract ()
{
}

void GuidelineStateDeployedAbstract::beginCommon (GuidelineFormat::HoverOption hoverOption)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedAbstract::begin";

  GuidelineFormat guidelineFormat;

  context().guideline().setZValue (Z_VALUE_GUIDELINE_DEPLOYED);
  context().guideline().setVisible (true);
  // ItemIsSelectable is overkill, and in special cases adds ugly selected dashes
  context().guideline().setFlags (QGraphicsItem::ItemIsFocusable |
                                  QGraphicsItem::ItemIsMovable);
  context().guideline().setAcceptHoverEvents (true); // Give feedback when user hovers
  context().guideline().setPenColor (hoverOption == GuidelineFormat::HOVER_ON ?
                                       guidelineFormat.colorDeployedHover () :
                                       guidelineFormat.colorDeployedNonHover (),
                                     hoverOption == GuidelineFormat::HOVER_ON ?
                                       guidelineFormat.lineWidthHover () :
                                       guidelineFormat.lineWidthNonHover ());
}

void GuidelineStateDeployedAbstract::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedAbstract::end";
}

void GuidelineStateDeployedAbstract::handleMouseRelease ()
{
  // Noop
}
