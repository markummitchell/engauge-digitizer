/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterStrategyValue.h"
#include <QColor>
#include <qmath.h>

ColorFilterStrategyValue::ColorFilterStrategyValue ()
{
}

ColorFilterStrategyValue::~ColorFilterStrategyValue ()
{
}

double ColorFilterStrategyValue::pixelToZeroToOne (const QColor &pixel,
                                                   QRgb /* rgbBackground */) const
{
  return pixel.valueF();
}

int ColorFilterStrategyValue::zeroToOneToValue (double s) const
{
  return VALUE_MIN + s * (VALUE_MAX - VALUE_MIN);
}
