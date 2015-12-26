#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Graph.h"

extern const QString AXIS_CURVE_NAME;

CallbackRemovePointsInCurvesGraphs::CallbackRemovePointsInCurvesGraphs(Graph &graph) :
  m_graph (graph)
{
}

CallbackSearchReturn CallbackRemovePointsInCurvesGraphs::callback (const QString &curveName,
                                                                   const Point &point)
{
  if (curveName == AXIS_CURVE_NAME) {
    m_graph.removePointAxis (point.identifier());
  } else {
    m_graph.removePointGraph (point.identifier());
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
