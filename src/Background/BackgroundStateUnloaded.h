#ifndef BACKGROUND_STATE_UNLOADED_H
#define BACKGROUND_STATE_UNLOADED_H

#include "BackgroundStateAbstractBase.h"

/// Background image state for interval between startup and loading of the image
class BackgroundStateUnloaded : public BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateUnloaded(BackgroundStateContext &context,
                          GraphicsScene &scene);

  virtual void begin();
  virtual void end();
  virtual void setPixmap (const QPixmap &pixmap);
  virtual void updateColorFilter (const DocumentModelColorFilter &colorFilter);

 private:
  BackgroundStateUnloaded();
};

#endif // BACKGROUND_STATE_UNLOADED_H
