#ifndef VIEW_PROFILE_SCALE_H
#define VIEW_PROFILE_SCALE_H

#include "FilterParameter.h"
#include <QColor>
#include <QLabel>
#include <QRgb>

/// Linear horizontal scale, with the spectrum reflecting the active filter parameter.
class ViewProfileScale : public QLabel
{
public:
  /// Single constructor.
  explicit ViewProfileScale(QWidget *parent = 0);

  /// Draw the gradient.
  virtual void paintEvent (QPaintEvent *);

  /// Save the background color for foreground calculations.
  void setBackgroundColor (QRgb rgbBackground);

  /// Change the gradient type.
  void setFilterParameter (FilterParameter filterParameter);

private:

  void paintForeground ();
  void paintHue ();
  void paintIntensity ();
  void paintOneSpectrum (const QColor &colorStart,
                         const QColor &colorStop); // Generic processing for painting with only one spectrum
  void paintSaturation ();
  void paintValue ();

  QRgb m_rgbBackground;
  FilterParameter m_filterParameter;
};

#endif // VIEW_PROFILE_SCALE_H
