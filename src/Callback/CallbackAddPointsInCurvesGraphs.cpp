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
    m_document.addPointAxisWithSpecifiedIdentifier (point.posScreen (),
                                                    point.posGraph (),
                                                    identifier,
                                                    point.ordinal ());
  } else {
    m_document.addPointGraphWithSpecifiedIdentifier (curveName,
                                                     point.posScreen (),
                                                     identifier,
                                                     point.ordinal ());
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
