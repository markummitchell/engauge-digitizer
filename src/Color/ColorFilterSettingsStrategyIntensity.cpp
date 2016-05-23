/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterSettings.h"
#include "ColorFilterSettingsStrategyIntensity.h"
#include <QTextStream>

ColorFilterSettingsStrategyIntensity::ColorFilterSettingsStrategyIntensity ()
{
}

ColorFilterSettingsStrategyIntensity::~ColorFilterSettingsStrategyIntensity ()
{
}

double ColorFilterSettingsStrategyIntensity::high (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.intensityHigh () - INTENSITY_MIN) /
    (double) (INTENSITY_MAX - INTENSITY_MIN); 
}

double ColorFilterSettingsStrategyIntensity::low (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.intensityLow () - INTENSITY_MIN) /
    (double) (INTENSITY_MAX - INTENSITY_MIN);
}

void ColorFilterSettingsStrategyIntensity::printStream (const ColorFilterSettings &colorFilterSettings,
                                                        QString indentation,
                                                        QTextStream &str) const
{
  str << indentation << "intensityLow=" << colorFilterSettings.intensityLow () << "\n";
  str << indentation << "intensityHigh=" << colorFilterSettings.intensityHigh () << "\n";
}

void ColorFilterSettingsStrategyIntensity::setHigh (ColorFilterSettings &colorFilterSettings,
                                                    double s0To1)
{
  colorFilterSettings.setIntensityHigh (INTENSITY_MIN + s0To1 * (INTENSITY_MAX - INTENSITY_MIN));  
}

void ColorFilterSettingsStrategyIntensity::setLow (ColorFilterSettings &colorFilterSettings,
                                                   double s0To1)
{
  colorFilterSettings.setIntensityLow (INTENSITY_MIN + s0To1 * (INTENSITY_MAX - INTENSITY_MIN));
}
