/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterSettings.h"
#include "ColorFilterSettingsStrategySaturation.h"
#include <qmath.h>
#include <QTextStream>

ColorFilterSettingsStrategySaturation::ColorFilterSettingsStrategySaturation ()
{
}

ColorFilterSettingsStrategySaturation::~ColorFilterSettingsStrategySaturation ()
{
}

double ColorFilterSettingsStrategySaturation::high (const ColorFilterSettings &colorFilterSettings) const
{
  return double (colorFilterSettings.saturationHigh () - SATURATION_MIN) /
    double (SATURATION_MAX - SATURATION_MIN);
}

double ColorFilterSettingsStrategySaturation::low (const ColorFilterSettings &colorFilterSettings) const
{
  return double (colorFilterSettings.saturationLow () - SATURATION_MIN) /
    double (SATURATION_MAX - SATURATION_MIN);
}

void ColorFilterSettingsStrategySaturation::printStream (const ColorFilterSettings &colorFilterSettings,
                                                         QString indentation,
                                                         QTextStream &str) const
{
  str << indentation << "saturationLow=" << colorFilterSettings.saturationLow () << "\n";
  str << indentation << "saturationHigh=" << colorFilterSettings.saturationHigh () << "\n";
}

void ColorFilterSettingsStrategySaturation::setHigh (ColorFilterSettings &colorFilterSettings,
                                                     double s0To1)
{
  colorFilterSettings.setSaturationHigh (qFloor (SATURATION_MIN + s0To1 * (SATURATION_MAX - SATURATION_MIN)));
}

void ColorFilterSettingsStrategySaturation::setLow (ColorFilterSettings &colorFilterSettings,
                                                    double s0To1)
{
  colorFilterSettings.setSaturationLow (qFloor (SATURATION_MIN + s0To1 * (SATURATION_MAX - SATURATION_MIN)));
}
