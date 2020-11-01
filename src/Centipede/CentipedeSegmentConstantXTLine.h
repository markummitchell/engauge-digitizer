/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_CONSTANT_XT_LINE_H
#define CENTIPEDE_SEGMENT_CONSTANT_XT_LINE_H

#include "CentipedeSegmentAbstract.h"

class QGraphicsLineItem;

/// Centipede for constant XT using QGraphicsLineItem
class CentipedeSegmentConstantXTLine : public CentipedeSegmentAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeSegmentConstantXTLine(const Transformation &transformation,
                                 const QPointF &posCenterScreen,
                                 double initialRadius);
  virtual ~CentipedeSegmentConstantXTLine();

  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const;
  virtual QGraphicsItem *graphicsItem ();
  virtual void updateRadius (double radius);
  
private:
  CentipedeSegmentConstantXTLine();

  QGraphicsLineItem *m_graphicsItem;
  
};

#endif // CENTIPEDE_SEGMENT_CONSTANT_XT_LINE_H
