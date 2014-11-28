#include "CmdMediator.h"
#include "DlgModelGridRemoval.h"

DlgModelGridRemoval::DlgModelGridRemoval() :
  m_gridCoordDisableX (GRID_COORD_DISABLE_COUNT),
  m_gridCoordDisableY (GRID_COORD_DISABLE_COUNT)
{
}

DlgModelGridRemoval::DlgModelGridRemoval(const CmdMediator &cmdMediator) :
  m_gridCoordDisableX (cmdMediator.document().modelGridRemoval().gridCoordDisableX()),
  m_gridCoordDisableY (cmdMediator.document().modelGridRemoval().gridCoordDisableY())
{
}

DlgModelGridRemoval::DlgModelGridRemoval(const DlgModelGridRemoval &other) :
  m_gridCoordDisableX (other.gridCoordDisableX()),
  m_gridCoordDisableY (other.gridCoordDisableX())
{
}

DlgModelGridRemoval &DlgModelGridRemoval::operator=(const DlgModelGridRemoval &other)
{
  m_gridCoordDisableX = other.gridCoordDisableX();
  m_gridCoordDisableY = other.gridCoordDisableY();

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

void DlgModelGridRemoval::setGridCoordDisableX (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableX = gridCoordDisable;
}

void DlgModelGridRemoval::setGridCoordDisableY (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableY = gridCoordDisable;
}
