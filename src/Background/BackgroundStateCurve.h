#ifndef BACKGROUND_STATE_CURVE_H
#define BACKGROUND_STATE_CURVE_H

#include "BackgroundStateAbstractBase.h"

/// Background image state for showing filter image from current curve
class BackgroundStateCurve : public BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateCurve(BackgroundStateContext &context);

  virtual void begin();
  virtual void end();

 private:
  BackgroundStateCurve();

};

#endif // BACKGROUND_STATE_CURVE_H
