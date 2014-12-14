#ifndef DLG_SCALE_H
#define DLG_SCALE_H

#include "FilterParameter.h"
#include <QLabel>
#include <QRgb>

/// Linear horizontal scale, with the spectrum reflecting the active filter parameter.
class DlgScale : public QLabel
{
public:
  /// Single constructor.
  explicit DlgScale(QWidget *parent = 0);

  /// Draw the gradient.
  virtual void paintEvent (QPaintEvent *);

  /// Change the gradient type.
  void setFilterParameter (FilterParameter filterParameter);

private:

  void paintForeground ();
  void paintHue ();
  void paintIntensity ();
  void paintOneStep (const QColor &colorStart,
                     const QColor &colorStop);
  void paintSaturation ();
  void paintValue ();

  FilterParameter m_filterParameter;
};

#endif // DLG_SCALE_H
