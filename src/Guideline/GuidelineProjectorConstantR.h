/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_CONSTANT_R_H
#define GUIDELINE_PROJECTOR_CONSTANT_R_H

#include "EllipseParameters.h"
#include "GuidelineProjectorAbstract.h"
#include <QList>
#include <QPointF>
#include <QRectF>

class QRectF;
class Transformation;

/// Project a point along the tangential direction in graph coordinates to produce
/// a curve along the constant-range direction, passing through a specified point
class GuidelineProjectorConstantR : public GuidelineProjectorAbstract
{
public:
  /// Single constructor.
  GuidelineProjectorConstantR();
  ~GuidelineProjectorConstantR();  

  /// Return line through y in graph coordinates
  EllipseParameters fromCoordinateR (const Transformation &transformation,
                                     const QRectF &sceneRect,
                                     double rGraph);

  /// Return line through point in screen coordinates
  EllipseParameters fromPosScreen (const Transformation &transformation,
                                   const QRectF &sceneRect,
                                   const QPointF &posScreen);

};

#endif // GUIDELINE_PROJECTOR_CONSTANT_R_H
