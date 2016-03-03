/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "ColorConstants.h"
#include "ColorFilterSettings.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "GridCoordDisable.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

ColorFilterSettings::ColorFilterSettings() :
  m_colorFilterMode (COLOR_FILTER_MODE_INTENSITY),
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

ColorFilterSettings::ColorFilterSettings(ColorFilterMode colorFilterMode,
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
  m_colorFilterMode (colorFilterMode),
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

ColorFilterSettings::ColorFilterSettings(const ColorFilterSettings &other) :
  m_colorFilterMode (other.colorFilterMode()),
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

ColorFilterSettings::ColorFilterSettings(QXmlStreamReader &reader)
{
  loadXml(reader);
}

ColorFilterSettings &ColorFilterSettings::operator=(const ColorFilterSettings &other)
{
  m_colorFilterMode = other.colorFilterMode();
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

ColorFilterMode ColorFilterSettings::colorFilterMode() const
{
  return m_colorFilterMode;
}

ColorFilterSettings ColorFilterSettings::defaultFilter ()
{
  return ColorFilterSettings ();
}

int ColorFilterSettings::foregroundHigh () const
{
  return m_foregroundHigh;
}

int ColorFilterSettings::foregroundLow () const
{
  return m_foregroundLow;
}

double ColorFilterSettings::high () const
{
  switch (m_colorFilterMode)
  {
    case COLOR_FILTER_MODE_FOREGROUND:
      return (double) (m_foregroundHigh - FOREGROUND_MIN) /
          (double) (FOREGROUND_MAX - FOREGROUND_MIN);

    case COLOR_FILTER_MODE_HUE:
      return (double) (m_hueHigh - HUE_MIN) /
          ((double) HUE_MAX - HUE_MIN);

    case COLOR_FILTER_MODE_INTENSITY:
      return (double) (m_intensityHigh - INTENSITY_MIN) /
          (double) (INTENSITY_MAX - INTENSITY_MIN);

    case COLOR_FILTER_MODE_SATURATION:
      return (double) (m_saturationHigh - SATURATION_MIN) /
          (double) (SATURATION_MAX - SATURATION_MIN);

    case COLOR_FILTER_MODE_VALUE:
      return (double) (m_valueHigh - VALUE_MIN) /
          (double) (VALUE_MAX - VALUE_MIN);

    default:
      ENGAUGE_ASSERT (false);
      return (double) (m_intensityHigh - INTENSITY_MIN) /
          (double) (INTENSITY_MAX - INTENSITY_MIN); // Default when asserts are disabled
  }
}

int ColorFilterSettings::hueHigh () const
{
  return m_hueHigh;
}

int ColorFilterSettings::hueLow () const
{
  return m_hueLow;
}

int ColorFilterSettings::intensityHigh () const
{
  return m_intensityHigh;
}

int ColorFilterSettings::intensityLow () const
{
  return m_intensityLow;
}

void ColorFilterSettings::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ColorFilterSettings::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_MODE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_HIGH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_LOW) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_HIGH)) {

    setColorFilterMode ((ColorFilterMode) attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_MODE).toInt());
    setIntensityLow (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_LOW).toInt());
    setIntensityHigh ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_HIGH).toInt());
    setForegroundLow (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_LOW).toInt());
    setForegroundHigh (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_HIGH).toInt());
    setHueLow (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_LOW).toInt());
    setHueHigh (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_HIGH).toInt());
    setSaturationLow ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_LOW).toInt());
    setSaturationHigh (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_HIGH).toInt());
    setValueLow (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_LOW).toInt());
    setValueHigh (attributes.value(DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_HIGH).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_COLOR_FILTER)){
      loadNextFromReader(reader);

      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read curve filter data"));
  }
}

double ColorFilterSettings::low () const
{
  switch (m_colorFilterMode)
  {
    case COLOR_FILTER_MODE_FOREGROUND:
      return (double) (m_foregroundLow - FOREGROUND_MIN) /
          (double) (FOREGROUND_MAX - FOREGROUND_MIN);

    case COLOR_FILTER_MODE_HUE:
      return (double) (m_hueLow - HUE_MIN) /
          ((double) HUE_MAX - HUE_MIN);

    case COLOR_FILTER_MODE_INTENSITY:
      return (double) (m_intensityLow - INTENSITY_MIN) /
          (double) (INTENSITY_MAX - INTENSITY_MIN);

    case COLOR_FILTER_MODE_SATURATION:
      return (double) (m_saturationLow - SATURATION_MIN) /
          (double) (SATURATION_MAX - SATURATION_MIN);

    case COLOR_FILTER_MODE_VALUE:
      return (double) (m_valueLow - VALUE_MIN) /
          (double) (VALUE_MAX - VALUE_MIN);

    default:
      ENGAUGE_ASSERT (false);
      return (double) (m_intensityLow - INTENSITY_MIN) /
          (double) (INTENSITY_MAX - INTENSITY_MIN); // Default when asserts are disabled
  }
}

void ColorFilterSettings::printStream (QString indentation,
                                       QTextStream &str) const
{
  str << indentation << "ColorFilterSettings\n";

  indentation += INDENTATION_DELTA;

  switch (m_colorFilterMode) {
    case COLOR_FILTER_MODE_INTENSITY:
      str << indentation << "intensityLow=" << m_intensityLow << "\n";
      str << indentation << "intensityHigh=" << m_intensityHigh << "\n";
      break;

    case COLOR_FILTER_MODE_FOREGROUND:
      str << indentation << "foregroundLow=" << m_foregroundLow << "\n";
      str << indentation << "foregroundHigh=" << m_foregroundHigh << "\n";
      break;

    case COLOR_FILTER_MODE_HUE:
      str << indentation << "hueLow=" << m_hueLow << "\n";
      str << indentation << "hueHigh=" << m_hueHigh << "\n";
      break;

    case COLOR_FILTER_MODE_SATURATION:
      str << indentation << "saturationLow" << m_saturationLow << "\n";
      str << indentation << "saturationHigh" << m_saturationHigh << "\n";
      break;

    case COLOR_FILTER_MODE_VALUE:
      str << indentation << "valueLow=" << m_valueLow << "\n";
      str << indentation << "valueHigh=" << m_valueHigh << "\n";
      break;

    default:
      break;
  }
}

int ColorFilterSettings::saturationHigh () const
{
  return m_saturationHigh;
}

int ColorFilterSettings::saturationLow () const
{
  return m_saturationLow;
}

void ColorFilterSettings::saveXml(QXmlStreamWriter &writer,
                                  const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ColorFilterSettings::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_COLOR_FILTER);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CURVE_NAME, curveName);
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_MODE, QString::number (m_colorFilterMode));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_MODE_STRING, colorFilterModeToString (m_colorFilterMode));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_LOW, QString::number (m_intensityLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_HIGH, QString::number (m_intensityHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_LOW, QString::number (m_foregroundLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_HIGH, QString::number (m_foregroundHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_LOW, QString::number (m_hueLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_HIGH, QString::number (m_hueHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_LOW, QString::number (m_saturationLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_HIGH, QString::number (m_saturationHigh));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_LOW, QString::number (m_valueLow));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_HIGH, QString::number (m_valueHigh));
  writer.writeEndElement();
}

void ColorFilterSettings::setColorFilterMode(ColorFilterMode colorFilterMode)
{
  m_colorFilterMode = colorFilterMode;
}

void ColorFilterSettings::setForegroundHigh (int foregroundHigh)
{
  ENGAUGE_ASSERT (FOREGROUND_MIN <= foregroundHigh && foregroundHigh <= FOREGROUND_MAX);
  m_foregroundHigh = foregroundHigh;
}

void ColorFilterSettings::setForegroundLow (int foregroundLow)
{
  ENGAUGE_ASSERT (FOREGROUND_MIN <= foregroundLow && foregroundLow <= FOREGROUND_MAX);
  m_foregroundLow = foregroundLow;
}

void ColorFilterSettings::setHigh (double s0To1)
{
  switch (m_colorFilterMode) {
    case COLOR_FILTER_MODE_FOREGROUND:
      setForegroundHigh (FOREGROUND_MIN + s0To1 * (FOREGROUND_MAX - FOREGROUND_MIN));
      break;

    case COLOR_FILTER_MODE_HUE:
      setHueHigh (HUE_MIN + s0To1 * (HUE_MAX - HUE_MIN));
      break;

    case COLOR_FILTER_MODE_INTENSITY:
      setIntensityHigh (INTENSITY_MIN + s0To1 * (INTENSITY_MAX - INTENSITY_MIN));
      break;

    case COLOR_FILTER_MODE_SATURATION:
      setSaturationHigh (SATURATION_MIN + s0To1 * (SATURATION_MAX - SATURATION_MIN));
      break;

    case COLOR_FILTER_MODE_VALUE:
      setValueHigh (VALUE_MIN + s0To1 * (VALUE_MAX - VALUE_MIN));
      break;

    default:
      ENGAUGE_ASSERT (false);
  }
}

void ColorFilterSettings::setHueHigh (int hueHigh)
{
  ENGAUGE_ASSERT (HUE_MIN <= hueHigh && hueHigh <= HUE_MAX);
  m_hueHigh = hueHigh;
}

void ColorFilterSettings::setHueLow (int hueLow)
{
  ENGAUGE_ASSERT (HUE_MIN <= hueLow && hueLow <= HUE_MAX);
  m_hueLow = hueLow;
}

void ColorFilterSettings::setIntensityHigh (int intensityHigh)
{
  ENGAUGE_ASSERT (INTENSITY_MIN <= intensityHigh && intensityHigh <= INTENSITY_MAX);
  m_intensityHigh = intensityHigh;
}

void ColorFilterSettings::setIntensityLow (int intensityLow)
{
  ENGAUGE_ASSERT (INTENSITY_MIN <= intensityLow && intensityLow <= INTENSITY_MAX);
  m_intensityLow = intensityLow;
}

void ColorFilterSettings::setLow (double s0To1)
{
  switch (m_colorFilterMode) {
    case COLOR_FILTER_MODE_FOREGROUND:
      setForegroundLow (FOREGROUND_MIN + s0To1 * (FOREGROUND_MAX - FOREGROUND_MIN));
      break;

    case COLOR_FILTER_MODE_HUE:
      setHueLow (HUE_MIN + s0To1 * (HUE_MAX - HUE_MIN));
      break;

    case COLOR_FILTER_MODE_INTENSITY:
      setIntensityLow (INTENSITY_MIN + s0To1 * (INTENSITY_MAX - INTENSITY_MIN));
      break;

    case COLOR_FILTER_MODE_SATURATION:
      setSaturationLow (SATURATION_MIN + s0To1 * (SATURATION_MAX - SATURATION_MIN));
      break;

    case COLOR_FILTER_MODE_VALUE:
      setValueLow (VALUE_MIN + s0To1 * (VALUE_MAX - VALUE_MIN));
      break;

    default:
      ENGAUGE_ASSERT (false);
  }
}

void ColorFilterSettings::setSaturationHigh (int saturationHigh)
{
  ENGAUGE_ASSERT (SATURATION_MIN <= saturationHigh && saturationHigh <= SATURATION_MAX);
  m_saturationHigh = saturationHigh;
}

void ColorFilterSettings::setSaturationLow (int saturationLow)
{
  ENGAUGE_ASSERT (SATURATION_MIN <= saturationLow && saturationLow <= SATURATION_MAX);
  m_saturationLow = saturationLow;
}

void ColorFilterSettings::setValueHigh (int valueHigh)
{
  ENGAUGE_ASSERT (VALUE_MIN <= valueHigh && valueHigh <= VALUE_MAX);
  m_valueHigh = valueHigh;
}

void ColorFilterSettings::setValueLow (int valueLow)
{
  ENGAUGE_ASSERT (VALUE_MIN <= valueLow && valueLow <= VALUE_MAX);
  m_valueLow = valueLow;
}

int ColorFilterSettings::valueHigh () const
{
  return m_valueHigh;
}

int ColorFilterSettings::valueLow () const
{
  return m_valueLow;
}
