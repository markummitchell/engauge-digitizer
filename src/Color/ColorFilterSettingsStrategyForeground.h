/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COLOR_FILTER_SETTINGS_STRATEGY_FOREGROUND_H
#define COLOR_FILTER_SETTINGS_STRATEGY_FOREGROUND_H

#include "ColorFilterSettingsStrategyAbstractBase.h"

/// Leaf class for foreground strategy for ColorFilterSettings
class ColorFilterSettingsStrategyForeground : public ColorFilterSettingsStrategyAbstractBase
{
 public:
  /// Single constructor.
  ColorFilterSettingsStrategyForeground();
  ~ColorFilterSettingsStrategyForeground();

  virtual double high (const ColorFilterSettings &colorFilterSettings) const;
  virtual double low (const ColorFilterSettings &colorFilterSettings) const;
  virtual void printStream (const ColorFilterSettings &colorFilterSettings,
                            QString indentation,
                            QTextStream &str) const;
  virtual void setHigh (ColorFilterSettings &colorFilterSettings,
                        double s0To1);
  virtual void setLow (ColorFilterSettings &colorFilterSettings,
                       double s0To1);
};

#endif // COLOR_FILTER_SETTINGS_STRATEGY_FOREGROUND_H
