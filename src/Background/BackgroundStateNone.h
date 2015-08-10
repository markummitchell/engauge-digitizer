#ifndef BACKGROUND_STATE_NONE_H
#define BACKGROUND_STATE_NONE_H

#include "BackgroundStateAbstractBase.h"

/// Background image state for showing no image
class BackgroundStateNone : public BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateNone(BackgroundStateContext &context,
                      GraphicsScene &scene);

  virtual void begin();
  virtual void end();
  virtual void setPixmap (const QPixmap &pixmap);
  virtual void updateColorFilter (const DocumentModelColorFilter &colorFilter);

 private:
  BackgroundStateNone();
};

#endif // BACKGROUND_STATE_NONE_H
