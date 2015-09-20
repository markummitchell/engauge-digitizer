#include "CmdMediator.h"
#include "DocumentModelGridRemoval.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

const double CLOSE_DISTANCE_DEFAULT = 1.0;

// These defaults should always be overwritten when Document coordinates are defined
const int DEFAULT_COUNT = 2;
const double DEFAULT_NON_COUNT = 0.0;

DocumentModelGridRemoval::DocumentModelGridRemoval() :
  m_removeDefinedGridLines (false),
  m_closeDistance (CLOSE_DISTANCE_DEFAULT),
  m_gridCoordDisableX (GRID_COORD_DISABLE_COUNT),
  m_countX (DEFAULT_COUNT),
  m_startX (DEFAULT_NON_COUNT),
  m_stepX (DEFAULT_NON_COUNT),
  m_stopX (DEFAULT_NON_COUNT),
  m_gridCoordDisableY (GRID_COORD_DISABLE_COUNT),
  m_countY (DEFAULT_COUNT),
  m_startY (DEFAULT_NON_COUNT),
  m_stepY (DEFAULT_NON_COUNT),
  m_stopY (DEFAULT_NON_COUNT),
  m_removeParallelToAxes (false)
{
}

DocumentModelGridRemoval::DocumentModelGridRemoval (double startX,
                                                    double startY,
                                                    double stepX,
                                                    double stepY,
                                                    int countX,
                                                    int countY) :
  m_removeDefinedGridLines (false),
  m_closeDistance (CLOSE_DISTANCE_DEFAULT),
  m_gridCoordDisableX (GRID_COORD_DISABLE_COUNT),
  m_countX (countX),
  m_startX (startX),
  m_stepX (stepX),
  m_stopX (startX + (countX - 1.0) * stepX),
  m_gridCoordDisableY (GRID_COORD_DISABLE_COUNT),
  m_countY (countY),
  m_startY (startY),
  m_stepY (stepY),
  m_stopY (startY + (countY - 1.0) * stepY)
{
}

DocumentModelGridRemoval::DocumentModelGridRemoval(const Document &document) :
  m_removeDefinedGridLines (document.modelGridRemoval().removeDefinedGridLines()),
  m_closeDistance (document.modelGridRemoval().closeDistance()),
  m_gridCoordDisableX (document.modelGridRemoval().gridCoordDisableX()),
  m_countX (document.modelGridRemoval().countX()),
  m_startX (document.modelGridRemoval().startX()),
  m_stepX (document.modelGridRemoval().stepX()),
  m_stopX (document.modelGridRemoval().stopX()),
  m_gridCoordDisableY (document.modelGridRemoval().gridCoordDisableY()),
  m_countY (document.modelGridRemoval().countY()),
  m_startY (document.modelGridRemoval().startY()),
  m_stepY (document.modelGridRemoval().stepY()),
  m_stopY (document.modelGridRemoval().stopY()),
  m_removeParallelToAxes (document.modelGridRemoval().removeParallelToAxes())
{
}

DocumentModelGridRemoval::DocumentModelGridRemoval(const DocumentModelGridRemoval &other) :
  m_removeDefinedGridLines (other.removeDefinedGridLines()),
  m_closeDistance (other.closeDistance()),
  m_gridCoordDisableX (other.gridCoordDisableX()),
  m_countX (other.countX()),
  m_startX (other.startX()),
  m_stepX (other.stepX()),
  m_stopX (other.stopX()),
  m_gridCoordDisableY (other.gridCoordDisableX()),
  m_countY (other.countY()),
  m_startY (other.startY()),
  m_stepY (other.stepY()),
  m_stopY (other.stopY()),
  m_removeParallelToAxes (other.removeParallelToAxes())
{
}

DocumentModelGridRemoval &DocumentModelGridRemoval::operator=(const DocumentModelGridRemoval &other)
{
  m_removeDefinedGridLines = other.removeDefinedGridLines();
  m_closeDistance = other.closeDistance();
  m_gridCoordDisableX = other.gridCoordDisableX();
  m_countX = other.countX();
  m_startX = other.startX();
  m_stepX = other.stepX();
  m_stopX = other.stopX();
  m_gridCoordDisableY = other.gridCoordDisableY();
  m_countY = other.countY();
  m_startY = other.startY();
  m_stepY = other.stepY();
  m_stopY = other.stopY();
  m_removeParallelToAxes = other.removeParallelToAxes();

  return *this;
}

double DocumentModelGridRemoval::closeDistance() const
{
  return m_closeDistance;
}

int DocumentModelGridRemoval::countX() const
{
  return m_countX;
}

int DocumentModelGridRemoval::countY() const
{
  return m_countY;
}

GridCoordDisable DocumentModelGridRemoval::gridCoordDisableX () const
{
  return m_gridCoordDisableX;
}

GridCoordDisable DocumentModelGridRemoval::gridCoordDisableY () const
{
  return m_gridCoordDisableY;
}

void DocumentModelGridRemoval::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridRemoval::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_DEFINED_GRID_LINES) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_CLOSE_DISTANCE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_REMOVE_PARALLEL_TO_AXES)) {

    // Boolean values
    QString definedValue = attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_DEFINED_GRID_LINES).toString();
    QString parallelValue = attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_REMOVE_PARALLEL_TO_AXES).toString();

    setRemoveDefinedGridLines (definedValue == DOCUMENT_SERIALIZE_BOOL_TRUE);
    setCloseDistance (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_CLOSE_DISTANCE).toDouble());
    setGridCoordDisableX ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X).toInt());
    setCountX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_X).toInt());
    setStartX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_X).toDouble());
    setStepX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_X).toDouble());
    setStopX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_X).toDouble());
    setGridCoordDisableY ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y).toInt());
    setCountY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_Y).toInt());
    setStartY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_Y).toDouble());
    setStepY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_Y).toDouble());
    setStopY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_Y).toDouble());
    setRemoveParallelToAxes (parallelValue == DOCUMENT_SERIALIZE_BOOL_TRUE);

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_GRID_REMOVAL)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read grid removal data");
  }
}

void DocumentModelGridRemoval::printStream(QString indentation,
                                           QTextStream &str) const
{
  str << indentation << "DocumentModelGridRemoval\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "removeDefinedGridLines=" << (m_removeDefinedGridLines ? "true" : "false") << "\n";
  str << indentation << "closeDistance=" << m_closeDistance << "\n";
  str << indentation << "gridCoordDisableX=" << gridCoordDisableToString (m_gridCoordDisableX) << "\n";
  str << indentation << "countX=" << m_countX << "\n";
  str << indentation << "startX=" << m_startX << "\n";
  str << indentation << "stepX=" << m_stepX << "\n";
  str << indentation << "stopX=" << m_stopX << "\n";
  str << indentation << "gridCoordDisableY=" << gridCoordDisableToString (m_gridCoordDisableY) << "\n";
  str << indentation << "countY=" << m_countY << "\n";
  str << indentation << "startY=" << m_startY << "\n";
  str << indentation << "stepY=" << m_stepY << "\n";
  str << indentation << "stopY=" << m_stopY << "\n";
  str << indentation << "removeParallelToAxes=" << (m_removeParallelToAxes ? "true" : "false") << "\n";
}

bool DocumentModelGridRemoval::removeDefinedGridLines () const
{
  return m_removeDefinedGridLines;
}

bool DocumentModelGridRemoval::removeParallelToAxes () const
{
  return m_removeParallelToAxes;
}

void DocumentModelGridRemoval::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridRemoval::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_GRID_REMOVAL);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_DEFINED_GRID_LINES, m_removeDefinedGridLines ?
                          DOCUMENT_SERIALIZE_BOOL_TRUE :
                          DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_CLOSE_DISTANCE, QString::number (m_closeDistance));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X, QString::number (m_gridCoordDisableX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X_STRING, gridCoordDisableToString (m_gridCoordDisableX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_X, QString::number (m_countX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_X, QString::number (m_startX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_X, QString::number (m_stepX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_X, QString::number (m_stopX));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y, QString::number (m_gridCoordDisableY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y_STRING, gridCoordDisableToString (m_gridCoordDisableY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_Y, QString::number (m_countY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_Y, QString::number (m_startY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_Y, QString::number (m_stepY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_Y, QString::number (m_stopY));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_REMOVE_PARALLEL_TO_AXES, m_removeParallelToAxes ?
                          DOCUMENT_SERIALIZE_BOOL_TRUE :
                          DOCUMENT_SERIALIZE_BOOL_FALSE);

  writer.writeEndElement();
}

void DocumentModelGridRemoval::setCloseDistance(double closeDistance)
{
  m_closeDistance = closeDistance;
}

void DocumentModelGridRemoval::setCountX(int countX)
{
  m_countX = countX;
}

void DocumentModelGridRemoval::setCountY(int countY)
{
  m_countY = countY;
}

void DocumentModelGridRemoval::setGridCoordDisableX (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableX = gridCoordDisable;
}

void DocumentModelGridRemoval::setGridCoordDisableY (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableY = gridCoordDisable;
}

void DocumentModelGridRemoval::setRemoveDefinedGridLines (bool removeDefinedGridLines)
{
  m_removeDefinedGridLines = removeDefinedGridLines;
}

void DocumentModelGridRemoval::setRemoveParallelToAxes (bool removeParallelToAxes)
{
  m_removeParallelToAxes = removeParallelToAxes;
}

void DocumentModelGridRemoval::setStartX(double startX)
{
  m_startX = startX;
}

void DocumentModelGridRemoval::setStartY(double startY)
{
  m_startY = startY;
}

void DocumentModelGridRemoval::setStepX(double stepX)
{
  m_stepX = stepX;
}

void DocumentModelGridRemoval::setStepY(double stepY)
{
  m_stepY = stepY;
}

void DocumentModelGridRemoval::setStopX(double stopX)
{
  m_stopX = stopX;
}

void DocumentModelGridRemoval::setStopY(double stopY)
{
  m_stopY = stopY;
}

double DocumentModelGridRemoval::startX() const
{
  return m_startX;
}

double DocumentModelGridRemoval::startY() const
{
  return m_startY;
}

double DocumentModelGridRemoval::stepX() const
{
  return m_stepX;
}

double DocumentModelGridRemoval::stepY() const
{
  return m_stepY;
}

double DocumentModelGridRemoval::stopX() const
{
  return m_stopX;
}

double DocumentModelGridRemoval::stopY() const
{
  return m_stopY;
}
