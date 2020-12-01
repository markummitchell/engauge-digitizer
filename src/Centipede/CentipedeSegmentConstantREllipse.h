/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_CONSTANT_R_ELLIPSE_H
#define CENTIPEDE_SEGMENT_CONSTANT_R_ELLIPSE_H

#include "CentipedeDebugPolar.h"
#include "CentipedeSegmentAbstract.h"

class DocumentModelCoords;
class GraphicsArcItem;
class GraphicsArcItemRelay;
class GraphicsScene;

/// Centipede for constant R
class CentipedeSegmentConstantREllipse : public CentipedeSegmentAbstract
{
  Q_OBJECT;

public:
  /// Constructor with individual coordinates
  CentipedeSegmentConstantREllipse(GraphicsScene &scene,
                                   const DocumentModelCoords &modelCoords,
                                   const DocumentModelGuideline &modelGuideline,
                                   const Transformation &transformation,
                                   const QPointF &posClickScreen);
  virtual ~CentipedeSegmentConstantREllipse();

  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const;
  virtual void updateRadius (double radius);

signals:
  
  /// Send new geometry for later updating
  void signalUpdateAngles (QPointF posTangentialLow,
                           QPointF posTangentialCenter,
                           QPointF posTangentialHigh,
                           double scaling);
  
private:
  CentipedeSegmentConstantREllipse();

  void posScreenConstantRForXTHighLowAngles (double radius,
                                             const QPointF &posLow,
                                             const QPointF &posHigh) const;

  GraphicsArcItem *m_graphicsItem;
  GraphicsArcItemRelay *m_graphicsItemRelay;  

  // Two points where circle around click point intersects constant theta coordinate line
  QPointF m_posRadialLow;
  QPointF m_posRadialHigh;

  // Two points where circle around click points intersects constant radius coordinate line
  QPointF m_posTangentialLow;
  QPointF m_posTangentialHigh;

  /// Debugging
  CentipedeDebugPolar m_debugPolar;
};

#endif // CENTIPEDE_SEGMENT_CONSTANT_R_ELLIPSE_H
