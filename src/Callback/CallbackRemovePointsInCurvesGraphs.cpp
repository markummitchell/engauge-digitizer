#include "CallbackRemovePointsInCurvesGraphs.h"
#include "CoordSystem.h"

extern const QString AXIS_CURVE_NAME;

CallbackRemovePointsInCurvesGraphs::CallbackRemovePointsInCurvesGraphs(
    CoordSystem &coordSystem)
    : m_coordSystem(coordSystem) {}

CallbackSearchReturn
CallbackRemovePointsInCurvesGraphs::callback(const QString &curveName,
                                             const Point &point) {
  if (curveName == AXIS_CURVE_NAME) {
    m_coordSystem.removePointAxis(point.identifier());
  } else {
    m_coordSystem.removePointGraph(point.identifier());
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
