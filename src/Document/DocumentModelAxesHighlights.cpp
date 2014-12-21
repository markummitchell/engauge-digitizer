#include "CmdMediator.h"
#include "DocumentModelAxesHighlights.h"
#include "Logger.h"
#include <QXmlStreamWriter>

const int DEFAULT_HIGHLIGHTS_SECONDS = 3;

DocumentModelAxesHighlights::DocumentModelAxesHighlights() :
  m_highlightsMode (HIGHLIGHTS_MODE_N_SECONDS),
  m_highlightsSeconds (DEFAULT_HIGHLIGHTS_SECONDS),
  m_lineColor (COLOR_PALETTE_YELLOW) // Bright color that should be easily visible against black axes lines
{
}

DocumentModelAxesHighlights::DocumentModelAxesHighlights(const Document &document) :
  m_highlightsMode (document.modelAxesHighlights().highlightsMode()),
  m_highlightsSeconds (document.modelAxesHighlights().highlightsSeconds()),
  m_lineColor (document.modelAxesHighlights().lineColor())
{
}

DocumentModelAxesHighlights::DocumentModelAxesHighlights(const DocumentModelAxesHighlights &other) :
  m_highlightsMode (other.highlightsMode()),
  m_highlightsSeconds (other.highlightsSeconds()),
  m_lineColor (other.lineColor())
{
}

DocumentModelAxesHighlights &DocumentModelAxesHighlights::operator=(const DocumentModelAxesHighlights &other)
{
  m_highlightsMode = other.highlightsMode();
  m_highlightsSeconds = other.highlightsSeconds();
  m_lineColor = other.lineColor();

  return *this;
}

HighlightsMode DocumentModelAxesHighlights::highlightsMode() const
{
  return m_highlightsMode;
}

int DocumentModelAxesHighlights::highlightsSeconds() const
{
  return m_highlightsSeconds;
}

ColorPalette DocumentModelAxesHighlights::lineColor () const
{
  return m_lineColor;
}

void DocumentModelAxesHighlights::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelAxesHighlights::saveModel";

  stream.writeStartElement("DocumentModelAxesHighlights");
  stream.writeEndElement();
}

void DocumentModelAxesHighlights::setHighlightsMode(HighlightsMode highlightsMode)
{
  m_highlightsMode = highlightsMode;
}

void DocumentModelAxesHighlights::setHighlightsSeconds(int seconds)
{
  m_highlightsSeconds = seconds;
}

void DocumentModelAxesHighlights::setLineColor (ColorPalette lineColor)
{
  m_lineColor = lineColor;
}
