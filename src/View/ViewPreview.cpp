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

  // Normally we would need to call QGraphicsView::mouseMoveEvent at this point so that the mouse move event could be handled,
  // but this is unwanted since:
  // 1) Everywhere, except the pdf import preview, there is nothing to drag
  // 2) Dragging of PdfFrameHandle objects in the pdf import preview is handled indirectly by PdfFrame
  QGraphicsView::mouseMoveEvent (event);
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
