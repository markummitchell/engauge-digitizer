#include "CallbackCheckAddPointAxis.h"
#include "Curve.h"
#include "Point.h"

extern const QString AXIS_CURVE_NAME;

CallbackCheckAddPointAxis::CallbackCheckAddPointAxis(const DocumentModelCoords &modelCoords,
                                                     const QPointF &posScreen,
                                                     const QPointF &posGraph) :
  CallbackAxisPointsAbstract (modelCoords)
{
  // Insert an extra Point as if it already was in the axes curve. This is done before iterating rather
  // than after since there is no safe place to do this afterwards (isError and errorMessage may be called more than once)
  Point point (AXIS_CURVE_NAME,
               posScreen,
               posGraph);

  callback (AXIS_CURVE_NAME,
            point);
}

bool CallbackCheckAddPointAxis::isError () const
{
  return CallbackAxisPointsAbstract::isError ();
}

QString CallbackCheckAddPointAxis::errorMessage () const
{
  return CallbackAxisPointsAbstract::errorMessage ();
}
