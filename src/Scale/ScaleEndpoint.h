/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SCALE_ENDPOINT_H
#define SCALE_ENDPOINT_H

#include <QGraphicsEllipseItem>

class QPointF;
class ScaleBar;

/// Scale bar endpoint that is implemented as a circle that can be selected and dragged
class ScaleEndpoint : public QGraphicsEllipseItem
{
public:
  /// Single constructor.
  ScaleEndpoint(ScaleBar &scaleBar,
                const QPointF &posScreen);
  ~ScaleEndpoint();

  /// Catch mouse move event to move scale bar in sync with this endpoint
  virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

  /// Set endpoint position relative to scale bar parent, for the specified absolute screen position
  void setEndpointPosition (const QPointF &posScreen);

private:
  ScaleEndpoint();

  ScaleBar &m_scaleBar;
};

#endif // SCALE_ENDPOINT_H
