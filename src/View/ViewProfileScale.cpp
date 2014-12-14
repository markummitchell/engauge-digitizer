#include "ViewProfileScale.h"
#include <QPainter>

ViewProfileScale::ViewProfileScale(QWidget *parent) :
  QLabel (parent),
  m_filterParameter (FILTER_PARAMETER_FOREGROUND)
{
}

void ViewProfileScale::paintEvent (QPaintEvent *event)
{
  switch (m_filterParameter) {
    case FILTER_PARAMETER_FOREGROUND:
      paintForeground ();
      break;

    case FILTER_PARAMETER_HUE:
      paintHue ();
      break;

    case FILTER_PARAMETER_INTENSITY:
      paintIntensity ();
      break;

    case FILTER_PARAMETER_SATURATION:
      paintSaturation ();
      break;

    case FILTER_PARAMETER_VALUE:
      paintValue ();
      break;

    default:
      Q_ASSERT (false);
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
  QLinearGradient gradientRG (QPointF (0.0,
                                       height() / 2.0),
                              QPointF (width () / 2.0,
                                       height () / 2.0));
  QLinearGradient gradientGB (QPointF (width() / 2.0,
                                       height () / 2.0),
                              QPointF (width (),
                                       height () / 2.0));
  gradientRG.setColorAt (0, Qt::red);
  gradientRG.setColorAt (1, Qt::green);
  gradientGB.setColorAt (0, Qt::green);
  gradientGB.setColorAt (1, Qt::blue);

  QPainter painter (this);
  painter.setPen (Qt::NoPen);

  QBrush brushRG (gradientRG);
  QBrush brushGB (gradientGB);

  painter.setBrush (brushRG);
  painter.drawRect (0,
                    0,
                    rect().width () / 2.0,
                    rect().height ());
  painter.setBrush (brushGB);
  painter.drawRect (rect().width() / 2.0,
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

void ViewProfileScale::setFilterParameter (FilterParameter filterParameter)
{
  m_filterParameter = filterParameter;
  update ();
}
