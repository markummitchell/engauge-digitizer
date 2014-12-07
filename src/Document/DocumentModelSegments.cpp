#include "CmdMediator.h"
#include "DocumentModelSegments.h"
#include "Logger.h"
#include <QXmlStreamWriter>

const double DEFAULT_POINT_SEPARATION = 1;
const double DEFAULT_MIN_LENGTH = 5;
const double DEFAULT_LINE_WIDTH = 1;
const ColorPalette DEFAULT_LINE_COLOR (COLOR_PALETTE_GREEN);

DocumentModelSegments::DocumentModelSegments() :
  m_pointSeparation (DEFAULT_POINT_SEPARATION),
  m_minLength (DEFAULT_MIN_LENGTH),
  m_fillCorners (false),
  m_lineWidth (DEFAULT_LINE_WIDTH),
  m_lineColor (DEFAULT_LINE_COLOR)
{
}

DocumentModelSegments::DocumentModelSegments(const Document &document) :
  m_pointSeparation (document.modelSegments().pointSeparation()),
  m_minLength (document.modelSegments().minLength()),
  m_fillCorners (document.modelSegments().fillCorners()),
  m_lineWidth (document.modelSegments().lineWidth()),
  m_lineColor (document.modelSegments().lineColor())
{
}

DocumentModelSegments::DocumentModelSegments(const DocumentModelSegments &other) :
  m_pointSeparation (other.pointSeparation()),
  m_minLength (other.minLength()),
  m_fillCorners (other.fillCorners ()),
  m_lineWidth (other.lineWidth()),
  m_lineColor (other.lineColor())
{
}

DocumentModelSegments &DocumentModelSegments::operator=(const DocumentModelSegments &other)
{
  m_pointSeparation = other.pointSeparation();
  m_minLength = other.minLength();
  m_fillCorners = other.fillCorners ();
  m_lineWidth = other.lineWidth();
  m_lineColor = other.lineColor();

  return *this;
}

bool DocumentModelSegments::fillCorners () const
{
  return m_fillCorners;
}

ColorPalette DocumentModelSegments::lineColor() const
{
  return m_lineColor;
}

double DocumentModelSegments::lineWidth() const
{
  return m_lineWidth;
}

double DocumentModelSegments::minLength() const
{
  return m_minLength;
}

double DocumentModelSegments::pointSeparation() const
{
  return m_pointSeparation;
}

void DocumentModelSegments::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelSegments::saveModel";

  stream.writeStartElement("DocumentModelSegments");
  stream.writeEndElement();
}

void DocumentModelSegments::setFillCorners (bool fillCorners)
{
  m_fillCorners = fillCorners;
}

void DocumentModelSegments::setLineColor(ColorPalette lineColor)
{
  m_lineColor = lineColor;
}

void DocumentModelSegments::setLineWidth(double lineWidth)
{
  m_lineWidth = lineWidth;
}

void DocumentModelSegments::setMinLength(double minLength)
{
  m_minLength = minLength;
}

void DocumentModelSegments::setPointSeparation(double pointSeparation)
{
  m_pointSeparation = pointSeparation;
}
