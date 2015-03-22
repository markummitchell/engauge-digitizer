#ifndef CALLBACK_POINT_ORDINAL_H
#define CALLBACK_POINT_ORDINAL_H

#include "CallbackSearchReturn.h"
#include "LineStyle.h"
#include <QPointF>
#include <QString>

class Point;

/// Callback for computing the ordinal for a specified point, as a function of the LineStyle and curve geometry
class CallbackPointOrdinal
{
public:
  /// Single constructor
  CallbackPointOrdinal(const LineStyle &lineStyle,
                       const QString &curveName,
                       const QPointF &posScreen);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Computed ordinal
  double ordinal () const;

private:
  CallbackPointOrdinal();

  const LineStyle m_lineStyle;
  const QString m_curveName;  
  const QPointF m_posScreen;
};

#endif // CALLBACK_POINT_ORDINAL_H
