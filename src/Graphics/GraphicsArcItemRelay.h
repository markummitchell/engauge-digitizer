/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_ARC_ITEM_RELAY_H
#define GRAPHICS_ARC_ITEM_RELAY_H

#include <QObject>

class GraphicsArcItem;

/// Enable postponed geometry changes for GraphicsArcItem, using a signal to trigger this class to
/// update its associated GraphicsArcItem instance.
///
/// By postponing geometry updates locally, this class
/// simplifies the calling code which can invoked while an event handler is on the stack.
/// Updating QGraphicsEllipseItem geometry while an event handler is on the stack is not
/// good software design, and results in visible drawing artifacts that may be
/// involved in QTBUG-80937.
class GraphicsArcItemRelay : public QObject
{
  Q_OBJECT;
  
public:
  /// Single constructor with associated GraphicsArcItem
  GraphicsArcItemRelay(QObject *caller,
                       GraphicsArcItem *graphicsItem);
  virtual ~GraphicsArcItemRelay();

public slots:

  /// Slot equivalent of setStartAngle and setSpanAngle
  void slotUpdateAngles (double startAngle,
                         double spanAngle);
  
private:
  GraphicsArcItemRelay();

  GraphicsArcItem *m_graphicsItem;
  
};

#endif // GRAPHICS_ARC_ITEM_RELAY_H
