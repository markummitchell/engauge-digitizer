/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_HORIZONTAL_H
#define GUIDELINE_PROJECTOR_HORIZONTAL_H

#include <QList>

class QPointF;
class QRectF;
class Transformation;

/// Project a point along the horizontal direction in graph coordinates to produce
/// a line segment along the constant-y direction, passing through a specified point
class GuidelineProjectorHorizontal
{
public:
  /// Single constructor.
  GuidelineProjectorHorizontal(const Transformation &transformation,
                               const QPointF &posScreen,
                               const QRectF &sceneRect);
  ~GuidelineProjectorHorizontal();  

  /// Return first of the two endpoints
  QPointF pos1() const;

  /// Return second of the two endpoints
  QPointF pos2() const;  

private:
  GuidelineProjectorHorizontal();

  void addSide (double num,
                double den,
                double x,
                double x1,
                double x2,
                QList<double> &xValuesBelow,
                QList<double> &xValuesAbove);
  
  QPointF m_pos1;
  QPointF m_pos2;

};

#endif // GUIDELINE_PROJECTOR_HORIZONTAL_H
