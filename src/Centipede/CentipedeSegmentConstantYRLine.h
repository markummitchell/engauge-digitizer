/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_CONSTANT_YR_LINE_H
#define CENTIPEDE_SEGMENT_CONSTANT_YR_LINE_H

#include "CentipedeSegmentAbstract.h"

class QGraphicsLineItem;

/// Centipede for constant YR using QGraphicsLineItem
class CentipedeSegmentConstantYRLine : public CentipedeSegmentAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeSegmentConstantYRLine(const DocumentModelGuideline &modelGuideline,
                                 const Transformation &transformation,
                                 const QPointF &posClickScreen);
  virtual ~CentipedeSegmentConstantYRLine();

  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const;
  virtual QGraphicsItem *graphicsItem ();
  virtual void updateRadius (double radius);
  
private:
  CentipedeSegmentConstantYRLine();

  QGraphicsLineItem *m_graphicsItem;

  // Two points where circle around click point intersects constant coordinate line. Due to symmetry about
  // the click circle center (for affine transformation), we do not need the center
  QPointF m_posLow;
  QPointF m_posHigh;
};

#endif // CENTIPEDE_SEGMENT_CONSTANT_YR_LINE_H
