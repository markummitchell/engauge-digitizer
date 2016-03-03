/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef POINT_SHAPE_H
#define POINT_SHAPE_H

#include <QString>

enum PointShape {
  POINT_SHAPE_CIRCLE,
  POINT_SHAPE_CROSS,
  POINT_SHAPE_DIAMOND,
  POINT_SHAPE_SQUARE,
  POINT_SHAPE_TRIANGLE,
  POINT_SHAPE_X
};

extern QString pointShapeToString (PointShape pointShape);

#endif // POINT_SHAPE_H
