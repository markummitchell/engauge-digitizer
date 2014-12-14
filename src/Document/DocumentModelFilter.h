#ifndef DOCUMENT_MODEL_FILTER_H
#define DOCUMENT_MODEL_FILTER_H

#include "DocumentModelAbstractBase.h"
#include "FilterParameter.h"

const int INTENSITY_MIN = 0;
const int INTENSITY_MAX = 100;
const int INTENSITY_LOW_DEFAULT = 0;
const int INTENSITY_HIGH_DEFAULT = 50;
const int FOREGROUND_MIN = 0;
const int FOREGROUND_MAX = 100;
const int FOREGROUND_LOW_DEFAULT = 0;
const int FOREGROUND_HIGH_DEFAULT = 10;
const int HUE_MIN = 0;
const int HUE_MAX = 360;
const int HUE_LOW_DEFAULT = 180;
const int HUE_HIGH_DEFAULT = 360;
const int SATURATION_MIN = 0;
const int SATURATION_MAX = 100;
const int SATURATION_LOW_DEFAULT = 50;
const int SATURATION_HIGH_DEFAULT = 100;
const int VALUE_MIN = 0;
const int VALUE_MAX = 100;
const int VALUE_LOW_DEFAULT = 0;
const int VALUE_HIGH_DEFAULT = 50;

class Document;

/// Model for DlgSettingsFilter and CmdSettingsFilter.
class DocumentModelFilter : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelFilter();

  /// Initial constructor from Document.
  DocumentModelFilter(const Document &document);

  /// Copy constructor.
  DocumentModelFilter(const DocumentModelFilter &other);

  /// Assignment constructor.
  DocumentModelFilter &operator=(const DocumentModelFilter &other);

  /// Get method for filter parameter.
  FilterParameter filterParameter() const;

  /// Get method for foreground higher bound.
  int foregroundHigh () const;

  /// Get method for foreground lower bound.
  int foregroundLow () const;

  /// High value (0-1) of foreground, hue, intensity, saturation or value according to current filter parameter.
  double high () const;

  /// Get method for hue higher bound.
  int hueHigh () const;

  /// Get method for hue lower bound.
  int hueLow () const;

  /// Get method for intensity higher bound.
  int intensityHigh () const;

  /// Get method for intensity lower bound.
  int intensityLow () const;

  /// Low value (0-1) of foreground, hue, intensity, saturation or value according to current filter parameter.
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

  /// Set method for hue higher bound.
  void setHueHigh (int hueHigh);

  /// Set method for hue lower bound.
  void setHueLow (int hueLow);

  /// Set method for intensity higher bound.
  void setIntensityHigh (int intensityHigh);

  /// Set method for intensity lower bound.
  void setIntensityLow (int intensityLow);

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

#endif // DOCUMENT_MODEL_FILTER_H
