/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef ORDINAL_TO_GRAPHICS_POINT_H
#define ORDINAL_TO_GRAPHICS_POINT_H

#include <QMap>

class GraphicsPoint;

// Use QMap, which keeps the keys sorted, to map ordinal to GraphicsPoint
typedef QMap<double, GraphicsPoint*> OrdinalToGraphicsPoint;

#endif // ORDINAL_TO_GRAPHICS_POINT_H
