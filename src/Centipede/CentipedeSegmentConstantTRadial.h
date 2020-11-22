/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_CONSTANT_T_RADIAL_H
#define CENTIPEDE_SEGMENT_CONSTANT_T_RADIAL_H

#include "CentipedeSegmentAbstract.h"
#include "DocumentModelCoords.h"

class GraphicsLineItemRelay;
class GraphicsScene;
class QGraphicsLineItem;

/// Centipede for constant T radial using QGraphicsLineItem
class CentipedeSegmentConstantTRadial : public CentipedeSegmentAbstract
{
  Q_OBJECT;
  
public:
  /// Constructor with individual coordinates
  CentipedeSegmentConstantTRadial(GraphicsScene &scene,
                                  const DocumentModelCoords &modelCoords,
                                  const DocumentModelGuideline &modelGuideline,
                                  const Transformation &transformation,
                                  const QPointF &posClickScreen);
  virtual ~CentipedeSegmentConstantTRadial();

  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const;
  virtual void updateRadius (double radius);

signals:

  /// Send new geometry for later updating
  void signalUpdateEndpoints (QPointF start,
                              QPointF end);
  
private:
  CentipedeSegmentConstantTRadial();

  QGraphicsLineItem *m_graphicsItem;
  GraphicsLineItemRelay *m_graphicsItemRelay;
  
  // Two points where circle around click point intersects constant coordinate line. Due to symmetry about
  // the click circle center (for affine transformation), we do not need the center
  QPointF m_posLow;
  QPointF m_posHigh;
};

#endif // CENTIPEDE_SEGMENT_CONSTANT_T_RADIAL_H
