#ifndef DLG_MODEL_GRID_DISPLAY_H
#define DLG_MODEL_GRID_DISPLAY_H

#include "Grid/GridCoordDisable.h"

class CmdMediator;

/// Model for DlgSettingsGridDisplay and CmdSettingsGridDisplay.
class DlgModelGridDisplay
{
public:
  /// Default constructor.
  DlgModelGridDisplay();

  /// Initial constructor from Document.
  DlgModelGridDisplay(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelGridDisplay(const DlgModelGridDisplay &other);

  /// Assignment constructor.
  DlgModelGridDisplay &operator=(const DlgModelGridDisplay &other);

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

#endif // DLG_MODEL_GRID_DISPLAY_H
