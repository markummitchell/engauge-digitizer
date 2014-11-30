#include "CmdMediator.h"
#include "DlgModelGridRemoval.h"

const double CLOSE_DISTANCE_DEFAULT = 1.0;

// These defaults should always be overwritten when Document coordinates are defined
const int DEFAULT_COUNT = 2;
const double DEFAULT_NON_COUNT = 0.0;

DlgModelGridRemoval::DlgModelGridRemoval() :
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

DlgModelGridRemoval::DlgModelGridRemoval(const CmdMediator &cmdMediator) :
  m_removeDefinedGridLines (cmdMediator.document().modelGridRemoval().removeDefinedGridLines()),
  m_closeDistance (cmdMediator.document().modelGridRemoval().closeDistance()),
  m_gridCoordDisableX (cmdMediator.document().modelGridRemoval().gridCoordDisableX()),
  m_countX (cmdMediator.document().modelGridRemoval().countX()),
  m_startX (cmdMediator.document().modelGridRemoval().startX()),
  m_stepX (cmdMediator.document().modelGridRemoval().stepX()),
  m_stopX (cmdMediator.document().modelGridRemoval().stopX()),
  m_gridCoordDisableY (cmdMediator.document().modelGridRemoval().gridCoordDisableY()),
  m_countY (cmdMediator.document().modelGridRemoval().countY()),
  m_startY (cmdMediator.document().modelGridRemoval().startY()),
  m_stepY (cmdMediator.document().modelGridRemoval().stepY()),
  m_stopY (cmdMediator.document().modelGridRemoval().stopY()),
  m_removeParallelToAxes (cmdMediator.document().modelGridRemoval().removeParallelToAxes())
{
}

DlgModelGridRemoval::DlgModelGridRemoval(const DlgModelGridRemoval &other) :
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

DlgModelGridRemoval &DlgModelGridRemoval::operator=(const DlgModelGridRemoval &other)
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

double DlgModelGridRemoval::closeDistance() const
{
  return m_closeDistance;
}

int DlgModelGridRemoval::countX() const
{
  return m_countX;
}

int DlgModelGridRemoval::countY() const
{
  return m_countY;
}

GridCoordDisable DlgModelGridRemoval::gridCoordDisableX () const
{
  return m_gridCoordDisableX;
}

GridCoordDisable DlgModelGridRemoval::gridCoordDisableY () const
{
  return m_gridCoordDisableY;
}

bool DlgModelGridRemoval::removeDefinedGridLines () const
{
  return m_removeDefinedGridLines;
}

bool DlgModelGridRemoval::removeParallelToAxes () const
{
  return m_removeParallelToAxes;
}

void DlgModelGridRemoval::setCloseDistance(double closeDistance)
{
  m_closeDistance = closeDistance;
}

void DlgModelGridRemoval::setCountX(int countX)
{
  m_countX = countX;
}

void DlgModelGridRemoval::setCountY(int countY)
{
  m_countY = countY;
}

void DlgModelGridRemoval::setGridCoordDisableX (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableX = gridCoordDisable;
}

void DlgModelGridRemoval::setGridCoordDisableY (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableY = gridCoordDisable;
}

void DlgModelGridRemoval::setRemoveDefinedGridLines (bool removeDefinedGridLines)
{
  m_removeDefinedGridLines = removeDefinedGridLines;
}

void DlgModelGridRemoval::setRemoveParallelToAxes (bool removeParallelToAxes)
{
  m_removeParallelToAxes = removeParallelToAxes;
}

void DlgModelGridRemoval::setStartX(double startX)
{
  m_startX = startX;
}

void DlgModelGridRemoval::setStartY(double startY)
{
  m_startY = startY;
}

void DlgModelGridRemoval::setStepX(double stepX)
{
  m_stepX = stepX;
}

void DlgModelGridRemoval::setStepY(double stepY)
{
  m_stepY = stepY;
}

void DlgModelGridRemoval::setStopX(double stopX)
{
  m_stopX = stopX;
}

void DlgModelGridRemoval::setStopY(double stopY)
{
  m_stopY = stopY;
}

double DlgModelGridRemoval::startX() const
{
  return m_startX;
}

double DlgModelGridRemoval::startY() const
{
  return m_startY;
}

double DlgModelGridRemoval::stepX() const
{
  return m_stepX;
}

double DlgModelGridRemoval::stepY() const
{
  return m_stepY;
}

double DlgModelGridRemoval::stopX() const
{
  return m_stopX;
}

double DlgModelGridRemoval::stopY() const
{
  return m_stopY;
}
