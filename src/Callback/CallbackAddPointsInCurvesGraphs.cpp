#include "CallbackAddPointsInCurvesGraphs.h"
#include "Document.h"

extern const QString AXIS_CURVE_NAME;

CallbackAddPointsInCurvesGraphs::CallbackAddPointsInCurvesGraphs(Document &document) :
  m_document (document)
{
}

CallbackSearchReturn CallbackAddPointsInCurvesGraphs::callback (const QString &curveName,
                                                                const Point &point)
{
  const QString identifier = point.identifier ();

  if (curveName == AXIS_CURVE_NAME) {
    m_document.addPointAxis (point.posScreen (),
                             point.posGraph (),
                             identifier);
  } else {
    m_document.addPointGraph (curveName,
                              point.posScreen (),
                              identifier);
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
