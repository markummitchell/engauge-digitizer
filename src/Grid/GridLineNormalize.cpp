/******************************************************************************************************
 * (C) 2021 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GridLineNormalize.h"
#include "MainWindowModel.h"
#include <qmath.h>

GridLineNormalize::GridLineNormalize (const MainWindowModel &modelMainWindow) :
  m_maximumGridLines (modelMainWindow.maximumGridLines())
{
}

GridLineNormalize::~GridLineNormalize ()
{
}

void GridLineNormalize::normalize (bool isLinear,
                                   GridCoordDisable disable,
                                   double &start,
                                   double &step,
                                   double &stop,
                                   unsigned int &num) const
{
  // Make sure we are not using any disabled parameters

  double numMinus1 = qMax (1.0, num - 1.0); 

  if (isLinear) {

    // Linear case
    if (disable == GRID_COORD_DISABLE_START) {
      start = stop - numMinus1 * step;
    } else if (disable == GRID_COORD_DISABLE_STEP) {
      step = (stop - start) / numMinus1;
    } else if (disable == GRID_COORD_DISABLE_STOP) {
      stop = start + numMinus1 * step; 
    } else if (disable == GRID_COORD_DISABLE_COUNT) {
      if (qAbs (step) * m_maximumGridLines < qAbs (stop - start)) {
        num = m_maximumGridLines;
      } else {
        num = qFloor (0.5 + 1.0 + (stop - start) / step);
      }
    }
  } else {

    // Log case
    if (disable == GRID_COORD_DISABLE_START) {
      start = stop / qPow (step, numMinus1);
    } else if (disable == GRID_COORD_DISABLE_STEP) {
      step = qExp (qLn (stop / start) / numMinus1);
    } else if (disable == GRID_COORD_DISABLE_STOP) {
      stop = start * qPow (step, numMinus1);
    } else if (disable == GRID_COORD_DISABLE_COUNT) {
      if (start <= 0.0 || step <= 0.0 || stop <= 0.) {
        num = 2;
      } else if (qAbs (qLn (step)) * m_maximumGridLines < qAbs (qLn (stop / start))) {
        num = m_maximumGridLines;
      } else {
        num = qFloor (0.5 + 1.0 + qLn (stop / start) / qLn (step));
      }
    }
  }
}
