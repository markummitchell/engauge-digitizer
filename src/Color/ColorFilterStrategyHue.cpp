/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterStrategyHue.h"
#include <QColor>
#include <qmath.h>

ColorFilterStrategyHue::ColorFilterStrategyHue ()
{
}

ColorFilterStrategyHue::~ColorFilterStrategyHue ()
{
}

double ColorFilterStrategyHue::pixelToZeroToOne (const QColor &pixel,
                                                 QRgb /* rgbBackground */) const
{
  double s = pixel.hueF();
  if (s < 0) {
    // Color is achromatic (r=g=b) so it has no hue
  }
  
  return s;
}

int ColorFilterStrategyHue::zeroToOneToValue (double s) const
{
  return qFloor (HUE_MIN + s * (HUE_MAX - HUE_MIN));
}
