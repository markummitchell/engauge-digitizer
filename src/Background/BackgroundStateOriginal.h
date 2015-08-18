#ifndef BACKGROUND_STATE_ORIGINAL_H
#define BACKGROUND_STATE_ORIGINAL_H

#include "BackgroundStateAbstractBase.h"

/// Background image state for showing original (=unfiltered) image
class BackgroundStateOriginal : public BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateOriginal(BackgroundStateContext &context,
                          GraphicsScene &scene);

  virtual void begin();
  virtual void end();
  virtual void fitInView (GraphicsView &view);
  virtual void setCurveSelected (const DocumentModelColorFilter &colorFilter,
                                 const QString &curveSelected);
  virtual void setPixmap (const DocumentModelColorFilter &modelColorFilter,
                          const QPixmap &pixmap);
  virtual QString state () const;
  virtual void updateColorFilter (const DocumentModelColorFilter &colorFilter);

 private:
  BackgroundStateOriginal();

};

#endif // BACKGROUND_STATE_ORIGINAL_H
