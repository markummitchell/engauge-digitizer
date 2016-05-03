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

DocumentModelGridDisplay::DocumentModelGridDisplay() :
  m_initialized (false)
{
}

DocumentModelGridDisplay::DocumentModelGridDisplay(const Document &document) :
  m_initialized (document.modelGridDisplay().initialized()),
  m_xCount (document.modelGridDisplay().xCount()),
  m_xStart (document.modelGridDisplay().xStart()),
  m_xStep (document.modelGridDisplay().xStep()),
  m_xStop (document.modelGridDisplay().xStop()),
  m_yCount (document.modelGridDisplay().yCount()),
  m_yStart (document.modelGridDisplay().yStart()),
  m_yStep (document.modelGridDisplay().yStep()),
  m_yStop (document.modelGridDisplay().yStop())
{
}

DocumentModelGridDisplay::DocumentModelGridDisplay(const DocumentModelGridDisplay &other) :
  m_initialized(other.initialized()),
  m_xCount (other.xCount()),
  m_xStart (other.xStart()),
  m_xStep (other.xStep()),
  m_xStop (other.xStop()),
  m_yCount (other.yCount()),
  m_yStart (other.yStart()),
  m_yStep (other.yStep()),
  m_yStop (other.yStop())
{
}

DocumentModelGridDisplay &DocumentModelGridDisplay::operator=(const DocumentModelGridDisplay &other)
{
  m_initialized = other.initialized();
  m_xCount = other.xCount();
  m_xStart = other.xStart();
  m_xStep = other.xStep();
  m_xStop = other.xStop();
  m_yCount = other.yCount();
  m_yStart = other.yStart();
  m_yStep = other.yStep();
  m_yStop = other.yStop();

  return *this;
}

bool DocumentModelGridDisplay::initialized() const
{
  return m_initialized;
}

void DocumentModelGridDisplay::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridDisplay::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_INITIALIZED) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_Y)) {

    // Boolean value
    QString initializedValue = attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_INITIALIZED).toString();

    setInitialized (initializedValue == DOCUMENT_SERIALIZE_BOOL_TRUE);
    setXCount (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_X).toInt());
    setXDisable ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_X).toInt());
    setXStart (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_X).toDouble());
    setXStep (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_X).toDouble());
    setXStop (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_X).toDouble());
    setYCount (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_Y).toInt());
    setYDisable ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_Y).toInt());
    setYStart (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_Y).toDouble());
    setYStep (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_Y).toDouble());
    setYStop (attributes.value(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_Y).toDouble());

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

void DocumentModelGridDisplay::printStream(QString indentation,
                                           QTextStream &str) const
{
  str << indentation << "DocumentModelGridDisplay\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "initialized=" << (m_initialized ? "true" : "false") << "\n";
  str << indentation << "xDisable=" << m_xDisable << "\n";
  str << indentation << "xCount=" << m_xCount << "\n";
  str << indentation << "xStart=" << m_xStart << "\n";
  str << indentation << "xStep=" << m_xStep << "\n";
  str << indentation << "xStop=" << m_xStop << "\n";
  str << indentation << "yDisable=" << m_yDisable << "\n";
  str << indentation << "yCount=" << m_yCount << "\n";
  str << indentation << "yStart=" << m_yStart << "\n";
  str << indentation << "yStep=" << m_yStep << "\n";
  str << indentation << "yStop=" << m_yStop << "\n";
}

void DocumentModelGridDisplay::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridDisplay::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_GRID_DISPLAY);
  writer.writeStartElement(DOCUMENT_SERIALIZE_GRID_DISPLAY_INITIALIZED, m_initialized ?
                            DOCUMENT_SERIALIZE_BOOL_TRUE :
                            DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_X, QString::number (m_xDisable));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_X, QString::number (m_xCount));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_X, QString::number  (m_xStart));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_X, QString::number (m_xStep));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_X, QString::number (m_xStop));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_Y, QString::number (m_yDisable));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_Y, QString::number (m_yCount));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_START_Y, QString::number  (m_yStart));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_Y, QString::number (m_yStep));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_Y, QString::number (m_yStop));
  writer.writeEndElement();
}

void DocumentModelGridDisplay::setInitialized(bool initialized)
{
  m_initialized = initialized;
}

void DocumentModelGridDisplay::setXCount (unsigned int xCount)
{
  m_xCount = xCount;
}

void DocumentModelGridDisplay::setXDisable (GridCoordDisable xDisable)
{
  m_xDisable = xDisable;
}

void DocumentModelGridDisplay::setXStart (double xStart)
{
  m_xStart = xStart;
}

void DocumentModelGridDisplay::setXStep (double xStep)
{
  m_xStep = xStep;
}

void DocumentModelGridDisplay::setXStop (double xStop)
{
  m_xStop = xStop;
}

void DocumentModelGridDisplay::setYCount (unsigned int yCount)
{
  m_yCount = yCount;
}

void DocumentModelGridDisplay::setYDisable (GridCoordDisable yDisable)
{
  m_yDisable = yDisable;
}

void DocumentModelGridDisplay::setYStart (double yStart)
{
  m_yStart = yStart;
}

void DocumentModelGridDisplay::setYStep (double yStep)
{
  m_yStep = yStep;
}

void DocumentModelGridDisplay::setYStop (double yStop)
{
  m_yStop = yStop;
}

unsigned int DocumentModelGridDisplay::xCount () const
{
  return m_xCount;
}

GridCoordDisable DocumentModelGridDisplay::xDisable () const
{
  return m_xDisable;
}

double DocumentModelGridDisplay::xStart() const
{
  return m_xStart;
}

double DocumentModelGridDisplay::xStep() const
{
  return m_xStep;
}

double DocumentModelGridDisplay::xStop() const
{
  return m_xStop;
}

unsigned int DocumentModelGridDisplay::yCount () const
{
  return m_yCount;
}

GridCoordDisable DocumentModelGridDisplay::yDisable () const
{
  return m_yDisable;
}

double DocumentModelGridDisplay::yStart() const
{
  return m_yStart;
}

double DocumentModelGridDisplay::yStep() const
{
  return m_yStep;
}

double DocumentModelGridDisplay::yStop() const
{
  return m_yStop;
}
