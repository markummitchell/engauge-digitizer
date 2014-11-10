#include "CallbackAngleY.h"
#include <math.h>
#include <QString>

CallbackAngleY::CallbackAngleY (const ForegroundPoints &foregroundPoints,
                                double angleRadians,
                                const QString &xOrY,
                                int imageWidth,
                                int imageHeight) :
  CallbackAngleAbstractBase (imageHeight + imageWidth * tan (qAbs (angleRadians)),
                             angleRadians,
                             xOrY),
  m_foregroundPoints (foregroundPoints)
{
  // If angleRadians<0 then the histogram is aligned along the right so top right corner has bin=0
  //                    x
  //                  x x
  //                x   x
  //              x     x
  //            x       x
  //            x     x |
  //            x   x   |
  //            x x     |
  //            x       |
  // If angleRadians>0 then the histogram is aligned along the left so top left corner has bin=0
  //            x
  //            x x
  //            x   x
  //            x     x
  //            x       x
  //            | x     x
  //            |   x   x
  //            |     x x
  //            |       x
  // In either case the histogram size is imageHeight + width * tan (angle)

  ForegroundPoints::const_iterator itr;
  for (itr = m_foregroundPoints.begin (); itr != m_foregroundPoints.end (); itr++) {
    QPoint point = *itr;

    int bin;
    if (angleRadians < 0) {
      bin = point.y () - point.x() * tan (angleRadians);
    } else {
      bin = point.y () + point.x() * tan (angleRadians);
    }

    incrementHistogramBin (bin);
  }

  initialize ();
}

double CallbackAngleY::callback (double period,
                                 int gridlineCount)
{
  return correlation (period,
                      gridlineCount);
}
