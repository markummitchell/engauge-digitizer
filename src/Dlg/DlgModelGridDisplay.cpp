#include "CmdMediator.h"
#include "DlgModelGridDisplay.h"

DlgModelGridDisplay::DlgModelGridDisplay() :
  m_gridCoordDisableX (GRID_COORD_DISABLE_COUNT),
  m_gridCoordDisableY (GRID_COORD_DISABLE_COUNT)
{
}

DlgModelGridDisplay::DlgModelGridDisplay(const CmdMediator &cmdMediator) :
  m_gridCoordDisableX (cmdMediator.document().modelGridDisplay().gridCoordDisableX()),
  m_gridCoordDisableY (cmdMediator.document().modelGridDisplay().gridCoordDisableY())
{
}

DlgModelGridDisplay::DlgModelGridDisplay(const DlgModelGridDisplay &other) :
  m_gridCoordDisableX (other.gridCoordDisableX()),
  m_gridCoordDisableY (other.gridCoordDisableX())
{
}

DlgModelGridDisplay &DlgModelGridDisplay::operator=(const DlgModelGridDisplay &other)
{
  m_gridCoordDisableX = other.gridCoordDisableX();
  m_gridCoordDisableY = other.gridCoordDisableY();

  return *this;
}

GridCoordDisable DlgModelGridDisplay::gridCoordDisableX () const
{
  return m_gridCoordDisableX;
}

GridCoordDisable DlgModelGridDisplay::gridCoordDisableY () const
{
  return m_gridCoordDisableY;
}

void DlgModelGridDisplay::setGridCoordDisableX (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableX = gridCoordDisable;
}

void DlgModelGridDisplay::setGridCoordDisableY (GridCoordDisable gridCoordDisable)
{
  m_gridCoordDisableY = gridCoordDisable;
}
