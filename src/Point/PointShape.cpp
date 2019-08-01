/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PointShape.h"
#include <QObject>

QString pointShapeToString (PointShape pointShape)
{
  QString rtn;

  switch (pointShape) {
    case POINT_SHAPE_CIRCLE:
      rtn = QObject::tr ("Circle");
      break;

    case POINT_SHAPE_CROSS:
      rtn = QObject::tr ("Cross");
      break;

    case POINT_SHAPE_DIAMOND:
      rtn = QObject::tr ("Diamond");
      break;

    case POINT_SHAPE_HOURGLASS:
      rtn = QObject::tr ("Hourglass");
      break;      

    case POINT_SHAPE_SQUARE:
      rtn = QObject::tr ("Square");
      break;

    case POINT_SHAPE_TRIANGLE:
      rtn = QObject::tr ("Triangle");
      break;

    case POINT_SHAPE_TRIANGLE2:
      rtn = QObject::tr ("Triangle2");
      break;      

    case POINT_SHAPE_X:
      rtn = QObject::tr ("X");
      break;
  }

  return rtn;
}
