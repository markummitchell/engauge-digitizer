/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportPointsSelectionFunctions.h"
#include <QObject>

QString exportPointsSelectionFunctionsToString (ExportPointsSelectionFunctions exportPointsSelectionFunctions)
{
  QString rtn;

  switch (exportPointsSelectionFunctions) {
    case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES:
      rtn = QObject::tr ("InterpolateAllCurves");
      break;

    case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE:
      rtn = QObject::tr ("InterpolateFirstCurve");
      break;

    case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC:
      rtn = QObject::tr ("InterpolatePeriodic");
      break;

    case EXPORT_POINTS_SELECTION_FUNCTIONS_RAW:
      rtn = QObject::tr ("Raw");
      break;

    default:
      rtn = QObject::tr ("Unknown");
      break;
  }

  return rtn;
}
