/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_ABSTRACT_H
#define GUIDELINE_PROJECTOR_ABSTRACT_H

class QPointF;
class QRectF;
class Transformation;

/// Base class for Guideline projectors
class GuidelineProjectorAbstract
{
public:
  /// Single constructor
  GuidelineProjectorAbstract();
  ~GuidelineProjectorAbstract();

protected:

  /// Conpute four corners of scene in graph coordinates
  void calculateCorners (const Transformation &transformation,
                         const QRectF &sceneRect,
                         QPointF &posGraphBL,
                         QPointF &posGraphTL,
                         QPointF &posGraphTR,
                         QPointF &posGraphBR) const;

  /// Return true if point is outside of the scene
  bool isOutside (const QRectF &sceneRect,
                  const QPointF &posScreen) const;
};

#endif // GUIDELINE_PROJECTOR_ABSTRACT_H
