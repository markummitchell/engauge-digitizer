/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COLOR_FILTER_SETTINGS_STRATEGY_ABSTRACT_BASE_H
#define COLOR_FILTER_SETTINGS_STRATEGY_ABSTRACT_BASE_H

#include <QString>

class ColorFilterSettings;
class QTextStream;

/// Base class for strategy pattern whose subclasses process the different color filter settings modes (one strategy per mode). The
/// strategy pattern nicely removes cyclomatic complexity from ColorFilterSettings
class ColorFilterSettingsStrategyAbstractBase
{
 public:
  /// Single constructor.
  ColorFilterSettingsStrategyAbstractBase();

  virtual ~ColorFilterSettingsStrategyAbstractBase();

  /// Return the high value normalized to 0 to 1
  virtual double high (const ColorFilterSettings &colorFilterSettings) const = 0;

  /// Return the low value normalized to 0 to 1
  virtual double low (const ColorFilterSettings &colorFilterSettings) const = 0;

  /// Print the low and high values
  virtual void printStream (const ColorFilterSettings &colorFilterSettings,
                            QString indentation,
                            QTextStream &str) const = 0;

  /// Set the high value given the normalized value
  virtual void setHigh (ColorFilterSettings &colorFilterSettings,
                        double s0To1) = 0;

  /// Set the low value given the normalized value
  virtual void setLow (ColorFilterSettings &colorFilterSettings,
                       double s0To1) = 0;
};

#endif // COLOR_FILTER_SETTINGS_STRATEGY_ABSTRACT_BASE_H
