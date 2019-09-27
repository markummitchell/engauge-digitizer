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

void GuidelineStateAbstractBase::handleMousePressCommon (const QPointF &posScreen,
                                                         GuidelineState stateDeployed,
                                                         GuidelineState stateReplacement)
{
  context().setStateReplacement (stateReplacement);

  // Unselect all selected items. This prevents the extremely confusing error where an
  // existing axis point stays selected and gets dragged along with this Guideline,
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

  // Visible Guideline will follow this one. Its geometry will be set after every drag event
  GuidelineAbstract *guidelineVisible = context().createGuideline (stateDeployed);

  GuidelineFormat guidelineFormat;
  guidelineVisible->setGraphicsItemPen (guidelineFormat.colorDeployedNonHover (),
                                        guidelineFormat.lineWidthNonHover ());

  guidelineVisible->updateGeometry (posScreen);

  context().guideline().bindGuidelineVisible (guidelineVisible);

  context().requestStateTransition (GUIDELINE_STATE_HANDLE);
}

QRectF GuidelineStateAbstractBase::sceneRect () const
{
  return m_context.guideline().scene().sceneRect();
}
