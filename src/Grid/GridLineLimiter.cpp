/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelCoords.h"
#include "DocumentModelGridDisplay.h"
#include "DocumentModelGridRemoval.h"
#include "GridLineLimiter.h"
#include "MainWindowModel.h"
#include <qmath.h>

const int DEFAULT_MAXIMUM_GRID_LINES = 25;

GridLineLimiter::GridLineLimiter ()
{
}

double GridLineLimiter::limitedStepXTheta (const DocumentModelCoords &modelCoords,
                                           const MainWindowModel &modelMainWindow,
                                           const DocumentModelGridDisplay &modelGrid) const
{
  double step = modelGrid.stepX();

  if (modelCoords.coordScaleXTheta() == COORD_SCALE_LINEAR) {

    // Linear
    double count = 1.0 + (modelGrid.stopX() - modelGrid.startX()) / modelGrid.stepX();
    if ((int) count > modelMainWindow.maximumGridLines()) {

      // Adjust step so maximum grid lines limit is met
      step = (modelGrid.stopX() - modelGrid.startX()) / (modelMainWindow.maximumGridLines() - 1);

    }

  } else {

    // Log
    double count = 1.0 + (qLn (modelGrid.stopX()) - qLn (modelGrid.startX())) / qLn (modelMainWindow.maximumGridLines());
    if ((int) count > modelMainWindow.maximumGridLines()) {

      // Adjust step so maximum grid lines limit is met
      step = qExp ((qLn (modelGrid.stopX()) - qLn (modelGrid.startX())) / (modelMainWindow.maximumGridLines() - 1));

    }
  }

  return step;
}

double GridLineLimiter::limitedStepYRange (const DocumentModelCoords &modelCoords,
                                           const MainWindowModel &modelMainWindow,
                                           const DocumentModelGridDisplay &modelGrid) const
{
  double step = modelGrid.stepY();

  if (modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR) {

    // Linear
    double count = 1.0 + (modelGrid.stopY() - modelGrid.startY()) / modelGrid.stepY();
    if ((int) count > modelMainWindow.maximumGridLines()) {

      // Adjust step so maximum grid lines limit is met
      step = (modelGrid.stopY() - modelGrid.startY()) / (modelMainWindow.maximumGridLines() - 1);

    }

  } else {

    // Log
    double count = 1.0 + (qLn (modelGrid.stopY()) - qLn (modelGrid.startY())) / qLn (modelMainWindow.maximumGridLines());
    if ((int) count > modelMainWindow.maximumGridLines()) {

      // Adjust step so maximum grid lines limit is met
      step = qExp ((qLn (modelGrid.stopY()) - qLn (modelGrid.startY())) / (modelMainWindow.maximumGridLines() - 1));

    }
  }

  return step;
}
