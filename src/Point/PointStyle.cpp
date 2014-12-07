#include "PointStyle.h"
#include <qmath.h>
#include <QXmlStreamWriter>

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
  switch (index % 4) {
    case 0:
      shape = POINT_SHAPE_CROSS;
      break;

    case 1:
      shape = POINT_SHAPE_X;
      break;

    case 2:
      shape = POINT_SHAPE_DIAMOND;
      break;

    case 3:
      shape = POINT_SHAPE_SQUARE;
      break;

    default:
      Q_ASSERT (false);
  }

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

ColorPalette PointStyle::paletteColor () const
{
  return m_paletteColor;
}

QPolygonF PointStyle::polygon () const
{
  QVector<QPointF> points;

  switch (m_shape) {

    case POINT_SHAPE_CIRCLE:
      Q_ASSERT (false);
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
      Q_ASSERT (false);
  }

  QPolygonF polygon (points);
  return polygon;
}

int PointStyle::radius () const
{
  return m_radius;
}

void PointStyle::saveStyle(QXmlStreamWriter &stream,
                           const QString &curveName) const
{
  stream.writeStartElement("PointStyle");
  stream.writeAttribute ("Curve", curveName);
  stream.writeAttribute ("Radius", QString::number (m_radius));
  stream.writeAttribute ("Color", QString::number (m_paletteColor));
  stream.writeAttribute ("Shape", QString::number (m_shape));
  stream.writeEndElement();
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
