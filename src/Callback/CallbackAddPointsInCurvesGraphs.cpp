#include "CallbackAddPointsInCurvesGraphs.h"
#include "Graph.h"

extern const QString AXIS_CURVE_NAME;

CallbackAddPointsInCurvesGraphs::CallbackAddPointsInCurvesGraphs(Graph &graph) :
  m_graph (graph)
{
}

CallbackSearchReturn CallbackAddPointsInCurvesGraphs::callback (const QString &curveName,
                                                                const Point &point)
{
  const QString identifier = point.identifier ();

  if (curveName == AXIS_CURVE_NAME) {
    m_graph.addPointAxisWithSpecifiedIdentifier (point.posScreen (),
                                                 point.posGraph (),
                                                 identifier,
                                                 point.ordinal ());
  } else {
    m_graph.addPointGraphWithSpecifiedIdentifier (curveName,
                                                  point.posScreen (),
                                                  identifier,
                                                  point.ordinal ());
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
