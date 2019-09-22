/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_CONSTANT_Y_H
#define GUIDELINE_PROJECTOR_CONSTANT_Y_H

#include "GuidelineProjectorAbstract.h"
#include <QLineF>
#include <QList>
#include <QPointF>

class QRectF;
class Transformation;

/// Project a point along the horizontal direction in graph coordinates to produce
/// a line segment along the constant-y direction, passing through a specified point
class GuidelineProjectorConstantY : public GuidelineProjectorAbstract
{
public:
  /// Single constructor.
  GuidelineProjectorConstantY();
  ~GuidelineProjectorConstantY();  

  /// Return line through y in graph coordinates
  QLineF fromCoordinateY (const Transformation &transformation,
                          const QRectF &sceneRect,
                          double yGraph);

  /// Return line through point in screen coordinates
  QLineF fromPosScreen (const Transformation &transformation,
                        const QRectF &sceneRect,
                        const QPointF &posScreen);

private:

  void addSide (const Transformation &transformation,
                double y,
                const QPointF &p1,
                const QPointF &p2,
                QList<QPointF> &intersections);

};

#endif // GUIDELINE_PROJECTOR_CONSTANT_Y_H
