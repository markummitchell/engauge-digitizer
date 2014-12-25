#include "CallbackUpdateTransform.h"
#include "Point.h"

CallbackUpdateTransform::CallbackUpdateTransform(const DocumentModelCoords &modelCoords) :
  CallbackAxisPointsAbstract (modelCoords)
{
}

QTransform CallbackUpdateTransform::transform ()
{
  return CallbackAxisPointsAbstract::transform();
}

bool CallbackUpdateTransform::transformIsDefined () const
{
  return !isError () && (numberAxisPoints () == 3);
}
