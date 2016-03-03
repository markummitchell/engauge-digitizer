/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_COLOR_FILTER_H
#define DOCUMENT_MODEL_COLOR_FILTER_H

#include "ColorFilterSettings.h"
#include "DocumentModelAbstractBase.h"
#include <QHash>

// Lookup-table by curve name
typedef QHash<QString, ColorFilterSettings> ColorFilterSettingsList;

class CoordSystem;
class QTextStream;

/// Model for DlgSettingsColorFilter and CmdSettingsColorFilter.
class DocumentModelColorFilter : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelColorFilter();

  /// Copy constructor.
  DocumentModelColorFilter(const DocumentModelColorFilter &other);

  /// Initial constructor from CoordSystem.
  DocumentModelColorFilter(const CoordSystem &coordSystem);

  /// Assignment constructor.
  DocumentModelColorFilter &operator=(const DocumentModelColorFilter &other);

  /// Get method for filter mode.
  ColorFilterMode colorFilterMode(const QString &curveName) const;

  /// Get method for copying one color filter. Cannot return just a reference or else there is a warning about returning reference to temporary
  const ColorFilterSettings colorFilterSettings (const QString &curveName) const;

  /// Get method for copying all color filters in one step.
  const ColorFilterSettingsList &colorFilterSettingsList () const;

  /// Get method for foreground higher bound.
  int foregroundHigh (const QString &curveName) const;

  /// Get method for foreground lower bound.
  int foregroundLow (const QString &curveName) const;

  /// High value of foreground, hue, intensity, saturation or value according to current filter mode.
  /// normalized to 0 to 1.
  double high (const QString &curveName) const;

  /// Get method for hue higher bound.
  int hueHigh (const QString &curveName) const;

  /// Get method for hue lower bound.
  int hueLow (const QString &curveName) const;

  /// Get method for intensity higher bound.
  int intensityHigh (const QString &curveName) const;

  /// Get method for intensity lower bound.
  int intensityLow (const QString &curveName) const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Low value of foreground, hue, intensity, saturation or value according to current filter mode
  /// normalized to 0 to 1.
  double low (const QString &curveName) const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Get method for saturation higher bound.
  int saturationHigh (const QString &curveName) const;

  /// Get method for saturation lower bound.
  int saturationLow (const QString &curveName) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for filter mode.
  void setColorFilterMode(const QString &curveName,
                          ColorFilterMode colorFilterMode);

  /// Set method for foreground higher bound.
  void setForegroundHigh (const QString &curveName,
                          int foregroundHigh);

  /// Set method for foreground lower bound.
  void setForegroundLow (const QString &curveName,
                         int foregroundLow);

  /// Set the high value for the current filter mode.
  void setHigh (const QString &curveName,
                double s0To1);

  /// Set method for hue higher bound.
  void setHueHigh (const QString &curveName,
                   int hueHigh);

  /// Set method for hue lower bound.
  void setHueLow (const QString &curveName,
                  int hueLow);

  /// Set method for intensity higher bound.
  void setIntensityHigh (const QString &curveName,
                         int intensityHigh);

  /// Set method for intensity lower bound.
  void setIntensityLow (const QString &curveName,
                        int intensityLow);

  /// Set the low value for the current filter mode.
  void setLow (const QString &curveName,
               double s0To1);

  /// Set method for saturation high.
  void setSaturationHigh (const QString &curveName,
                          int saturationHigh);

  /// Set method for saturation low.
  void setSaturationLow (const QString &curveName,
                         int saturationLow);

  /// Set method for value high.
  void setValueHigh (const QString &curveName,
                     int valueHigh);

  /// Set method for value low.
  void setValueLow (const QString &curveName,
                    int valueLow);

  /// Get method for value high.
  int valueHigh (const QString &curveName) const;

  /// Get method for value low.
  int valueLow (const QString &curveName) const;

private:

  ColorFilterSettingsList m_colorFilterSettingsList;
};

#endif // DOCUMENT_MODEL_COLOR_FILTER_H
