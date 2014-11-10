#include "MimePoints.h"

const QString FORMAT_CSV ("text/csv");
const QString FORMAT_CSV_INTERNAL ("text/engauge-points-csv"); // Custom mime type keeps points coordinates internal to engauge
const QString FORMAT_HTML ("text/html");
const QString FORMAT_PLAIN ("text/plain");

MimePoints::MimePoints ()
{
}

MimePoints::MimePoints(const QString &csvGraph,
                       const QString &htmlGraph) :
  m_csvGraph (csvGraph),
  m_htmlGraph (htmlGraph)
{
  m_formats << FORMAT_CSV << FORMAT_HTML << FORMAT_PLAIN;
}

MimePoints::MimePoints (const QString &csvPoints) :
  m_csvPoints (csvPoints)
{
  m_formats << FORMAT_CSV_INTERNAL;
}

MimePoints &MimePoints::operator=(const MimePoints &other)
{
  m_csvGraph = other.csvGraph();
  m_csvPoints = other.csvPoints();
  m_htmlGraph = other.htmlGraph();
  m_formats = other.formats();

  return *this;
}

MimePoints::~MimePoints ()
{
}

QString MimePoints::csvGraph () const
{
  return m_csvGraph;
}

QString MimePoints::csvPoints () const
{
  return m_csvPoints;
}

QStringList MimePoints::formats() const
{
  return m_formats;
}

QString MimePoints::htmlGraph () const
{
  return m_htmlGraph;
}

QVariant MimePoints::retrieveData (const QString &format,
                                   QVariant::Type /* preferredType */) const
{
  if (format == FORMAT_CSV) {
    return m_csvGraph;
  } else if (format == FORMAT_CSV_INTERNAL) {
    return m_csvPoints;
  } else if (format == FORMAT_HTML) {
    return m_htmlGraph;
  } else if (format == FORMAT_PLAIN) {
    return m_csvGraph;
  } else {
    QVariant null;
    return null;
  }
}
