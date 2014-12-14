#include "DlgScale.h"
#include <QPainter>

DlgScale::DlgScale(QWidget *parent) :
  QLabel (parent),
  m_filterParameter (FILTER_PARAMETER_FOREGROUND)
{
}

void DlgScale::paintEvent (QPaintEvent *event)
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

void DlgScale::paintForeground ()
{
  paintOneSpectrum (QColor (Qt::white), QColor (Qt::black));
}

void DlgScale::paintHue ()
{
  // Create one spectrum from red to green, then another from green to blue
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

void DlgScale::paintIntensity ()
{
  paintOneSpectrum (QColor (Qt::black), QColor (Qt::red));
}

void DlgScale::paintOneSpectrum (const QColor &colorStart,
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

void DlgScale::paintSaturation ()
{
  paintOneSpectrum (QColor (Qt::white), QColor (Qt::red));
}

void DlgScale::paintValue ()
{
  paintOneSpectrum (QColor (Qt::black), QColor (Qt::red));
}

void DlgScale::setFilterParameter (FilterParameter filterParameter)
{
  m_filterParameter = filterParameter;
  update ();
}
