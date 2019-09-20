/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_PROJECTOR_CONSTANT_R_H
#define GUIDELINE_PROJECTOR_CONSTANT_R_H

#include <QList>
#include <QPointF>

class QRectF;
class Transformation;

/// Project a point along the tangential direction in graph coordinates to produce
/// a curve along the constant-range direction, passing through a specified point
class GuidelineProjectorConstantR
{
public:
  /// Single constructor.
  GuidelineProjectorConstantR(const Transformation &transformation,
                              const QPointF &posScreen,
                              const QRectF &sceneRect);
  ~GuidelineProjectorConstantR();  

  /// Return first of the two endpoints
  QPointF pos1() const;

  /// Return second of the two endpoints
  QPointF pos2() const;  

private:
  GuidelineProjectorConstantR();

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

#endif // GUIDELINE_PROJECTOR_CONSTANT_R_H
