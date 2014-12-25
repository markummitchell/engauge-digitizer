#ifndef CALLBACK_CHECK_ADD_POINT_AXIS_H
#define CALLBACK_CHECK_ADD_POINT_AXIS_H

#include "CallbackAxisPointsAbstract.h"
#include <QPointF>
#include <QString>

class DocumentModelCoords;
class Point;

/// Callback for sanity checking the screen and graph coordinates of an axis point, before it is added to the axes curve.
class CallbackCheckAddPointAxis : public CallbackAxisPointsAbstract
{
public:
  /// Single constructor.
  CallbackCheckAddPointAxis(const DocumentModelCoords &modelCoords,
                            const QPointF &posScreen,
                            const QPointF &posGraph);

  /// True if an error occurred during iteration.
  bool isError () const;

  /// Error message that explains the problem indicated by isError.
  QString errorMessage () const;

private:
  CallbackCheckAddPointAxis();
};

#endif // CALLBACK_CHECK_ADD_POINT_AXIS_H
