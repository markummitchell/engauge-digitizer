#include "CallbackCheckEditPointAxis.h"
#include "Point.h"

CallbackCheckEditPointAxis::CallbackCheckEditPointAxis(const DocumentModelCoords &modelCoords,
                                                       const QString &pointIdentifier,
                                                       const QPointF &posScreen,
                                                       const QPointF &posGraph) :
  CallbackAxisPointsAbstract (modelCoords,
                              pointIdentifier,
                              posScreen,
                              posGraph)
{
}

bool CallbackCheckEditPointAxis::isError () const
{
  return CallbackAxisPointsAbstract::isError ();
}

QString CallbackCheckEditPointAxis::errorMessage () const
{
  return CallbackAxisPointsAbstract::errorMessage ();
}
