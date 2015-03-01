#include "CallbackUpdateTransform.h"
#include "Point.h"

CallbackUpdateTransform::CallbackUpdateTransform(const DocumentModelCoords &modelCoords) :
  CallbackAxisPointsAbstract (modelCoords)
{
}

CallbackUpdateTransform::CallbackUpdateTransform(const DocumentModelCoords &modelCoords,
                                                 const QPointF &posScreen0,
                                                 const QPointF &posScreen1,
                                                 const QPointF &posScreen2,
                                                 const QPointF &posGraph0,
                                                 const QPointF &posGraph1,
                                                 const QPointF &posGraph2) :
  CallbackAxisPointsAbstract (modelCoords)
{
  const QString DUMMY_CURVENAME ("dummy");

  Point p1 (DUMMY_CURVENAME, posScreen0, posGraph0);
  Point p2 (DUMMY_CURVENAME, posScreen1, posGraph1);
  Point p3 (DUMMY_CURVENAME, posScreen2, posGraph2);

  callback (DUMMY_CURVENAME, p1);
  callback (DUMMY_CURVENAME, p2);
  callback (DUMMY_CURVENAME, p3);
}

QTransform CallbackUpdateTransform::transform ()
{
  return CallbackAxisPointsAbstract::transform();
}

bool CallbackUpdateTransform::transformIsDefined () const
{
  return !isError () && (numberAxisPoints () == 3);
}
