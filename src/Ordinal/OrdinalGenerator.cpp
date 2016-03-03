#include "CallbackPointOrdinal.h"
#include "Document.h"
#include "OrdinalGenerator.h"
#include "Transformation.h"

OrdinalGenerator::OrdinalGenerator() {}

double OrdinalGenerator::generateAxisPointOrdinal(const Document &document) {
  // Values that really only apply to curve points. These are set arbitrarily
  QPointF posScreen(0, 0);
  Transformation transformation;

  CallbackPointOrdinal ftor(
      document.modelCurveStyles().lineStyle(AXIS_CURVE_NAME), transformation,
      posScreen);

  Functor2wRet<const Point &, const Point &, CallbackSearchReturn>
      ftorWithCallback = functor_ret(ftor, &CallbackPointOrdinal::callback);
  document.iterateThroughCurveSegments(AXIS_CURVE_NAME, ftorWithCallback);

  return ftor.ordinal() + 1.0;
}

double OrdinalGenerator::generateCurvePointOrdinal(
    const Document &document, const Transformation &transformation,
    const QPointF &posScreen, const QString &curveName) {
  CallbackPointOrdinal ftor(document.modelCurveStyles().lineStyle(curveName),
                            transformation, posScreen);

  Functor2wRet<const Point &, const Point &, CallbackSearchReturn>
      ftorWithCallback = functor_ret(ftor, &CallbackPointOrdinal::callback);
  document.iterateThroughCurveSegments(curveName, ftorWithCallback);

  return ftor.ordinal() + 1.0;
}
