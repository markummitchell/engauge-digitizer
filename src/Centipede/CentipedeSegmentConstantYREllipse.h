/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H
#define CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H

#include "CentipedeSegmentAbstract.h"

class GraphicsArcItem;
class GraphicsArcItemRelay;

/// Centipede for constant YR
class CentipedeSegmentConstantYREllipse : public CentipedeSegmentAbstract
{
  Q_OBJECT;

public:
  /// Constructor with individual coordinates
  CentipedeSegmentConstantYREllipse(const DocumentModelGuideline &modelGuideline,
                                    const Transformation &transformation,
                                    const QPointF &posClickScreen);
  virtual ~CentipedeSegmentConstantYREllipse();

  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const;
  virtual QGraphicsItem *graphicsItem ();
  virtual void updateRadius (double radius);

signals:
  
  /// Send new geometry for later updating
  void signalUpdateAngles (int, int);
  
private:
  CentipedeSegmentConstantYREllipse();

  GraphicsArcItem *m_graphicsItem;
  GraphicsArcItemRelay *m_graphicsItemRelay;  

  double m_angleScreenToEllipseAxes;

  // Two points where circle around click point intersects constant coordinate line
  QPointF m_posLow;
  QPointF m_posHigh;

  // Two angles where circle around click point intersects constant coordinate line. Angle is
  // about the origin and starting around one (semiminor or semimajor) axes of the ellipe
  //
  // Due to asymmetry (angles between center-and-high and center-and-low are usually different),
  // we know the angle to click point cannot be calculated as (m_angleLow + m_angleHigh) / 2
  double m_angleLow;
  double m_angleCenter;
  double m_angleHigh;
};

#endif // CENTIPEDE_SEGMENT_CONSTANT_YR_ELLIPSE_H
