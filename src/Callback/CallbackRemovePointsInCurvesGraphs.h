#ifndef CALLBACK_REMOVE_POINTS_IN_CURVES_GRAPHS_H
#define CALLBACK_REMOVE_POINTS_IN_CURVES_GRAPHS_H

#include "CallbackSearchReturn.h"

class Document;
class Point;
class QString;

/// Callback that is used when iterating through a read-only CurvesGraphs to remove corresponding points in Document.
class CallbackRemovePointsInCurvesGraphs
{
public:
  /// Single constructor.
  CallbackRemovePointsInCurvesGraphs(Document &document);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

private:
  CallbackRemovePointsInCurvesGraphs ();

  Document &m_document;
};

#endif // CALLBACK_REMOVE_POINTS_IN_CURVES_GRAPHS_H
