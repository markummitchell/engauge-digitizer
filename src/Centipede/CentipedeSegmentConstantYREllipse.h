/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H
#define CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H

#include "CentipedeSegmentAbstract.h"

class QGraphicsEllipseItem;

/// Centipede for constant YR using QGraphicsEllipseItem
class CentipedeSegmentConstantYREllipse : public CentipedeSegmentAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeSegmentConstantYREllipse(const Transformation &transformation,
                                    const QPointF &posCenterScreen,
                                    double initialRadius);
  virtual ~CentipedeSegmentConstantYREllipse();

  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const;
  virtual QGraphicsItem *graphicsItem ();
  virtual void updateRadius (double radius);
  
private:
  CentipedeSegmentConstantYREllipse();

  QGraphicsEllipseItem *m_graphicsItem;
  
};

#endif // CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H
