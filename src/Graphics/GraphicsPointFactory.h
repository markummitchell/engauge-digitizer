/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_POINT_FACTORY_H
#define GRAPHICS_POINT_FACTORY_H

#include "PointShape.h"

class GeometryWindow;
class GraphicsPoint;
class PointStyle;
class QGraphicsScene;
class QPointF;

/// Factor for generating GraphicsPointAbstractBase class objects.
class GraphicsPointFactory
{
public:
  /// Single constructor.
  GraphicsPointFactory();

  /// Create circle or polygon point according to the PointStyle.
  GraphicsPoint *createPoint (QGraphicsScene &scene,
                              const QString &identifier,
                              const QPointF &posScreen,
                              const PointStyle &pointStyle,
                              GeometryWindow *geometryWindow);
};

#endif // GRAPHICS_POINT_FACTORY_H
