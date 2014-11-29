#include "CmdMediator.h"
#include "DlgModelGridRemoval.h"

DlgModelGridRemoval::DlgModelGridRemoval() :
  m_removeDefinedGridLines (false),
  m_gridCoordDisableX (GRID_COORD_DISABLE_COUNT),
  m_gridCoordDisableY (GRID_COORD_DISABLE_COUNT),
  m_removeParallelToAxes (false)
{
}

DlgModelGridRemoval::DlgModelGridRemoval(const CmdMediator &cmdMediator) :
  m_removeDefinedGridLines (cmdMediator.document().modelGridRemoval().removeDefinedGridLines()),
  m_gridCoordDisableX (cmdMediator.document().modelGridRemoval().gridCoordDisableX()),
  m_gridCoordDisableY (cmdMediator.document().modelGridRemoval().gridCoordDisableY()),
  m_removeParallelToAxes (cmdMediator.document().modelGridRemoval().removeParallelToAxes())
{
}

DlgModelGridRemoval::DlgModelGridRemoval(const DlgModelGridRemoval &other) :
  m_removeDefinedGridLines (other.removeDefinedGridLines()),
  m_gridCoordDisableX (other.gridCoordDisableX()),
  m_gridCoordDisableY (other.gridCoordDisableX()),
  m_removeParallelToAxes (other.removeParallelToAxes())
{
}

DlgModelGridRemoval &DlgModelGridRemoval::operator=(const DlgModelGridRemoval &other)
{
  m_removeDefinedGridLines = other.removeDefinedGridLines();
  m_gridCoordDisableX = other.gridCoordDisableX();
  m_gridCoordDisableY = other.gridCoordDisableY();
  m_removeParallelToAxes = other.removeParallelToAxes();

  return *this;
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
