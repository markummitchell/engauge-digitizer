/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_CONSTANT_X_H
#define GUIDELINE_PROJECTOR_CONSTANT_X_H

#include "GuidelineProjectorAbstract.h"
#include <QLineF>
#include <QList>
#include <QPointF>

class QRectF;
class Transformation;

/// Project a point along the vertical direction in graph coordinates to produce
/// a line segment along the constant-x direction, passing through a specified point
class GuidelineProjectorConstantX : public GuidelineProjectorAbstract
{
public:
  /// Single constructor.
  GuidelineProjectorConstantX();
  ~GuidelineProjectorConstantX();  

  /// Return line through x in graph coordinates
  QLineF fromCoordinateX (const Transformation &transformation,
                          const QRectF &sceneRect,
                          double xGraph);

  /// Return line through point in screen coordinates
  QLineF fromPosScreen (const Transformation &transformation,
                        const QRectF &sceneRect,
                        const QPointF &posScreen);

private:

  void addSide (const Transformation &transformation,
                double x,
                const QPointF &p1,
                const QPointF &p2,
                QList<QPointF> &intersections);

};

#endif // GUIDELINE_PROJECTOR_CONSTANT_X_H
