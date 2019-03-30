/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_POINTS_SELECTION_FUNCTIONS_H
#define EXPORT_POINTS_SELECTION_FUNCTIONS_H

#include <QString>

enum ExportPointsSelectionFunctions {
  EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES,
  EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE,
  EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC,
  EXPORT_POINTS_SELECTION_FUNCTIONS_RAW,
  EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_GRID_LINES
};

extern QString exportPointsSelectionFunctionsToString (ExportPointsSelectionFunctions exportPointsSelectionFunctions);

#endif // EXPORT_POINTS_SELECTION_FUNCTIONS_H
