/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterStrategySaturation.h"
#include <QColor>
#include <qmath.h>

ColorFilterStrategySaturation::ColorFilterStrategySaturation ()
{
}

ColorFilterStrategySaturation::~ColorFilterStrategySaturation ()
{
}

double ColorFilterStrategySaturation::pixelToZeroToOne (const QColor &pixel,
                                                        QRgb /* rgbBackground */) const
{
  return pixel.saturationF();
}

int ColorFilterStrategySaturation::zeroToOneToValue (double s) const
{
  return qFloor (SATURATION_MIN + s * (SATURATION_MAX - SATURATION_MIN));
}
