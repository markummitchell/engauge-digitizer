/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FITTING_POINTS_CONVENIENT_H
#define FITTING_POINTS_CONVENIENT_H

#include <QPointF>
#include <QVector>

/// Array of (x,y) points in graph coordinates. This array is more convenient that working with points in
/// screen coordinates that must be transformed repeatedly into graph coordinates
typedef QList<QPointF> FittingPointsConvenient;

#endif // FITTING_POINTS_CONVENIENT_H
