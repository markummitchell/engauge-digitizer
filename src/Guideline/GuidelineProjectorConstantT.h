/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_CONSTANT_T_H
#define GUIDELINE_PROJECTOR_CONSTANT_T_H

#include <QList>
#include <QPointF>

class QRectF;
class Transformation;

/// Project a point along the radial direction in graph coordinates to produce
/// a curve along the constant-theta direction, passing through a specified point
class GuidelineProjectorConstantT
{
public:
  /// Single constructor.
  GuidelineProjectorConstantT(const Transformation &transformation,
                              const QPointF &posScreen,
                              const QRectF &sceneRect);
  ~GuidelineProjectorConstantT();  

  /// Return first of the two endpoints
  QPointF pos1() const;

  /// Return second of the two endpoints
  QPointF pos2() const;  

private:
  GuidelineProjectorConstantT();

  void addSide (double num,
                double den,
                double x,
                double x1,
                double x2,
                QList<double> &xValuesBelow,
                QList<double> &xValuesAbove);
  bool isOutside (const QPointF &posScreen,
                  const QPointF &posScreenBL,
                  const QPointF &posScreenTL,
                  const QPointF &posScreenTR,
                  const QPointF &posScreenBR) const;

  QPointF m_pos1;
  QPointF m_pos2;

};

#endif // GUIDELINE_PROJECTOR_CONSTANT_T_H
