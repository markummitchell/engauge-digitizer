#include "CmdMediator.h"
#include "DocumentModelAxesHighlight.h"
#include "Logger.h"
#include <QXmlStreamWriter>

DocumentModelAxesHighlight::DocumentModelAxesHighlight() :
  m_axesHighlight (AXES_HIGHLIGHT_10_SECONDS)
{
}

DocumentModelAxesHighlight::DocumentModelAxesHighlight(const Document &document) :
  m_axesHighlight (document.modelAxesHighlight().axesHighlight())
{
}

DocumentModelAxesHighlight::DocumentModelAxesHighlight(const DocumentModelAxesHighlight &other) :
  m_axesHighlight (other.axesHighlight())
{
}

DocumentModelAxesHighlight &DocumentModelAxesHighlight::operator=(const DocumentModelAxesHighlight &other)
{
  m_axesHighlight = other.axesHighlight();

  return *this;
}

AxesHighlight DocumentModelAxesHighlight::axesHighlight() const
{
  return m_axesHighlight;
}

void DocumentModelAxesHighlight::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelAxesHighlight::saveModel";

  stream.writeStartElement("DocumentModelAxesHighlight");
  stream.writeEndElement();
}

void DocumentModelAxesHighlight::setAxesHighlight(AxesHighlight axesHighlight)
{
  m_axesHighlight = axesHighlight;
}
