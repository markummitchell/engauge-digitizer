/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COLOR_FILTER_STRATEGY_ABSTRACT_BASE_H
#define COLOR_FILTER_STRATEGY_ABSTRACT_BASE_H

#include <QRgb>
#include <QString>

class ColorFilter;
class QColor;
class QTextStream;

/// Base class for strategy pattern whose subclasses process the different color filter settings modes (one strategy per mode). The
/// strategy pattern nicely removes cyclomatic complexity from ColorFilter
class ColorFilterStrategyAbstractBase
{
 public:
  /// Single constructor.
  ColorFilterStrategyAbstractBase();

  virtual ~ColorFilterStrategyAbstractBase();

  /// Return a normalized value of 0 to 1 given input pixel
  virtual double pixelToZeroToOne  (const QColor &pixel,
                                    QRgb rgbBackground) const = 0;

  /// Return the low value normalized to 0 to 1
  virtual int zeroToOneToValue (double s) const = 0;

};

#endif // COLOR_FILTER_STRATEGY_ABSTRACT_BASE_H
