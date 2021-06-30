/******************************************************************************************************
 * (C) 2021 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_LINE_NORMALIZE_H
#define GRID_LINE_NORMALIZE_H

#include "GridCoordDisable.h"

class MainWindowModel;

/// Normalize the four parameters used to define a grid line for display or removal
class GridLineNormalize
{
public:
  /// Default constructor
  GridLineNormalize (const MainWindowModel &modelMainWindow);
  virtual ~GridLineNormalize ();

  /// Normalize the quartet of grid line parameters by adjusting the disabled one to achieve consistency
  void normalize (bool isLinear,
                  GridCoordDisable disable,
                  double &start,
                  double &step,
                  double &stop,
                  unsigned int &num) const;

private:
  unsigned int m_maximumGridLines;
};

#endif // GRID_LINE_NORMALIZE_H
