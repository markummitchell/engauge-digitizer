/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterStrategyForeground.h"
#include <QColor>
#include <qmath.h>

ColorFilterStrategyForeground::ColorFilterStrategyForeground ()
{
}

ColorFilterStrategyForeground::~ColorFilterStrategyForeground ()
{
}

double ColorFilterStrategyForeground::pixelToZeroToOne (const QColor &pixel,
                                                        QRgb rgbBackground) const
{
  double distance = qSqrt (pow ((double) pixel.red()   - qRed   (rgbBackground), 2) +
                           pow ((double) pixel.green() - qGreen (rgbBackground), 2) +
                           pow ((double) pixel.blue()  - qBlue  (rgbBackground), 2));
  return distance / qSqrt (255.0 * 255.0 + 255.0 * 255.0 + 255.0 * 255.0);
}

int ColorFilterStrategyForeground::zeroToOneToValue (double s) const
{
  return FOREGROUND_MIN + s * (FOREGROUND_MAX - FOREGROUND_MIN);
}
