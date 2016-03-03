/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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

    // Make image fit the new window size. This is needed since QGraphicsView ignores layout stretching
    fitInView (scene()->itemsBoundingRect ());

    QGraphicsView::resizeEvent (event);
  }
}
