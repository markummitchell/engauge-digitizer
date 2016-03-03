/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "PointStyle.h"
#include <qmath.h>
#include <QObject>
#include <QSettings>
#include <QTextStream>
#include <QtToString.h>
#include <QXmlStreamWriter>
#include "Settings.h"
#include "SettingsForGraph.h"
#include "Xml.h"

const ColorPalette DEFAULT_POINT_COLOR_AXES = COLOR_PALETTE_RED;
const ColorPalette DEFAULT_POINT_COLOR_GRAPH = COLOR_PALETTE_BLUE;
const int DEFAULT_POINT_LINE_WIDTH = 1;
const int DEFAULT_POINT_RADIUS = 10;
const PointShape DEFAULT_POINT_SHAPE_AXIS = POINT_SHAPE_CROSS;
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
  // Get settings if available, otherwise use defaults
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (SETTINGS_GROUP_CURVE_AXES);
  PointShape shape = (PointShape) settings.value (SETTINGS_CURVE_POINT_SHAPE,
                                                  DEFAULT_POINT_SHAPE_AXIS).toInt();
  int radius = settings.value (SETTINGS_CURVE_POINT_RADIUS,
                               DEFAULT_POINT_RADIUS).toInt();
  int pointLineWidth = settings.value (SETTINGS_CURVE_POINT_LINE_WIDTH,
                                       DEFAULT_POINT_LINE_WIDTH).toInt();
  ColorPalette pointColor = (ColorPalette) settings.value (SETTINGS_CURVE_POINT_COLOR,
                                                           DEFAULT_POINT_COLOR_AXES).toInt();
  settings.endGroup ();

  return PointStyle (shape,
                     radius,
                     pointLineWidth,
                     pointColor);
}

PointStyle PointStyle::defaultGraphCurve (int index)
{
  // Shape is always computed on the fly
  PointShape shape = POINT_SHAPE_CROSS;
  static PointShape pointShapes [] = {POINT_SHAPE_CROSS,
                                      POINT_SHAPE_X,
                                      POINT_SHAPE_DIAMOND,
                                      POINT_SHAPE_SQUARE};
  shape = pointShapes [index % 4];

  SettingsForGraph settingsForGraph;
  int indexOneBased = index + 1;
  QString groupName = settingsForGraph.groupNameForNthCurve (indexOneBased);

  // Get settings if available, otherwise use defaults
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (groupName);
  int radius = settings.value (SETTINGS_CURVE_POINT_RADIUS,
                               DEFAULT_POINT_RADIUS).toInt();
  int pointLineWidth = settings.value (SETTINGS_CURVE_POINT_LINE_WIDTH,
                                       DEFAULT_POINT_LINE_WIDTH).toInt();
  ColorPalette pointColor = (ColorPalette) settings.value (SETTINGS_CURVE_POINT_COLOR,
                                                           DEFAULT_POINT_COLOR_GRAPH).toInt();
  settings.endGroup ();

  return PointStyle (shape,
                     radius,
                     pointLineWidth,
                     pointColor);
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
    reader.raiseError (QObject::tr ("Cannot read point style data"));
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
