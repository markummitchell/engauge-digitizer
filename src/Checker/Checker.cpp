#include "Checker.h"
#include "Logger.h"
#include <qmath.h>
#include <QPen>
#include "Transformation.h"

// To emphasize that the axis lines are still there, we make these checker somewhat transparent
const double CHECKER_OPACITY = 0.6;

// One-pixel wide line (produced by setting width=0) is too small
const int CHECKER_POINTS_WIDTH = 5;

Checker::Checker(const QPolygonF &polygon) :
  QGraphicsPolygonItem (polygon)
{
  setOpacity (CHECKER_OPACITY);
}

void Checker::setLineColor (const QColor &lineColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::setLineColor";

  setPen (QPen (QBrush (lineColor), CHECKER_POINTS_WIDTH));
}
