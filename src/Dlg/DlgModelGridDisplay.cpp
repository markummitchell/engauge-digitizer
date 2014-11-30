#include "CmdMediator.h"
#include "DlgModelGridDisplay.h"

// These defaults should always be overwritten when Document coordinates are defined
const int DEFAULT_COUNT = 2;
const double DEFAULT_NON_COUNT = 0.0;

DlgModelGridDisplay::DlgModelGridDisplay() :
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

DlgModelGridDisplay::DlgModelGridDisplay(const CmdMediator &cmdMediator) :
  m_gridCoordDisableX (cmdMediator.document().modelGridDisplay().gridCoordDisableX()),
  m_countX (cmdMediator.document().modelGridDisplay().countX()),
  m_startX (cmdMediator.document().modelGridDisplay().startX()),
  m_stepX (cmdMediator.document().modelGridDisplay().stepX()),
  m_stopX (cmdMediator.document().modelGridDisplay().stopX()),
  m_gridCoordDisableY (cmdMediator.document().modelGridDisplay().gridCoordDisableY()),
  m_countY (cmdMediator.document().modelGridDisplay().countY()),
  m_startY (cmdMediator.document().modelGridDisplay().startY()),
  m_stepY (cmdMediator.document().modelGridDisplay().stepY()),
  m_stopY (cmdMediator.document().modelGridDisplay().stopY())
{
}

DlgModelGridDisplay::DlgModelGridDisplay(const DlgModelGridDisplay &other) :
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

DlgModelGridDisplay &DlgModelGridDisplay::operator=(const DlgModelGridDisplay &other)
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

int DlgModelGridDisplay::countX() const
{
  return m_countX;
}

int DlgModelGridDisplay::countY() const
{
  return m_countY;
}

GridCoordDisable DlgModelGridDisplay::gridCoordDisableX () const
{
  return m_gridCoordDisableX;
}

GridCoordDisable DlgModelGridDisplay::gridCoordDisableY () const
{
  return m_gridCoordDisableY;
}

void DlgModelGridDisplay::setCountX(int countX)
{
  m_countX = countX;
}

void DlgModelGridDisplay::setCountY(int countY)
{
  m_countY = countY;
}

void DlgModelGridDisplay::setGridCoordDisableX (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableX = gridCoordDisable;
}

void DlgModelGridDisplay::setGridCoordDisableY (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableY = gridCoordDisable;
}

void DlgModelGridDisplay::setStartX(double startX)
{
  m_startX = startX;
}

void DlgModelGridDisplay::setStartY(double startY)
{
  m_startY = startY;
}

void DlgModelGridDisplay::setStepX(double stepX)
{
  m_stepX = stepX;
}

void DlgModelGridDisplay::setStepY(double stepY)
{
  m_stepY = stepY;
}

void DlgModelGridDisplay::setStopX(double stopX)
{
  m_stopX = stopX;
}

void DlgModelGridDisplay::setStopY(double stopY)
{
  m_stopY = stopY;
}

double DlgModelGridDisplay::startX() const
{
  return m_startX;
}

double DlgModelGridDisplay::startY() const
{
  return m_startY;
}

double DlgModelGridDisplay::stepX() const
{
  return m_stepX;
}

double DlgModelGridDisplay::stepY() const
{
  return m_stepY;
}

double DlgModelGridDisplay::stopX() const
{
  return m_stopX;
}

double DlgModelGridDisplay::stopY() const
{
  return m_stopY;
}
