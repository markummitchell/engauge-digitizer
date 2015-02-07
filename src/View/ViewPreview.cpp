#include <QGraphicsScene>
#include <QMouseEvent>
#include "ViewPreview.h"

ViewPreview::ViewPreview(QGraphicsScene *scene,
                         QWidget *parent) :
  QGraphicsView (scene, parent)
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
  // Make image fit the new window size. This is needed since QGraphicsView ignores layout stretching
  fitInView (scene()->itemsBoundingRect ());

  QGraphicsView::resizeEvent (event);
}
