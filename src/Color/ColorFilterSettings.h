#ifndef COLOR_FILTER_SETTINGS_H
#define COLOR_FILTER_SETTINGS_H

#include "ColorFilterMode.h"

class QTextStream;
class QXmlStreamReader;
class QXmlStreamWriter;

/// Color filter parameters for one curve. For a class, this is handled the same as LineStyle and PointStyle
class ColorFilterSettings
{
public:
  /// Default constructor only for use when this class is being stored by a container that requires the default constructor.
  ColorFilterSettings ();

  /// Normal constructor. The style type and radius are determined by the currently selected Curve
  ColorFilterSettings (ColorFilterMode colorFilterMode,
                       int intensityLow,
                       int intensityHigh,
                       int foregroundLow,
                       int foregroundHigh,
                       int hueLow,
                       int hueHigh,
                       int saturationLow,
                       int saturationHigh,
                       int valueLow,
                       int valueHigh);

  /// Copy constructor.
  ColorFilterSettings (const ColorFilterSettings &other);
  
  /// Constructor when loading from serialized xml
  ColorFilterSettings (QXmlStreamReader &reader);

  /// Assignment operator.
  ColorFilterSettings &operator= (const ColorFilterSettings &other);

  /// Get method for filter mode.
  ColorFilterMode colorFilterMode() const;

  /// Initial default for any Curve.
  static ColorFilterSettings defaultFilter ();

  /// Get method for foreground higher bound.
  int foregroundHigh () const;

  /// Get method for foreground lower bound.
  int foregroundLow () const;

  /// High value of foreground, hue, intensity, saturation or value according to current filter mode,
  /// normalized to 0 to 1.
  double high () const;

  /// Get method for hue higher bound.
  int hueHigh () const;

  /// Get method for hue lower bound.
  int hueLow () const;

  /// Get method for intensity higher bound.
  int intensityHigh () const;

  /// Get method for intensity lower bound.
  int intensityLow () const;

  /// Load curve filter to stream.
  void loadXml(QXmlStreamReader &reader);

  /// Low value of foreground, hue, intensity, saturation or value according to current filter mode,
  /// normalized to 0 to 1.
  double low () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Get method for saturation higher bound.
  int saturationHigh () const;

  /// Get method for saturation lower bound.
  int saturationLow () const;

  /// Save curve filter to stream.
  void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for filter mode.
  void setColorFilterMode(ColorFilterMode colorFilterMode);

  /// Set method for foreground higher bound.
  void setForegroundHigh (int foregroundHigh);

  /// Set method for foreground lower bound.
  void setForegroundLow (int foregroundLow);

  /// Set the high value for the current filter mode.
  void setHigh (double s0To1);

  /// Set method for hue higher bound.
  void setHueHigh (int hueHigh);

  /// Set method for hue lower bound.
  void setHueLow (int hueLow);

  /// Set method for intensity higher bound.
  void setIntensityHigh (int intensityHigh);

  /// Set method for intensity lower bound.
  void setIntensityLow (int intensityLow);

  /// Set the low value for the current filter mode.
  void setLow (double s0To1);

  /// Set method for saturation high.
  void setSaturationHigh (int saturationHigh);

  /// Set method for saturation low.
  void setSaturationLow (int saturationLow);

  /// Set method for value high.
  void setValueHigh (int valueHigh);

  /// Set method for value low.
  void setValueLow (int valueLow);

  /// Get method for value high.
  int valueHigh () const;

  /// Get method for value low.
  int valueLow () const;

private:

  ColorFilterMode m_colorFilterMode;
  int m_intensityLow;
  int m_intensityHigh;
  int m_foregroundLow;
  int m_foregroundHigh;
  int m_hueLow;
  int m_hueHigh;
  int m_saturationLow;
  int m_saturationHigh;
  int m_valueLow;
  int m_valueHigh;
};

#endif // COLOR_FILTER_SETTINGS_H
