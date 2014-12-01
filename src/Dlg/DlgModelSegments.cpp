#include "CmdMediator.h"
#include "DlgModelSegments.h"
#include "Logger.h"
#include <QXmlStreamWriter>

const double DEFAULT_POINT_SEPARATION = 1;
const double DEFAULT_MIN_LENGTH = 5;
const double DEFAULT_LINE_SIZE = 1;
const ColorPalette DEFAULT_LINE_COLOR (COLOR_PALETTE_GREEN);

DlgModelSegments::DlgModelSegments() :
  m_pointSeparation (DEFAULT_POINT_SEPARATION),
  m_minLength (DEFAULT_MIN_LENGTH),
  m_fillCorners (false),
  m_lineSize (DEFAULT_LINE_SIZE),
  m_lineColor (DEFAULT_LINE_COLOR)
{
}

DlgModelSegments::DlgModelSegments(const CmdMediator &cmdMediator) :
  m_pointSeparation (cmdMediator.document().modelSegments().pointSeparation()),
  m_minLength (cmdMediator.document().modelSegments().minLength()),
  m_fillCorners (cmdMediator.document().modelSegments().fillCorners()),
  m_lineSize (cmdMediator.document().modelSegments().lineSize()),
  m_lineColor (cmdMediator.document().modelSegments().lineColor())
{
}

DlgModelSegments::DlgModelSegments(const DlgModelSegments &other) :
  m_pointSeparation (other.pointSeparation()),
  m_minLength (other.minLength()),
  m_fillCorners (other.fillCorners ()),
  m_lineSize (other.lineSize()),
  m_lineColor (other.lineColor())
{
}

DlgModelSegments &DlgModelSegments::operator=(const DlgModelSegments &other)
{
  m_pointSeparation = other.pointSeparation();
  m_minLength = other.minLength();
  m_fillCorners = other.fillCorners ();
  m_lineSize = other.lineSize();
  m_lineColor = other.lineColor();

  return *this;
}

bool DlgModelSegments::fillCorners () const
{
  return m_fillCorners;
}

ColorPalette DlgModelSegments::lineColor() const
{
  return m_lineColor;
}

double DlgModelSegments::lineSize() const
{
  return m_lineSize;
}

double DlgModelSegments::minLength() const
{
  return m_minLength;
}

double DlgModelSegments::pointSeparation() const
{
  return m_pointSeparation;
}

void DlgModelSegments::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgModelSegments::saveModel";

  stream.writeStartElement("DlgModelSegments");
  stream.writeEndElement();
}

void DlgModelSegments::setFillCorners (bool fillCorners)
{
  m_fillCorners = fillCorners;
}

void DlgModelSegments::setLineColor(ColorPalette lineColor)
{
  m_lineColor = lineColor;
}

void DlgModelSegments::setLineSize(double lineSize)
{
  m_lineSize = lineSize;
}

void DlgModelSegments::setMinLength(double minLength)
{
  m_minLength = minLength;
}

void DlgModelSegments::setPointSeparation(double pointSeparation)
{
  m_pointSeparation = pointSeparation;
}
