#ifndef CALLBACK_ANGLE_Y_H
#define CALLBACK_ANGLE_Y_H

#include "CallbackAngleAbstractBase.h"

class CallbackAngleY : public CallbackAngleAbstractBase
{
 public:
  CallbackAngleY (const ForegroundPoints &foregroundPoints,
                  double angleRadians,
                  const QString &xOrY,
                  int imageWidth,
                  int imageHeight);

  double callback (double period,
                   int gridlineCount);

 private:
  CallbackAngleY ();

  const ForegroundPoints m_foregroundPoints;
};

#endif // CALLBACK_ANGLE_Y_H
