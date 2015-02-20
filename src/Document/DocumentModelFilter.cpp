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
  m_curveFilters [AXIS_CURVE_NAME] = curveAxes.curveFilter();

  // Graph curves
  QStringList graphCurveNames = document.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = graphCurveNames.begin (); itr != graphCurveNames.end (); itr++) {

    const QString &graphCurveName = *itr;
    const Curve *graphCurve = document.curveForCurveName(graphCurveName);
    m_curveFilters [graphCurveName] = graphCurve->curveFilter();
  }
}

DocumentModelFilter::DocumentModelFilter(const DocumentModelFilter &other)
{
  // Curve filters
  CurveFilters::const_iterator itr;
  for (itr = other.curveFilters().constBegin (); itr != other.curveFilters().constEnd(); itr++) {
    QString curveName = itr.key();
    CurveFilter curveFilter = itr.value();
    m_curveFilters [curveName] = curveFilter;
  }
}

DocumentModelFilter &DocumentModelFilter::operator=(const DocumentModelFilter &other)
{
  // Curve filters
  CurveFilters::const_iterator itr;
  for (itr = other.curveFilters().constBegin (); itr != other.curveFilters().constEnd(); itr++) {
    QString curveName = itr.key();
    CurveFilter curveFilter = itr.value();
    m_curveFilters [curveName] = curveFilter;
  }

  return *this;
}

const CurveFilter DocumentModelFilter::curveFilter (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName];
}

const CurveFilters &DocumentModelFilter::curveFilters() const
{
  return m_curveFilters;
}

FilterMode DocumentModelFilter::filterMode(const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].filterMode();
}

int DocumentModelFilter::foregroundHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].foregroundHigh();
}

int DocumentModelFilter::foregroundLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].foregroundLow();
}

double DocumentModelFilter::high (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].high();
}

int DocumentModelFilter::hueHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].hueHigh();
}

int DocumentModelFilter::hueLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].hueLow();
}

int DocumentModelFilter::intensityHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].intensityHigh();
}

int DocumentModelFilter::intensityLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].intensityLow();
}

void DocumentModelFilter::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelFilter::loadXml";

  bool success = true;

  m_curveFilters.clear();

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

        CurveFilter curveFilter(reader);
        m_curveFilters [curveName] = curveFilter;

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
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].low();
}

int DocumentModelFilter::saturationHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].saturationHigh();
}

int DocumentModelFilter::saturationLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].saturationLow();
}

void DocumentModelFilter::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelFilter::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_FILTER);

  // Loop through filters
  CurveFilters::const_iterator itr;
  for (itr = m_curveFilters.begin (); itr != m_curveFilters.end (); itr++) {
    const CurveFilter &curveFilter = *itr;
    curveFilter.saveXml(writer);
  }

  writer.writeEndElement();
}

void DocumentModelFilter::setFilterMode(const QString &curveName,
                                             FilterMode filterMode)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setFilterMode(filterMode);
}

void DocumentModelFilter::setForegroundHigh (const QString &curveName,
                                             int foregroundHigh)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setForegroundHigh(foregroundHigh);
}

void DocumentModelFilter::setForegroundLow (const QString &curveName,
                                            int foregroundLow)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setForegroundLow(foregroundLow);
}

void DocumentModelFilter::setHigh (const QString &curveName,
                                   double s0To1)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setHigh(s0To1);
}

void DocumentModelFilter::setHueHigh (const QString &curveName,
                                      int hueHigh)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setHueHigh(hueHigh);
}

void DocumentModelFilter::setHueLow (const QString &curveName,
                                     int hueLow)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setHueLow(hueLow);
}

void DocumentModelFilter::setIntensityHigh (const QString &curveName,
                                            int intensityHigh)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setIntensityHigh(intensityHigh);
}

void DocumentModelFilter::setIntensityLow (const QString &curveName,
                                           int intensityLow)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setIntensityLow(intensityLow);
}

void DocumentModelFilter::setLow (const QString &curveName,
                                  double s0To1)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setLow(s0To1);
}

void DocumentModelFilter::setSaturationHigh (const QString &curveName,
                                             int saturationHigh)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setSaturationHigh(saturationHigh);
}

void DocumentModelFilter::setSaturationLow (const QString &curveName,
                                            int saturationLow)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setSaturationLow(saturationLow);
}

void DocumentModelFilter::setValueHigh (const QString &curveName,
                                        int valueHigh)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setValueHigh(valueHigh);
}

void DocumentModelFilter::setValueLow (const QString &curveName,
                                       int valueLow)
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setValueLow(valueLow);
}

int DocumentModelFilter::valueHigh (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].valueHigh();
}

int DocumentModelFilter::valueLow (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].valueLow();
}
