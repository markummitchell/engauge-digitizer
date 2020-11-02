/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
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

void GuidelineStateDeployedAbstract::beginCommon (bool hovering,
                                                  bool locked)
{
  context().guideline().setGraphicsItemZValue (Z_VALUE_GUIDELINE_DEPLOYED);
  context().guideline().setGraphicsItemVisible (true);

  if (locked) {

    // Prevent interaction. ItemIsSelectable is overkill, and in special cases adds ugly selected dashes
    QGraphicsItem::GraphicsItemFlags flags = context().guideline ().graphicsItemFlags();
    flags &= ~QGraphicsItem::ItemIsFocusable;
    flags &= ~QGraphicsItem::ItemIsMovable;
    context().guideline().setGraphicsItemFlags (flags);
    context().guideline().setGraphicsItemAcceptHoverEvents (false);

    const DocumentModelGuideline &modelGuideline = context ().modelGuideline ();
    
    context().guideline().setGraphicsItemPen (ColorPaletteToQColor (modelGuideline.lineColor ()),
                                              modelGuideline.lineWidthInactive ());

  } else {

    // Give feedback when user hovers    
    context().guideline().setGraphicsItemFlags (QGraphicsItem::ItemIsFocusable |
                                                QGraphicsItem::ItemIsMovable);
    context().guideline().setGraphicsItemAcceptHoverEvents (true);

    const DocumentModelGuideline &modelGuideline = context ().modelGuideline ();
    
    context().guideline().setGraphicsItemPen (ColorPaletteToQColor (modelGuideline.lineColor ()),
                                              hovering ? modelGuideline.lineWidthActive () : modelGuideline.lineWidthInactive ());
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

