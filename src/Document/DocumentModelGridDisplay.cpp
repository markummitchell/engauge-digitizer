/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DocumentModelGridDisplay.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QObject>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamWriter>
#include "Xml.h"

const ColorPalette DEFAULT_COLOR = COLOR_PALETTE_BLACK;

DocumentModelGridDisplay::DocumentModelGridDisplay() :
  m_stable (false),
  m_disableX (GRID_COORD_DISABLE_COUNT),
  m_countX (2),
  m_startX (0.0),
  m_stepX (1.0),
  m_stopX (1.0),
  m_disableY (GRID_COORD_DISABLE_COUNT),
  m_countY (2),
  m_startY (0.0),
  m_stepY (1.0),
  m_stopY (1.0),
  m_paletteColor (DEFAULT_COLOR)
{
}

DocumentModelGridDisplay::DocumentModelGridDisplay(const Document &document) :
  m_stable (document.modelGridDisplay().stable()),
  m_disableX (document.modelGridDisplay().disableX()),
  m_countX (document.modelGridDisplay().countX()),
  m_startX (document.modelGridDisplay().startX()),
  m_stepX (document.modelGridDisplay().stepX()),
  m_stopX (document.modelGridDisplay().stopX()),
  m_disableY (document.modelGridDisplay().disableY()),
  m_countY (document.modelGridDisplay().countY()),
  m_startY (document.modelGridDisplay().startY()),
  m_stepY (document.modelGridDisplay().stepY()),
  m_stopY (document.modelGridDisplay().stopY()),
  m_paletteColor (document.modelGridDisplay().paletteColor())
{
}

DocumentModelGridDisplay::DocumentModelGridDisplay(const DocumentModelGridDisplay &other) :
  m_stable(other.stable()),
  m_disableX (other.disableX()),
  m_countX (other.countX()),
  m_startX (other.startX()),
  m_stepX (other.stepX()),
  m_stopX (other.stopX()),
  m_disableY (other.disableY()),
  m_countY (other.countY()),
  m_startY (other.startY()),
  m_stepY (other.stepY()),
  m_stopY (other.stopY()),
  m_paletteColor (other.paletteColor())
{
}

DocumentModelGridDisplay &DocumentModelGridDisplay::operator=(const DocumentModelGridDisplay &other)
{
  m_stable = other.stable();
  m_disableX = other.disableX();
  m_countX = other.countX();
  m_startX = other.startX();
  m_stepX = other.stepX();
  m_stopX = other.stopX();
  m_disableY = other.disableY();
  m_countY = other.countY();
  m_startY = other.startY();
  m_stepY = other.stepY();
  m_stopY = other.stopY();
  m_paletteColor = other.paletteColor();

  return *this;
}

unsigned int DocumentModelGridDisplay::countX () const
{
  return m_countX;
}

unsigned int DocumentModelGridDisplay::countY () const
{
  return m_countY;
}

GridCoordDisable DocumentModelGridDisplay::disableX () const
{
  return m_disableX;
}

GridCoordDisable DocumentModelGridDisplay::disableY () const
{
  return m_disableY;
}

void DocumentModelGridDisplay::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridDisplay::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STABLE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COLOR)) {

    // Boolean values
    QString stableValue = attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STABLE).toString();

    setStable (stableValue == DOCUMENT_SERIALIZE_BOOL_TRUE);
    setDisableX (static_cast<GridCoordDisable> (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_X).toInt()));
    setCountX (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_X).toUInt());
    setStartX (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_X).toDouble());
    setStepX (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_X).toDouble());
    setStopX (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_X).toDouble());
    setDisableY (static_cast<GridCoordDisable> (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_Y).toUInt()));
    setCountY (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_Y).toUInt());
    setStartY (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_Y).toDouble());
    setStepY (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_Y).toDouble());
    setStopY (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_Y).toDouble());
    setPaletteColor (static_cast<ColorPalette> (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_COLOR).toInt()));

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_GRID_DISPLAY)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read grid display data"));
  }
}

ColorPalette DocumentModelGridDisplay::paletteColor() const
{
  return m_paletteColor;
}

void DocumentModelGridDisplay::printStream(QString indentation,
                                           QTextStream &str) const
{
  str << indentation << "DocumentModelGridDisplay\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "stable=" << (m_stable ? "true" : "false") << "\n";
  str << indentation << "disableX=" << m_disableX << "\n";
  str << indentation << "countX=" << m_countX << "\n";
  str << indentation << "startX=" << m_startX << "\n";
  str << indentation << "stepX=" << m_stepX << "\n";
  str << indentation << "stopX=" << m_stopX << "\n";
  str << indentation << "disableY=" << m_disableY << "\n";
  str << indentation << "countY=" << m_countY << "\n";
  str << indentation << "startY=" << m_startY << "\n";
  str << indentation << "stepY=" << m_stepY << "\n";
  str << indentation << "stopY=" << m_stopY << "\n";
  str << indentation << "color=" << colorPaletteToString (m_paletteColor) << "\n";
}

void DocumentModelGridDisplay::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridDisplay::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_GRID_DISPLAY);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STABLE, m_stable ?
                            DOCUMENT_SERIALIZE_BOOL_TRUE :
                            DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_X, QString::number (m_disableX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_X, QString::number (m_countX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_X, QString::number  (m_startX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_X, QString::number (m_stepX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_X, QString::number (m_stopX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_Y, QString::number (m_disableY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_Y, QString::number (m_countY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_Y, QString::number  (m_startY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_Y, QString::number (m_stepY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_Y, QString::number (m_stopY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COLOR, QString::number (m_paletteColor));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COLOR_STRING, colorPaletteToString (m_paletteColor));
  writer.writeEndElement();
}

void DocumentModelGridDisplay::setCountX (unsigned int countX)
{
  m_countX = countX;
}

void DocumentModelGridDisplay::setCountY (unsigned int countY)
{
  m_countY = countY;
}

void DocumentModelGridDisplay::setDisableX (GridCoordDisable disableX)
{
  m_disableX = disableX;
}

void DocumentModelGridDisplay::setDisableY (GridCoordDisable disableY)
{
  m_disableY = disableY;
}

void DocumentModelGridDisplay::setPaletteColor(ColorPalette paletteColor)
{
  m_paletteColor = paletteColor;
}

void DocumentModelGridDisplay::setStable(bool stable)
{
  m_stable = stable;
}

void DocumentModelGridDisplay::setStartX (double startX)
{
  m_startX = startX;
}

void DocumentModelGridDisplay::setStartY (double startY)
{
  m_startY = startY;
}

void DocumentModelGridDisplay::setStepX (double stepX)
{
  m_stepX = stepX;
}

void DocumentModelGridDisplay::setStepY (double stepY)
{
  m_stepY = stepY;
}

void DocumentModelGridDisplay::setStopX (double stopX)
{
  m_stopX = stopX;
}

void DocumentModelGridDisplay::setStopY (double stopY)
{
  m_stopY = stopY;
}

bool DocumentModelGridDisplay::stable() const
{
  return m_stable;
}

double DocumentModelGridDisplay::startX() const
{
  return m_startX;
}

double DocumentModelGridDisplay::startY() const
{
  return m_startY;
}

double DocumentModelGridDisplay::stepX() const
{
  return m_stepX;
}

double DocumentModelGridDisplay::stepY() const
{
  return m_stepY;
}

double DocumentModelGridDisplay::stopX() const
{
  return m_stopX;
}

double DocumentModelGridDisplay::stopY() const
{
  return m_stopY;
}
