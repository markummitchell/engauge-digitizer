/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterSettings.h"
#include "ColorFilterSettingsStrategyForeground.h"
#include <QTextStream>

ColorFilterSettingsStrategyForeground::ColorFilterSettingsStrategyForeground ()
{
}

ColorFilterSettingsStrategyForeground::~ColorFilterSettingsStrategyForeground ()
{
}

double ColorFilterSettingsStrategyForeground::high (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.foregroundHigh () - FOREGROUND_MIN) /
    (double) (FOREGROUND_MAX - FOREGROUND_MIN); 
}

double ColorFilterSettingsStrategyForeground::low (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.foregroundLow () - FOREGROUND_MIN) /
    (double) (FOREGROUND_MAX - FOREGROUND_MIN);
}

void ColorFilterSettingsStrategyForeground::printStream (const ColorFilterSettings &colorFilterSettings,
                                                         QString indentation,
                                                         QTextStream &str) const
{
  str << indentation << "foregroundLow=" << colorFilterSettings.intensityLow () << "\n";
  str << indentation << "foregroundHigh=" << colorFilterSettings.intensityHigh () << "\n";
}

void ColorFilterSettingsStrategyForeground::setHigh (ColorFilterSettings &colorFilterSettings,
                                                     double s0To1)
{
  colorFilterSettings.setForegroundHigh (FOREGROUND_MIN + s0To1 * (FOREGROUND_MAX - FOREGROUND_MIN));  
}

void ColorFilterSettingsStrategyForeground::setLow (ColorFilterSettings &colorFilterSettings,
                                                    double s0To1)
{
  colorFilterSettings.setForegroundLow (FOREGROUND_MIN + s0To1 * (FOREGROUND_MAX - FOREGROUND_MIN));
}
