/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsLineItemRelay.h"
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QLineF>
#include <QObject>
#include <QPainter>
#include "QtToString.h"

GraphicsLineItemRelay::GraphicsLineItemRelay (QObject *caller,
                                              QGraphicsLineItem *graphicsItem) :
  m_graphicsItem (graphicsItem)
{
  // Queue for later by including Qt::QueuedConnection
  connect (caller, SIGNAL (signalUpdateEndpoints (QPointF, QPointF)),
           this, SLOT (slotUpdateEndpoints (QPointF, QPointF)),
           Qt::QueuedConnection);
}

GraphicsLineItemRelay::~GraphicsLineItemRelay ()
{
  // Calling code is responsible for deallocating graphics item
}
                                 
void GraphicsLineItemRelay::slotUpdateEndpoints (QPointF start,
                                                 QPointF end)
{
  m_graphicsItem->setLine (QLineF (start,
                                   end));
}
