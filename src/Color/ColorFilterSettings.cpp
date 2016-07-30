/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "ColorConstants.h"
#include "ColorFilterSettings.h"
#include "ColorFilterSettingsStrategyAbstractBase.h"
#include "ColorFilterSettingsStrategyForeground.h"
#include "ColorFilterSettingsStrategyHue.h"
#include "ColorFilterSettingsStrategyIntensity.h"
#include "ColorFilterSettingsStrategySaturation.h"
#include "ColorFilterSettingsStrategyValue.h"
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
  createStrategies ();
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
  createStrategies ();
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
  createStrategies ();
}

ColorFilterSettings::ColorFilterSettings(QXmlStreamReader &reader)
{
  loadXml(reader);
  createStrategies ();
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

  createStrategies ();

  return *this;
}

ColorFilterMode ColorFilterSettings::colorFilterMode() const
{
  return m_colorFilterMode;
}

void ColorFilterSettings::createStrategies ()
{
  m_strategies [COLOR_FILTER_MODE_FOREGROUND] = new ColorFilterSettingsStrategyForeground ();
  m_strategies [COLOR_FILTER_MODE_HUE       ] = new ColorFilterSettingsStrategyHue        ();
  m_strategies [COLOR_FILTER_MODE_INTENSITY ] = new ColorFilterSettingsStrategyIntensity  ();
  m_strategies [COLOR_FILTER_MODE_SATURATION] = new ColorFilterSettingsStrategySaturation ();
  m_strategies [COLOR_FILTER_MODE_VALUE     ] = new ColorFilterSettingsStrategyValue      ();
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
  if (m_strategies.contains (m_colorFilterMode)) {

    // Ignore false positive cmake compiler warning about -Wreturn-stack-address in next line (bug #26396)
    const ColorFilterSettingsStrategyAbstractBase *strategy = m_strategies.value (m_colorFilterMode);
    return strategy->high (*this);
  } else {
    ENGAUGE_ASSERT (false);
    return m_strategies [COLOR_FILTER_MODE_INTENSITY]->high (*this);
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
  if (m_strategies.contains (m_colorFilterMode)) {
    const ColorFilterSettingsStrategyAbstractBase *strategy = m_strategies.value (m_colorFilterMode);
    return strategy->low (*this);
  } else {
    ENGAUGE_ASSERT (false);
    return m_strategies [COLOR_FILTER_MODE_INTENSITY]->low (*this);
  }
}

void ColorFilterSettings::printStream (QString indentation,
                                       QTextStream &str) const
{
  str << indentation << "ColorFilterSettings\n";

  indentation += INDENTATION_DELTA;

  if (m_strategies.contains (m_colorFilterMode)) {
    const ColorFilterSettingsStrategyAbstractBase *strategy = m_strategies.value (m_colorFilterMode);
    return strategy->printStream (*this,
                                  indentation,
                                  str);
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
  if (m_strategies.contains (m_colorFilterMode)) {
    ColorFilterSettingsStrategyAbstractBase *strategy = m_strategies [m_colorFilterMode];
    return strategy->setHigh (*this,
                              s0To1);
  } else {
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
  if (m_strategies.contains (m_colorFilterMode)) {
    ColorFilterSettingsStrategyAbstractBase *strategy = m_strategies [m_colorFilterMode];
    return strategy->setLow (*this,
                             s0To1);
  } else {
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
