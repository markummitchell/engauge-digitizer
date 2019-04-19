/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilter.h"
#include "ColorFilterSettings.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <qmath.h>
#include <QPainter>
#include <QPixmap>
#include "ViewSegmentFilter.h"

const QColor COLOR_FOR_BRUSH_DISABLED (Qt::gray);

ViewSegmentFilter::ViewSegmentFilter(QWidget *parent) :
  QLabel (parent),
  m_filterIsDefined (false),
  m_rgbBackground (QColor (Qt::white)),
  m_enabled (true)
{
  // Note the size is set externally by the layout engine
}

QColor ViewSegmentFilter::colorFromSetting (ColorFilterMode coloFilterMode,
                                            int foreground,
                                            int hue,
                                            int intensity,
                                            int saturation,
                                            int value) const
{
  int r = 0, g = 0, b = 0;

  switch (coloFilterMode)
  {
    case COLOR_FILTER_MODE_FOREGROUND:
      {
        double s = double (foreground - FOREGROUND_MIN) / double (FOREGROUND_MAX - FOREGROUND_MIN);
        if (qGray (m_rgbBackground.rgb ()) < 127) {
          // Go from blackish to white
          r = qFloor (s * 255);
          g = qFloor (s * 255);
          b = qFloor (s * 255);
        } else {
          // Go from whitish to black
          r = qFloor ((1.0 - s) * 255);
          g = qFloor ((1.0 - s) * 255);
          b = qFloor ((1.0 - s) * 255);
        }
      }
      break;

    case COLOR_FILTER_MODE_HUE:
      {
        // red-green and green-blue like ViewProfileScale::paintHue

        int HUE_THRESHOLD_LOW = qFloor (0.666 * HUE_MIN + 0.333 * HUE_MAX);
        int HUE_THRESHOLD_HIGH = qFloor (0.333 * HUE_MIN + 0.666 * HUE_MAX);

        if (hue < HUE_THRESHOLD_LOW) {
          // 0-0.333 is red-green
          double s = double (hue - HUE_MIN) / double (HUE_THRESHOLD_LOW - HUE_MIN);
          r = qFloor ((1.0 - s) * 255);
          g = qFloor (s * 255);
        } else if (hue < HUE_THRESHOLD_HIGH) {
          // 0.333-0.666 is green-blue
          double s = double (hue - HUE_THRESHOLD_LOW) / double (HUE_THRESHOLD_HIGH - HUE_THRESHOLD_LOW);
          g = qFloor ((1.0 - s) * 255);
          b = qFloor (s * 255);
        } else {
          // 0.666-1 is blue-red
          double s = double (hue - HUE_THRESHOLD_HIGH) / double (HUE_MAX - HUE_THRESHOLD_HIGH);
          b = qFloor ((1.0 - s) * 255);
          r = qFloor (s * 255);
        }
      }
      break;

    case COLOR_FILTER_MODE_INTENSITY:
      {
        // black-white like ViewProfileScale::paintIntensity

        double s = double (intensity - INTENSITY_MIN) / double (INTENSITY_MAX - INTENSITY_MIN);
        r = qFloor (s * 255);
        g = qFloor (s * 255);
        b = qFloor (s * 255);
      }
      break;

    case COLOR_FILTER_MODE_SATURATION:
      {
        // white-red like ViewProfileScale::paintSaturation

        double s = double (saturation - SATURATION_MIN) / double (SATURATION_MAX - SATURATION_MIN);
        r = qFloor (255);
        g = qFloor ((1.0 - s) * 255);
        b = qFloor ((1.0 - s) * 255);
      }
      break;

    case COLOR_FILTER_MODE_VALUE:
      {
        // black-red like ViewProfileScale::paintValue

        double s = double (value - VALUE_MIN) / double (VALUE_MAX - VALUE_MIN);
        r = qFloor (s * 255);
        g = qFloor (0);
        b = qFloor (0);
      }
      break;

    default:
      ENGAUGE_ASSERT (false);
  }

  if (!m_enabled) {

    // Change to gray scale
    int rgbAverage = (r + g + b) / 3;
    r = rgbAverage;
    g = rgbAverage;
    b = rgbAverage;
  }

  return QColor (r, g, b);
}

QColor ViewSegmentFilter::colorHigh () const
{
  if (m_enabled) {
    return colorFromSetting (m_colorFilterSettings.colorFilterMode (),
                             m_colorFilterSettings.foregroundHigh (),
                             m_colorFilterSettings.hueHigh (),
                             m_colorFilterSettings.intensityHigh(),
                             m_colorFilterSettings.saturationHigh(),
                             m_colorFilterSettings.valueHigh());
  } else {
    return QColor (COLOR_FOR_BRUSH_DISABLED);
  }
}

QColor ViewSegmentFilter::colorLow () const
{
  if (m_enabled) {
    return colorFromSetting (m_colorFilterSettings.colorFilterMode (),
                             m_colorFilterSettings.foregroundLow (),
                             m_colorFilterSettings.hueLow (),
                             m_colorFilterSettings.intensityLow(),
                             m_colorFilterSettings.saturationLow(),
                             m_colorFilterSettings.valueLow());
  } else {
    return QColor (COLOR_FOR_BRUSH_DISABLED);
  }
}

void ViewSegmentFilter::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);

  if (m_filterIsDefined) {

    // Start and end points are midway up on both sides
    QLinearGradient gradient (0, height()/2, width(), height()/2);

    // One color at either end
    gradient.setColorAt (0.0, colorLow ());
    gradient.setColorAt (1.0, colorHigh ());
    painter.setBrush (gradient);

    // No border, which is consistent with ViewPointStyle and cleaner
    painter.setPen (Qt::NoPen);

    painter.drawRect (0, 0, width(), height());

  } else {

    painter.fillRect (0, 0, width (), height (), QBrush (COLOR_FOR_BRUSH_DISABLED));

  }
}

void ViewSegmentFilter::setColorFilterSettings (const ColorFilterSettings &colorFilterSettings,
                                                const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ViewSegmentFilter::setColorFilterSettings";

  m_colorFilterSettings = colorFilterSettings;
  m_filterIsDefined = true;

  // Compute background color
  ColorFilter filter;
  QImage img = pixmap.toImage();
  m_rgbBackground = filter.marginColor(&img);

  // Force a redraw
  update();
}

void ViewSegmentFilter::setEnabled (bool enabled)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ViewSegmentFilter::setEnabled"
                              << " enabled=" << (enabled ? "true" : "false");

  m_enabled = enabled;

  // Force a redraw
  update();
}

void ViewSegmentFilter::unsetColorFilterSettings ()
{
  m_filterIsDefined = false;

  // Force a redraw
  update();
}
