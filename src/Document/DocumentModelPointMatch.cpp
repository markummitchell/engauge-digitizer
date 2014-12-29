#include "CmdMediator.h"
#include "DocumentModelPointMatch.h"
#include "Logger.h"
#include <QXmlStreamWriter>

const double DEFAULT_MIN_POINT_SEPARATION = 20;
const double DEFAULT_MAX_POINT_SIZE = 20;
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
  m_minPointSeparation (document.modelPointMatch().minPointSeparation()),
  m_maxPointSize (document.modelPointMatch().maxPointSize()),
  m_paletteColorAccepted (document.modelPointMatch().paletteColorAccepted()),
  m_paletteColorCandidate (document.modelPointMatch().paletteColorCandidate()),
  m_paletteColorRejected (document.modelPointMatch().paletteColorRejected())
{
}

DocumentModelPointMatch::DocumentModelPointMatch(const DocumentModelPointMatch &other) :
  m_minPointSeparation (other.minPointSeparation()),
  m_maxPointSize (other.maxPointSize()),
  m_paletteColorAccepted (other.paletteColorAccepted()),
  m_paletteColorCandidate (other.paletteColorCandidate()),
  m_paletteColorRejected (other.paletteColorRejected())
{
}

DocumentModelPointMatch &DocumentModelPointMatch::operator=(const DocumentModelPointMatch &other)
{
  m_minPointSeparation = other.minPointSeparation();
  m_maxPointSize = other.maxPointSize();
  m_paletteColorAccepted = other.paletteColorAccepted();
  m_paletteColorCandidate = other.paletteColorCandidate();
  m_paletteColorRejected = other.paletteColorRejected();

  return *this;
}

double DocumentModelPointMatch::maxPointSize () const
{
  return m_maxPointSize;
}

double DocumentModelPointMatch::minPointSeparation() const
{
  return m_minPointSeparation;
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

void DocumentModelPointMatch::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelPointMatch::saveModel";

  stream.writeStartElement("DocumentModelPointMatch");
  stream.writeEndElement();
}

void DocumentModelPointMatch::setMaxPointSize(double maxPointSize)
{
  m_maxPointSize = maxPointSize;
}

void DocumentModelPointMatch::setMinPointSeparation(double minPointSeparation)
{
  m_minPointSeparation = minPointSeparation;
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
