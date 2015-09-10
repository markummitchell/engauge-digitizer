#include "EngaugeAssert.h"
#include "ViewProfileScale.h"
#include <QPainter>

ViewProfileScale::ViewProfileScale(int minimumWidth,
                                   QWidget *parent) :
  QLabel (parent),
  m_colorFilterMode (COLOR_FILTER_MODE_FOREGROUND)
{
  setMinimumWidth(minimumWidth);
}

void ViewProfileScale::paintEvent (QPaintEvent *event)
{
  switch (m_colorFilterMode) {
    case COLOR_FILTER_MODE_FOREGROUND:
      paintForeground ();
      break;

    case COLOR_FILTER_MODE_HUE:
      paintHue ();
      break;

    case COLOR_FILTER_MODE_INTENSITY:
      paintIntensity ();
      break;

    case COLOR_FILTER_MODE_SATURATION:
      paintSaturation ();
      break;

    case COLOR_FILTER_MODE_VALUE:
      paintValue ();
      break;

    default:
      ENGAUGE_ASSERT (false);
  }

  QLabel::paintEvent (event);
}

void ViewProfileScale::paintForeground ()
{
  if (qGray (m_rgbBackground) < 127) {
    // Go from blackish to white
    paintOneSpectrum (QColor (m_rgbBackground), QColor (Qt::white));
  } else {
    // Go from whitish to black
    paintOneSpectrum (QColor (m_rgbBackground), QColor (Qt::black));
  }
}

void ViewProfileScale::paintHue ()
{
  // Create two spectrums:
  // 1) one spectrum from red to green
  // 2) another from green to blue
  QLinearGradient gradient (QPointF (0.0,
                                     height() / 2.0),
                            QPointF (width (),
                                     height () / 2.0));
  gradient.setColorAt (0.0000, Qt::red);
  gradient.setColorAt (0.3333, Qt::green);
  gradient.setColorAt (0.6666, Qt::blue);
  gradient.setColorAt (1.0000, Qt::red);

  QPainter painter (this);
  painter.setPen (Qt::NoPen);

  QBrush brush (gradient);

  painter.setBrush (brush);
  painter.drawRect (0,
                    0,
                    rect().width (),
                    rect().height ());
}

void ViewProfileScale::paintIntensity ()
{
  paintOneSpectrum (QColor (Qt::black), QColor (Qt::white));
}

void ViewProfileScale::paintOneSpectrum (const QColor &colorStart,
                                 const QColor &colorStop)
{
  QLinearGradient gradient (QPointF (0.0,
                                       height() / 2.0),
                              QPointF (width (),
                                       height () / 2.0));
  gradient.setColorAt (0, colorStart);
  gradient.setColorAt (1, colorStop);

  QPainter painter (this);
  painter.setPen (Qt::NoPen);

  QBrush brush (gradient);

  painter.setBrush (brush);
  painter.drawRect (0,
                    0,
                    rect().width (),
                    rect().height ());
}

void ViewProfileScale::paintSaturation ()
{
  paintOneSpectrum (QColor (Qt::white), QColor (Qt::red));
}

void ViewProfileScale::paintValue ()
{
  paintOneSpectrum (QColor (Qt::black), QColor (Qt::red));
}

void ViewProfileScale::setBackgroundColor (QRgb rgbBackground)
{
  m_rgbBackground = rgbBackground;
}

void ViewProfileScale::setColorFilterMode (ColorFilterMode colorFilterMode)
{
  m_colorFilterMode = colorFilterMode;
  update ();
}
