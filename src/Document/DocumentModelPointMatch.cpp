#include "CmdMediator.h"
#include "DocumentModelPointMatch.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

const double DEFAULT_MIN_POINT_SEPARATION = 20;
const double DEFAULT_MAX_POINT_SIZE = 48;
const ColorPalette DEFAULT_COLOR_ACCEPTED = COLOR_PALETTE_GREEN;
const ColorPalette DEFAULT_COLOR_CANDIDATE = COLOR_PALETTE_YELLOW;
const ColorPalette DEFAULT_COLOR_REJECTED = COLOR_PALETTE_RED;

DocumentModelPointMatch::DocumentModelPointMatch() :
  m_minPointSeparation (DEFAULT_MIN_POINT_SEPARATION),
  m_maxPointSize (DEFAULT_MAX_POINT_SIZE),
  m_paletteColorAccepted (DEFAULT_COLOR_ACCEPTED),
  m_paletteColorCandidate (DEFAULT_COLOR_CANDIDATE),
  m_paletteColorRejected (DEFAULT_COLOR_REJECTED)
{
}

DocumentModelPointMatch::DocumentModelPointMatch(const Document &document) :
  m_maxPointSize (document.modelPointMatch().maxPointSize()),
  m_paletteColorAccepted (document.modelPointMatch().paletteColorAccepted()),
  m_paletteColorCandidate (document.modelPointMatch().paletteColorCandidate()),
  m_paletteColorRejected (document.modelPointMatch().paletteColorRejected())
{
}

DocumentModelPointMatch::DocumentModelPointMatch(const DocumentModelPointMatch &other) :
  m_maxPointSize (other.maxPointSize()),
  m_paletteColorAccepted (other.paletteColorAccepted()),
  m_paletteColorCandidate (other.paletteColorCandidate()),
  m_paletteColorRejected (other.paletteColorRejected())
{
}

DocumentModelPointMatch &DocumentModelPointMatch::operator=(const DocumentModelPointMatch &other)
{
  m_maxPointSize = other.maxPointSize();
  m_paletteColorAccepted = other.paletteColorAccepted();
  m_paletteColorCandidate = other.paletteColorCandidate();
  m_paletteColorRejected = other.paletteColorRejected();

  return *this;
}

void DocumentModelPointMatch::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelPointMatch::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SIZE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED)) {

    setMaxPointSize (attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SIZE).toDouble());
    setPaletteColorAccepted ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED).toInt());
    setPaletteColorCandidate ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE).toInt());
    setPaletteColorRejected ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_POINT_MATCH)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read point match data");
  }
}

double DocumentModelPointMatch::maxPointSize () const
{
  return m_maxPointSize;
}

ColorPalette DocumentModelPointMatch::paletteColorAccepted() const
{
  return m_paletteColorAccepted;
}

ColorPalette DocumentModelPointMatch::paletteColorCandidate() const
{
  return  m_paletteColorCandidate;
}

ColorPalette DocumentModelPointMatch::paletteColorRejected() const
{
  return m_paletteColorRejected;
}

void DocumentModelPointMatch::printStream(QString indentation,
                                          QTextStream &str) const
{
  str << indentation << "DocumentModelPointMatch\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "minPointSeparation=" << m_minPointSeparation << "\n";
  str << indentation << "maxPointSize=" << m_maxPointSize << "\n";
  str << indentation << "colorAccepted=" << colorPaletteToString (m_paletteColorAccepted) << "\n";
  str << indentation << "colorCandidate=" << colorPaletteToString (m_paletteColorCandidate) << "\n";
  str << indentation << "colorRejected=" << colorPaletteToString (m_paletteColorRejected) << "\n";
}

void DocumentModelPointMatch::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelPointMatch::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_MATCH);
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SIZE, QString::number (m_maxPointSize));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED, QString::number (m_paletteColorAccepted));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED_STRING, colorPaletteToString (m_paletteColorAccepted));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE, QString::number (m_paletteColorCandidate));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE_STRING, colorPaletteToString (m_paletteColorCandidate));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED, QString::number (m_paletteColorRejected));
  writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED_STRING, colorPaletteToString (m_paletteColorRejected));
  writer.writeEndElement();
}

void DocumentModelPointMatch::setMaxPointSize(double maxPointSize)
{
  m_maxPointSize = maxPointSize;
}

void DocumentModelPointMatch::setPaletteColorAccepted(ColorPalette paletteColorAccepted)
{
  m_paletteColorAccepted = paletteColorAccepted;
}

void DocumentModelPointMatch::setPaletteColorCandidate(ColorPalette paletteColorCandidate)
{
  m_paletteColorCandidate = paletteColorCandidate;
}

void DocumentModelPointMatch::setPaletteColorRejected(ColorPalette paletteColorRejected)
{
  m_paletteColorRejected = paletteColorRejected;
}
