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
  virtual void fitInView (GraphicsView &view);
  virtual void setCurveSelected (const Transformation &transformation,
                                 const DocumentModelGridRemoval &modelGridRemoval,
                                 const DocumentModelColorFilter &colorFilter,
                                 const QString &curveSelected);
  virtual void setPixmap (const Transformation &transformation,
                          const DocumentModelGridRemoval &modelGridRemoval,
                          const DocumentModelColorFilter &modelColorFilter,
                          const QPixmap &pixmap);
  virtual QString state () const;
  virtual void updateColorFilter (const Transformation &transformation,
                                  const DocumentModelGridRemoval &modelGridRemoval,
                                  const DocumentModelColorFilter &colorFilter);

 private:
  BackgroundStateUnloaded();
};

#endif // BACKGROUND_STATE_UNLOADED_H
