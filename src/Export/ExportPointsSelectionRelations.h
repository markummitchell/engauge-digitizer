/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_POINTS_SELECTION_RELATIONS_H
#define EXPORT_POINTS_SELECTION_RELATIONS_H

#include <QString>

enum ExportPointsSelectionRelations {
  EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE,
  EXPORT_POINTS_SELECTION_RELATIONS_RAW
};

extern QString exportPointsSelectionRelationsToString (ExportPointsSelectionRelations exportPointsSelectionRelations);

#endif // EXPORT_POINTS_SELECTION_RELATIONS_H
