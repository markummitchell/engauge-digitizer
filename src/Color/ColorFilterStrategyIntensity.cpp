/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterStrategyIntensity.h"
#include <QColor>
#include <qmath.h>

ColorFilterStrategyIntensity::ColorFilterStrategyIntensity ()
{
}

ColorFilterStrategyIntensity::~ColorFilterStrategyIntensity ()
{
}

double ColorFilterStrategyIntensity::pixelToZeroToOne (const QColor &pixel,
                                                       QRgb /* rgbBackground */) const
{
  double distance = qSqrt (pow (double (pixel.red())  , 2) +
                           pow (double (pixel.green()), 2) +
                           pow (double (pixel.blue()) , 2));
  return distance / qSqrt (255.0 * 255.0 + 255.0 * 255.0 + 255.0 * 255.0);
}

int ColorFilterStrategyIntensity::zeroToOneToValue (double s) const
{
  return qFloor (INTENSITY_MIN + s * (INTENSITY_MAX - INTENSITY_MIN));
}
