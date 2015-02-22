#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "PointStyle.h"
#include <qmath.h>
#include <QXmlStreamWriter>
#include "Xml.h"

const int DEFAULT_POINT_RADIUS = 10;
const double DEFAULT_LINE_WIDTH = 1;

PointStyle::PointStyle ()
{
}

PointStyle::PointStyle(PointShape shape,
                       unsigned int radius,
                       double lineWidth,
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

double PointStyle::lineWidth() const
{
  return m_lineWidth;
}

QString PointStyle::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointStyle::loadXml";

  QString curveName;
  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_NAME) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_RADIUS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_LINE_WIDTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_COLOR) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE)) {

    curveName = attributes.value(DOCUMENT_SERIALIZE_CURVE_NAME).toString();
    setRadius (attributes.value(DOCUMENT_SERIALIZE_POINT_STYLE_RADIUS).toInt());
    setLineWidth (attributes.value(DOCUMENT_SERIALIZE_POINT_STYLE_LINE_WIDTH).toDouble());
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

  return curveName;
}

ColorPalette PointStyle::paletteColor () const
{
  return m_paletteColor;
}

QPolygonF PointStyle::polygon () const
{
  QVector<QPointF> points;

  switch (m_shape) {

    case POINT_SHAPE_CIRCLE:
      ENGAUGE_ASSERT (false);
      break;

    case POINT_SHAPE_CROSS:
      {
        int component = m_radius;

        points.append (QPointF (-1 * component, 0));
        points.append (QPointF (component, 0));
        points.append (QPointF (0, 0));
        points.append (QPointF (0, component));
        points.append (QPointF (0, -1 * component));
        points.append (QPointF (0, 0));
      }
      break;

    case POINT_SHAPE_DIAMOND:
      {
        int component = m_radius;

        points.append (QPointF (0, -1 * component));
        points.append (QPointF (-1 * component, 0));
        points.append (QPointF (0, component));
        points.append (QPointF (component, 0));
      }
      break;

    case POINT_SHAPE_SQUARE:
      {
        int component = m_radius;

        points.append (QPointF (-1 * component, -1 * component));
        points.append (QPointF (-1 * component, component));
        points.append (QPointF (component, component));
        points.append (QPointF (component, -1 * component));
      }
      break;

    case POINT_SHAPE_TRIANGLE:
      {
        int component = m_radius;

        points.append (QPointF (-1 * component, -1 * component));
        points.append (QPointF (0, component));
        points.append (QPointF (component, -1 * component));
      }
      break;

    case POINT_SHAPE_X:
      {
        int component = m_radius * qSqrt (0.5);

        points.append (QPointF (-1 * component, -1 * component));
        points.append (QPointF (component, component));
        points.append (QPointF (0, 0));
        points.append (QPointF (-1 * component, component));
        points.append (QPointF (component, -1 * component));
        points.append (QPointF (0, 0));
      }
      break;

    default:
      ENGAUGE_ASSERT (false);
  }

  QPolygonF polygon (points);
  return polygon;
}

int PointStyle::radius () const
{
  return m_radius;
}

void PointStyle::saveXml(QXmlStreamWriter &writer,
                         const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointStyle::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_STYLE);
  writer.writeAttribute (DOCUMENT_SERIALIZE_CURVE_NAME, curveName);
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_RADIUS, QString::number (m_radius));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_LINE_WIDTH, QString::number (m_lineWidth));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_COLOR, QString::number (m_paletteColor));
  writer.writeAttribute (DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE, QString::number (m_shape));
  writer.writeEndElement();
}

void PointStyle::setLineWidth(double width)
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
