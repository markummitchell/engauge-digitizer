#include "CmdMediator.h"
#include "DocumentModelColorFilter.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

DocumentModelColorFilter::DocumentModelColorFilter()
{
}

DocumentModelColorFilter::DocumentModelColorFilter(const Document &document)
{
  // Axis curve
  const Curve &curveAxes = document.curveAxes();
  m_colorFilterSettingsList [AXIS_CURVE_NAME] = curveAxes.colorFilterSettings ();

  // Graph curves
  QStringList graphCurveNames = document.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = graphCurveNames.begin (); itr != graphCurveNames.end (); itr++) {

    const QString &graphCurveName = *itr;
    const Curve *graphCurve = document.curveForCurveName(graphCurveName);
    m_colorFilterSettingsList [graphCurveName] = graphCurve->colorFilterSettings();
  }
}

DocumentModelColorFilter::DocumentModelColorFilter(const DocumentModelColorFilter &other)
{
  // Curve filters
  ColorFilterSettingsList::const_iterator itr;
  for (itr = other.colorFilterSettingsList ().constBegin (); itr != other.colorFilterSettingsList().constEnd(); itr++) {
    QString curveName = itr.key();
    ColorFilterSettings colorFilterSettings = itr.value();
    m_colorFilterSettingsList [curveName] = colorFilterSettings;
  }
}

DocumentModelColorFilter &DocumentModelColorFilter::operator=(const DocumentModelColorFilter &other)
{
  // Curve filters
  ColorFilterSettingsList::const_iterator itr;
  for (itr = other.colorFilterSettingsList ().constBegin (); itr != other.colorFilterSettingsList ().constEnd(); itr++) {
    QString curveName = itr.key();
    ColorFilterSettings colorFilterSettings = itr.value();
    m_colorFilterSettingsList [curveName] = colorFilterSettings;
  }

  return *this;
}

ColorFilterMode DocumentModelColorFilter::colorFilterMode(const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].colorFilterMode();
}

const ColorFilterSettings DocumentModelColorFilter::colorFilterSettings (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName];
}

const ColorFilterSettingsList &DocumentModelColorFilter::colorFilterSettingsList () const
{
  return m_colorFilterSettingsList;
}

int DocumentModelColorFilter::foregroundHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].foregroundHigh();
}

int DocumentModelColorFilter::foregroundLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].foregroundLow();
}

double DocumentModelColorFilter::high (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].high();
}

int DocumentModelColorFilter::hueHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].hueHigh();
}

int DocumentModelColorFilter::hueLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].hueLow();
}

int DocumentModelColorFilter::intensityHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].intensityHigh();
}

int DocumentModelColorFilter::intensityLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].intensityLow();
}

void DocumentModelColorFilter::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelColorFilter::loadXml";

  bool success = true;

  m_colorFilterSettingsList.clear();

  while ((reader.tokenType() != QXmlStreamReader::EndElement) &&
         (reader.name() != DOCUMENT_SERIALIZE_FILTER)) {
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_COLOR_FILTER)) {
      
      QXmlStreamAttributes attributes = reader.attributes();

      if (attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_NAME)) {

        QString curveName = attributes.value(DOCUMENT_SERIALIZE_CURVE_NAME).toString();

        ColorFilterSettings colorFilterSettings (reader);
        m_colorFilterSettingsList [curveName] = colorFilterSettings;

      } else {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError("Cannot read filter data");
  }
}

double DocumentModelColorFilter::low (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].low();
}

int DocumentModelColorFilter::saturationHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].saturationHigh();
}

int DocumentModelColorFilter::saturationLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].saturationLow();
}

void DocumentModelColorFilter::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelColorFilter::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_FILTER);

  // Loop through filters
  ColorFilterSettingsList::const_iterator itr;
  for (itr = m_colorFilterSettingsList.begin (); itr != m_colorFilterSettingsList.end (); itr++) {
    const ColorFilterSettings &colorFilterSettings = *itr;
    colorFilterSettings.saveXml(writer);
  }

  writer.writeEndElement();
}

void DocumentModelColorFilter::setColorFilterMode(const QString &curveName,
                                             ColorFilterMode colorFilterMode)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setColorFilterMode(colorFilterMode);
}

void DocumentModelColorFilter::setForegroundHigh (const QString &curveName,
                                             int foregroundHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setForegroundHigh(foregroundHigh);
}

void DocumentModelColorFilter::setForegroundLow (const QString &curveName,
                                            int foregroundLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setForegroundLow(foregroundLow);
}

void DocumentModelColorFilter::setHigh (const QString &curveName,
                                   double s0To1)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setHigh(s0To1);
}

void DocumentModelColorFilter::setHueHigh (const QString &curveName,
                                      int hueHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setHueHigh(hueHigh);
}

void DocumentModelColorFilter::setHueLow (const QString &curveName,
                                     int hueLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setHueLow(hueLow);
}

void DocumentModelColorFilter::setIntensityHigh (const QString &curveName,
                                            int intensityHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setIntensityHigh(intensityHigh);
}

void DocumentModelColorFilter::setIntensityLow (const QString &curveName,
                                           int intensityLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setIntensityLow(intensityLow);
}

void DocumentModelColorFilter::setLow (const QString &curveName,
                                  double s0To1)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setLow(s0To1);
}

void DocumentModelColorFilter::setSaturationHigh (const QString &curveName,
                                             int saturationHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setSaturationHigh(saturationHigh);
}

void DocumentModelColorFilter::setSaturationLow (const QString &curveName,
                                            int saturationLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setSaturationLow(saturationLow);
}

void DocumentModelColorFilter::setValueHigh (const QString &curveName,
                                        int valueHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setValueHigh(valueHigh);
}

void DocumentModelColorFilter::setValueLow (const QString &curveName,
                                       int valueLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setValueLow(valueLow);
}

int DocumentModelColorFilter::valueHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].valueHigh();
}

int DocumentModelColorFilter::valueLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].valueLow();
}
