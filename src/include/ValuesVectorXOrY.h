/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef VALUES_VECTOR_X_OR_Y_H
#define VALUES_VECTOR_X_OR_Y_H

#include <QMap>

// Save values into container that preserves order by key (QMap). These are common to all included curves
// QMap is for fast random access
typedef QMap<double, bool> ValuesVectorXOrY;

#endif // VALUES_VECTOR_X_OR_Y_H
