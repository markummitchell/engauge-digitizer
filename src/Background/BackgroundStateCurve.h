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
  virtual void fitInView (GraphicsView &view);
  virtual void setCurveSelected (const Transformation &transformation,
                                 const DocumentModelGridRemoval &modelGridRemoval,
                                 const DocumentModelColorFilter &colorFilter,
                                 const QString &curveSelected);
  virtual void setPixmap (const Transformation &transformation,
                          const DocumentModelGridRemoval &modelGridRemoval,
                          const DocumentModelColorFilter &modelColorFilter,
                          const QPixmap &pixmapOriginal);
  virtual QString state () const;
  virtual void updateColorFilter (const Transformation &transformation,
                                  const DocumentModelGridRemoval &modelGridRemoval,
                                  const DocumentModelColorFilter &colorFilter);

 private:
  BackgroundStateCurve();

  void processImageFromSavedInputs(const Transformation &transformation,
                                   const DocumentModelGridRemoval &modelGridRemoval,
                                   const DocumentModelColorFilter &modelColorFilter);

  // Data saved for use by processImageFromSavedInputs
  QString m_curveSelected;
  QPixmap m_pixmapOriginal;
};

#endif // BACKGROUND_STATE_CURVE_H
