#ifndef VIEW_PROFILE_SCALE_H
#define VIEW_PROFILE_SCALE_H

#include "ColorFilterMode.h"
#include <QColor>
#include <QLabel>
#include <QRgb>

/// Linear horizontal scale, with the spectrum reflecting the active filter parameter.
class ViewProfileScale : public QLabel
{
public:
  /// Single constructor.
  explicit ViewProfileScale(int minimumWidth,
                            QWidget *parent = 0);

  /// Draw the gradient.
  virtual void paintEvent (QPaintEvent *);

  /// Save the background color for foreground calculations.
  void setBackgroundColor (QRgb rgbBackground);

  /// Change the gradient type.
  void setColorFilterMode (ColorFilterMode colorFilterMode);

private:

  void paintForeground ();
  void paintHue ();
  void paintIntensity ();
  void paintOneSpectrum (const QColor &colorStart,
                         const QColor &colorStop); // Generic processing for painting with only one spectrum
  void paintSaturation ();
  void paintValue ();

  QRgb m_rgbBackground;
  ColorFilterMode m_colorFilterMode;
};

#endif // VIEW_PROFILE_SCALE_H
