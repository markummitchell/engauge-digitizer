#include "CmdMediator.h"
#include "DocumentModelAxesChecker.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QXmlStreamWriter>

const int DEFAULT_CHECKER_SECONDS = 3;

// Color that should be easily visible against black axes lines. Red resonates with
// the default axes point color, and seems fairly bright when opacity is made transparent.
const ColorPalette DEFAULT_LINE_COLOR = COLOR_PALETTE_RED;

DocumentModelAxesChecker::DocumentModelAxesChecker() :
  m_checkerMode (CHECKER_MODE_N_SECONDS),
  m_checkerSeconds (DEFAULT_CHECKER_SECONDS),
  m_lineColor (DEFAULT_LINE_COLOR)
{
}

DocumentModelAxesChecker::DocumentModelAxesChecker(const Document &document) :
  m_checkerMode (document.modelAxesChecker().checkerMode()),
  m_checkerSeconds (document.modelAxesChecker().checkerSeconds()),
  m_lineColor (document.modelAxesChecker().lineColor())
{
}

DocumentModelAxesChecker::DocumentModelAxesChecker(const DocumentModelAxesChecker &other) :
  m_checkerMode (other.checkerMode()),
  m_checkerSeconds (other.checkerSeconds()),
  m_lineColor (other.lineColor())
{
}

DocumentModelAxesChecker &DocumentModelAxesChecker::operator=(const DocumentModelAxesChecker &other)
{
  m_checkerMode = other.checkerMode();
  m_checkerSeconds = other.checkerSeconds();
  m_lineColor = other.lineColor();

  return *this;
}

CheckerMode DocumentModelAxesChecker::checkerMode() const
{
  return m_checkerMode;
}

int DocumentModelAxesChecker::checkerSeconds() const
{
  return m_checkerSeconds;
}

ColorPalette DocumentModelAxesChecker::lineColor () const
{
  return m_lineColor;
}

void DocumentModelAxesChecker::saveDocument(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelAxesChecker::saveDocument";

  stream.writeStartElement(DOCUMENT_SERIALIZE_AXES_CHECKER);
  stream.writeAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_MODE, QString::number (m_checkerMode));
  stream.writeAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_SECONDS, QString::number (m_checkerSeconds));
  stream.writeAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_LINE_COLOR, QString::number (m_lineColor));
  stream.writeEndElement();
}

void DocumentModelAxesChecker::setCheckerMode(CheckerMode checkerMode)
{
  m_checkerMode = checkerMode;
}

void DocumentModelAxesChecker::setCheckerSeconds(int seconds)
{
  m_checkerSeconds = seconds;
}

void DocumentModelAxesChecker::setLineColor (ColorPalette lineColor)
{
  m_lineColor = lineColor;
}
