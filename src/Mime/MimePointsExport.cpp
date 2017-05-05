/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "MimePointsExport.h"

const QString FORMAT_CSV ("text/csv");
const QString FORMAT_CSV_INTERNAL ("text/engauge-points-csv"); // Custom mime type keeps points coordinates internal to engauge
const QString FORMAT_HTML ("text/html");
const QString FORMAT_PLAIN ("text/plain");

MimePointsExport::MimePointsExport ()
{
}

MimePointsExport::MimePointsExport(const QString &csvGraph,
                                   const QString &htmlGraph) :
  m_csvGraph (csvGraph),
  m_htmlGraph (htmlGraph)
{
  m_formats << FORMAT_CSV << FORMAT_HTML << FORMAT_PLAIN;
}

MimePointsExport::MimePointsExport (const QString &csvPoints) :
  m_csvPoints (csvPoints)
{
  m_formats << FORMAT_CSV_INTERNAL;
}

MimePointsExport &MimePointsExport::operator=(const MimePointsExport &other)
{
  m_csvGraph = other.csvGraph();
  m_csvPoints = other.csvPoints();
  m_htmlGraph = other.htmlGraph();
  m_formats = other.formats();

  return *this;
}

MimePointsExport::~MimePointsExport ()
{
}

QString MimePointsExport::csvGraph () const
{
  return m_csvGraph;
}

QString MimePointsExport::csvPoints () const
{
  return m_csvPoints;
}

QStringList MimePointsExport::formats() const
{
  return m_formats;
}

QString MimePointsExport::htmlGraph () const
{
  return m_htmlGraph;
}

QVariant MimePointsExport::retrieveData (const QString &format,
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
