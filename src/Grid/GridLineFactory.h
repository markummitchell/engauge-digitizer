/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_LINE_FACTORY_H
#define GRID_LINE_FACTORY_H

#include "GridLine.h"
#include "Point.h"
#include <QList>

class DocumentModelCoords;
class QGraphicsScene;
class Transformation;

/// Factory class for generating the points, composed of QGraphicsItem objects, along a GridLine
///
/// For polar coordinates, the grid lines will appear as an annular segments.
class GridLineFactory
{
public:
  /// Single constructor for DlgSettingsAxesGridLineFactory, which does not have an explicit transformation. The identity transformation is assumed
  GridLineFactory(QGraphicsScene &scene,
                  int pointRadius,
                  const QList<Point> &points,
                  const DocumentModelCoords &modelCoords,
                  const Transformation &transformation);

  /// Create grid line, either along constant X/theta or constant Y/radius side. Line goes from pointFromGraph to pointToGraph.
  /// If the coordinates are polar, we go clockwise from pointFromGraph to pointToGraph (as set up by adjustPolarAngleRange).
  void createGridLine (double xFrom,
                       double yFrom,
                       double xTo,
                       double yTo,
                       GridLine &gridLine);

  /// Deallocate the graphics items associated with the specified grid line. This is static so it can be used without calling the constructor
  static void deleteSide (GridLine &gridLine);

private:
  GridLineFactory();

  void bindItemToScene(QGraphicsItem *item) const;
  void createTransformAlign (const Transformation &transformation,
                             double radiusLinearCartesian,
                             const QPointF &posOriginScreen,
                             QTransform &transformAlign,
                             double &ellipseXAxis,
                             double &ellipseYAxis) const;
  QGraphicsItem *ellipseItem (const Transformation &transformation,
                              double radiusLinearCartesian,
                              const QPointF &posStartScreen,
                              const QPointF &posEndScreen) const;
  void finishActiveGridLine (const QPointF &posStartScreen,
                             const QPointF &posEndScreen,
                             double yFrom,
                             double yTo,
                             GridLine &gridLine) const;
  QGraphicsItem *lineItem (const QPointF &posStartScreen,
                           const QPointF &posEndScreen) const;
  double minScreenDistanceFromPoints (const QPointF &posScreen,
                                      const QList<Point> &points);

  QGraphicsScene &m_scene;
  const int m_pointRadius;
  const QList<Point> &m_points;
  const DocumentModelCoords &m_modelCoords;
  const Transformation &m_transformation;

};

#endif // GRID_LINE_FACTORY_H
