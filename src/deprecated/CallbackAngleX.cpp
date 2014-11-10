#include "CallbackAngleX.h"
#include <math.h>
#include <QString>

CallbackAngleX::CallbackAngleX (const ForegroundPoints &foregroundPoints,
                                double angleRadians,
                                const QString &xOrY,
                                int imageWidth,
                                int imageHeight) :
  CallbackAngleAbstractBase (imageWidth + imageHeight * tan (qAbs (angleRadians)),
                             angleRadians,
                             xOrY),
  m_foregroundPoints (foregroundPoints)
{
  // If angleRadians<0 then the histogram is aligned along the top so top left corner has bin=0
  //            xxxxxxxxx---
  //             x       x
  //              x       x
  //               xxxxxxxxx
  // If angleRadians>0 then the histogram is aligned along the bottom to bottom left corner has bin=0
  //               xxxxxxxxx
  //              x       x
  //             x       x
  //            xxxxxxxxx---
  // In either case the histogram size is imageWidth + imageHeight * tan (angle)

  ForegroundPoints::const_iterator itr;
  for (itr = m_foregroundPoints.begin (); itr != m_foregroundPoints.end (); itr++) {
    QPoint point = *itr;

    int bin;
    if (angleRadians < 0) {
      bin = point.x () - point.y() * tan (angleRadians);
    } else {
      bin = point.x () + (imageHeight - point.y()) * tan (angleRadians);
    }

    incrementHistogramBin (bin);
  }

  initialize ();
}

double CallbackAngleX::callback (double period,
                                 int gridlineCount)
{
  return correlation (period,
                      gridlineCount);
}
