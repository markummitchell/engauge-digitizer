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

  /// Get method for removing defined grid lines.
  bool removeDefinedGridLines () const;

  /// Get method for removing lines parallel to axes.
  bool removeParallelToAxes () const;

  /// Get method for x coord parameter to disable.
  void setGridCoordDisableX (GridCoordDisable gridCoordDisable);

  /// Get method for y coord parameter to disable.
  void setGridCoordDisableY (GridCoordDisable gridCoordDisable);

  /// Set method for removing defined grid lines.
  void setRemoveDefinedGridLines (bool removeDefinedGridLines);

  /// Set method for removing lines parallel to axes.
  void setRemoveParallelToAxes (bool removeParallelToAxes);

private:

  bool m_removeDefinedGridLines;
  GridCoordDisable m_gridCoordDisableX;
  GridCoordDisable m_gridCoordDisableY;

  bool m_removeParallelToAxes;
};

#endif // DLG_MODEL_GRID_REMOVAL_H
