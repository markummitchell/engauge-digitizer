#include "CmdMediator.h"
#include "DocumentModelFilter.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QXmlStreamWriter>
#include "Xml.h"

DocumentModelFilter::DocumentModelFilter()
{
}

DocumentModelFilter::DocumentModelFilter(const Document &document)
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

DocumentModelFilter::DocumentModelFilter(const DocumentModelFilter &other)
{
  // Curve filters
  ColorFilterSettingsList::const_iterator itr;
  for (itr = other.colorFilterSettingsList ().constBegin (); itr != other.colorFilterSettingsList().constEnd(); itr++) {
    QString curveName = itr.key();
    ColorFilterSettings colorFilterSettings = itr.value();
    m_colorFilterSettingsList [curveName] = colorFilterSettings;
  }
}

DocumentModelFilter &DocumentModelFilter::operator=(const DocumentModelFilter &other)
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

const ColorFilterSettings DocumentModelFilter::colorFilterSettings (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName];
}

const ColorFilterSettingsList &DocumentModelFilter::colorFilterSettingsList () const
{
  return m_colorFilterSettingsList;
}

FilterMode DocumentModelFilter::filterMode(const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].filterMode();
}

int DocumentModelFilter::foregroundHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].foregroundHigh();
}

int DocumentModelFilter::foregroundLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].foregroundLow();
}

double DocumentModelFilter::high (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].high();
}

int DocumentModelFilter::hueHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].hueHigh();
}

int DocumentModelFilter::hueLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].hueLow();
}

int DocumentModelFilter::intensityHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].intensityHigh();
}

int DocumentModelFilter::intensityLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].intensityLow();
}

void DocumentModelFilter::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelFilter::loadXml";

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
        (reader.name() == DOCUMENT_SERIALIZE_CURVE_FILTER)) {
      
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

double DocumentModelFilter::low (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].low();
}

int DocumentModelFilter::saturationHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].saturationHigh();
}

int DocumentModelFilter::saturationLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].saturationLow();
}

void DocumentModelFilter::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelFilter::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_FILTER);

  // Loop through filters
  ColorFilterSettingsList::const_iterator itr;
  for (itr = m_colorFilterSettingsList.begin (); itr != m_colorFilterSettingsList.end (); itr++) {
    const ColorFilterSettings &colorFilterSettings = *itr;
    colorFilterSettings.saveXml(writer);
  }

  writer.writeEndElement();
}

void DocumentModelFilter::setFilterMode(const QString &curveName,
                                             FilterMode filterMode)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setFilterMode(filterMode);
}

void DocumentModelFilter::setForegroundHigh (const QString &curveName,
                                             int foregroundHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setForegroundHigh(foregroundHigh);
}

void DocumentModelFilter::setForegroundLow (const QString &curveName,
                                            int foregroundLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setForegroundLow(foregroundLow);
}

void DocumentModelFilter::setHigh (const QString &curveName,
                                   double s0To1)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setHigh(s0To1);
}

void DocumentModelFilter::setHueHigh (const QString &curveName,
                                      int hueHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setHueHigh(hueHigh);
}

void DocumentModelFilter::setHueLow (const QString &curveName,
                                     int hueLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setHueLow(hueLow);
}

void DocumentModelFilter::setIntensityHigh (const QString &curveName,
                                            int intensityHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setIntensityHigh(intensityHigh);
}

void DocumentModelFilter::setIntensityLow (const QString &curveName,
                                           int intensityLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setIntensityLow(intensityLow);
}

void DocumentModelFilter::setLow (const QString &curveName,
                                  double s0To1)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setLow(s0To1);
}

void DocumentModelFilter::setSaturationHigh (const QString &curveName,
                                             int saturationHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setSaturationHigh(saturationHigh);
}

void DocumentModelFilter::setSaturationLow (const QString &curveName,
                                            int saturationLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setSaturationLow(saturationLow);
}

void DocumentModelFilter::setValueHigh (const QString &curveName,
                                        int valueHigh)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setValueHigh(valueHigh);
}

void DocumentModelFilter::setValueLow (const QString &curveName,
                                       int valueLow)
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  m_colorFilterSettingsList [curveName].setValueLow(valueLow);
}

int DocumentModelFilter::valueHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].valueHigh();
}

int DocumentModelFilter::valueLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_colorFilterSettingsList.contains (curveName));
  return m_colorFilterSettingsList [curveName].valueLow();
}
