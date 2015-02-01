#ifndef CURVE_FILTER_H
#define CURVE_FILTER_H

#include "FilterParameter.h"

class QXmlStreamWriter;

/// Filter parameters for one curve. For a class, this is handled the same as LineStyle and PointStyle
class CurveFilter
{
public:
  /// Default constructor only for use when this class is being stored by a container that requires the default constructor.
  CurveFilter ();

  /// Normal constructor. The style type and radius are determined by the currently selected Curve
  CurveFilter (FilterParameter m_filterParameter,
               int m_intensityLow,
               int m_intensityHigh,
               int m_foregroundLow,
               int m_foregroundHigh,
               int m_hueLow,
               int m_hueHigh,
               int m_saturationLow,
               int m_saturationHigh,
               int m_valueLow,
               int m_valueHigh);

  /// Copy constructor.
  CurveFilter (const CurveFilter &other);

  /// Assignment operator.
  CurveFilter &operator= (const CurveFilter &other);

  /// Initial default for any Curve.
  static CurveFilter defaultFilter ();

  /// Get method for filter parameter.
  FilterParameter filterParameter() const;

  /// Get method for foreground higher bound.
  int foregroundHigh () const;

  /// Get method for foreground lower bound.
  int foregroundLow () const;

  /// High value of foreground, hue, intensity, saturation or value according to current filter parameter,
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

  /// Low value of foreground, hue, intensity, saturation or value according to current filter parameter,
  /// normalized to 0 to 1.
  double low () const;

  /// Get method for saturation higher bound.
  int saturationHigh () const;

  /// Get method for saturation lower bound.
  int saturationLow () const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for filter parameter.
  void setFilterParameter(FilterParameter filterParameter);

  /// Set method for foreground higher bound.
  void setForegroundHigh (int foregroundHigh);

  /// Set method for foreground lower bound.
  void setForegroundLow (int foregroundLow);

  /// Set the high value for the current filter parameter.
  void setHigh (double s0To1);

  /// Set method for hue higher bound.
  void setHueHigh (int hueHigh);

  /// Set method for hue lower bound.
  void setHueLow (int hueLow);

  /// Set method for intensity higher bound.
  void setIntensityHigh (int intensityHigh);

  /// Set method for intensity lower bound.
  void setIntensityLow (int intensityLow);

  /// Set the low value for the current filter parameter.
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

  FilterParameter m_filterParameter;
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

#endif // CURVE_FILTER_H
