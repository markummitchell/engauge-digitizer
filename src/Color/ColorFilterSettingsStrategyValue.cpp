/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilterSettings.h"
#include "ColorFilterSettingsStrategyValue.h"
#include <QTextStream>

ColorFilterSettingsStrategyValue::ColorFilterSettingsStrategyValue ()
{
}

ColorFilterSettingsStrategyValue::~ColorFilterSettingsStrategyValue ()
{
}

double ColorFilterSettingsStrategyValue::high (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.valueHigh () - VALUE_MIN) /
    (double) (VALUE_MAX - VALUE_MIN); 
}

double ColorFilterSettingsStrategyValue::low (const ColorFilterSettings &colorFilterSettings) const
{
  return (double) (colorFilterSettings.valueLow () - VALUE_MIN) /
    (double) (VALUE_MAX - VALUE_MIN);
}

void ColorFilterSettingsStrategyValue::printStream (const ColorFilterSettings &colorFilterSettings,
                                                    QString indentation,
                                                    QTextStream &str) const
{
  str << indentation << "valueLow=" << colorFilterSettings.valueLow () << "\n";
  str << indentation << "valueHigh=" << colorFilterSettings.valueHigh () << "\n";
}

void ColorFilterSettingsStrategyValue::setHigh (ColorFilterSettings &colorFilterSettings,
                                                double s0To1)
{
  colorFilterSettings.setValueHigh (VALUE_MIN + s0To1 * (VALUE_MAX - VALUE_MIN));  
}

void ColorFilterSettingsStrategyValue::setLow (ColorFilterSettings &colorFilterSettings,
                                               double s0To1)
{
  colorFilterSettings.setValueLow (VALUE_MIN + s0To1 * (VALUE_MAX - VALUE_MIN));
}
