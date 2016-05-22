/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "ViewPreview.h"

ViewPreview::ViewPreview(QGraphicsScene *scene,
                         ViewAspectRatio viewAspectRatio,
                         QWidget *parent) :
  QGraphicsView (scene, parent),
  m_viewAspectRatio (viewAspectRatio)
{
  setMouseTracking(true);
}

void ViewPreview::mouseMoveEvent(QMouseEvent *event)
{
  QPointF pos = mapToScene (event->pos ());

  emit signalMouseMove (pos);
}

void ViewPreview::resizeEvent(QResizeEvent *event)
{
  if (m_viewAspectRatio == VIEW_ASPECT_RATIO_ONE_TO_ONE) {

    fitInView (scene()->sceneRect(),
               Qt::KeepAspectRatio);

  } else {

    // Make image fit the new window size by using fitInView. This is needed since QGraphicsView ignores layout stretching.
    // If there is an image then we use its extent, so DlgSettingsGridDisplay with polar coordinates (which can extend well
    // outside of image) does not end up with tiny image with wasted space around it
    bool foundImage = false;
    for (int i = 0; i < scene()->items().count (); i++) {
      const QGraphicsItem *item = scene()->items().at (i);
      const QGraphicsPixmapItem *itemPixmap = dynamic_cast<const QGraphicsPixmapItem*> (item);
      if (itemPixmap != 0) {
        foundImage = true;
        fitInView (itemPixmap->boundingRect());
      }
    }

    if (!foundImage) {
      // Use the extent of everything
      fitInView (scene()->itemsBoundingRect ());
    }

    QGraphicsView::resizeEvent (event);
  }
}

void ViewPreview::wheelEvent (QWheelEvent *event)
{
  event->accept ();
}
