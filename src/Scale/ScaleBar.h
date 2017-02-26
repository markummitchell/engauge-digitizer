/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SCALE_BAR_H
#define SCALE_BAR_H

#include <QGraphicsLineItem>

class QGraphicsScene;
class QPointF;
class ScaleEndpoint;

/// Scale bar that is defined as the line segment between two endpoints that are placed at the two ends of a
/// maps scale bar. The scale bar can be edited to set the scale bar length in graph coordinates
class ScaleBar : public QGraphicsLineItem
{
public:
  /// Single constructor.
  ScaleBar(QGraphicsScene &scene,
           const QPointF &posScreen);
  ~ScaleBar();

  /// Update the two ends of the scale bar line segment to be consistent with the endpoints of one endpoint was moved
  void handleEndpointMove ();

  /// During creation, while mouse is still pressed, we move one endpoint (arbitrarily the second)
  void moveSecondEndpointDuringCreation (const QPointF &posScreen);

  /// Select an endpoint immediately after the scale bar has been created. This is called after a timer delay so
  /// the stack is clean (=no event handling other than the timer=done with scale bar creation and registration)
  void selectAnEndpointAfterCreation ();

private:
  ScaleBar();

  ScaleEndpoint *m_endpoint1;
  ScaleEndpoint *m_endpoint2;
};

#endif // SCALE_BAR_H
