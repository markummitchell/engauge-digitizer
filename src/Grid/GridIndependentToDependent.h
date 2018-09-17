/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_INDEPENDENT_TO_DEPENDENT_H
#define GRID_INDEPENDENT_TO_DEPENDENT_H

#include <QMap>

/// (X,Y) pairs for horizontal lines, and (Y,X) pairs for vertical lines
typedef QMap<int, int> GridIndependentToDependent;

#endif // GRID_INDEPENDENT_TO_DEPENDENT_H
