#include <QGraphicsScene>
#include "ViewPreview.h"

ViewPreview::ViewPreview(QGraphicsScene *scene,
                         QWidget *parent) :
  QGraphicsView (scene, parent)
{
}

void ViewPreview::resizeEvent(QResizeEvent *event)
{
  fitInView (scene()->itemsBoundingRect ());

  QGraphicsView::resizeEvent (event);
}
