#include "CmdMediator.h"
#include "CurveConstants.h"
#include "CurveFilter.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QXmlStreamWriter>
#include "Xml.h"

CurveFilter::CurveFilter() :
  m_filterMode (FILTER_MODE_INTENSITY),
  m_intensityLow (INTENSITY_LOW_DEFAULT),
  m_intensityHigh (INTENSITY_HIGH_DEFAULT),
  m_foregroundLow (FOREGROUND_LOW_DEFAULT),
  m_foregroundHigh (FOREGROUND_HIGH_DEFAULT),
  m_hueLow (HUE_LOW_DEFAULT),
  m_hueHigh (HUE_HIGH_DEFAULT),
  m_saturationLow (SATURATION_LOW_DEFAULT),
  m_saturationHigh (SATURATION_HIGH_DEFAULT),
  m_valueLow (VALUE_LOW_DEFAULT),
  m_valueHigh (VALUE_HIGH_DEFAULT)
{
}

CurveFilter::CurveFilter(FilterMode filterMode,
                         int intensityLow,
                         int intensityHigh,
                         int foregroundLow,
                         int foregroundHigh,
                         int hueLow,
                         int hueHigh,
                         int saturationLow,
                         int saturationHigh,
                         int valueLow,
                         int valueHigh) :
  m_filterMode (filterMode),
  m_intensityLow (intensityLow),
  m_intensityHigh (intensityHigh),
  m_foregroundLow (foregroundLow),
  m_foregroundHigh (foregroundHigh),
  m_hueLow (hueLow),
  m_hueHigh (hueHigh),
  m_saturationLow (saturationLow),
  m_saturationHigh (saturationHigh),
  m_valueLow (valueLow),
  m_valueHigh (valueHigh)
{
}

CurveFilter::CurveFilter(const CurveFilter &other) :
  m_filterMode (other.filterMode()),
  m_intensityLow (other.intensityLow()),
  m_intensityHigh (other.intensityHigh()),
  m_foregroundLow (other.foregroundLow()),
  m_foregroundHigh (other.foregroundHigh()),
  m_hueLow (other.hueLow()),
  m_hueHigh (other.hueHigh()),
  m_saturationLow (other.saturationLow()),
  m_saturationHigh (other.saturationHigh()),
  m_valueLow (other.valueLow()),
  m_valueHigh (other.valueHigh())
{
}

CurveFilter::CurveFilter(QXmlStreamReader &reader)
{
  loadXml(reader);
}

CurveFilter &CurveFilter::operator=(const CurveFilter &other)
{
  m_filterMode = other.filterMode();
  m_intensityLow = other.intensityLow();
  m_intensityHigh = other.intensityHigh();
  m_foregroundLow = other.foregroundLow();
  m_foregroundHigh = other.foregroundHigh();
  m_hueLow = other.hueLow();
  m_hueHigh = other.hueHigh();
  m_saturationLow = other.saturationLow();
  m_saturationHigh = other.saturationHigh();
  m_valueLow = other.valueLow();
  m_valueHigh = other.valueHigh();

  return *this;
}

CurveFilter CurveFilter::defaultFilter ()
{
  return CurveFilter ();
}

FilterMode CurveFilter::filterMode() const
{
  return m_filterMode;
}

int CurveFilter::foregroundHigh () const
{
  return m_foregroundHigh;
}

int CurveFilter::foregroundLow () const
{
  return m_foregroundLow;
}

double CurveFilter::high () const
{
  switch (m_filterMode)
  {
    case FILTER_MODE_FOREGROUND:
      return (double) (m_foregroundHigh - FOREGROUND_MIN) /
          (double) (FOREGROUND_MAX - FOREGROUND_MIN);

    case FILTER_MODE_HUE:
      return (double) (m_hueHigh - HUE_MIN) /
          ((double) HUE_MAX - HUE_MIN);

    case FILTER_MODE_INTENSITY:
      return (double) (m_intensityHigh - INTENSITY_MIN) /
          (double) (INTENSITY_MAX - INTENSITY_MIN);

    case FILTER_MODE_SATURATION:
      return (double) (m_saturationHigh - SATURATION_MIN) /
          (double) (SATURATION_MAX - SATURATION_MIN);

    case FILTER_MODE_VALUE:
      return (double) (m_valueHigh - VALUE_MIN) /
          (double) (VALUE_MAX - VALUE_MIN);

    default:
      Q_ASSERT (false);
  }
}

int CurveFilter::hueHigh () const
{
  return m_hueHigh;
}

int CurveFilter::hueLow () const
{
  return m_hueLow;
}

int CurveFilter::intensityHigh () const
{
  return m_intensityHigh;
}

int CurveFilter::intensityLow () const
{
  return m_intensityLow;
}

void CurveFilter::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveFilter::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_MODE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_INTENSITY_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_INTENSITY_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_FOREGROUND_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_FOREGROUND_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_HUE_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_HUE_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_SATURATION_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_SATURATION_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_VALUE_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_VALUE_HIGH)) {

    setFilterMode ((FilterMode) attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_MODE).toInt());
    setIntensityLow (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_INTENSITY_LOW).toInt());
    setIntensityHigh ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_INTENSITY_HIGH).toInt());
    setForegroundLow (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_FOREGROUND_LOW).toInt());
    setForegroundHigh (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_FOREGROUND_HIGH).toInt());
    setHueLow (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_HUE_LOW).toInt());
    setHueHigh (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_HUE_HIGH).toInt());
    setSaturationLow ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_SATURATION_LOW).toInt());
    setSaturationHigh (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_SATURATION_HIGH).toInt());
    setValueLow (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_VALUE_LOW).toInt());
    setValueHigh (attributes.value(DOCUMENT_SERIALIZE_CURVE_FILTER_VALUE_HIGH).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_CURVE_FILTER)){
      loadNextFromReader(reader);

      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read curve filter data");
  }
}

double CurveFilter::low () const
{
  switch (m_filterMode)
  {
    case FILTER_MODE_FOREGROUND:
      return (double) (m_foregroundLow - FOREGROUND_MIN) /
          (double) (FOREGROUND_MAX - FOREGROUND_MIN);

    case FILTER_MODE_HUE:
      return (double) (m_hueLow - HUE_MIN) /
          ((double) HUE_MAX - HUE_MIN);

    case FILTER_MODE_INTENSITY:
      return (double) (m_intensityLow - INTENSITY_MIN) /
          (double) (INTENSITY_MAX - INTENSITY_MIN);

    case FILTER_MODE_SATURATION:
      return (double) (m_saturationLow - SATURATION_MIN) /
          (double) (SATURATION_MAX - SATURATION_MIN);

    case FILTER_MODE_VALUE:
      return (double) (m_valueLow - VALUE_MIN) /
          (double) (VALUE_MAX - VALUE_MIN);

    default:
      Q_ASSERT (false);
  }
}

int CurveFilter::saturationHigh () const
{
  return m_saturationHigh;
}

int CurveFilter::saturationLow () const
{
  return m_saturationLow;
}

void CurveFilter::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveFilter::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVE_FILTER);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_MODE, QString::number (m_filterMode));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_INTENSITY_LOW, QString::number (m_intensityLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_INTENSITY_HIGH, QString::number (m_intensityHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_FOREGROUND_LOW, QString::number (m_foregroundLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_FOREGROUND_HIGH, QString::number (m_foregroundHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_HUE_LOW, QString::number (m_hueLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_HUE_HIGH, QString::number (m_hueHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_SATURATION_LOW, QString::number (m_saturationLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_SATURATION_HIGH, QString::number (m_saturationHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_VALUE_LOW, QString::number (m_valueLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_FILTER_VALUE_HIGH, QString::number (m_valueHigh));
  writer.writeEndElement();
}

void CurveFilter::setFilterMode(FilterMode filterMode)
{
  m_filterMode = filterMode;
}

void CurveFilter::setForegroundHigh (int foregroundHigh)
{
  Q_ASSERT (FOREGROUND_MIN <= foregroundHigh && foregroundHigh <= FOREGROUND_MAX);
  m_foregroundHigh = foregroundHigh;
}

void CurveFilter::setForegroundLow (int foregroundLow)
{
  Q_ASSERT (FOREGROUND_MIN <= foregroundLow && foregroundLow <= FOREGROUND_MAX);
  m_foregroundLow = foregroundLow;
}

void CurveFilter::setHigh (double s0To1)
{
  switch (m_filterMode) {
    case FILTER_MODE_FOREGROUND:
      setForegroundHigh (FOREGROUND_MIN + s0To1 * (FOREGROUND_MAX - FOREGROUND_MIN));
      break;

    case FILTER_MODE_HUE:
      setHueHigh (HUE_MIN + s0To1 * (HUE_MAX - HUE_MIN));
      break;

    case FILTER_MODE_INTENSITY:
      setIntensityHigh (INTENSITY_MIN + s0To1 * (INTENSITY_MAX - INTENSITY_MIN));
      break;

    case FILTER_MODE_SATURATION:
      setSaturationHigh (SATURATION_MIN + s0To1 * (SATURATION_MAX - SATURATION_MIN));
      break;

    case FILTER_MODE_VALUE:
      setValueHigh (VALUE_MIN + s0To1 * (VALUE_MAX - VALUE_MIN));
      break;

    default:
      Q_ASSERT (false);
  }
}

void CurveFilter::setHueHigh (int hueHigh)
{
  Q_ASSERT (HUE_MIN <= hueHigh && hueHigh <= HUE_MAX);
  m_hueHigh = hueHigh;
}

void CurveFilter::setHueLow (int hueLow)
{
  Q_ASSERT (HUE_MIN <= hueLow && hueLow <= HUE_MAX);
  m_hueLow = hueLow;
}

void CurveFilter::setIntensityHigh (int intensityHigh)
{
  Q_ASSERT (INTENSITY_MIN <= intensityHigh && intensityHigh <= INTENSITY_MAX);
  m_intensityHigh = intensityHigh;
}

void CurveFilter::setIntensityLow (int intensityLow)
{
  Q_ASSERT (INTENSITY_MIN <= intensityLow && intensityLow <= INTENSITY_MAX);
  m_intensityLow = intensityLow;
}

void CurveFilter::setLow (double s0To1)
{
  switch (m_filterMode) {
    case FILTER_MODE_FOREGROUND:
      setForegroundLow (FOREGROUND_MIN + s0To1 * (FOREGROUND_MAX - FOREGROUND_MIN));
      break;

    case FILTER_MODE_HUE:
      setHueLow (HUE_MIN + s0To1 * (HUE_MAX - HUE_MIN));
      break;

    case FILTER_MODE_INTENSITY:
      setIntensityLow (INTENSITY_MIN + s0To1 * (INTENSITY_MAX - INTENSITY_MIN));
      break;

    case FILTER_MODE_SATURATION:
      setSaturationLow (SATURATION_MIN + s0To1 * (SATURATION_MAX - SATURATION_MIN));
      break;

    case FILTER_MODE_VALUE:
      setValueLow (VALUE_MIN + s0To1 * (VALUE_MAX - VALUE_MIN));
      break;

    default:
      Q_ASSERT (false);
  }
}

void CurveFilter::setSaturationHigh (int saturationHigh)
{
  Q_ASSERT (SATURATION_MIN <= saturationHigh && saturationHigh <= SATURATION_MAX);
  m_saturationHigh = saturationHigh;
}

void CurveFilter::setSaturationLow (int saturationLow)
{
  Q_ASSERT (SATURATION_MIN <= saturationLow && saturationLow <= SATURATION_MAX);
  m_saturationLow = saturationLow;
}

void CurveFilter::setValueHigh (int valueHigh)
{
  Q_ASSERT (VALUE_MIN <= valueHigh && valueHigh <= VALUE_MAX);
  m_valueHigh = valueHigh;
}

void CurveFilter::setValueLow (int valueLow)
{
  Q_ASSERT (VALUE_MIN <= valueLow && valueLow <= VALUE_MAX);
  m_valueLow = valueLow;
}

int CurveFilter::valueHigh () const
{
  return m_valueHigh;
}

int CurveFilter::valueLow () const
{
  return m_valueLow;
}
