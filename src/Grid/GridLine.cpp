/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GridLine.h"
#include <qdebug.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>

GridLine::GridLine ()
{
}

GridLine::~GridLine ()
{
  // Crash here means QGraphicsScene::clear was called, which is entirely unnecessary

  for (int i = 0; i < m_segments.count(); i++) {
    QGraphicsItem *item = m_segments [i];
    delete item;
  }

  m_segments.clear ();
}

GridLine::GridLine (const GridLine & /* other */)
{
  ENGAUGE_ASSERT (false);
}

GridLine &GridLine::operator= (GridLine & /* other */)
{
  ENGAUGE_ASSERT (false);

  return *this;
}

void GridLine::add (QGraphicsItem *item)
{
  m_segments.push_back (item);
}

void GridLine::setPen (const QPen &pen)
{
  for (int i = 0; i < m_segments.count(); i++) {
    QGraphicsItem *item = m_segments [i];
    if (item != 0) {

      // Downcast since QGraphicsItem does not have a pen
      QGraphicsLineItem *itemLine = dynamic_cast<QGraphicsLineItem*> (item);
      QGraphicsEllipseItem *itemArc = dynamic_cast<QGraphicsEllipseItem*> (item);
      if (itemLine != 0) {
        itemLine->setPen (pen);
      } else if (itemArc != 0) {
        itemArc->setPen (pen);
      }
    }
  }
}

void GridLine::setVisible (bool visible)
{
  for (int i = 0; i < m_segments.count(); i++) {
    QGraphicsItem *item = m_segments [i];
    item->setVisible (visible);
  }
}
