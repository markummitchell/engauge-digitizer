/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QPen>
#include "ScaleBar.h"
#include "ZValues.h"

ScaleBar::ScaleBar(QGraphicsScene  &scene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleBar::ScaleBar";

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SCALE_BAR));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (Qt::transparent));
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setAcceptHoverEvents (true);
  setFlags (QGraphicsItem::ItemIsFocusable);
}

ScaleBar::~ScaleBar ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleBar::~ScaleBar";
}
