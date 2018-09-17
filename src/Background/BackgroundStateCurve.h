/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
  virtual void setCurveSelected (bool isGnuplot,
                                 const Transformation &transformation,
                                 const DocumentModelGridRemoval &modelGridRemoval,
                                 const DocumentModelColorFilter &colorFilter,
                                 const QString &curveSelected);
  virtual void setPixmap (bool isGnuplot,
                          const Transformation &transformation,
                          const DocumentModelGridRemoval &modelGridRemoval,
                          const DocumentModelColorFilter &modelColorFilter,
                          const QPixmap &pixmapOriginal,
                          const QString &curveSelected);
  virtual QString state () const;
  virtual void updateColorFilter (bool isGnuplot,
                                  const Transformation &transformation,
                                  const DocumentModelGridRemoval &modelGridRemoval,
                                  const DocumentModelColorFilter &colorFilter,
                                  const QString &curveSelected);

 private:
  BackgroundStateCurve();

  void processImageFromSavedInputs(bool isGnuplot,
                                   const Transformation &transformation,
                                   const DocumentModelGridRemoval &modelGridRemoval,
                                   const DocumentModelColorFilter &modelColorFilter,
                                   const QString &curveSelected);

  // Data saved for use by processImageFromSavedInputs
  QPixmap m_pixmapOriginal;
};

#endif // BACKGROUND_STATE_CURVE_H
