#include "CallbackUpdateTransform.h"
#include "Point.h"

CallbackUpdateTransform::CallbackUpdateTransform(
    const DocumentModelCoords &modelCoords,
    DocumentAxesPointsRequired documentAxesPointsRequired)
    : CallbackAxisPointsAbstract(modelCoords, documentAxesPointsRequired) {}

bool CallbackUpdateTransform::transformIsDefined() const {
  if (documentAxesPointsRequired() == DOCUMENT_AXES_POINTS_REQUIRED_3) {
    return !isError() && (numberAxisPoints() == 3);
  } else {
    return !isError() && (numberAxisPoints() == 4);
  }
}
