/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_LINE_ITEM_RELAY_H
#define GRAPHICS_LINE_ITEM_RELAY_H

#include <QObject>
#include <QPointF>

class QGraphicsLineItem;

/// Enable postponed geometry changes for QGraphicsLineItem, using a signal to trigger this class to
/// update its associated QGraphicsLineItem instance.
///
/// By postponing geometry updates locally, this class simplifies the calling code which can invoked
/// while an event handler is on the stack. Updating QGraphicsEllipseItem geometry while an event handler
/// is on the stack is not good software design
class GraphicsLineItemRelay : public QObject
{
  Q_OBJECT;
  
public:
  /// Single constructor with associated GraphicsArcItem
  GraphicsLineItemRelay(QObject *caller,
                        QGraphicsLineItem *graphicsItem);
  virtual ~GraphicsLineItemRelay();

public slots:

  /// Slot equivalent of setStartAngle and setSpanAngle
  void slotUpdateEndpoints (QPointF start,
                            QPointF end);
                            
  
private:
  GraphicsLineItemRelay();

  QGraphicsLineItem *m_graphicsItem;
  
};

#endif // GRAPHICS_LINE_ITEM_RELAY_H
