#ifndef CALLBACK_ADD_POINTS_IN_CURVES_GRAPHS_H
#define CALLBACK_ADD_POINTS_IN_CURVES_GRAPHS_H

#include "CallbackSearchReturn.h"

class Document;
class Point;
class QString;

/// Callback that is used when iterating through a read-only CurvesGraphs to add corresponding points in Document.
class CallbackAddPointsInCurvesGraphs
{
public:
  /// Single constructor.
  CallbackAddPointsInCurvesGraphs(Document &document);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

private:
  CallbackAddPointsInCurvesGraphs ();

  Document &m_document;
};

#endif // CALLBACK_ADD_POINTS_IN_CURVES_GRAPHS_H
