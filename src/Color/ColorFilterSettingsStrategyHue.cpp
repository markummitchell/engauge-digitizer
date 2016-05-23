/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterSettings.h"
#include "ColorFilterSettingsStrategyHue.h"
#include <QTextStream>

ColorFilterSettingsStrategyHue::ColorFilterSettingsStrategyHue ()
{
}

ColorFilterSettingsStrategyHue::~ColorFilterSettingsStrategyHue ()
{
}

double ColorFilterSettingsStrategyHue::high (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.hueHigh () - HUE_MIN) /
    (double) (HUE_MAX - HUE_MIN); 
}

double ColorFilterSettingsStrategyHue::low (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.hueLow () - HUE_MIN) /
    (double) (HUE_MAX - HUE_MIN);
}

void ColorFilterSettingsStrategyHue::printStream (const ColorFilterSettings &colorFilterSettings,
                                                  QString indentation,
                                                  QTextStream &str) const
{
  str << indentation << "hueLow=" << colorFilterSettings.intensityLow () << "\n";
  str << indentation << "hueHigh=" << colorFilterSettings.intensityHigh () << "\n";
}

void ColorFilterSettingsStrategyHue::setHigh (ColorFilterSettings &colorFilterSettings,
                                              double s0To1)
{
  colorFilterSettings.setHueHigh (HUE_MIN + s0To1 * (HUE_MAX - HUE_MIN));  
}

void ColorFilterSettingsStrategyHue::setLow (ColorFilterSettings &colorFilterSettings,
                                             double s0To1)
{
  colorFilterSettings.setHueLow (HUE_MIN + s0To1 * (HUE_MAX - HUE_MIN));
}
