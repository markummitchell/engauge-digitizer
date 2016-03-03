/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GHOSTS_H
#define GHOSTS_H

#include "GhostEllipse.h"
#include "GhostPath.h"
#include "GhostPolygon.h"
#include <QList>
#include <QPainterPath>
#include <QPolygonF>
#include <QRectF>

class QGraphicsScene;

/// Class for showing points and lines for all coordinate systems simultaneously, even though
/// the code normally only allows graphical items for once coordinate system to be visible at a time
///
/// QGraphicsLineItems are ignored since those are just used for the AxesChecker, and
/// QGraphicsPixmapItems are ignored since those are just used for the background. The
/// other QGraphicsItem subclasses are captured and converted into ghosts.
class Ghosts
{
 public:
  /// Single constructor
  Ghosts(unsigned int coordSystemIndexToBeRestored);
  ~Ghosts();

  /// Coordinate system index that was active before the ghosts
  unsigned int coordSystemIndexToBeRestored() const;

  /// Take a snapshot of the graphics items
  void captureGraphicsItems (QGraphicsScene &scene);

  /// Create ghosts from the path/rect/polygon lists
  void createGhosts (QGraphicsScene &scene);

  /// Destory ghosts. Called at end of algorithm
  void destroyGhosts (QGraphicsScene &scene);

 private:
  Ghosts();

  unsigned int m_coordSystemIndexToBeRestored;

  QList<GhostEllipse> m_ellipses;
  QList<GhostPath> m_paths;
  QList<GhostPolygon> m_polygons;
};

#endif // GHOSTS_H
