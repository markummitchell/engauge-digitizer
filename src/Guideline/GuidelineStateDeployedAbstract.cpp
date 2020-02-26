/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
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

void GuidelineStateDeployedAbstract::beginCommon (GuidelineFormat::HoverOption hoverOption,
                                                  bool locked)
{
  GuidelineFormat guidelineFormat (context().color());

  context().guideline().setGraphicsItemZValue (Z_VALUE_GUIDELINE_DEPLOYED);
  context().guideline().setGraphicsItemVisible (true);

  if (locked) {

    // Prevent interaction. ItemIsSelectable is overkill, and in special cases adds ugly selected dashes
    QGraphicsItem::GraphicsItemFlags flags = context().guideline ().graphicsItemFlags();
    flags &= ~QGraphicsItem::ItemIsFocusable;
    flags &= ~QGraphicsItem::ItemIsMovable;
    context().guideline().setGraphicsItemFlags (flags);
    context().guideline().setGraphicsItemAcceptHoverEvents (false);

    context().guideline().setGraphicsItemPen (guidelineFormat.colorDeployedNonHover (),
                                              guidelineFormat.lineWidthNonHover ());

  } else {

    // Give feedback when user hovers    
    context().guideline().setGraphicsItemFlags (QGraphicsItem::ItemIsFocusable |
                                                QGraphicsItem::ItemIsMovable);
    context().guideline().setGraphicsItemAcceptHoverEvents (true);

    context().guideline().setGraphicsItemPen (hoverOption == GuidelineFormat::HOVER_ON ?
                                              guidelineFormat.colorDeployedHover () :
                                              guidelineFormat.colorDeployedNonHover (),
                                              hoverOption == GuidelineFormat::HOVER_ON ?
                                              guidelineFormat.lineWidthHover () :
                                              guidelineFormat.lineWidthNonHover ());
  }
}

void GuidelineStateDeployedAbstract::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedAbstract::end";
}

void GuidelineStateDeployedAbstract::handleMouseRelease (const QPointF & /* posScene */)
{
  // Noop
}

void GuidelineStateDeployedAbstract::handleTimeout ()
{
  // Noop
}

