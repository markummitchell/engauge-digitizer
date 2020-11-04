/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H
#define CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H

#include "CentipedeSegmentAbstract.h"

class GraphicsArcItem;

/// Centipede for constant YR using QGraphicsEllipseItem
///
/// Due to bug QTBUG-80937 at https://bugreports.qt.io/browse/QTBUG-80937, the elliptical
/// segment is not always drawn correctly when the QGraphicsEllipseItem::scanAngle is less than
/// 360 degrees (which we want for finite length Centipedes). For example, at 90 degrees the curve
/// is much shorter than it should be. So a full ellipse is drawn
class CentipedeSegmentConstantYREllipse : public CentipedeSegmentAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeSegmentConstantYREllipse(const DocumentModelGuideline &modelGuideline,
                                    const Transformation &transformation,
                                    const QPointF &posClickScreen);
  virtual ~CentipedeSegmentConstantYREllipse();

  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const;
  virtual QGraphicsItem *graphicsItem ();
  virtual void updateRadius (double radius);
  
private:
  CentipedeSegmentConstantYREllipse();

  GraphicsArcItem *m_graphicsItem;

  // Two points where circle around click point intersects constant coordinate line
  QPointF m_posLow;
  QPointF m_posHigh;
};

#endif // CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H
