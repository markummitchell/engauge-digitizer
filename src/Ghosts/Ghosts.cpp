/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "Ghosts.h"
#include <qdebug.h>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>

const double Z_VALUE = 100.0;

Ghosts::Ghosts (unsigned int coordSystemIndexToBeRestored) :
  m_coordSystemIndexToBeRestored (coordSystemIndexToBeRestored)
{
}

Ghosts::~Ghosts ()
{
}

void Ghosts::captureGraphicsItems (QGraphicsScene &scene)
{
  QList<QGraphicsItem*> items = scene.items();

  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem *item = *itr;

    QGraphicsEllipseItem *itemEllipse = dynamic_cast<QGraphicsEllipseItem*> (item);
    if (itemEllipse != nullptr) {

      GhostEllipse ghost (itemEllipse->boundingRect(),
                          itemEllipse->pen(),
                          itemEllipse->brush());
      m_ellipses.push_back (ghost);

    } else {

      QGraphicsPathItem *itemPath = dynamic_cast<QGraphicsPathItem*> (item);
      if (itemPath != nullptr) {

        GhostPath ghost (itemPath->path (),
                         itemPath->pen(),
                         itemPath->brush());
        m_paths.push_back (ghost);

      } else {

        QGraphicsPolygonItem *itemPolygon = dynamic_cast<QGraphicsPolygonItem*> (item);
        if (itemPolygon != nullptr) {

          // Polygon is centered at origin so we have to add offset
          QPolygonF polygon = itemPolygon->polygon();
          polygon.translate (itemPolygon->pos ());

          GhostPolygon ghost (polygon,
                              itemPolygon->pen(),
                              itemPolygon->brush());
          m_polygons.push_back (ghost);

        }
      }
    }
  }
}

unsigned int Ghosts::coordSystemIndexToBeRestored () const
{
  return m_coordSystemIndexToBeRestored;
}

void Ghosts::createGhosts (QGraphicsScene &scene)
{
  int i;

  for (i = 0; i < m_ellipses.count(); i++) {
    GhostEllipse ghost = m_ellipses.at(i);

    QGraphicsEllipseItem *item = scene.addEllipse (ghost.rect());

    item->setData (DATA_KEY_GHOST, QVariant (true));
    item->setPen (ghost.pen());
    item->setBrush (ghost.brush());
    item->setZValue (Z_VALUE);
    item->setVisible (true);
  }

  for (i = 0; i < m_paths.count(); i++) {
    GhostPath ghost = m_paths.at(i);

    QGraphicsPathItem *item = scene.addPath (ghost.path(),
                                             ghost.pen(),
                                             ghost.brush());

    item->setData (DATA_KEY_GHOST, QVariant (true));
    item->setZValue (Z_VALUE);
    item->setVisible (true);
  }

  for (i = 0; i < m_polygons.count(); i++) {
    GhostPolygon ghost = m_polygons.at(i);

    QGraphicsPolygonItem *item = scene.addPolygon (ghost.polygon(),
                                                   ghost.pen(),
                                                   ghost.brush());

    item->setData (DATA_KEY_GHOST, QVariant (true));
    item->setZValue (Z_VALUE);
    item->setVisible (true);
  }
}

void Ghosts::destroyGhosts (QGraphicsScene &scene)
{
  QList<QGraphicsItem*> items = scene.items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem *item = *itr;
    QVariant data = item->data (DATA_KEY_GHOST);
    if (!data.isNull()) {
      if (data.toBool()) {
        scene.removeItem (item);
      }
    }
  }
}
