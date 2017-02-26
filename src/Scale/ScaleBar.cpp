/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QPointF>
#include "ScaleBar.h"
#include "ScaleEndpoint.h"
#include "ZValues.h"

ScaleBar::ScaleBar(QGraphicsScene  &scene,
                   const QPointF &posScreen) :
  m_endpoint1 (0),
  m_endpoint2 (0)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleBar::ScaleBar";

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SCALE_BAR));

  scene.addItem (this);
  setPen (QPen (Qt::black));
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setAcceptHoverEvents (true);
  setFlags (QGraphicsItem::ItemIsFocusable);

  // Initially the line starts and stops at the same spot. As cursor is moved, one of the end points will follow it
  setLine (QLineF (posScreen,
                   posScreen));

  m_endpoint1 = new ScaleEndpoint (*this,
                                   posScreen);
  m_endpoint2 = new ScaleEndpoint (*this,
                                   posScreen);
}

ScaleBar::~ScaleBar ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleBar::~ScaleBar";
}

void ScaleBar::handleEndpointMove ()
{
  setLine (QLineF (m_endpoint1->pos ().x () + m_endpoint1->boundingRect ().size ().width () / 2,
                   m_endpoint1->pos ().y () + m_endpoint1->boundingRect ().size ().height () / 2,
                   m_endpoint2->pos ().x () + m_endpoint2->boundingRect ().size ().width () / 2,
                   m_endpoint2->pos ().y () + m_endpoint2->boundingRect ().size ().height ()/ 2));
}

void ScaleBar::moveSecondEndpointDuringCreation (const QPointF &posScreen)
{
  ENGAUGE_CHECK_PTR (m_endpoint2);

  m_endpoint2->setEndpointPosition (posScreen);
}

void ScaleBar::selectAnEndpointAfterCreation ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleBar::selectAnEndpointAfterCreation";

  m_endpoint2->setSelected (true);
}
