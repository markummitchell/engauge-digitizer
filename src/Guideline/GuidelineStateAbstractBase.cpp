/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineIdentifierGenerator.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <qmath.h>

GuidelineStateAbstractBase::GuidelineStateAbstractBase(GuidelineStateContext &context) :
  m_context (context)
{
}

GuidelineStateAbstractBase::~GuidelineStateAbstractBase ()
{
}

GuidelineStateContext &GuidelineStateAbstractBase::context () const
{
  return m_context;
}

void GuidelineStateAbstractBase::handleMousePressCommon (const QPointF &posScene,
                                                         GuidelineState stateHandle,
                                                         GuidelineState stateDeployed)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateAbstractBase::handleMousePressCommon "
                              << m_context.stateDump ().toLatin1().data();

  // Unselect all selected items. This prevents the extremely confusing error where an
  // a currently-selected axis point stays selected and gets dragged along with this Guideline,
  // which moves the axis unexpectedly
  QList<QGraphicsItem*>::iterator itr;
  QList<QGraphicsItem*> items = m_context.guideline().scene().selectedItems();
  for (itr = items.begin(); itr != items.end(); itr++) {
    QGraphicsItem *item = *itr;

    // How do we know which is the Guideline that we want to keep selected? By its type
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () != GRAPHICS_ITEM_TYPE_GUIDELINE) {
      item->setSelected (false);
    }
  }

  // Visible Guideline will follow this one. Its geometry will be set after every drag event. It is
  // not registered with Guidelines container
  GuidelineAbstract *guidelineVisible = context().createGuideline (GuidelineIdentifierGenerator::next (),
                                                                   stateDeployed);

  GuidelineFormat guidelineFormat (context().color());
  guidelineVisible->setGraphicsItemPen (guidelineFormat.colorDeployedNonHover (),
                                        guidelineFormat.lineWidthNonHover ());

  // Place new Guideline at cursor position
  guidelineVisible->updateGeometry (posScene);

  context().guideline().bindGuidelineVisibleToInvisible (guidelineVisible);

  context().requestStateTransition (stateHandle);
}

QRectF GuidelineStateAbstractBase::sceneRect () const
{
  return m_context.guideline().scene().sceneRect();
}
