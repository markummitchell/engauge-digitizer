#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Document.h"

extern const QString AXIS_CURVE_NAME;

CallbackRemovePointsInCurvesGraphs::CallbackRemovePointsInCurvesGraphs(Document &document) :
  m_document (document)
{
}

CallbackSearchReturn CallbackRemovePointsInCurvesGraphs::callback (const QString &curveName,
                                                                   const Point &point)
{
  if (curveName == AXIS_CURVE_NAME) {
    m_document.removePointAxis (point.identifier());
  } else {
    m_document.removePointGraph (point.identifier());
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
