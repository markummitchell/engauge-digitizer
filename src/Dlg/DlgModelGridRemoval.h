#ifndef DLG_MODEL_GRID_REMOVAL_H
#define DLG_MODEL_GRID_REMOVAL_H

#include "Grid/GridCoordDisable.h"

class CmdMediator;

/// Model for DlgSettingsGridRemoval and CmdSettingsGridRemoval.
class DlgModelGridRemoval
{
public:
  /// Default constructor.
  DlgModelGridRemoval();

  /// Initial constructor from Document.
  DlgModelGridRemoval(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelGridRemoval(const DlgModelGridRemoval &other);

  /// Assignment constructor.
  DlgModelGridRemoval &operator=(const DlgModelGridRemoval &other);

  /// Get method for x coord parameter to disable.
  GridCoordDisable gridCoordDisableX () const;

  /// Get method for y coord parameter to disable.
  GridCoordDisable gridCoordDisableY () const;

  /// Get method for x coord parameter to disable.
  void setGridCoordDisableX (GridCoordDisable gridCoordDisable);

  /// Get method for y coord parameter to disable.
  void setGridCoordDisableY (GridCoordDisable gridCoordDisable);

private:

  GridCoordDisable m_gridCoordDisableX;
  GridCoordDisable m_gridCoordDisableY;
};

#endif // DLG_MODEL_GRID_REMOVAL_H
