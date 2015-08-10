#ifndef BACKGROUND_STATE_CURVE_H
#define BACKGROUND_STATE_CURVE_H

#include "BackgroundStateAbstractBase.h"
#include "DocumentModelColorFilter.h"

/// Background image state for showing filter image from current curve
class BackgroundStateCurve : public BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateCurve(BackgroundStateContext &context,
                       GraphicsScene &scene);

  virtual void begin();
  virtual void end();
  virtual void fitInView (GraphicsView &view);
  virtual void setColorFilter (const DocumentModelColorFilter &colorFilter);
  virtual void setCurveSelected (const QString &curveSelected);
  virtual void setPixmap (const QPixmap &pixmapOriginal);

 private:
  BackgroundStateCurve();

  void processImageFromSavedInputs();

  // Data saved for use by processImageFromSavedInputs
  QString m_curveSelected;
  QPixmap m_pixmapOriginal;
  DocumentModelColorFilter m_modelColorFilter;
};

#endif // BACKGROUND_STATE_CURVE_H
