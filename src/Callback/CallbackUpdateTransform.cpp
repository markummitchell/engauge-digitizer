#include "CallbackUpdateTransform.h"
#include "Point.h"

CallbackUpdateTransform::CallbackUpdateTransform(const DocumentModelCoords &modelCoords,
                                                 DocumentAxesPointsRequired documentAxesPointsRequired) :
  CallbackAxisPointsAbstract (modelCoords,
                              documentAxesPointsRequired)
{
}

bool CallbackUpdateTransform::transformIsDefined () const
{
  return !isError () && (numberAxisPoints () == 3);
}
