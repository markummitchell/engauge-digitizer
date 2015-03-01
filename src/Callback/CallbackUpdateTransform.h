#ifndef CALLBACK_UPDATE_TRANSFORM_H
#define CALLBACK_UPDATE_TRANSFORM_H

#include "CallbackAxisPointsAbstract.h"
#include <QPointF>
#include <QString>
#include <QTransform>

class Point;

/// Callback for collecting axis points and then calculating the current transform from those axis points.
/// Sanity checking of the axis points was applied earlier when the axis points were added/edited.
class CallbackUpdateTransform : public CallbackAxisPointsAbstract
{
public:
  /// Single constructor.
  CallbackUpdateTransform(const DocumentModelCoords &modelCoords);

  /// Constructor from three graph/screen position pairs.
  CallbackUpdateTransform(const DocumentModelCoords &modelCoords,
                          const QPointF &posScreen0,
                          const QPointF &posScreen1,
                          const QPointF &posScreen2,
                          const QPointF &posGraph0,
                          const QPointF &posGraph1,
                          const QPointF &posGraph2);

  /// Returns screen-to-graph transform after transformIsDefined has already indicated success.
  QTransform transform ();

  /// True if enough Points were available to create a Transformation. Except for the node count, all other
  /// failure modes are caught externally so user gets immediate feedback as soon as bad axis point data appears
  bool transformIsDefined () const;

private:
  CallbackUpdateTransform();

};

#endif // CALLBACK_UPDATE_TRANSFORM_H
