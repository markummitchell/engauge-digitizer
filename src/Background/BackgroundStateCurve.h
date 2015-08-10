#ifndef BACKGROUND_STATE_CURVE_H
#define BACKGROUND_STATE_CURVE_H

#include "BackgroundStateAbstractBase.h"

/// Background image state for showing filter image from current curve
class BackgroundStateCurve : public BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateCurve(BackgroundStateContext &context,
                       GraphicsScene &scene);

  virtual void begin();
  virtual void end();
  virtual void setPixmap (const QPixmap &pixmap);
  virtual void updateColorFilter (const DocumentModelColorFilter &colorFilter);

 private:
  BackgroundStateCurve();

};

#endif // BACKGROUND_STATE_CURVE_H
