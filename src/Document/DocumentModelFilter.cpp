#include "CmdMediator.h"
#include "DocumentModelFilter.h"
#include "Logger.h"
#include <QXmlStreamWriter>

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

const CurveFilters &DocumentModelFilter::curveFilters() const
{
  return m_curveFilters;
}

FilterParameter DocumentModelFilter::filterParameter(const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].filterParameter();
}

int DocumentModelFilter::foregroundHigh (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].foregroundHigh();
}

int DocumentModelFilter::foregroundLow (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].foregroundLow();
}

double DocumentModelFilter::high (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].high();
}

int DocumentModelFilter::hueHigh (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].hueHigh();
}

int DocumentModelFilter::hueLow (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].hueLow();
}

int DocumentModelFilter::intensityHigh (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].intensityHigh();
}

int DocumentModelFilter::intensityLow (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].intensityLow();
}

double DocumentModelFilter::low (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].low();
}

int DocumentModelFilter::saturationHigh (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].saturationHigh();
}

int DocumentModelFilter::saturationLow (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].saturationLow();
}

void DocumentModelFilter::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelFilter::saveModel";

  stream.writeStartElement("DocumentModelFilter");
  stream.writeEndElement();
}

void DocumentModelFilter::setFilterParameter(const QString &curveName,
                                             FilterParameter filterParameter)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setFilterParameter(filterParameter);
}

void DocumentModelFilter::setForegroundHigh (const QString &curveName,
                                             int foregroundHigh)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setForegroundHigh(foregroundHigh);
}

void DocumentModelFilter::setForegroundLow (const QString &curveName,
                                            int foregroundLow)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setForegroundLow(foregroundLow);
}

void DocumentModelFilter::setHigh (const QString &curveName,
                                   double s0To1)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setHigh(s0To1);
}

void DocumentModelFilter::setHueHigh (const QString &curveName,
                                      int hueHigh)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setHueHigh(hueHigh);
}

void DocumentModelFilter::setHueLow (const QString &curveName,
                                     int hueLow)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setHueLow(hueLow);
}

void DocumentModelFilter::setIntensityHigh (const QString &curveName,
                                            int intensityHigh)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setIntensityHigh(intensityHigh);
}

void DocumentModelFilter::setIntensityLow (const QString &curveName,
                                           int intensityLow)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setIntensityLow(intensityLow);
}

void DocumentModelFilter::setLow (const QString &curveName,
                                  double s0To1)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setLow(s0To1);
}

void DocumentModelFilter::setSaturationHigh (const QString &curveName,
                                             int saturationHigh)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setSaturationHigh(saturationHigh);
}

void DocumentModelFilter::setSaturationLow (const QString &curveName,
                                            int saturationLow)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setSaturationLow(saturationLow);
}

void DocumentModelFilter::setValueHigh (const QString &curveName,
                                        int valueHigh)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setValueHigh(valueHigh);
}

void DocumentModelFilter::setValueLow (const QString &curveName,
                                       int valueLow)
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  m_curveFilters [curveName].setValueLow(valueLow);
}

int DocumentModelFilter::valueHigh (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].valueHigh();
}

int DocumentModelFilter::valueLow (const QString &curveName) const
{
  Q_ASSERT (m_curveFilters.contains (curveName));
  return m_curveFilters [curveName].valueLow();
}
