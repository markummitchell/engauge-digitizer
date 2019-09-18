/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_VERTICAL_H
#define GUIDELINE_PROJECTOR_VERTICAL_H

#include <QList>

class QPointF;
class QRectF;
class Transformation;

/// Project a point along the vertical direction in graph coordinates to produce
/// a line segment along the constant-x direction, passing through a specified point
class GuidelineProjectorVertical
{
public:
  /// Single constructor.
  GuidelineProjectorVertical(const Transformation &transformation,
                             const QPointF &posScreen,
                             const QRectF &sceneRect);
  ~GuidelineProjectorVertical();  

  /// Return first of the two endpoints
  QPointF pos1() const;

  /// Return second of the two endpoints
  QPointF pos2() const;  

private:
  GuidelineProjectorVertical();

  void addSide (double num,
                double den,
                double y,
                double y1,
                double y2,
                QList<double> &yValuesBelow,
                QList<double> &yValuesAbove);
  
  QPointF m_pos1;
  QPointF m_pos2;

};

#endif // GUIDELINE_PROJECTOR_VERTICAL_H
