#include "CallbackAddPointsInCurvesGraphs.h"
#include "CoordSystem.h"

extern const QString AXIS_CURVE_NAME;

CallbackAddPointsInCurvesGraphs::CallbackAddPointsInCurvesGraphs(
    CoordSystem &coordSystem)
    : m_coordSystem(coordSystem) {}

CallbackSearchReturn
CallbackAddPointsInCurvesGraphs::callback(const QString &curveName,
                                          const Point &point) {
  const QString identifier = point.identifier();

  if (curveName == AXIS_CURVE_NAME) {
    m_coordSystem.addPointAxisWithSpecifiedIdentifier(
        point.posScreen(), point.posGraph(), identifier, point.ordinal(),
        point.isXOnly());
  } else {
    m_coordSystem.addPointGraphWithSpecifiedIdentifier(
        curveName, point.posScreen(), identifier, point.ordinal());
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
