#include "CmdMediator.h"
#include "DocumentModelGridDisplay.h"
#include "Logger.h"
#include <QXmlStreamWriter>

// These defaults should always be overwritten when Document coordinates are defined
const int DEFAULT_COUNT = 2;
const double DEFAULT_NON_COUNT = 0.0;

DocumentModelGridDisplay::DocumentModelGridDisplay() :
  m_gridCoordDisableX (GRID_COORD_DISABLE_COUNT),
  m_countX (DEFAULT_COUNT),
  m_startX (DEFAULT_NON_COUNT),
  m_stepX (DEFAULT_NON_COUNT),
  m_stopX (DEFAULT_NON_COUNT),
  m_gridCoordDisableY (GRID_COORD_DISABLE_COUNT),
  m_countY (DEFAULT_COUNT),
  m_startY (DEFAULT_NON_COUNT),
  m_stepY (DEFAULT_NON_COUNT),
  m_stopY (DEFAULT_NON_COUNT)
{
}

DocumentModelGridDisplay::DocumentModelGridDisplay(const Document &document) :
  m_gridCoordDisableX (document.modelGridDisplay().gridCoordDisableX()),
  m_countX (document.modelGridDisplay().countX()),
  m_startX (document.modelGridDisplay().startX()),
  m_stepX (document.modelGridDisplay().stepX()),
  m_stopX (document.modelGridDisplay().stopX()),
  m_gridCoordDisableY (document.modelGridDisplay().gridCoordDisableY()),
  m_countY (document.modelGridDisplay().countY()),
  m_startY (document.modelGridDisplay().startY()),
  m_stepY (document.modelGridDisplay().stepY()),
  m_stopY (document.modelGridDisplay().stopY())
{
}

DocumentModelGridDisplay::DocumentModelGridDisplay(const DocumentModelGridDisplay &other) :
  m_gridCoordDisableX (other.gridCoordDisableX()),
  m_countX (other.countX()),
  m_startX (other.startX()),
  m_stepX (other.stepX()),
  m_stopX (other.stopX()),
  m_gridCoordDisableY (other.gridCoordDisableX()),
  m_countY (other.countY()),
  m_startY (other.startY()),
  m_stepY (other.stepY()),
  m_stopY (other.stopY())
{
}

DocumentModelGridDisplay &DocumentModelGridDisplay::operator=(const DocumentModelGridDisplay &other)
{
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

  return *this;
}

int DocumentModelGridDisplay::countX() const
{
  return m_countX;
}

int DocumentModelGridDisplay::countY() const
{
  return m_countY;
}

GridCoordDisable DocumentModelGridDisplay::gridCoordDisableX () const
{
  return m_gridCoordDisableX;
}

GridCoordDisable DocumentModelGridDisplay::gridCoordDisableY () const
{
  return m_gridCoordDisableY;
}

void DocumentModelGridDisplay::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGridDisplay::saveModel";

  stream.writeStartElement("DocumentModelGridDisplay");
  stream.writeEndElement();
}

void DocumentModelGridDisplay::setCountX(int countX)
{
  m_countX = countX;
}

void DocumentModelGridDisplay::setCountY(int countY)
{
  m_countY = countY;
}

void DocumentModelGridDisplay::setGridCoordDisableX (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableX = gridCoordDisable;
}

void DocumentModelGridDisplay::setGridCoordDisableY (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableY = gridCoordDisable;
}

void DocumentModelGridDisplay::setStartX(double startX)
{
  m_startX = startX;
}

void DocumentModelGridDisplay::setStartY(double startY)
{
  m_startY = startY;
}

void DocumentModelGridDisplay::setStepX(double stepX)
{
  m_stepX = stepX;
}

void DocumentModelGridDisplay::setStepY(double stepY)
{
  m_stepY = stepY;
}

void DocumentModelGridDisplay::setStopX(double stopX)
{
  m_stopX = stopX;
}

void DocumentModelGridDisplay::setStopY(double stopY)
{
  m_stopY = stopY;
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
