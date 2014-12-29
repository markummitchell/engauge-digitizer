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
  emit signalMouseMove (event->localPos ());
}

void ViewPreview::resizeEvent(QResizeEvent *event)
{
  // Make image fit the new window size
  fitInView (scene()->itemsBoundingRect ());

  QGraphicsView::resizeEvent (event);
}
