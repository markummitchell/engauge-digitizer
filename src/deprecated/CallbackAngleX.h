#ifndef CALLBACK_ANGLE_X_H
#define CALLBACK_ANGLE_X_H

#include "CallbackAngleAbstractBase.h"

class CallbackAngleX : public CallbackAngleAbstractBase
{
 public:
  CallbackAngleX (const ForegroundPoints &foregroundPoints,
                  double angleRadians,
                  const QString &xOrY,
                  int imageWidth,
                  int imageHeight);

  double callback (double period,
                   int gridlineCount);

 private:
  CallbackAngleX ();

  const ForegroundPoints m_foregroundPoints;
};

#endif // CALLBACK_ANGLE_X_H
