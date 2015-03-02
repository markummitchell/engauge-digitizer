#include "CallbackUpdateTransform.h"
#include "Point.h"

CallbackUpdateTransform::CallbackUpdateTransform(const DocumentModelCoords &modelCoords) :
  CallbackAxisPointsAbstract (modelCoords)
{
}

bool CallbackUpdateTransform::transformIsDefined () const
{
  return !isError () && (numberAxisPoints () == 3);
}
