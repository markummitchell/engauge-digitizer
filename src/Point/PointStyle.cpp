#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "PointStyle.h"
#include <qmath.h>
#include <QTextStream>
#include <QtToString.h>
#include <QXmlStreamWriter>
#include "Xml.h"

const int DEFAULT_POINT_RADIUS = 10;
const int DEFAULT_LINE_WIDTH = 1;
const double PI = 3.1415926535;
const double TWO_PI = 2.0 * PI;

PointStyle::PointStyle ()
{
}

PointStyle::PointStyle(PointShape shape,
                       unsigned int radius,
                       int lineWidth,
                       ColorPalette paletteColor) :
  m_shape (shape),
  m_radius (radius),
  m_lineWidth (lineWidth),
  m_paletteColor (paletteColor)
{
}

PointStyle::PointStyle (const PointStyle &other) :
  m_shape (other.shape()),
  m_radius (other.radius ()),
  m_lineWidth (other.lineWidth ()),
  m_paletteColor (other.paletteColor ())
{
}

PointStyle &PointStyle::operator=(const PointStyle &other)
{
  m_shape = other.shape ();
  m_radius = other.radius ();
  m_lineWidth = other.lineWidth ();
  m_paletteColor = other.paletteColor ();

  return *this;
}

PointStyle PointStyle::defaultAxesCurve ()
{
  return PointStyle (POINT_SHAPE_CROSS,
                     DEFAULT_POINT_RADIUS,
                     DEFAULT_LINE_WIDTH,
                     COLOR_PALETTE_RED);
}

PointStyle PointStyle::defaultGraphCurve (int index)
{
  PointShape shape = POINT_SHAPE_CROSS;
  static PointShape pointShapes [] = {POINT_SHAPE_CROSS,
                                      POINT_SHAPE_X,
                                      POINT_SHAPE_DIAMOND,
                                      POINT_SHAPE_SQUARE};
  shape = pointShapes [index % 4];

  return PointStyle (shape,
                     DEFAULT_POINT_RADIUS,
                     DEFAULT_LINE_WIDTH,
                     COLOR_PALETTE_BLUE);
}

bool PointStyle::isCircle () const
{
  return m_shape == POINT_SHAPE_CIRCLE;
}

int PointStyle::lineWidth() const
{
  return m_lineWidth;
}

void PointStyle::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointStyle::loadXml";

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_RADIUS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_LINE_WIDTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_COLOR) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE)) {

    setRadius (attributes.value(DOCUMENT_SERIALIZE_POINT_STYLE_RADIUS).toInt());
    setLineWidth (attributes.value(DOCUMENT_SERIALIZE_POINT_STYLE_LINE_WIDTH).toInt());
    setPaletteColor ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_POINT_STYLE_COLOR).toInt());
    setShape ((PointShape) attributes.value(DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_POINT_STYLE)){
      loadNextFromReader(reader);
    }
  } else {
    reader.raiseError ("Cannot read point style data");
  }
}

ColorPalette PointStyle::paletteColor () const
{
  return m_paletteColor;
}

QPolygonF PointStyle::polygon () const
{
  const int NUM_XY = 60;
  QVector<QPointF> points;

  switch (m_shape) {

    case POINT_SHAPE_CIRCLE:
      {
        int xyWidth = m_radius;
        for (int i = 0; i <= NUM_XY; i++) {
          double angle = TWO_PI * (double) i / (double) NUM_XY;
          double x = xyWidth * cos (angle);
          double y = xyWidth * sin (angle);
          points.append (QPointF (x, y));
        }
      }
      break;

    case POINT_SHAPE_CROSS:
      {
        int xyWidth = m_radius;

        points.append (QPointF (-1 * xyWidth, 0));
        points.append (QPointF (xyWidth, 0));
        points.append (QPointF (0, 0));
        points.append (QPointF (0, xyWidth));
        points.append (QPointF (0, -1 * xyWidth));
        points.append (QPointF (0, 0));
      }
      break;

    case POINT_SHAPE_DIAMOND:
      {
        int xyWidth = m_radius;

        points.append (QPointF (0, -1 * xyWidth));
        points.append (QPointF (-1 * xyWidth, 0));
        points.append (QPointF (0, xyWidth));
        points.append (QPointF (xyWidth, 0));
      }
      break;

    case POINT_SHAPE_SQUARE:
      {
        int xyWidth = m_radius;

        points.append (QPointF (-1 * xyWidth, -1 * xyWidth));
        points.append (QPointF (-1 * xyWidth, xyWidth));
        points.append (QPointF (xyWidth, xyWidth));
        points.append (QPointF (xyWidth, -1 * xyWidth));
      }
      break;

    case POINT_SHAPE_TRIANGLE:
      {
        int xyWidth = m_radius;

        points.append (QPointF (-1 * xyWidth, -1 * xyWidth));
        points.append (QPointF (0, xyWidth));
        points.append (QPointF (xyWidth, -1 * xyWidth));
      }
      break;

    case POINT_SHAPE_X:
      {
        int xyWidth = m_radius * qSqrt (0.5);

        points.append (QPointF (-1 * xyWidth, -1 * xyWidth));
        points.append (QPointF (xyWidth, xyWidth));
        points.append (QPointF (0, 0));
        points.append (QPointF (-1 * xyWidth, xyWidth));
        points.append (QPointF (xyWidth, -1 * xyWidth));
        points.append (QPointF (0, 0));
      }
      break;

    default:
      ENGAUGE_ASSERT (false);
  }

  QPolygonF polygon (points);
  return polygon;
}

void PointStyle::printStream(QString indentation,
                             QTextStream &str) const
{
  str << indentation << "PointStyle\n";

  indentation += INDENTATION_DELTA;

  str << indentation << pointShapeToString (m_shape) << "\n";
  str << indentation << "radius=" << m_radius << "\n";
  str << indentation << "lineWidth=" << m_lineWidth << "\n";
  str << indentation << "color=" << colorPaletteToString (m_paletteColor) << "\n";
}

int PointStyle::radius () const
{
  return m_radius;
}

void PointStyle::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointStyle::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_STYLE);
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_RADIUS, QString::number (m_radius));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_LINE_WIDTH, QString::number (m_lineWidth));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_COLOR, QString::number (m_paletteColor));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_COLOR_STRING, colorPaletteToString (m_paletteColor));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE, QString::number (m_shape));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE_STRING, pointShapeToString (m_shape));
  writer.writeEndElement();
}

void PointStyle::setLineWidth(int width)
{
  m_lineWidth = width;
}

void PointStyle::setPaletteColor (ColorPalette paletteColor)
{
  m_paletteColor = paletteColor;
}

void PointStyle::setRadius (int radius)
{
  m_radius = radius;
}

void PointStyle::setShape (PointShape shape)
{
  m_shape = shape;
}

PointShape PointStyle::shape () const
{
  return m_shape;
}
