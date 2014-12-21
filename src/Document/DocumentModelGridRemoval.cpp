#include "CmdMediator.h"
#include "DocumentModelGridRemoval.h"
#include "Logger.h"
#include <QXmlStreamWriter>

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

bool DocumentModelGridRemoval::removeDefinedGridLines () const
{
  return m_removeDefinedGridLines;
}

bool DocumentModelGridRemoval::removeParallelToAxes () const
{
  return m_removeParallelToAxes;
}

void DocumentModelGridRemoval::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridRemoval::saveModel";

  stream.writeStartElement("DocumentModelGridRemoval");
  stream.writeEndElement();
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
