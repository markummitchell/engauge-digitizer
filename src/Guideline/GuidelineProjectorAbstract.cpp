/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineProjectorAbstract.h"
#include <QPointF>
#include <QRectF>
#include "Transformation.h"

GuidelineProjectorAbstract::GuidelineProjectorAbstract()
{
}

GuidelineProjectorAbstract::~GuidelineProjectorAbstract()
{
}

void GuidelineProjectorAbstract::calculateCorners (const Transformation &transformation,
                                                   const QRectF &sceneRect,
                                                   QPointF &posGraphBL,
                                                   QPointF &posGraphTL,
                                                   QPointF &posGraphTR,
                                                   QPointF &posGraphBR) const
{
  double width = sceneRect.width();
  double height = sceneRect.height();

  // Convert sceneRect to graph coordinates
  QPointF posScreenBL (0, 0), posScreenTL (0, height), posScreenTR (width, height), posScreenBR (width, 0);
  
  transformation.transformScreenToRawGraph (posScreenBL, posGraphBL);
  transformation.transformScreenToRawGraph (posScreenTL, posGraphTL);
  transformation.transformScreenToRawGraph (posScreenTR, posGraphTR);
  transformation.transformScreenToRawGraph (posScreenBR, posGraphBR);
}

bool GuidelineProjectorAbstract::isOutside (const QRectF &sceneRect,
                                            const QPointF &posScreen) const
{
  double width = sceneRect.width();
  double height = sceneRect.height();

  QPointF posScreenBL (0, 0), posScreenTL (0, height), posScreenTR (width, height), posScreenBR (width, 0);

  QPolygonF polygon;
  polygon << posScreenBL << posScreenTL << posScreenTR << posScreenBR;

  // Qt::OddEvenFill is faster and less accurate and Qt::WindingFill is slower and more accurate
  return !polygon.containsPoint (posScreen,
                                 Qt::WindingFill);
}
